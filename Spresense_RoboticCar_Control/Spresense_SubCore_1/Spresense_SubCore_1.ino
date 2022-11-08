// Written by MAX (Created 31-08-2022)

/* Features :   Code for Spresense SubCore 1
                SubCore 1 -> General Tasks
*/
//--------------------------------------------------------//

#if (SUBCORE == 1)

//--------------------------------------------------------//

#include "Spresense_SubCore_1_TaskList.h"
// #include "C:/Users/Max/Documents/Workspace/Spresense_RoboticCar_Control_2/Spresense_RoboticCar_Control/Spresense_Include_List.h" // lab-pc
#include "C:/Max/Workspace/Spresense_RoboticCar_Control_2/Spresense_RoboticCar_Control/Spresense_Include_List.h"    // laptop

#include <Arduino.h>
#include <MP.h>

//--------------------------------------------------------//

// Functions Declaration

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
        digitalWrite(PIKAPIKA_LED, HIGH);
        while (millis() < endtime){};
        digitalWrite(PIKAPIKA_LED, LOW);
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