// Written by MAX (Created 06-01-2023)

// Features : Motor Control Functions

//--------------------------------------------------------//

#ifndef NUCLEO64_MOTOR_CONTROL_H
#define NUCLEO64_MOTOR_CONTROL_H

#include "mbed.h"
#include "Nucleo64_Global_Var_Def.h"

void Motor_Apply_Input();

void Motor_Apply_Input(Motor_Input input);

void Motor_Apply_Input(Motor motor, float pwm, bool dir, float mul);

#endif