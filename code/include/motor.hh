/**
 * @file motor.hh
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

enum Direction{
  Forward,
  Backward
};

class Motor{
  public:
    Motor(int dirPin, int speedPin, bool reverseDirection);
    void setSpeed(int speed);
    void setDirection(Direction direction);
  private:
    int dirPin;
    int speedPin;
    bool reverseDir;
};
