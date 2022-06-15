//Written by MAX (Created 10-06-2022)

//Features : Main program for Nucleo64

//--------------------------------------------------------//

//files created by me(max12345)
#include "Nucleo64_Pin_Mapping.h"
#include "Nucleo64_Init.h"
#include "Nucleo64_Tool.h"
#include "Nucleo64_Test.h"
#include "Nucleo64_Global_Var_Def.h"
//files from libraries
#include "mbed.h"
#include <cmath>
#include <cstdint>
#include <string>
#include <cstring>

#define from_MAX    12345

//--------------------------------------------------------//

//PIN Variables
//  onboard LED & Button
DigitalOut*         LED;
DigitalIn*          Button;     //Pressed=0, NOT Pressed=1
//  I2C
I2C*                I2C_M;
//  Motor variables
PwmOut*             motor_PWM[4];
DigitalOut*         motor_DIR[2*4];
InterruptIn*        motor_HALL[2*4];
uint16_t*           motor_HALL_count[2*4];
//  Serial communication
BufferedSerial*     Serial_M;

//POSITION Variables
//  Coordinates
int                 x, y;
int                 target_x, target_y;

//--------------------------------------------------------//

//FUNCTION Declaration
void i2c_read_M();
float get_radian_from_target();
void motor_PWM_DIR_input(float radian);
void motor_HALL_feedback();

//--------------------------------------------------------//

// main() runs in its own thread in the OS
int main()
{
    //Nucleo64 Init
    Onboard_LED_Init(LED);
    Onboard_Button_Init(Button);
    I2C_Init(I2C_M);
    Motor_PWM_Pin_Init(motor_PWM);
    Motor_DIR_Pin_Init(motor_DIR);
    Motor_HALL_Pin_Init(motor_HALL,motor_HALL_count);
    Serial_Init(Serial_M);
    x = 0;
    y = 0;
    target_x = 0;
    target_y = 0;
    // Nucleo64_Init_Finished_Successfully(LED);
    serial_println("Init finished successfully");
    LED->write(1);

    //TEST Functions here
    test_init();

    while (true) {

        //TEST Functions here
        test_loop();

        i2c_read_M();   //read I2C (return 0==success, 1==fail ?)
        if (abs(target_y-y)>MIN_MOVE_DIST || abs(target_x-x)>MIN_MOVE_DIST){
            float radian = get_radian_from_target();
            motor_PWM_DIR_input(radian);
        }
        motor_HALL_feedback();
        
    }
}

//--------------------------------------------------------//

//FUNCTION Implementation
void i2c_read_M(){

}
float get_radian_from_target(){
    float temp_radian = atan2(target_y-y, target_x-x);
    if (temp_radian < 0.0) {
        temp_radian += 2*PI_M;
    }
    return temp_radian;
}
void motor_PWM_DIR_input(float radian){
    float M14_PWM = sin(radian+M14_PHASE);
    float M23_PWM = sin(radian+M23_PHASE);

    motor_PWM[0]->write(M14_PWM);
    motor_DIR[0]->write(M14_PWM>0);
    motor_DIR[1]->write(M14_PWM<0);

    motor_PWM[1]->write(M23_PWM);
    motor_DIR[2]->write(M23_PWM>0);
    motor_DIR[3]->write(M23_PWM<0);

    motor_PWM[2]->write(M23_PWM);
    motor_DIR[4]->write(M23_PWM>0);
    motor_DIR[5]->write(M23_PWM<0);

    motor_PWM[3]->write(M14_PWM);
    motor_DIR[6]->write(M14_PWM>0);
    motor_DIR[7]->write(M14_PWM<0);
}
void motor_HALL_feedback(){

}