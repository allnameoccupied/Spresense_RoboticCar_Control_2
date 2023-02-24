// Written by MAX (Created 06-01-2023)

// Features : Translator to Motor Input

//--------------------------------------------------------//

#ifndef NUCLEO64_INPUT_TRANSLATE_H
#define NUCLEO64_INPUT_TRANSLATE_H

#include "mbed.h"
#include "Nucleo64_Motor_Control.h"
#include "Nucleo64_I2C_Handler.h"


void PWM_to_Input(I2C_PWM_DIR_Input input);

void TargetXY_to_Input(I2C_Target_XY_Input input);

void Radian_to_Input(float input);

void Encoder_to_Input(I2C_Encoder_Input input);

#endif