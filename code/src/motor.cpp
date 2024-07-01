/**
 * @file motor.cpp
 * @author Dominik Workshop
 * @brief 
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "motor.hh"

Motor::Motor(int dirPin, int speedPin, bool reverseDirection){
  this->dirPin = dirPin;
  this->speedPin = speedPin;
  this->reverseDir = reverseDirection;
  pinMode(dirPin, OUTPUT);
  pinMode(speedPin, OUTPUT);
  setSpeed(0);
  setDirection(Forward);
}

void Motor::setSpeed(int speed){
  if (speed < 0) 
    speed = 0;
  else if (speed > 255) 
    speed = 255;
  analogWrite(this->speedPin, speed);
}

void Motor::setDirection(Direction direction){
  if(reverseDir)
    digitalWrite(dirPin, !direction);
  else
    digitalWrite(dirPin, direction);
}
