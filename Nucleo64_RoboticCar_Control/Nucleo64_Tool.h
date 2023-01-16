//Written by MAX (Created 13-06-2022)

//Funtions : Common Functions for Nucleo-64

#ifndef NUCLEO_TOOL_H
#define NUCLEO_TOOL_H

#include "mbed.h"

//--------------------------------------------------------//

// Easy Serial Write
void serial_println();
void serial_print(const char* msg);
void serial_println(const char* msg);
void serial_print(string msg);
void serial_println(string msg);
void serial_print(int msg);
void serial_println(int msg);
void serial_print(uint16_t msg);
void serial_println(uint16_t msg);
void serial_print(uint32_t msg);
void serial_println(uint32_t msg);
// -> print to 8 decimal points only
void serial_print(float msg);
// -> print to 8 decimal points only
void serial_println(float msg);

// Easy Wait
void wait_ms(uint16_t ms);
void wait_s(uint16_t s);

// Easy float -> char[]
//TODO

// Easy [Basic Type] -> char[]
//TODO

// Easy Angle <=> Radian
float angle_to_radian(float angle);
float radian_to_angle(float radian);

#endif