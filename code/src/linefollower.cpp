/**
 * @file linefollower.cpp
 * @author Dominik Workshop
 * @brief 
 * @version 0.1
 * @date 2024-03-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <EEPROM.h>

#include "linefollower.hh"

Linefollower::Linefollower(): Rmotor(R_MOTOR_DIR, R_MOTOR_SPEED, true), Lmotor(L_MOTOR_DIR, L_MOTOR_SPEED, false){
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BATTERY, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  readSettingsFromEEPROM();
}

void Linefollower::driveOnLine(){
  uint8_t numOfSens = 0; //number of sensors that see the line at given moment
  int16_t error = 0;
  int16_t lastError = 0;  
  int16_t deltaV = 0;
  int16_t Lspeed = 0;
  int16_t Rspeed = 0;

  uint32_t time = millis();

  digitalWrite(FRONT_POWER, HIGH);  //turn sensors on
  Rmotor.setDirection(Forward);
  Lmotor.setDirection(Forward);
  while(!isReceived('D')){
    while(time+2000>micros());   //frequency of 500 Hz
    time = micros();
    
    lineSensors.readSensors();
    error = lineSensors.calculateError();
    numOfSens = lineSensors.getNumOfDetectingSensors(); 
    
    ///////////// when the line isn't seen /////////
    if (numOfSens == 0){  
      if (lastError < 0){
        Rmotor.setDirection(Backward);
        Lspeed = lineLostDeltaV;
        Rspeed = lineLostDeltaV;
      } else if (lastError > 0){
        Lmotor.setDirection(Backward);
        Lspeed = lineLostDeltaV;
        Rspeed = lineLostDeltaV;
      }else {
        Lspeed = maxSpeed;
        Rspeed = maxSpeed;
      }
    }
    ///////////// when the line is seen //////////
    else { 
      Rmotor.setDirection(Forward);
      Lmotor.setDirection(Forward);
      
      deltaV = ((Kp * error) + 10 * Kd * (error - lastError))/10;
      Lspeed = maxSpeed - deltaV;
      Rspeed = maxSpeed + deltaV;
      
      lastError = error;
    }

    Rmotor.setSpeed(Rspeed);
    Lmotor.setSpeed(Lspeed);
  }
  //finish driving
  Rmotor.setSpeed(0);
  Lmotor.setSpeed(0);
  digitalWrite(FRONT_POWER, LOW); //turn sensors off
}

void Linefollower::readSettingsFromEEPROM(){
  Kp = EEPROM.read(KP_EEPROM_ADDRESS);
  Kd = EEPROM.read(KD_EEPROM_ADDRESS);
  maxSpeed = EEPROM.read(MAX_SPEED_EEPROM_ADDRESS);
  maxSpeedStraight = EEPROM.read(MAX_SPEED_STRGHT_EEPROM_ADDRESS);
  lineLostDeltaV = EEPROM.read(LINE_LOST_D_V_EEPROM_ADDRESS);
}

void Linefollower::spinWheelsForCleaning(){
  Rmotor.setSpeed(50);
  Lmotor.setSpeed(50);
  delay(5000);
  Rmotor.setSpeed(0);
  Lmotor.setSpeed(0);
}

void Linefollower::calibration(){
  char data;
  int16_t value; 
  Serial.println("You are in calibration mode");
  while (1){
    delay(100);
    if(Serial.available()>0){
      data = Serial.read();
      switch(data){
        case 's':
          value = Serial.parseInt();
          if (value <= 255 && value >= 0){
            maxSpeed = value;
            EEPROM.write(MAX_SPEED_EEPROM_ADDRESS, maxSpeed); //save in EEPROM
            Serial.print("Max speed is set to: ");
            Serial.println(maxSpeed);
          }else Serial.println("Max speed should be between 0 and 255");
          break;
        case 'p':
          value = Serial.parseInt();
          if (value <= 32767 && value >= -32768){
            Kp= value;
            EEPROM.write(KP_EEPROM_ADDRESS, Kp);
            Serial.print("Proportional gain Kp is set to:  ");
            Serial.println(Kp);
          }else Serial.println("Kp should be between -32768 and 32767");
          break;
        case 'd':
          value = Serial.parseInt();
          if (value <= 32767 && value >= -32768){
            Kd = value;
            EEPROM.write(KD_EEPROM_ADDRESS, Kd);
            Serial.print("Derivative gain Kd is set to:  ");
            Serial.println(Kd);
          }else Serial.println("Kd should be between -32768 and 32767");
          break;
        case 'r':
          value = Serial.parseInt();
          if (value <= 32767 && value >= -32768){
            lineLostDeltaV = value;
            EEPROM.write(LINE_LOST_D_V_EEPROM_ADDRESS, lineLostDeltaV);
            Serial.print("Line lost delta V is set to:  ");
            Serial.println(lineLostDeltaV);
          }else Serial.println("Line lost delta V should be between -32768 and 32767");
          break;
        case 'm':
          value = Serial.parseInt();
          if (value <= 32767 && value >= -32768){
            maxSpeedStraight = value;
            EEPROM.write(MAX_SPEED_STRGHT_EEPROM_ADDRESS, maxSpeedStraight);
            Serial.print("Max speed on straight line is set to:  ");
            Serial.println(maxSpeedStraight);
          }else Serial.println("Max speed on straight line should be between -32768 and 32767");
          break;
        case 'v':
          Serial.print("Kp = ");
          Serial.println(Kp);
          Serial.print("Kd = ");
          Serial.println(Kd);
          Serial.print("MAXspeed = ");
          Serial.println(maxSpeed);
          Serial.print("Max speed on straight line = ");
          Serial.println(maxSpeedStraight);
          Serial.print("Line lost delta V= ");
          Serial.println(lineLostDeltaV);
          break;
        case 'H':
          Serial.println("v - show current settings");
          Serial.println("p - set proportional gain Kp");
          Serial.println("d - set derivative gain Kd");
          Serial.println("s - set MAXspeed");
          Serial.println("m - set MAXspeed on straight line");
          Serial.println("r - set 'deltaV when line is lost'");
        case 0x0A:
          break;
        case 0x0D:
          break; 
        case 'c':
          //Serial.println("Exiting calibration mode");
          return;
        default : 
          Serial.println("Incorrect command");
          break;
        }
    }
  }
}
