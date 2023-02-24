// Written by MAX (Created 05-01-2023)

/* Features :   Code for Spresense SubCore 3
                SubCore 3 -> Motor Encoders Feedback Tracking
*/
//--------------------------------------------------------//

#if (SUBCORE == 3)

//--------------------------------------------------------//

#include "Spresense_SubCore_3_TaskList.h"
#include "C:/Users/Max/Documents/Workspace/Spresense_RoboticCar_Control_2/Spresense_RoboticCar_Control/Spresense_Include_List.h" // lab-pc

//--------------------------------------------------------//

// Variables Declaration
uint32_t    encoder_tick_count[4] = {0,0,0,0};
uint32_t    encoder_last_access_tick[4] = {0,0,0,0};
uint64_t    encoder_last_access_time[4] = {0,0,0,0};
float       encoder_mul[4] = {1.0, 1.0, 1.0, 1.0};

// Functions Declaration
void Interrupt_Tick_Update(uint8_t motor_num);
void M1_Int_Handler();
void M2_Int_Handler();
void M3_Int_Handler();
void M4_Int_Handler();

// Speed in tick/s
float get_Speed_Since_Last_Access(uint8_t motor_num);

//--------------------------------------------------------//

void setup(void){
    MP.begin();

    Wire.begin();
    Wire.setClock(TWI_FREQ_400KHZ);
    
    //Pin Init + Attach Interrupt
    pinMode(M1_HALL_PIN, INPUT);
    pinMode(M2_HALL_PIN, INPUT);
    pinMode(M3_HALL_PIN, INPUT);
    pinMode(M4_HALL_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(M1_HALL_PIN), M1_Int_Handler, FALLING);
    attachInterrupt(digitalPinToInterrupt(M2_HALL_PIN), M2_Int_Handler, FALLING);
    attachInterrupt(digitalPinToInterrupt(M3_HALL_PIN), M3_Int_Handler, FALLING);
    attachInterrupt(digitalPinToInterrupt(M4_HALL_PIN), M4_Int_Handler, FALLING);

    delay(1000);
    
    // MPLog("Subcore 3 inited \n");
}
void loop(void){

    delay(500);

    MPLog("%ld\n", encoder_tick_count[0]);
    MPLog("%ld\n", encoder_tick_count[1]);
    MPLog("%ld\n", encoder_tick_count[2]);
    MPLog("%ld\n", encoder_tick_count[3]);
    // MPLog("\n");

    uint8_t slowest = 10;  

    if (((encoder_tick_count[0]+3)<encoder_tick_count[1]) && ((encoder_tick_count[0]+3)<encoder_tick_count[2]) && ((encoder_tick_count[0]+3)<encoder_tick_count[3]))
    {
        // slowest = 0;
        float m2_mul_temp = 1.0;
        float m3_mul_temp = 1.0;
        float m4_mul_temp = 1.0;

        m2_mul_temp = 1.0 - ((float)encoder_tick_count[1]-(float)encoder_tick_count[0])/(float)encoder_tick_count[1]/2.0;
        m3_mul_temp = 1.0 - ((float)encoder_tick_count[2]-(float)encoder_tick_count[0])/(float)encoder_tick_count[2]/2.0;
        m4_mul_temp = 1.0 - ((float)encoder_tick_count[3]-(float)encoder_tick_count[0])/(float)encoder_tick_count[3]/2.0;

        encoder_mul[1] = encoder_mul[1] * m2_mul_temp;
        encoder_mul[2] = encoder_mul[2] * m3_mul_temp;
        encoder_mul[3] = encoder_mul[3] * m4_mul_temp;
    }
    if (((encoder_tick_count[1]+3)<encoder_tick_count[0]) && ((encoder_tick_count[1]+3)<encoder_tick_count[2]) && ((encoder_tick_count[1]+3)<encoder_tick_count[3]))
    {
        // slowest = 1;
        float m1_mul_temp = 1.0;
        float m3_mul_temp = 1.0;
        float m4_mul_temp = 1.0;

        m1_mul_temp = 1.0 - ((float)encoder_tick_count[0]-(float)encoder_tick_count[1])/(float)encoder_tick_count[0]/2.0;
        m3_mul_temp = 1.0 - ((float)encoder_tick_count[2]-(float)encoder_tick_count[1])/(float)encoder_tick_count[2]/2.0;
        m4_mul_temp = 1.0 - ((float)encoder_tick_count[3]-(float)encoder_tick_count[1])/(float)encoder_tick_count[3]/2.0;

        encoder_mul[0] = encoder_mul[0] * m1_mul_temp;
        encoder_mul[2] = encoder_mul[2] * m3_mul_temp;
        encoder_mul[3] = encoder_mul[3] * m4_mul_temp;
    }
    if (((encoder_tick_count[2]+3)<encoder_tick_count[0]) && ((encoder_tick_count[2]+3)<encoder_tick_count[1]) && ((encoder_tick_count[2]+3)<encoder_tick_count[3]))
    {
        // slowest = 2;
        float m1_mul_temp = 1.0;
        float m2_mul_temp = 1.0;
        float m4_mul_temp = 1.0;

        m1_mul_temp = 1.0 - ((float)encoder_tick_count[0]-(float)encoder_tick_count[2])/(float)encoder_tick_count[0]/2.0;
        m2_mul_temp = 1.0 - ((float)encoder_tick_count[1]-(float)encoder_tick_count[2])/(float)encoder_tick_count[1]/2.0;
        m4_mul_temp = 1.0 - ((float)encoder_tick_count[3]-(float)encoder_tick_count[2])/(float)encoder_tick_count[3]/2.0;

        encoder_mul[0] = encoder_mul[0] * m1_mul_temp;
        encoder_mul[1] = encoder_mul[1] * m2_mul_temp;
        encoder_mul[3] = encoder_mul[3] * m4_mul_temp;
    }
    if (((encoder_tick_count[3]+3)<encoder_tick_count[0]) && ((encoder_tick_count[3]+3)<encoder_tick_count[1]) && ((encoder_tick_count[3]+3)<encoder_tick_count[2]))
    {
        // slowest = 3;
        float m1_mul_temp = 1.0;
        float m2_mul_temp = 1.0;
        float m3_mul_temp = 1.0;

        m1_mul_temp = 1.0 - ((float)encoder_tick_count[0]-(float)encoder_tick_count[3])/(float)encoder_tick_count[0]/2.0;
        m2_mul_temp = 1.0 - ((float)encoder_tick_count[1]-(float)encoder_tick_count[3])/(float)encoder_tick_count[1]/2.0;
        m3_mul_temp = 1.0 - ((float)encoder_tick_count[2]-(float)encoder_tick_count[3])/(float)encoder_tick_count[2]/2.0;

        encoder_mul[0] = encoder_mul[0] * m1_mul_temp;
        encoder_mul[1] = encoder_mul[1] * m2_mul_temp;
        encoder_mul[2] = encoder_mul[2] * m3_mul_temp;
    }

    MPLog("%f\n", encoder_mul[0]);
    MPLog("%f\n", encoder_mul[1]);
    MPLog("%f\n", encoder_mul[2]);
    MPLog("%f\n", encoder_mul[3]);
    MPLog("\n");
    
    encoder_tick_count[0]=0;
    encoder_tick_count[1]=0;
    encoder_tick_count[2]=0;
    encoder_tick_count[3]=0;

    I2C_Write_Encoder(encoder_mul[0],encoder_mul[1],encoder_mul[2],encoder_mul[3]);

    // I2C_Write_PWM_DIR(Motor_TL, , 1);
    // I2C_Write_PWM_DIR(Motor_TR, , 1);
    // I2C_Write_PWM_DIR(Motor_BL, , 1);
    // I2C_Write_PWM_DIR(Motor_BR, , 1);

    // int8_t msgid;
    // uint32_t msgdata;

    // MP.Recv(&msgid, &msgdata);

    // switch (msgid)
    // {
    // case xxx:{
    // }
    // default:
    //     break;
    // }
}

//--------------------------------------------------------//

float get_Speed_Since_Last_Access(uint8_t motor_num){
    
    float speed = 0.0;
    uint32_t curr_tick = encoder_tick_count[motor_num];
    uint64_t curr_time = millis();
    
    speed = (curr_tick - encoder_last_access_tick[motor_num]) / (curr_time - encoder_last_access_time[motor_num]) * 1000;

    encoder_last_access_tick[motor_num] = curr_tick;
    encoder_last_access_time[motor_num] = curr_time;

    return speed;
}

void Interrupt_Tick_Update(uint8_t motor_num){
    encoder_tick_count[motor_num]++;
}
void M1_Int_Handler(){Interrupt_Tick_Update(0);}
void M2_Int_Handler(){Interrupt_Tick_Update(1);}
void M3_Int_Handler(){Interrupt_Tick_Update(2);}
void M4_Int_Handler(){Interrupt_Tick_Update(3);}

#endif