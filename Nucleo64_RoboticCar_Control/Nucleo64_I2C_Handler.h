// Written by MAX (Created 09-01-2023)

// Features : Handle I2C Communication with Spresense

//--------------------------------------------------------//

#ifndef NUCLEO64_I2C_HANDLER_H
#define NUCLEO64_I2C_HANDLER_H

#include "mbed.h"
#include "Nucleo64_Global_Var_Def.h"
#include <cstdint>

class I2C_PWM_DIR_Input {
    public:
    Motor motor;
    float pwm;      // <0.0 = no change
    uint8_t dir;    // 3 = no change
};
I2C_PWM_DIR_Input I2C_Read_PWM_DIR(char* input);


class I2C_Target_XY_Input {
    public:     // if no change, dont send
    uint32_t target_X;
    uint32_t target_Y;
};
I2C_Target_XY_Input I2C_Read_TargetXY(char* input);


float I2C_Read_Radian(char* input);


class I2C_Encoder_Input {
    public:
    float M1_Multiplier;
    float M2_Multiplier;
    float M3_Multiplier;
    float M4_Multiplier;
};
I2C_Encoder_Input I2C_Read_Encoder(char* input);


enum I2C_Input_Type { PWM_DIR, TargetXY, Radian, Encoder };
class I2C_Input{
    public:
    I2C_Input_Type          input_type;
    I2C_PWM_DIR_Input       pwm_dir;
    I2C_Target_XY_Input     targetXY;
    float                   radian;
    I2C_Encoder_Input       encoder;
};
I2C_Input* I2C_Read();

#endif