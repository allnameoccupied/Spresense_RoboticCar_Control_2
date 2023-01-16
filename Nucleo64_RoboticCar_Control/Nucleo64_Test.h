//Written by MAX (Created 14-06-2022)

//Funtions : Write test functions here, 
//              so main program will not be messy
//                  (For Nucleo-64)

// *** ONLY CASE WHICH FUNCTIONS ARE DEFINED IN HEADER *** 

#ifndef NUCLEO_TEST_H
#define NUCLEO_TEST_H

#include "Nucleo64_Include_List.h"

#include "mbed.h"
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ctime>

//--------------------------------------------------------//

//EXTERN of FUNCTION Declaration
extern void i2c_read_M();
extern float get_radian_from_target();
extern void Motor_PWM_DIR_input(float radian);
extern void Motor_HALL_feedback();

//--------------------------------------------------------//

void test_init(){
    serial_println("now monitor I2C la");

    Curr_Motor_Input.M1_PWM = 1.0;
    Curr_Motor_Input.M1_DIR = 1;
    Curr_Motor_Input.M1_MUL = 1.0;
    
    Curr_Motor_Input.M2_PWM = 1.0;
    Curr_Motor_Input.M2_DIR = 1;
    Curr_Motor_Input.M2_MUL = 1.0;

    Curr_Motor_Input.M3_PWM = 1.0;
    Curr_Motor_Input.M3_DIR = 1;
    Curr_Motor_Input.M3_MUL = 1.0;

    Curr_Motor_Input.M4_PWM = 1.0;
    Curr_Motor_Input.M4_DIR = 1;
    Curr_Motor_Input.M4_MUL = 1.0;

    Motor_Apply_Input();
}

// void test_init(){

//     serial_println("now monitor I2C la");

//     while(1){
//         // static uint32_t count = 0;

//         // serial_println(count);

//         // if (count >= 50000000) {
//             I2C_Input* i2c_input = I2C_Read();
//             if (i2c_input == nullptr) {
//                 // serial_println("is null");
//             } else {
//                 serial_println(i2c_input->input_type);
//                 serial_println();
//                 serial_println(i2c_input->pwm_dir.motor);
//                 serial_println(i2c_input->pwm_dir.pwm);
//                 serial_println(i2c_input->pwm_dir.dir);
//                 serial_println();
//                 serial_println(i2c_input->targetXY.target_X);
//                 serial_println(i2c_input->targetXY.target_Y);
//                 serial_println();
//                 serial_println(i2c_input->radian);
//                 serial_println();
//                 serial_println(i2c_input->encoder.M1_Multiplier);
//                 serial_println(i2c_input->encoder.M2_Multiplier);
//                 serial_println(i2c_input->encoder.M3_Multiplier);
//                 serial_println(i2c_input->encoder.M4_Multiplier);
//                 serial_println();
//             }
//         //     count = 0;
//         // } else {
//         //     count++;
//         // }

//         // int addressed = I2C_SLAVE_M->receive();

//         // // serial_println(addressed);

//         // if (addressed == I2CSlave::WriteAddressed) {
//         //     char buf[32];
//         //     int data = I2C_SLAVE_M->read(buf, 32);
//         //     serial_println(buf);
//         // }
//     }

//     serial_println("not dead");
// }

void test_loop(){

    // I2C_Input* i2c_input = I2C_Read();

    // if (i2c_input != nullptr) {
    //     switch (i2c_input->input_type) {
    //         case PWM_DIR:{
    //             PWM_to_Input(i2c_input->pwm_dir);
    //             break;
    //         }
    //         case TargetXY:{
    //             TargetXY_to_Input(i2c_input->targetXY);
    //             break;
    //         }
    //         case Radian:{
    //             Radian_to_Input(i2c_input->radian);
    //             break;
    //         }
    //         case Encoder:{
    //             Encoder_to_Input(i2c_input->encoder);
    //             break;
    //         }
    //         default:break;
    //     }
    // }

    // serial_println(Motor_HALL_count[0]);
    // for (int i = 0; i < 10; i++) {
    //     serial_println((uint32_t)(Motor_HALL_time[i]));
    // }
    // serial_println();
    // serial_println(Motor_HALL_count[0]);
    // serial_println(Motor_HALL_count[1]);
    // serial_println(Motor_HALL_count[2]);
    // serial_println(Motor_HALL_count[3]);
    // serial_println(Motor_HALL_count[4]);
    // serial_println(Motor_HALL_count[5]);
    // serial_println(Motor_HALL_count[6]);
    // serial_println(Motor_HALL_count[7]);

    // serial_println((int)(HAL_GetTick()));

    // for (float f=0.0f; f<1.1f; f+=0.1f) {
    //     Motor_PWM[2]->write(f);
    //     Motor_PWM[3]->write(f);
    //     wait_us(500*1000);
    // }

    // *LED = Button->read();

}

#endif