//Written by MAX (Created 21-06-2022)

//Funtions : PikaPika Interrupt Handler for Spresense

#include "Spresense_PikaPika_Interrupt.h"

#include "Spresense_Pin_Mapping.h"
#include "Spresense_Global_Var_Def.h"
#include "Spresense_Tool.h"

void PikaPika_Int_Handler_0(){
    PikaPika_light_sensor[0] = true;
}
void PikaPika_Int_Handler_1(){
    PikaPika_light_sensor[1] = true;
}
void PikaPika_Int_Handler_2(){
    PikaPika_light_sensor[2] = true;
}
void PikaPika_Int_Handler_3(){
    PikaPika_light_sensor[3] = true;
}
void PikaPika_Int_Handler_4(){
    PikaPika_light_sensor[4] = true;
}
void PikaPika_Int_Handler_5(){
    PikaPika_light_sensor[5] = true;
}
void PikaPika_Int_Handler_6(){
    PikaPika_light_sensor[6] = true;
}
void PikaPika_Int_Handler_7(){
    PikaPika_light_sensor[7] = true;
}