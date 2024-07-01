/**
 * @file defines.hh
 * @author Dominik Workshop
 * @brief definition of undervoltage value, pin numbers and EEPROM adresses
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#define BATTERY_UNDERVOLTAGE 7.2  // [V], if battery drops below this voltage, red LED wil turn on

/*EEPROM addreses where calibration values are stored, so that they aren't lost after restart,
calibration values stored in EEPROM can't exceed 255!!!!!!!!!!!!!!*/
#define KP_EEPROM_ADDRESS 0
#define KD_EEPROM_ADDRESS 1
#define MAX_SPEED_EEPROM_ADDRESS 2
#define MAX_SPEED_STRGHT_EEPROM_ADDRESS 3
#define LINE_LOST_D_V_EEPROM_ADDRESS 4

#define BUTTON 4
#define GREEN_LED 5
#define RED_LED 6
#define FRONT_POWER 1     // output pin to turn on/off front sensors
#define L_MOTOR_SPEED 13  // PWM pin for controlling left motor's speed
#define L_MOTOR_DIR 15    // digital pin for controlling left motor's direction
#define R_MOTOR_SPEED 12  // PWM pin for controlling right motor's speed
#define R_MOTOR_DIR 14    // digital pin for controlling right motor's direction
#define BATTERY A0        // pin for battery voltage measurement (using 10 bit ADC)

/*pins for transoptor sensors*/
#define CZ1 16
#define CZ2 17
#define CZ3 18
#define CZ4 19
#define CZ5 20
#define CZ6 21
#define CZ7 22
#define CZ8 23
#define CZ9 31
#define CZ10 30
#define CZ11 29
#define CZ12 28
#define CZ13 27
#define CZ14 26
#define CZ15 25
#define CZ16 0
