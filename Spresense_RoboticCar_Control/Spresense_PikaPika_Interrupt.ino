// Written by MAX (Created 21-06-2022)

// Features : PikaPika Interrupt Handler for Spresense

//--------------------------------------------------------//

#include "Spresense_PikaPika_Interrupt.h"
#include "Spresense_Include_List.h"

uint64_t PikaPika_detected_timestamp[PIKAPIKA_SENSOR_COUNT] = {0,0,0,0,0,0,0,0};

bool ison=false;
void blink_demo(){
    ison = 1-ison;
    digitalWrite(INSIDE_LED, ison);
}

void PikaPika_Int_Handler_0(){
    uint64_t now_millis = millis();
    if (now_millis - PikaPika_detected_timestamp[0] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[0] = mod_varphi - PI;
        PikaPika_light_sensor_life[0] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        blink_demo();
    }
}
void PikaPika_Int_Handler_1(){
    uint64_t now_millis = millis();
    if (now_millis - PikaPika_detected_timestamp[1] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[1] = mod_varphi - PI;
        PikaPika_light_sensor_life[1] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        blink_demo();
    }
}
void PikaPika_Int_Handler_2(){
    uint64_t now_millis = millis();
    if (now_millis - PikaPika_detected_timestamp[2] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[2] = mod_varphi - PI;
        PikaPika_light_sensor_life[2] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        blink_demo();
    }
}
void PikaPika_Int_Handler_3(){
    uint64_t now_millis = millis();
    if (now_millis - PikaPika_detected_timestamp[3] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[3] = mod_varphi - PI;
        PikaPika_light_sensor_life[3] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        blink_demo();
    }
}
void PikaPika_Int_Handler_4(){
    uint64_t now_millis = millis();
    if (now_millis - PikaPika_detected_timestamp[4] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[4] = mod_varphi - PI;
        PikaPika_light_sensor_life[4] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        blink_demo();
    }
}
void PikaPika_Int_Handler_5(){
    uint64_t now_millis = millis();
    if (now_millis - PikaPika_detected_timestamp[5] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[5] = mod_varphi - PI;
        PikaPika_light_sensor_life[5] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        blink_demo();
    }
}
void PikaPika_Int_Handler_6(){
    uint64_t now_millis = millis();
    if (now_millis - PikaPika_detected_timestamp[6] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[6] = mod_varphi - PI;
        PikaPika_light_sensor_life[6] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        blink_demo();
    }
}
void PikaPika_Int_Handler_7(){
    uint64_t now_millis = millis();
    if (now_millis - PikaPika_detected_timestamp[7] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[7] = mod_varphi - PI;
        PikaPika_light_sensor_life[7] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        blink_demo();
    }
}

