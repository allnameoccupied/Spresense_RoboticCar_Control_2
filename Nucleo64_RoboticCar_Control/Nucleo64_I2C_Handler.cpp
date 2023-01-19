// Written by MAX (Created 09-01-2023)

// Features : Handle I2C Communication with Spresense

//--------------------------------------------------------//

#include "Nucleo64_I2C_Handler.h"

#include "Nucleo64_Include_List.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

I2C_Input* I2C_Read(){

    I2C_Input* i2c_input = nullptr;

    int addressed = I2C_SLAVE_M->receive();

    if (addressed == I2CSlave::WriteAddressed) {
        char buffer[I2C_MSG_LENGTH];
        I2C_SLAVE_M->read(buffer, I2C_MSG_LENGTH);
        serial_println(buffer);

        switch (buffer[0]) {
            case '0':{  // PWM
                i2c_input = new I2C_Input();
                i2c_input->input_type = PWM_DIR;
                i2c_input->pwm_dir = I2C_Read_PWM_DIR(buffer);
                break;
            }
            case '1':{  // Target XY
                i2c_input = new I2C_Input();
                i2c_input->input_type = TargetXY;
                i2c_input->targetXY = I2C_Read_TargetXY(buffer);
                break;
            }
            case '2':{  // Radian
                i2c_input = new I2C_Input();
                i2c_input->input_type = Radian;
                i2c_input->radian = I2C_Read_Radian(buffer);
                break;
            }
            case '3':{  // Encoder
                i2c_input = new I2C_Input();
                i2c_input->input_type = Encoder;
                i2c_input->encoder = I2C_Read_Encoder(buffer);
                break;
            }
            default:break;
        }
    }
    return i2c_input;
}

I2C_PWM_DIR_Input I2C_Read_PWM_DIR(char* input){

    I2C_PWM_DIR_Input i2c_package;
    
    i2c_package.motor = static_cast<Motor>((int)(input[1]-'0'));

    int tempi = (int)(input[2]-'0');
    char tempa[8];
    memcpy(&tempa, &input[3], 8);
    i2c_package.pwm = (float)tempi + (float)(atoi(tempa))/100000000;

    i2c_package.dir = (int)(input[11]-'0');
    
    return i2c_package;
}

I2C_Target_XY_Input I2C_Read_TargetXY(char* input){

    I2C_Target_XY_Input i2c_package;

    char temp[9];
    memcpy(&temp, &input[1], 9);
    i2c_package.target_X = atoi(temp);

    memcpy(&temp, &input[10], 9);
    i2c_package.target_Y = atoi(temp);

    return i2c_package;
}

float I2C_Read_Radian(char* input){

    float i2c_package;

    int tempi = (int)(input[1]-'0');
    char tempa[8];
    memcpy(&tempa, &input[2], 8);
    i2c_package = (float)tempi + (float)(atoi(tempa))/100000000;

    return i2c_package;
}

I2C_Encoder_Input I2C_Read_Encoder(char* input){

    I2C_Encoder_Input i2c_package;

    int tempia = (int)(input[1]-'0');
    char tempa[6];
    memcpy(&tempa, &input[2], 6);
    i2c_package.M1_Multiplier = (float)tempia + (float)(atoi(tempa))/1000000;

    int tempib = (int)(input[8]-'0');
    char tempb[6];
    memcpy(&tempb, &input[9], 6);
    i2c_package.M2_Multiplier = (float)tempib + (float)(atoi(tempb))/1000000;

    int tempic = (int)(input[15]-'0');
    char tempc[6];
    memcpy(&tempc, &input[16], 6);
    i2c_package.M3_Multiplier = (float)tempic + (float)(atoi(tempc))/1000000;

    int tempid = (int)(input[22]-'0');
    char tempd[6];
    memcpy(&tempd, &input[23], 6);
    i2c_package.M4_Multiplier = (float)tempid + (float)(atoi(tempd))/1000000;

    return i2c_package;
}