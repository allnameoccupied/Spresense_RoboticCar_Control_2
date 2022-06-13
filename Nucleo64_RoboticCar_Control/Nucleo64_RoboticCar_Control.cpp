//Written by MAX (Created 10-06-2022)

//Features : Main program for Nucleo64

//--------------------------------------------------------//

//files created by me(max12345)
#include "Nucleo64_Pin_Mapping.h"
#include "Nucleo64_Init.h"
#include "Nucleo64_Tool.h"
//files from libraries
#include "mbed.h"
#include <string>
#include <cstring>

#define from_MAX 12345

//--------------------------------------------------------//

//Global Variables
//  onboard LED & Button
DigitalOut*     LED;
DigitalIn*      Button;
//  I2C
I2C*            I2C_M;
//  Motor variables
PwmOut*         motor_PWM[4];
DigitalOut*     motor_DIR[2*4];
DigitalIn*      motor_HALL[2*4];
//  Serial communication
BufferedSerial* Serial_M;

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
    Motor_HALL_Pin_Init(motor_HALL);
    Serial_Init(Serial_M);
    Nucleo64_Init_Finished_Successfully(LED);
    serial_print("Init finished successfully");
    LED->write(1);

    while (true) {
        for(float p = 0.0f; p < 1.1f; p += 0.1f) {
            *motor_PWM[0]=p;
            wait_us(1 *1000*1000);
        }
        if (Button->read()) {
            LED->write(0);
        } else {
            LED->write(1);
        }
    }
}