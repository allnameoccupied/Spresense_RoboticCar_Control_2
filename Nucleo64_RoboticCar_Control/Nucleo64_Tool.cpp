//Written by MAX (Created 13-06-2022)

//Funtions : Common Functions for Nucleo-64

#include "Nucleo64_Tool.h"

#include "mbed.h"
#include <cstring>
#include <string>

//Easy Serial Write
void serial_print(const char* msg){
    Serial_M->write(msg,strlen(msg));
}
void serial_println(const char* msg){
    serial_print(msg);
    serial_print("\n");
}
void serial_print(string& msg){
    char msg_char_array[msg.length()+1];
    strcpy(msg_char_array, msg.c_str());
    serial_print(msg_char_array);
}
void serial_println(string& msg){
    serial_print(msg.append("\n"));
}
void serial_print(int msg){
    serial_print(to_string(msg).c_str());
}
void serial_println(int msg){
    serial_println(to_string(msg).c_str());
}

//Easy Wait
void wait_ms(uint16_t ms){
    wait_us(ms*1000);
}
void wait_s(uint16_t s){
    wait_ms(s*1000);
}

//Easy Angle <=> Radian
float angle_to_radian(uint16_t angle){
    return angle*3.14159265358979323846/180;
}
uint16_t radian_to_angle(float radian){
    return (((uint16_t)(radian*180/3.14159265358979323846+360))%360);
}