/**
 * @file battery.cpp
 * @author Dominik Workshop
 * @brief Battery class, responsible for monitoring and sending voltage data.
 * @version 0.1
 * @date 2024-03-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "battery.hh"

#define V_REF 5
#define ADC_RESOLUTION 1024
#define VOLTAGE_ATTENUATION_FACTOR 2.0  // attenuation due to the voltage divider


/**
 * @brief measueres and calculates battery's voltage, turns on red LED when battery is below given threshold voltage
 * 
 * @return float measured battery voltage
 */
float Battery::checkVoltage(){
  voltage = VOLTAGE_ATTENUATION_FACTOR*(analogRead(BATTERY))*V_REF/ADC_RESOLUTION;
  if (voltage < BATTERY_UNDERVOLTAGE)
    digitalWrite(RED_LED, HIGH);    
  else 
    digitalWrite(RED_LED, LOW);
  return voltage;
}

/**
 * @brief sends battery voltage via bluetooth
 * 
 */
void Battery::sendVoltage(){
  Serial.print("Battery=");
  Serial.print(voltage);
  Serial.println("V");
}
