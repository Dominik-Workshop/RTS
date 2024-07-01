/**
 * @file line_sensors.cpp
 * @author Dominik Workshop
 * @brief 
 * @version 0.1
 * @date 2024-03-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "line_sensors.hh"

LineSensors::LineSensors(){
  pinMode(FRONT_POWER, OUTPUT);
  digitalWrite(FRONT_POWER, LOW);

  pinMode(CZ1, INPUT);
  pinMode(CZ2, INPUT);
  pinMode(CZ3, INPUT);
  pinMode(CZ4, INPUT);
  pinMode(CZ5, INPUT);
  pinMode(CZ6, INPUT);
  pinMode(CZ7, INPUT);
  pinMode(CZ8, INPUT);
  pinMode(CZ9, INPUT);
  pinMode(CZ10, INPUT);
  pinMode(CZ11, INPUT);
  pinMode(CZ12, INPUT);
  pinMode(CZ13, INPUT);
  pinMode(CZ14, INPUT);
  pinMode(CZ15, INPUT);
  pinMode(CZ16, INPUT);
}

void LineSensors::readSensors(){
  #ifdef NEGATIVE
  sensorReadings[0] = !(PINC & B00000001);            //CZ1
  sensorReadings[1] = !(PINC >> 1 & B00000010 >> 1);  //CZ2
  sensorReadings[2] = !(PINC >> 2 & B00000100 >> 2);  //CZ3
  sensorReadings[3] = !(PINC >> 3 & B00001000 >> 3);  //CZ4
  sensorReadings[4] = !(PINC >> 4 & B00010000 >> 4);  //CZ5
  sensorReadings[5] = !(PINC >> 5 & B00100000 >> 5);  //CZ6
  sensorReadings[6] = !(PINC >> 6 & B01000000 >> 6);  //CZ7
  sensorReadings[7] = !(PINC >> 7 & B10000000 >> 7);  //CZ8
  sensorReadings[8] = !(PINA >> 7 & B10000000 >> 7);  //CZ9
  sensorReadings[9] = !(PINA >> 6 & B01000000 >> 6);  //CZ10
  sensorReadings[10] = !(PINA >> 5 & B00100000 >> 5); //CZ11
  sensorReadings[11] = !(PINA >> 4 & B00010000 >> 4); //CZ12
  sensorReadings[12] = !(PINA >> 3 & B00001000 >> 3); //CZ13
  sensorReadings[13] = !(PINA >> 2 & B00000100 >> 2); //CZ14
  sensorReadings[14] = !(PINA >> 1 & B00000010 >> 1); //CZ15
  sensorReadings[15] = !(PINB & B00000001);           //CZ16
  #else
  sensorReadings[0] = (PINC & B00000001);            //CZ1
  sensorReadings[1] = (PINC >> 1 & B00000010 >> 1);  //CZ2
  sensorReadings[2] = (PINC >> 2 & B00000100 >> 2);  //CZ3
  sensorReadings[3] = (PINC >> 3 & B00001000 >> 3);  //CZ4
  sensorReadings[4] = (PINC >> 4 & B00010000 >> 4);  //CZ5
  sensorReadings[5] = (PINC >> 5 & B00100000 >> 5);  //CZ6
  sensorReadings[6] = (PINC >> 6 & B01000000 >> 6);  //CZ7
  sensorReadings[7] = (PINC >> 7 & B10000000 >> 7);  //CZ8
  sensorReadings[8] = (PINA >> 7 & B10000000 >> 7);  //CZ9
  sensorReadings[9] = (PINA >> 6 & B01000000 >> 6);  //CZ10
  sensorReadings[10] = (PINA >> 5 & B00100000 >> 5); //CZ11
  sensorReadings[11] = (PINA >> 4 & B00010000 >> 4); //CZ12
  sensorReadings[12] = (PINA >> 3 & B00001000 >> 3); //CZ13
  sensorReadings[13] = (PINA >> 2 & B00000100 >> 2); //CZ14
  sensorReadings[14] = (PINA >> 1 & B00000010 >> 1); //CZ15
  sensorReadings[15] = (PINB & B00000001);           //CZ16
  #endif
}

/**
 * @brief sends 16 sensor readouts via bluetooth in one line (eg. 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), 
 * untill this function is selected again
 * 
 */
void LineSensors::test(){
  digitalWrite(FRONT_POWER, HIGH);
  while(!isReceived('t')){
    readSensors();
    for (int i = 0; i < 16; ++i){
      Serial.print(sensorReadings[i]);
      Serial.print(", ");
    }
    Serial.println(" ");
    delay(100);
  }
  digitalWrite(FRONT_POWER, LOW);
}

int16_t LineSensors::calculateError(){
  numOfDetectingSensors = 0; 
  weightedSumError = 0;
  for(int i = 0; i < 16; ++i){
    numOfDetectingSensors += sensorReadings[i]; // count how many sensors see the line
    weightedSumError += sensorReadings[i] * weights[i];
  }
  return error = weightedSumError / numOfDetectingSensors;
}

uint8_t LineSensors::getNumOfDetectingSensors(){
  return numOfDetectingSensors;
}
