//Written by MAX (Created 20-06-2022)

//Funtions : Common Functions for Spresense

#include "Spresense_Tool.h"

#include "Spresense_Global_Var_Def.h"

//Easy LED ON/OFF
void LED_ON(uint8_t LED_index){
    switch (LED_index)
    {
    case 0:
        digitalWrite(LED0, true);
        break;

    case 1:
        digitalWrite(LED1, true);
        break;

    case 2:
        digitalWrite(LED2, true);
        break;

    case 3:
        digitalWrite(LED3, true);
        break;
    
    default:
        break;
    }
}
void LED_OFF(uint8_t LED_index){
    switch (LED_index)
    {
    case 0:
        digitalWrite(LED0, false);
        break;

    case 1:
        digitalWrite(LED1, false);
        break;

    case 2:
        digitalWrite(LED2, false);
        break;

    case 3:
        digitalWrite(LED3, false);
        break;
    
    default:
        break;
    }
}