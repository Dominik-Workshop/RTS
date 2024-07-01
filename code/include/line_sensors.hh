/**
 * @file line_sensors.hh
 * @author Dominik Workshop
 * @brief 
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <Arduino.h>

#include "defines.hh"
#include "bluetooth.hh"

class LineSensors{
  public:
    uint8_t sensorReadings[16];  // array containing sensor readings (0 or 1)
    LineSensors();
    void readSensors();
    void test();
    int16_t calculateError();
    uint8_t getNumOfDetectingSensors();
  private:
    uint8_t numOfDetectingSensors = 0;   // number of sensors that see the line at given moment
    int16_t weightedSumError = 0;
    int16_t error = 0;
    int8_t weights[16] = {-20, -15, -12, -8, -5, -3, -2, -1, 1, 2, 3, 5, 8, 12, 15, 20}; // weights for the sensors
};
