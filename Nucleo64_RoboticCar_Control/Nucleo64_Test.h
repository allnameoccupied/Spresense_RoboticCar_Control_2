//Written by MAX (Created 14-06-2022)

//Funtions : Write test functions here, 
//              so main program will not be messy
//                  (For Nucleo-64)

// *** ONLY CASE WHICH FUNCTIONS ARE DEFINED IN HEADER *** 

#ifndef NUCLEO_TEST_H
#define NUCLEO_TEST_H

#include "Nucleo64_Tool.h"

#include "Nucleo64_Global_Var_Def.h"

#include "mbed.h"
#include <cstdint>

//EXTERN of PIN Variables
//  onboard LED & Button
extern DigitalOut*     LED;
extern DigitalIn*      Button;
//  I2C
extern I2C*            I2C_M;
//  Motor variables
extern PwmOut*         motor_PWM[4];
extern DigitalOut*     motor_DIR[2*4];
extern InterruptIn*    motor_HALL[2*4];
extern uint16_t*       motor_HALL_count[2*4];
//  Serial communication
extern BufferedSerial* Serial_M;

//--------------------------------------------------------//

//EXTERN of FUNCTION Declaration
extern void i2c_read_M();
extern float get_radian_from_target();
extern void motor_PWM_DIR_input(float radian);
extern void motor_HALL_feedback();

//--------------------------------------------------------//

void test_init(){

    uint16_t test = 100;
    serial_println((int)test);

    motor_DIR[0]->write(1);
    motor_DIR[1]->write(0);

    // motor_DIR[2]->write(0);
    // motor_DIR[3]->write(1);
    
    // motor_DIR[4]->write(0);
    // motor_DIR[5]->write(1);
    
    // motor_DIR[6]->write(1);
    // motor_DIR[7]->write(0);

    motor_PWM[0]->write(0.1f);
    // motor_PWM[1]->write(0.0f);
    // motor_PWM[2]->write(0.0f);
    // motor_PWM[3]->write(0.25f);
}
void test_loop(){
    wait_s(10);
    // for (float f=0.0f; f<1.1f; f+=0.1f) {
    //     motor_PWM[2]->write(f);
    //     motor_PWM[3]->write(f);
    //     wait_us(500*1000);
    // }

    serial_println((int)*motor_HALL_count[0]);
    serial_println((int)*motor_HALL_count[1]);
    serial_println();
}

void circle_demo(){

    uint16_t dur = 500;

    motor_PWM_DIR_input(PI_M*0.0/4.0);
    wait_ms(dur);
    motor_PWM_DIR_input(PI_M*1.0/4.0);
    wait_ms(dur);
    motor_PWM_DIR_input(PI_M*2.0/4.0);
    wait_ms(dur);
    motor_PWM_DIR_input(PI_M*3.0/4.0);
    wait_ms(dur);
    motor_PWM_DIR_input(PI_M*4.0/4.0);
    wait_ms(dur);
    motor_PWM_DIR_input(PI_M*5.0/4.0);
    wait_ms(dur);
    motor_PWM_DIR_input(PI_M*6.0/4.0);
    wait_ms(dur);
    motor_PWM_DIR_input(PI_M*7.0/4.0);
    wait_ms(dur);
}

#endif