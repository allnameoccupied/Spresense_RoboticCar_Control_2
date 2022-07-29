//Written by MAX (Created 14-06-2022)

//Funtions : Write test functions here, 
//              so main program will not be messy
//                  (For Nucleo-64)

// *** ONLY CASE WHICH FUNCTIONS ARE DEFINED IN HEADER *** 

#ifndef NUCLEO_TEST_H
#define NUCLEO_TEST_H

#include "Nucleo64_Tool.h"
#include "Nucleo64_Global_Var_Def.h"
#include "Nucleo64_Pin_Mapping.h"

#include "mbed.h"
#include <cstdint>
#include <cstring>
#include <ctime>

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
extern uint16_t        motor_HALL_count[2*4];
//  Serial communication
extern BufferedSerial* Serial_M;

//--------------------------------------------------------//

//EXTERN of FUNCTION Declaration
extern void i2c_read_M();
extern float get_radian_from_target();
extern void motor_PWM_DIR_input(float radian);
extern void motor_HALL_feedback();

//--------------------------------------------------------//

// void test_init(){
    
// }

void test_init(){

    // uint16_t test = 100;
    // serial_println((int)test);

    // motor_DIR[0]->write(1);
    // motor_DIR[1]->write(0);
    // motor_PWM[0]->write(1.0f);

    // HAL_Init();

    I2CSlave slave(I2C_M_SDA_PIN,I2C_M_SCL_PIN);
    slave.frequency(400000);
    slave.address(NUCLEO_I2C_ADDR);
    serial_println("now monitor I2C la");

    while(1){

        int addressed = slave.receive();

        // serial_println(addressed);

        if (addressed == I2CSlave::WriteAddressed) {
            *LED = 0;
            char buf[32];
            int data = slave.read(buf, 32);
            serial_println(buf);
        }

        // char buf[10];
        // buf[0] = 0;
        // slave.read(buf,10);
        // if(strlen(buf) != 0){
        //     serial_println(buf);
        // }
    }
}

void test_loop(){
    // wait_s(5);

    // serial_println(motor_HALL_count[0]);
    // serial_println(motor_HALL_count[1]);
    // serial_println();

    // serial_println((int)(HAL_GetTick()));

    // for (float f=0.0f; f<1.1f; f+=0.1f) {
    //     motor_PWM[2]->write(f);
    //     motor_PWM[3]->write(f);
    //     wait_us(500*1000);
    // }

    // *LED = Button->read();

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