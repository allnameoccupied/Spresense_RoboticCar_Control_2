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
    if ((now_millis - PikaPika_detected_timestamp[0]) > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[0] = mod_varphi - PI;
        PikaPika_light_sensor_life[0] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        PikaPika_detected_timestamp[0] = now_millis;
        // blink_demo();
    }
}
void PikaPika_Int_Handler_1(){
    uint64_t now_millis = millis();
    if ((now_millis - PikaPika_detected_timestamp[1]) > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[1] = mod_varphi - PI;
        PikaPika_light_sensor_life[1] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        PikaPika_detected_timestamp[1] = now_millis;
        // blink_demo();
    }
}
void PikaPika_Int_Handler_2(){
    uint64_t now_millis = millis();
    if ((now_millis - PikaPika_detected_timestamp[2]) > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[2] = mod_varphi - PI;
        PikaPika_light_sensor_life[2] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        PikaPika_detected_timestamp[2] = now_millis;
        // blink_demo();
    }
}
void PikaPika_Int_Handler_3(){
    uint64_t now_millis = millis();
    if ((now_millis - PikaPika_detected_timestamp[3]) > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[3] = mod_varphi - PI;
        PikaPika_light_sensor_life[3] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        PikaPika_detected_timestamp[3] = now_millis;
        // blink_demo();
    }
}
void PikaPika_Int_Handler_4(){
    uint64_t now_millis = millis();
    if ((now_millis - PikaPika_detected_timestamp[4]) > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[4] = mod_varphi - PI;
        PikaPika_light_sensor_life[4] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        PikaPika_detected_timestamp[4] = now_millis;
        // blink_demo();
    }
}
void PikaPika_Int_Handler_5(){
    uint64_t now_millis = millis();
    if ((now_millis - PikaPika_detected_timestamp[5]) > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[5] = mod_varphi - PI;
        PikaPika_light_sensor_life[5] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        PikaPika_detected_timestamp[5] = now_millis;
        // blink_demo();
    }
}
void PikaPika_Int_Handler_6(){
    uint64_t now_millis = millis();
    if ((now_millis - PikaPika_detected_timestamp[6]) > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[6] = mod_varphi - PI;
        PikaPika_light_sensor_life[6] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        PikaPika_detected_timestamp[6] = now_millis;
        // blink_demo();
    }
}
void PikaPika_Int_Handler_7(){
    uint64_t now_millis = millis();
    if ((now_millis - PikaPika_detected_timestamp[7]) > PIKAPIKA_MIN_INTERRUPT_INTERVAL)
    {
        dphi[7] = mod_varphi - PI;
        PikaPika_light_sensor_life[7] = PIKAPIKA_LIGHT_SENSOR_LIFETIME;
        PikaPika_detected_timestamp[7] = now_millis;
        // blink_demo();
    }
}