/* Interrupt Functions for TESTING
extern bool PikaPika_light_sensor [8];
extern uint64_t*** PikaPika_detected_timestamp;

void PikaPika_Int_Handler_0(){

    uint64_t now_millis = millis();

    if (now_millis - *PikaPika_detected_timestamp[0][4] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        PikaPika_light_sensor[0] = true;
        delete PikaPika_detected_timestamp[0][0];
        PikaPika_detected_timestamp[0][0] = PikaPika_detected_timestamp[0][1];
        PikaPika_detected_timestamp[0][1] = PikaPika_detected_timestamp[0][2];
        PikaPika_detected_timestamp[0][2] = PikaPika_detected_timestamp[0][3];
        PikaPika_detected_timestamp[0][3] = PikaPika_detected_timestamp[0][4];
        PikaPika_detected_timestamp[0][4] = new uint64_t (now_millis);
    }
}
void PikaPika_Int_Handler_1(){

    uint64_t now_millis = millis();

    if (now_millis - *PikaPika_detected_timestamp[1][4] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        PikaPika_light_sensor[1] = true;
        delete PikaPika_detected_timestamp[1][0];
        PikaPika_detected_timestamp[1][0] = PikaPika_detected_timestamp[1][1];
        PikaPika_detected_timestamp[1][1] = PikaPika_detected_timestamp[1][2];
        PikaPika_detected_timestamp[1][2] = PikaPika_detected_timestamp[1][3];
        PikaPika_detected_timestamp[1][3] = PikaPika_detected_timestamp[1][4];
        PikaPika_detected_timestamp[1][4] = new uint64_t (now_millis);
    }
}
void PikaPika_Int_Handler_2(){

    uint64_t now_millis = millis();

    if (now_millis - *PikaPika_detected_timestamp[2][4] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        PikaPika_light_sensor[2] = true;
        delete PikaPika_detected_timestamp[2][0];
        PikaPika_detected_timestamp[2][0] = PikaPika_detected_timestamp[2][1];
        PikaPika_detected_timestamp[2][1] = PikaPika_detected_timestamp[2][2];
        PikaPika_detected_timestamp[2][2] = PikaPika_detected_timestamp[2][3];
        PikaPika_detected_timestamp[2][3] = PikaPika_detected_timestamp[2][4];
        PikaPika_detected_timestamp[2][4] = new uint64_t (now_millis);
    }
}
void PikaPika_Int_Handler_3(){

    uint64_t now_millis = millis();

    if (now_millis - *PikaPika_detected_timestamp[3][4] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        PikaPika_light_sensor[3] = true;
        delete PikaPika_detected_timestamp[3][0];
        PikaPika_detected_timestamp[3][0] = PikaPika_detected_timestamp[3][1];
        PikaPika_detected_timestamp[3][1] = PikaPika_detected_timestamp[3][2];
        PikaPika_detected_timestamp[3][2] = PikaPika_detected_timestamp[3][3];
        PikaPika_detected_timestamp[3][3] = PikaPika_detected_timestamp[3][4];
        PikaPika_detected_timestamp[3][4] = new uint64_t (now_millis);
    }
}
void PikaPika_Int_Handler_4(){
    
    uint64_t now_millis = millis();

    if (now_millis - *PikaPika_detected_timestamp[4][4] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        PikaPika_light_sensor[4] = true;
        delete PikaPika_detected_timestamp[4][0];
        PikaPika_detected_timestamp[4][0] = PikaPika_detected_timestamp[4][1];
        PikaPika_detected_timestamp[4][1] = PikaPika_detected_timestamp[4][2];
        PikaPika_detected_timestamp[4][2] = PikaPika_detected_timestamp[4][3];
        PikaPika_detected_timestamp[4][3] = PikaPika_detected_timestamp[4][4];
        PikaPika_detected_timestamp[4][4] = new uint64_t (now_millis);
    }
}
void PikaPika_Int_Handler_5(){

    uint64_t now_millis = millis();

    if (now_millis - *PikaPika_detected_timestamp[5][4] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        PikaPika_light_sensor[5] = true;
        delete PikaPika_detected_timestamp[5][0];
        PikaPika_detected_timestamp[5][0] = PikaPika_detected_timestamp[5][1];
        PikaPika_detected_timestamp[5][1] = PikaPika_detected_timestamp[5][2];
        PikaPika_detected_timestamp[5][2] = PikaPika_detected_timestamp[5][3];
        PikaPika_detected_timestamp[5][3] = PikaPika_detected_timestamp[5][4];
        PikaPika_detected_timestamp[5][4] = new uint64_t (now_millis);
    }
}
void PikaPika_Int_Handler_6(){

    uint64_t now_millis = millis();

    if (now_millis - *PikaPika_detected_timestamp[6][4] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        PikaPika_light_sensor[6] = true;
        delete PikaPika_detected_timestamp[6][0];
        PikaPika_detected_timestamp[6][0] = PikaPika_detected_timestamp[6][1];
        PikaPika_detected_timestamp[6][1] = PikaPika_detected_timestamp[6][2];
        PikaPika_detected_timestamp[6][2] = PikaPika_detected_timestamp[6][3];
        PikaPika_detected_timestamp[6][3] = PikaPika_detected_timestamp[6][4];
        PikaPika_detected_timestamp[6][4] = new uint64_t (now_millis);
    }
}
void PikaPika_Int_Handler_7(){
    
    uint64_t now_millis = millis();

    if (now_millis - *PikaPika_detected_timestamp[7][4] > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        PikaPika_light_sensor[7] = true;
        delete PikaPika_detected_timestamp[7][0];
        PikaPika_detected_timestamp[7][0] = PikaPika_detected_timestamp[7][1];
        PikaPika_detected_timestamp[7][1] = PikaPika_detected_timestamp[7][2];
        PikaPika_detected_timestamp[7][2] = PikaPika_detected_timestamp[7][3];
        PikaPika_detected_timestamp[7][3] = PikaPika_detected_timestamp[7][4];
        PikaPika_detected_timestamp[7][4] = new uint64_t (now_millis);
    }
}
*/
