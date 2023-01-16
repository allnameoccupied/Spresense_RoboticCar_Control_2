// Written by MAX (Created 10-01-2023)

// Features : Handle I2C Communication with Nucleo64

//--------------------------------------------------------//

#ifndef SPRESENSE_I2C_HANDLER_H
#define SPRESENSE_I2C_HANDLER_H

// no -ve, >0 part will be omitted, only to 8 decimal, dir only 0,1,2(2=no change)
bool I2C_Write_PWM_DIR (Motor motor, float pwm, uint8_t dir);

// no -ve , will send 9 digits, as 10th degit will have boundary for int (and uint32_t)
bool I2C_Write_Target_XY (int tar_X, int tar_Y);

// limit input to [0,2pi], no -ve, >0 part will be omitted, only to 8 decimal
bool I2C_Write_Radian (float radian);

// scale down w.r.t slowest motor please, no -ve, >0 part will be omitted, only 6 decimal points cause no enough message length
bool I2C_Write_Encoder (float m1_mul, float m2_mul, float m3_mul, float m4_mul);

#endif