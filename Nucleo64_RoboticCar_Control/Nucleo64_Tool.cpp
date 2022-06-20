//Written by MAX (Created 13-06-2022)

//Funtions : Common Functions for Nucleo-64

#include "Nucleo64_Tool.h"

#include "Nucleo64_Global_Var_Def.h"

#include "mbed.h"
#include <cstring>
#include <string>

//Easy Serial Write
void serial_println(){
    serial_print("\n");
}
void serial_print(const char* msg){
    Serial_M->write(msg,strlen(msg));
}
void serial_println(const char* msg){
    serial_print(msg);
    serial_print("\n");
}
void serial_print(string msg){
    char msg_char_array[msg.length()+1];
    strcpy(msg_char_array, msg.c_str());
    serial_print(msg_char_array);
}
void serial_println(string msg){
    serial_print(msg.append("\n"));
}
void serial_print(int msg){
    serial_print(to_string(msg).c_str());
}
void serial_println(int msg){
    serial_println(to_string(msg).c_str());
}
void serial_print(uint16_t msg){
    serial_print(to_string((long)msg).c_str());
}
void serial_println(uint16_t msg){
    serial_println(to_string((long)msg).c_str());
}
void serial_print(uint32_t msg){
    serial_print(to_string((long)msg).c_str());
}
void serial_println(uint32_t msg){
    serial_println(to_string((long)msg).c_str());
}

//Easy Wait
void wait_ms(uint16_t ms){
    wait_us(ms*1000);
}
void wait_s(uint16_t s){
    wait_ms(s*1000);
}

//Easy Angle <=> Radian
float angle_to_radian(float angle){
    return angle*PI_M/180.0;
}
float radian_to_angle(float radian){
    float temp_angle = radian*180.0/PI_M;
    if (temp_angle < 0.0) {
        temp_angle += 360.0;
    }
    return temp_angle;
}