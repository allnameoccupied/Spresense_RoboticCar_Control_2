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
uint32_t encoder_tick_count[4] = {0,0,0,0};
uint32_t encoder_last_access_tick[4] = {0,0,0,0};
uint64_t encoder_last_access_time[4] = {0,0,0,0};

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
    MPLog("subcore 3 inited");

    //Pin Init + Attach Interrupt
    pinMode(M1_HALL_PIN, INPUT);
    pinMode(M2_HALL_PIN, INPUT);
    pinMode(M3_HALL_PIN, INPUT);
    pinMode(M4_HALL_PIN, INPUT);

    //TODO attachInterrupt not allowed in sub core ?
    attachInterrupt(digitalPinToInterrupt(M1_HALL_PIN), M1_Int_Handler, FALLING);
    attachInterrupt(digitalPinToInterrupt(M2_HALL_PIN), M2_Int_Handler, FALLING);
    attachInterrupt(digitalPinToInterrupt(M3_HALL_PIN), M3_Int_Handler, FALLING);
    attachInterrupt(digitalPinToInterrupt(M4_HALL_PIN), M4_Int_Handler, FALLING);
}
void loop(void){
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