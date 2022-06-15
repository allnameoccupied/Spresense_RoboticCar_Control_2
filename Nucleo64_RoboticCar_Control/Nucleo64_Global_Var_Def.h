//Written by MAX (Created 14-06-2022)

//Features : Global Variables & Constant Definitions for Nucleo64

#ifndef NUCLEO_GLOBAL_VAR_DEF_H
#define NUCLEO_GLOBAL_VAR_DEF_H

//PI
#define PI_M            3.14159265358979323846f

//MAX Motor Speed Ratio
#define MAX_MOTOR_SPD   0.8f

//Phase when calculating Motor Input
#define M14_PHASE       PI_M*1.0/4.0
#define M23_PHASE       PI_M*7.0/4.0

//MIN Distance to trigger Motor Movement
#define MIN_MOVE_DIST   0   

//Motor Physical Properties
//According to: https://www.amazon.com/OSOYOO-Robotic-Mecanum-Platform-Raspberry/dp/B07WZJYVB5
#define RATED_V         9   //V
#define WHEEL_D         80  //mm
//  circumference for half wheel (for hall sensor feedback)
#define WHEEL_HALF_C    80/2*PI_M  //mm
#define MOTOR_GEAR_RATIO    75 //1:75
#define MOTOR_SPEC_SPEED    11500 //rpm

#endif