//Written by MAX (Created 21-06-2022)

//Funtions : PikaPika Interrupt Handler for Spresense

#include "Spresense_PikaPika_Interrupt.h"

#include "Spresense_Pin_Mapping.h"
#include "Spresense_Global_Var_Def.h"
#include "Spresense_Tool.h"

extern bool PikaPika_light_sensor [8];
extern ulong*** PikaPika_detected_timestamp;

void PikaPika_Int_Handler_0(){
    PikaPika_light_sensor[0] = true;
    delete PikaPika_detected_timestamp[0][0];
    PikaPika_detected_timestamp[0][0] = PikaPika_detected_timestamp[0][1];
    PikaPika_detected_timestamp[0][1] = PikaPika_detected_timestamp[0][2];
    PikaPika_detected_timestamp[0][2] = PikaPika_detected_timestamp[0][3];
    PikaPika_detected_timestamp[0][3] = PikaPika_detected_timestamp[0][4];
    PikaPika_detected_timestamp[0][4] = millis();
}
void PikaPika_Int_Handler_1(){
    PikaPika_light_sensor[1] = true;
    delete PikaPika_detected_timestamp[1][0];
    PikaPika_detected_timestamp[1][0] = PikaPika_detected_timestamp[1][1];
    PikaPika_detected_timestamp[1][1] = PikaPika_detected_timestamp[1][2];
    PikaPika_detected_timestamp[1][2] = PikaPika_detected_timestamp[1][3];
    PikaPika_detected_timestamp[1][3] = PikaPika_detected_timestamp[1][4];
    PikaPika_detected_timestamp[1][4] = millis();
}
void PikaPika_Int_Handler_2(){
    PikaPika_light_sensor[2] = true;
    delete PikaPika_detected_timestamp[2][0];
    PikaPika_detected_timestamp[2][0] = PikaPika_detected_timestamp[2][1];
    PikaPika_detected_timestamp[2][1] = PikaPika_detected_timestamp[2][2];
    PikaPika_detected_timestamp[2][2] = PikaPika_detected_timestamp[2][3];
    PikaPika_detected_timestamp[2][3] = PikaPika_detected_timestamp[2][4];
    PikaPika_detected_timestamp[2][4] = millis();
}
void PikaPika_Int_Handler_3(){
    PikaPika_light_sensor[3] = true;
    delete PikaPika_detected_timestamp[3][0];
    PikaPika_detected_timestamp[3][0] = PikaPika_detected_timestamp[3][1];
    PikaPika_detected_timestamp[3][1] = PikaPika_detected_timestamp[3][2];
    PikaPika_detected_timestamp[3][2] = PikaPika_detected_timestamp[3][3];
    PikaPika_detected_timestamp[3][3] = PikaPika_detected_timestamp[3][4];
    PikaPika_detected_timestamp[3][4] = millis();
}
void PikaPika_Int_Handler_4(){
    PikaPika_light_sensor[4] = true;
    delete PikaPika_detected_timestamp[4][0];
    PikaPika_detected_timestamp[4][0] = PikaPika_detected_timestamp[4][1];
    PikaPika_detected_timestamp[4][1] = PikaPika_detected_timestamp[4][2];
    PikaPika_detected_timestamp[4][2] = PikaPika_detected_timestamp[4][3];
    PikaPika_detected_timestamp[4][3] = PikaPika_detected_timestamp[4][4];
    PikaPika_detected_timestamp[4][4] = millis();
}
void PikaPika_Int_Handler_5(){
    PikaPika_light_sensor[5] = true;
    delete PikaPika_detected_timestamp[5][0];
    PikaPika_detected_timestamp[5][0] = PikaPika_detected_timestamp[5][1];
    PikaPika_detected_timestamp[5][1] = PikaPika_detected_timestamp[5][2];
    PikaPika_detected_timestamp[5][2] = PikaPika_detected_timestamp[5][3];
    PikaPika_detected_timestamp[5][3] = PikaPika_detected_timestamp[5][4];
    PikaPika_detected_timestamp[5][4] = millis();
}
void PikaPika_Int_Handler_6(){
    PikaPika_light_sensor[6] = true;
    delete PikaPika_detected_timestamp[6][0];
    PikaPika_detected_timestamp[6][0] = PikaPika_detected_timestamp[6][1];
    PikaPika_detected_timestamp[6][1] = PikaPika_detected_timestamp[6][2];
    PikaPika_detected_timestamp[6][2] = PikaPika_detected_timestamp[6][3];
    PikaPika_detected_timestamp[6][3] = PikaPika_detected_timestamp[6][4];
    PikaPika_detected_timestamp[6][4] = millis();
}
void PikaPika_Int_Handler_7(){
    PikaPika_light_sensor[7] = true;
    delete PikaPika_detected_timestamp[7][0];
    PikaPika_detected_timestamp[7][0] = PikaPika_detected_timestamp[7][1];
    PikaPika_detected_timestamp[7][1] = PikaPika_detected_timestamp[7][2];
    PikaPika_detected_timestamp[7][2] = PikaPika_detected_timestamp[7][3];
    PikaPika_detected_timestamp[7][3] = PikaPika_detected_timestamp[7][4];
    PikaPika_detected_timestamp[7][4] = millis();
}