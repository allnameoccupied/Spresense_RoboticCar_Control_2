//Written by MAX (Created 31-08-2022)

//Features : Code for Spresense SubCore 1 -> General

//--------------------------------------------------------//

#if (SUBCORE == 1)

//--------------------------------------------------------//

#include "Spresense_SubCore_1_TaskList.h"
#include "C:\Users\Max\Documents\Workspace\Spresense_RoboticCar_Control_2\Spresense_RoboticCar_Control\Spresense_Pin_Mapping.h"
#include "C:\Users\Max\Documents\Workspace\Spresense_RoboticCar_Control_2\Spresense_RoboticCar_Control\Spresense_Tool.h"
#include "C:\Users\Max\Documents\Workspace\Spresense_RoboticCar_Control_2\Spresense_RoboticCar_Control\Spresense_Global_Var_Def.h"

#include <Arduino.h>
#include <MP.h>

//--------------------------------------------------------//

//FUNCTION Declaration

//--------------------------------------------------------//

void setup(void){
    MP.begin();
}

void loop(void){
    int8_t msgid;
    uint32_t msgdata;

    MP.Recv(&msgid, &msgdata);

    switch (msgid)
    {
    case C1_T0_COMMU_TEST:
        MP.Send(msgid, msgdata+100);
        break;
    case C1_T1_PIKAPIKA_LED:{
        uint64_t endtime = millis()+(uint64_t)msgdata;
        digitalWrite(LED_PIKA, HIGH);
        while (millis() < endtime){};
        digitalWrite(LED_PIKA, LOW);
        break;
    }
    case C1_T2_INSIDE_LED:{
        digitalWrite(INSIDE_LED, HIGH);
        uint64_t endtime = millis()+(uint64_t)msgdata;
        while (millis() < endtime){};
        digitalWrite(INSIDE_LED, LOW);
        break;
    }
    case C1_T3_OUTSIDE_LED:{
        digitalWrite(OUTSIDE_LED, HIGH);
        uint64_t endtime = millis()+(uint64_t)msgdata;
        while (millis() < endtime){};
        digitalWrite(OUTSIDE_LED, LOW);
        break;
    }
    default:
        break;
    }
}

#endif