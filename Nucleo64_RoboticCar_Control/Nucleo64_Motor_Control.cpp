// Written by MAX (Created 06-01-2023)

// Features : Motor Control Functions

//--------------------------------------------------------//

#include "Nucleo64_Motor_Control.h"

#include "Nucleo64_Include_List.h"

void Motor_Apply_Input(){
    Motor_Apply_Input(Motor_TL, Curr_Motor_Input.M1_PWM, Curr_Motor_Input.M1_DIR, Curr_Motor_Input.M1_MUL);
    Motor_Apply_Input(Motor_TR, Curr_Motor_Input.M2_PWM, Curr_Motor_Input.M2_DIR, Curr_Motor_Input.M2_MUL);
    Motor_Apply_Input(Motor_BL, Curr_Motor_Input.M3_PWM, Curr_Motor_Input.M3_DIR, Curr_Motor_Input.M3_MUL);
    Motor_Apply_Input(Motor_BR, Curr_Motor_Input.M4_PWM, Curr_Motor_Input.M4_DIR, Curr_Motor_Input.M4_MUL);
}

void Motor_Apply_Input(Motor_Input input){
    Motor_Apply_Input(Motor_TL, input.M1_PWM, input.M1_DIR, input.M1_MUL);
    Motor_Apply_Input(Motor_TR, input.M2_PWM, input.M2_DIR, input.M2_MUL);
    Motor_Apply_Input(Motor_BL, input.M3_PWM, input.M3_DIR, input.M3_MUL);
    Motor_Apply_Input(Motor_BR, input.M4_PWM, input.M4_DIR, input.M4_MUL);
}

void Motor_Apply_Input(Motor motor, float pwm, bool dir, float mul){
    switch (motor) {
        case Motor_TL:{
            Motor_PWM[0]->write(pwm*mul*MAX_MOTOR_SPD);
            Motor_DIR[0]->write(dir);
            Motor_DIR[1]->write(!dir);
            break;
        }
        case Motor_TR:{
            Motor_PWM[1]->write(pwm*mul*MAX_MOTOR_SPD);
            Motor_DIR[2]->write(dir);
            Motor_DIR[3]->write(!dir);
            break;
        }
        case Motor_BL:{
            Motor_PWM[2]->write(pwm*mul*MAX_MOTOR_SPD);
            Motor_DIR[4]->write(dir);
            Motor_DIR[5]->write(!dir);
            break;
        }
        case Motor_BR:{
            Motor_PWM[3]->write(pwm*mul*MAX_MOTOR_SPD);
            Motor_DIR[6]->write(dir);
            Motor_DIR[7]->write(!dir);
            break;
        }
        default:break;
    }
}