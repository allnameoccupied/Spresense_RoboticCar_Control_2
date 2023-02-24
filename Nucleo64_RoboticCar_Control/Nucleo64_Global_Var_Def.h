//Written by MAX (Created 14-06-2022)

//Features : Global Variables & Constant Definitions for Nucleo64

#ifndef NUCLEO_GLOBAL_VAR_DEF_H
#define NUCLEO_GLOBAL_VAR_DEF_H

#include "mbed.h"

// I2C Address of Nucleo-64
#define NUCLEO_I2C_ADDR 0x45
// -> I2C Message Length
#define I2C_MSG_LENGTH  32

// PI
#define PI_M            3.14159265358979323846f

// MAX Motor Speed Ratio
#define MAX_MOTOR_SPD   0.95f

// MIN Distance to trigger Motor Movement
#define MIN_MOVE_DIST   0   

// Motor Physical Properties
// -> According to: https://osoyoo.com/2019/11/08/how-to-test-motor-encoder-with-arduino/
// #define RATED_V         6   //V
// #define WHEEL_D         80  //mm
// -> Circumference for half wheel (for hall sensor feedback)
// #define WHEEL_HALF_C    80/2*PI_M  //mm
// #define MOTOR_GEAR_RATIO    75 //1:75
// #define MOTOR_SPEC_SPEED    11500 //rpm

// MIN Time for next SAME Interrupt to be handled
// #define HALL_UPDATE_PERIOD  1  //ms

//--------------------------------------------------------//

// Position Variables
// -> Coordinates
extern uint32_t         X, Y;
extern uint32_t         target_X, target_Y;

// PIN Variables
// -> onboard LED & Button
extern DigitalOut*      LED;
extern DigitalIn*       Button;     //Pressed=0, NOT Pressed=1
// -> I2C
extern I2CSlave*        I2C_SLAVE_M;
// -> Motor pins
extern PwmOut*          Motor_PWM[4];
extern DigitalOut*      Motor_DIR[2*4];
// extern InterruptIn*     Motor_HALL[2*4];

// Motor Related
// -> Motor enum
enum                    Motor { Motor_TL, Motor_TR, Motor_BL, Motor_BR };
// -> Motor Current Input
class Motor_Input { // DIR : True = forward, False = backward
    public:
    bool is_available;    // use mutex with this if want to update with timer interrupt, don't forget to implement checking tho
    //
    float M1_PWM;
    bool M1_DIR;
    float M1_MUL;
    //
    float M2_PWM;
    bool M2_DIR;
    float M2_MUL;
    //
    float M3_PWM;
    bool M3_DIR;
    float M3_MUL;
    //
    float M4_PWM;
    bool M4_DIR;
    float M4_MUL;
};
extern Motor_Input      Curr_Motor_Input;
// -> Motor Hall Sensors Count
// extern uint16_t         Hotor_HALL_count[2*4] = {0,0,0,0,0,0,0,0};

//  Serial communication
extern BufferedSerial*  Serial_M;

#endif