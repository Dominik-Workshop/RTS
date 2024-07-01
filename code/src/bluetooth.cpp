/**
 * @file bluetooth.cpp
 * @author Dominik Workshop
 * @brief functions for serial
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "bluetooth.hh"

/**
 * @brief check if a given character was received via serial
 * @param symbol character to check for
 * @return true if the given character was received, false otherwise
 */
bool isReceived(char symbol){
  if (Serial.available() > 0) {
    return Serial.read() == symbol;
  }
  return false;
}
