//Written by MAX (Created 14-06-2022)

//Funtions : Write test functions here, 
//              so main program will not be messy
//                  (For Nucleo-64)

// *** ONLY CASE WHICH FUNCTIONS ARE DEFINED IN HEADER *** 

#ifndef NUCLEO_TEST_H
#define NUCLEO_TEST_H

#include "Nucleo64_Tool.h"

#include "mbed.h"

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

void test_init(){
    motor_DIR[0]->write(1);
    motor_DIR[1]->write(0);

    motor_DIR[2]->write(0);
    motor_DIR[3]->write(1);
    
    motor_DIR[4]->write(0);
    motor_DIR[5]->write(1);
    
    motor_DIR[6]->write(1);
    motor_DIR[7]->write(0);

    motor_PWM[0]->write(0.25f);
    motor_PWM[1]->write(0.0f);
    motor_PWM[2]->write(0.0f);
    motor_PWM[3]->write(0.25f);
}
void test_loop(){
    // for (float f=0.0f; f<1.1f; f+=0.1f) {
    //     motor_PWM[2]->write(f);
    //     motor_PWM[3]->write(f);
    //     wait_us(500*1000);
    // }
}

#endif