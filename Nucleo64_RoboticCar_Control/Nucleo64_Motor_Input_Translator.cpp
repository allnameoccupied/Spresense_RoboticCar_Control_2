// Written by MAX (Created 06-01-2023)

// Features : Translator to Motor Input

//--------------------------------------------------------//

#include "Nucleo64_Motor_Input_Translator.h"

#include "Nucleo64_Include_List.h"

void PWM_to_Input(I2C_PWM_DIR_Input input){
    switch (input.motor) {
        case Motor_TL:{
            if (input.pwm >= 0.0) {
                Curr_Motor_Input.M1_PWM = input.pwm;
            }
            if (input.dir != 2) {
                Curr_Motor_Input.M1_DIR = input.dir;
            }
            break;
        }
        case Motor_TR:{
            if (input.pwm >= 0.0) {
                Curr_Motor_Input.M2_PWM = input.pwm;
            }
            if (input.dir != 2) {
                Curr_Motor_Input.M2_DIR = input.dir;
            }
            break;
        }
        case Motor_BL:{
            if (input.pwm >= 0.0) {
                Curr_Motor_Input.M3_PWM = input.pwm;
            }
            if (input.dir != 2) {
                Curr_Motor_Input.M3_DIR = input.dir;
            }
            break;
        }
        case Motor_BR:{
            if (input.pwm >= 0.0) {
                Curr_Motor_Input.M4_PWM = input.pwm;
            }
            if (input.dir != 2) {
                Curr_Motor_Input.M4_DIR = input.dir;
            }
            break;
        }
        default:break;
    }
}

void TargetXY_to_Input(I2C_Target_XY_Input input){

    target_X = input.target_X;
    target_Y = input.target_Y;

    float temp_radian = atan2(target_Y-Y, target_X-X);
    if (temp_radian < 0.0) {
        temp_radian += 2*PI_M;
    }

    Radian_to_Input(temp_radian);
}

void Radian_to_Input(float input){
    float sinr = sin(input);
    float cosr = cos(input);
    float M14_PWM = ((sinr>0.0 ? 1 : -1)*sinr*sinr + 
                     (cosr>0.0 ? 1 : -1)*cosr*cosr );
    float M23_PWM = ((sinr>0.0 ? 1 : -1)*sinr*sinr - 
                     (cosr>0.0 ? 1 : -1)*cosr*cosr );

    Curr_Motor_Input.M1_PWM = abs(M14_PWM);
    Curr_Motor_Input.M1_DIR = M14_PWM>0;

    Curr_Motor_Input.M2_PWM = abs(M23_PWM);
    Curr_Motor_Input.M2_DIR = M23_PWM>0;

    Curr_Motor_Input.M3_PWM = abs(M23_PWM);
    Curr_Motor_Input.M3_DIR = M23_PWM>0;

    Curr_Motor_Input.M4_PWM = abs(M14_PWM);
    Curr_Motor_Input.M4_DIR = M14_PWM>0;
}

void Encoder_to_Input(I2C_Encoder_Input input){
    if (input.M1_Multiplier >= 0.0) {
        Curr_Motor_Input.M1_MUL = input.M1_Multiplier;
    }
    if (input.M2_Multiplier >= 0.0) {
        Curr_Motor_Input.M2_MUL = input.M2_Multiplier;
    }
    if (input.M3_Multiplier >= 0.0) {
        Curr_Motor_Input.M3_MUL = input.M3_Multiplier;
    }
    if (input.M4_Multiplier >= 0.0) {
        Curr_Motor_Input.M4_MUL = input.M4_Multiplier;
    }
}