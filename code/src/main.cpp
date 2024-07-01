/**
 * @file main.cpp
 * @author Dominik Workshop
 * @brief 
 * @version 0.1
 * @date 2024-03-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Arduino.h>

#include "linefollower.hh"

int main() {

  init();   // Arduino function, initializes peripherals

  Serial.begin(9600);

  Linefollower linefollower;

  while(1){
    linefollower.battery.checkVoltage();
    if(digitalRead(BUTTON) == LOW)
      linefollower.spinWheelsForCleaning();

    if(Serial.available()>0){
      char data = Serial.read();
      switch(data){
        case 'B':
          linefollower.battery.sendVoltage();
          break;
        case 't': 
          linefollower.lineSensors.test();
          break;
        case 'D': 
          linefollower.driveOnLine();
          break;
        case 'c':
          linefollower.calibration();
          break;  
        case 0x0A:
          break;
        case 0x0D:
          break;
        default : 
          Serial.println("Incorrect option");
          break;
        }
    }
  }
} 