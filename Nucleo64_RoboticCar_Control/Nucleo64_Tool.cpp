//Written by MAX (Created 13-06-2022)

//Funtions : Common Functions for Nucleo-64

#include "Nucleo64_Tool.h"

#include "mbed.h"

//Easy Serial Write
void serial_print(const char* msg){
    Serial_M->write(msg,sizeof(msg));
}
void serial_print(string& msg){
    char msg_char_array[msg.length()+1];
    strcpy(msg_char_array, msg.c_str());
    serial_print(msg_char_array);
}