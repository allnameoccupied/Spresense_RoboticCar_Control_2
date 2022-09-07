// Written by MAX (Created 07-09-2022)

/* Features :   Code for Spresense SubCore 2
                SubCore 2 -> FFT
*/
//--------------------------------------------------------//

#if (SUBCORE == 2)

//--------------------------------------------------------//

#include "Spresense_SubCore_2_TaskList.h"
// #include "C:\Users\Max\Documents\Workspace\Spresense_RoboticCar_Control_2\Spresense_RoboticCar_Control\Spresense_Pin_Mapping.h"
// #include "C:\Users\Max\Documents\Workspace\Spresense_RoboticCar_Control_2\Spresense_RoboticCar_Control\Spresense_Tool.h"
// #include "C:\Users\Max\Documents\Workspace\Spresense_RoboticCar_Control_2\Spresense_RoboticCar_Control\Spresense_Global_Var_Def.h"

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
    case C2_T0_FFT:{
        break;
    }
    case C2_T1_NO_PEAK:{
        // Just placeholder, C2_T1_NO_PEAK is for sending back to Main core
        break;
    }
    default:
        break;
    }
}

#endif