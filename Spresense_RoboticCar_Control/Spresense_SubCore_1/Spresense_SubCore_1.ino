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
#include <StaticThreadController.h>
#include <Thread.h>
#include <ThreadController.h>

//--------------------------------------------------------//

//FUNCTION Declaration
void Core_Communication_Test(int8_t msgid, uint32_t msgdata);
void TurnON_PikaPika_LED();
void TurnON_Inside_LED();
void TurnON_Outside_LED();

//--------------------------------------------------------//

uint32_t msgdata_Array[4];

//--------------------------------------------------------//

void setup(void){
    MP.begin();
}

void loop(void){
    int ret;
    int8_t msgid;
    uint32_t msgdata;

    MP.Recv(&msgid, &msgdata);

    switch (msgid)
    {
    case C1_T0_COMMU_TEST:
        Core_Communication_Test(msgid, msgdata);
        break;
    
    case C1_T1_PIKAPIKA_LED:{
        msgdata_Array[C1_T1_PIKAPIKA_LED] = msgdata;
        Thread thread = Thread();
        thread.onRun(TurnON_PikaPika_LED);
        thread.run();
        break;
    }

    case C1_T2_INSIDE_LED:{
        msgdata_Array[C1_T2_INSIDE_LED] = msgdata;
        Thread thread = Thread();
        thread.onRun(TurnON_Inside_LED);
        thread.run();
        break;
    }

    case C1_T3_OUTSIDE_LED:{
        msgdata_Array[C1_T3_OUTSIDE_LED] = msgdata;
        Thread thread = Thread();
        thread.onRun(TurnON_Outside_LED);
        thread.run();
        break;
    }

    default:
        break;
    }
}

void Core_Communication_Test(int8_t msgid, uint32_t msgdata){
    MP.Send(msgid, msgdata+100);
}

void TurnON_PikaPika_LED(){
    digitalWrite(LED_PIKA, HIGH);
    delay(msgdata_Array[C1_T1_PIKAPIKA_LED]);
    digitalWrite(LED_PIKA, LOW);
}

void TurnON_Inside_LED(){
    digitalWrite(INSIDE_LED, HIGH);
    delay(msgdata_Array[C1_T2_INSIDE_LED]);
    digitalWrite(INSIDE_LED, LOW);
}

void TurnON_Outside_LED(){
    digitalWrite(OUTSIDE_LED, HIGH);
    delay(msgdata_Array[C1_T3_OUTSIDE_LED]);
    digitalWrite(INSIDE_LED, LOW);
}

#endif