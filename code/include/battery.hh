/**
 * @file battery.hh
 * @author Dominik Workshop
 * @brief Battery class, responsible for monitoring and sending voltage data.
 * @version 0.1
 * @date 2024-03-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <Arduino.h>
#include "defines.hh"

class Battery{
  public:
    float checkVoltage();
    void sendVoltage();
  private:
    float voltage;
};
