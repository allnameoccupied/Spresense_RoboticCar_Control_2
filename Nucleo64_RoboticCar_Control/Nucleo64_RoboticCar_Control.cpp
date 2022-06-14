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
DigitalIn*          motor_HALL[2*4];
//  Serial communication
BufferedSerial*     Serial_M;

//POSITION Variables
//  Coordinates
int                 x, y;

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
    x = 0;
    y = 0;
    // Nucleo64_Init_Finished_Successfully(LED);
    serial_println("Init finished successfully");
    LED->write(1);

    //TEST Functions here
    test_init();

    while (true) {

        //TEST Functions here
        test_loop();

        //read I2C (return 0==success, 1==fail ?)
        //      input == target x,y
        //cal angle
        
    }
}