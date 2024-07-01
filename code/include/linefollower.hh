/**
 * @file linefollower.hh
 * @author Dominik Workshop
 * @brief 
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "defines.hh"
#include "motor.hh"
#include "line_sensors.hh"
#include "battery.hh"

class Linefollower{
  public:
    Motor Rmotor;
    Motor Lmotor;
    LineSensors lineSensors;
    Battery battery;
    Linefollower();
    void driveOnLine();
    void readSettingsFromEEPROM();
    void spinWheelsForCleaning();
    void calibration();
  private:
    float batteryVoltage;
    int16_t Kp = 93; //Proportional gain
    int16_t Kd = 250; //Derivative gain
    uint8_t maxSpeed = 100;
    uint8_t maxSpeedStraight = 150;
    int16_t lineLostDeltaV = 90;
};
