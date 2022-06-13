//Written by MAX (Created 13-06-2022)

//Funtions : Common Functions for Nucleo-64

#ifndef NUCLEO_TOOL_H
#define NUCLEO_TOOL_H

#include "mbed.h"
#include <string>
#include <cstring>

//Easy Serial Write
extern BufferedSerial* Serial_M;
void serial_print(const char* msg);
void serial_print(string& msg);

#endif