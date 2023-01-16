// Written by MAX (Created 10-01-2023)

// Features : Handle I2C Communication with Nucleo64

//--------------------------------------------------------//

#include "Spresense_I2C_Handler.h"
#include "Spresense_Include_List.h"

bool I2C_Write_PWM_DIR (Motor motor, float pwm, uint8_t dir){
    if (pwm < 0.0 || pwm > 1.0){return false;}
    if (dir != 0 && dir != 1 && dir != 2){return false;}

    char msg[I2C_MSG_LENGTH];

    msg[0] = '0';

    msg[1] = static_cast<int>(motor) + '0';

    int temp_whole = (int)pwm;
    int temp_decimal = (int)((pwm-(int)pwm)*100000000);
    char tempa[8];
    itoa(temp_decimal, tempa, 10);
    std::string temps = tempa;
    temps.insert(0, 8-temps.length(), '0');
    msg[2] = temp_whole + '0';
    memcpy(&msg[3], temps.c_str(), 8);

    msg[11] = dir + '0';

    Serial.println(msg);

    // Wire.beginTransmission(NUCLEO_I2C_ADDR);
    // Wire.endTransmission();
    Wire.beginTransmission(NUCLEO_I2C_ADDR);
    Wire.write(msg);
    Wire.endTransmission();

    return true;
}

bool I2C_Write_Target_XY (int tar_X, int tar_Y){
    if (tar_X < 0 || tar_X >= 1000000000){return false;}
    if (tar_Y < 0 || tar_Y >= 1000000000){return false;}

    char msg[I2C_MSG_LENGTH];

    msg[0] = '1';

    char tempax[9];
    itoa(tar_X, tempax, 10);
    std::string tempsx = tempax;
    tempsx.insert(0, 9-tempsx.length(), '0');
    memcpy(&msg[1], tempsx.c_str(), 9);

    char tempay[9];
    itoa(tar_Y, tempay, 10);
    std::string tempsy = tempay;
    tempsy.insert(0, 9-tempsy.length(), '0');
    memcpy(&msg[10], tempsy.c_str(), 9);

    Serial.println(msg);

    // Wire.beginTransmission(NUCLEO_I2C_ADDR);
    // Wire.endTransmission();
    Wire.beginTransmission(NUCLEO_I2C_ADDR);
    Wire.write(msg);
    Wire.endTransmission();

    return true;
}

bool I2C_Write_Radian (float radian){

    char msg[I2C_MSG_LENGTH];

    msg[0] = '2';

    float mod_radian = fmod(radian, 2*PI);

    int temp_whole = (int)mod_radian;
    int temp_decimal = (int)((mod_radian-(int)mod_radian)*100000000);
    char tempa[8];
    itoa(temp_decimal, tempa, 10);
    std::string temps = tempa;
    temps.insert(0, 8-temps.length(), '0');
    msg[1] = temp_whole + '0';
    memcpy(&msg[2], temps.c_str(), 8);

    Serial.println(msg);

    // Wire.beginTransmission(NUCLEO_I2C_ADDR);
    // Wire.endTransmission();
    Wire.beginTransmission(NUCLEO_I2C_ADDR);
    Wire.write(msg);
    Wire.endTransmission();

    return true;
}

bool I2C_Write_Encoder (float m1_mul, float m2_mul, float m3_mul, float m4_mul){
    if (m1_mul < 0.0 || m1_mul > 1.0){return false;}
    if (m2_mul < 0.0 || m2_mul > 1.0){return false;}
    if (m3_mul < 0.0 || m3_mul > 1.0){return false;}
    if (m4_mul < 0.0 || m4_mul > 1.0){return false;}

    char msg[I2C_MSG_LENGTH];

    msg[0] = '3';
    
    int temp_whole1 = (int)m1_mul;
    int temp_decimal1 = (int)((m1_mul-(int)m1_mul)*1000000);
    char tempa1[8];
    itoa(temp_decimal1, tempa1, 10);
    std::string temps1 = tempa1;
    temps1.insert(0, 6-temps1.length(), '0');
    msg[1] = temp_whole1 + '0';
    memcpy(&msg[2], temps1.c_str(), 6);

    int temp_whole2 = (int)m2_mul;
    int temp_decimal2 = (int)((m2_mul-(int)m2_mul)*1000000);
    char tempa2[8];
    itoa(temp_decimal2, tempa2, 10);
    std::string temps2 = tempa2;
    temps2.insert(0, 6-temps2.length(), '0');
    msg[8] = temp_whole2 + '0';
    memcpy(&msg[9], temps2.c_str(), 6);

    int temp_whole3 = (int)m3_mul;
    int temp_decimal3 = (int)((m3_mul-(int)m3_mul)*1000000);
    char tempa3[8];
    itoa(temp_decimal3, tempa3, 10);
    std::string temps3 = tempa3;
    temps3.insert(0, 6-temps3.length(), '0');
    msg[15] = temp_whole3 + '0';
    memcpy(&msg[16], temps3.c_str(), 6);

    int temp_whole4 = (int)m4_mul;
    int temp_decimal4 = (int)((m4_mul-(int)m4_mul)*1000000);
    char tempa4[8];
    itoa(temp_decimal4, tempa4, 10);
    std::string temps4 = tempa4;
    temps4.insert(0, 6-temps4.length(), '0');
    msg[22] = temp_whole4 + '0';
    memcpy(&msg[23], temps4.c_str(), 6);

    Serial.println(msg);

    // Wire.beginTransmission(NUCLEO_I2C_ADDR);
    // Wire.endTransmission();
    Wire.beginTransmission(NUCLEO_I2C_ADDR);
    Wire.write(msg);
    Wire.endTransmission();

    return true;
}