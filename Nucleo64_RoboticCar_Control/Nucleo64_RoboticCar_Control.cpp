//Written by MAX (Created 10-06-2022)

//Features : Main program for Nucleo64

//--------------------------------------------------------//

//files created by me(max12345)
#include "Nucleo64_Include_List.h"
#include "Nucleo64_Test.h"
#include "Nucleo64_Pin_Mapping.h"
#include "Nucleo64_Init.h"
#include "Nucleo64_Tool.h"
#include "Nucleo64_Global_Var_Def.h"
//files from libraries
#include "mbed.h"
#include <cmath>
#include <cstdint>
#include <string>
#include <cstring>

#define from_MAX    12345

//--------------------------------------------------------//

// GLOBAL VARIABLES

// Position Variables
// -> Coordinates
uint32_t            X, Y;
uint32_t            target_X, target_Y;

// PIN Variables
// -> onboard LED & Button
DigitalOut*         LED;
DigitalIn*          Button;     //Pressed=0, NOT Pressed=1
// -> I2C
I2CSlave*           I2C_SLAVE_M;
// -> Motor pins
PwmOut*             Motor_PWM[4];
DigitalOut*         Motor_DIR[2*4];
// InterruptIn*        Motor_HALL[2*4];

// Motor Related
// -> Motor enum (PLACEHOLDER)
// enum Motor { Motor_TL, Motor_TR, Motor_BL, Motor_BR };
// -> Motor Current Input
Motor_Input         Curr_Motor_Input;
// -> Motor Hall Sensors Count
// uint16_t            Hotor_HALL_count[2*4] = {0,0,0,0,0,0,0,0};

//  Serial communication
BufferedSerial*     Serial_M;

//--------------------------------------------------------//

// main() runs in its own thread in the OS
int main()
{
    //Nucleo64 Init
    Onboard_LED_Init(LED);
    Onboard_Button_Init(Button);
    I2C_Init(I2C_SLAVE_M);
    Motor_Input_Init();
    Motor_PWM_Pin_Init(Motor_PWM);
    Motor_DIR_Pin_Init(Motor_DIR);
    // Motor_HALL_Pin_Init(Motor_HALL);
    Serial_Init(Serial_M);
    HAL_Init();     //get time with HAL_GetTick, return (uint32_t)
    X = 0;
    Y = 0;
    target_X = 0;
    target_Y = 0;
    // Nucleo64_Init_Finished_Successfully(LED);
    serial_println("Init finished successfully");
    LED->write(1);
    
    //TEST FUNCTION
    test_init();
    // while (1) {test_loop();}

    while (true) {

        I2C_Input* i2c_input = I2C_Read();

        if (i2c_input != nullptr) {
            switch (i2c_input->input_type) {
                case PWM_DIR:{
                    PWM_to_Input(i2c_input->pwm_dir);
                    break;
                }
                case TargetXY:{
                    TargetXY_to_Input(i2c_input->targetXY);
                    break;
                }
                case Radian:{
                    Radian_to_Input(i2c_input->radian);
                    break;
                }
                case Encoder:{
                    Encoder_to_Input(i2c_input->encoder);
                    break;
                }
                default:break;
            }

            Motor_Apply_Input();

            delete i2c_input;
        }
    }
}