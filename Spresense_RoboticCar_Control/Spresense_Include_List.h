// Written by MAX (Created 07-09-2022)

// Features : List of all general header files for #include

//--------------------------------------------------------//

#ifndef SPRESENSE_INCLUDE_LIST_H
#define SPRESENSE_INCLUDE_LIST_H

#include <Arduino.h>
#include <MP.h>
#include <Wire.h>
#include <VL53L1X.h>

#include "Spresense_Global_Var_Def.h"
#include "Spresense_Pin_Mapping.h"
#include "Spresense_FFT_Param.h"

#include "Spresense_Init.h"
#include "Spresense_PikaPika_Interrupt.h"
#if (SUBCORE == 2)
    #include "Spresense_SubCore_2/Spresense_Sub2_FFT_Functions.h"
#endif

#include "Spresense_SubCore_1/Spresense_SubCore_1_TaskList.h"
#include "Spresense_SubCore_2/Spresense_SubCore_2_TaskList.h"

#endif