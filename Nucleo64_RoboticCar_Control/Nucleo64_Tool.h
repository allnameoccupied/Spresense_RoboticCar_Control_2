//Written by MAX (Created 13-06-2022)

//Funtions : Common Functions for Nucleo-64

#ifndef NUCLEO_TOOL_H
#define NUCLEO_TOOL_H

#include "mbed.h"
#include <cstdint>
#include <string>
#include <cstring>

//EXTERN of PIN Variables
//  onboard LED & Button
extern DigitalOut*     LED;
extern DigitalIn*      Button;
//  I2C
extern I2C*            I2C_M;
//  Motor variables
extern PwmOut*         motor_PWM[4];
extern DigitalOut*     motor_DIR[2*4];
extern DigitalIn*      motor_HALL[2*4];
//  Serial communication
extern BufferedSerial* Serial_M;

//--------------------------------------------------------//

//Easy Serial Write
void serial_print(const char* msg);
void serial_println(const char* msg);
void serial_print(string& msg);
void serial_println(string& msg);
void serial_print(int msg);
void serial_println(int msg);

//Easy Wait
void wait_ms(uint16_t ms);
void wait_s(uint16_t s);

//Easy Angle <=> Radian
float angle_to_radian(uint16_t angle);
uint16_t radian_to_angle(float radian);

#endif