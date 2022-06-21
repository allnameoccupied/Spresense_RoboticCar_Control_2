//Written by MAX (Created 20-06-2022)

//Funtions : Write test functions here, 
//              so main program will not be messy
//                  (For Spresense)

// *** ONLY CASE WHICH FUNCTIONS ARE DEFINED IN HEADER *** 

#ifndef SPRESENSE_TEST_H
#define SPRESENSE_TEST_H

#include "Spresense_Tool.h"
#include "Spresense_Global_Var_Def.h"
#include "Spresense_Pin_Mapping.h"

#include <VL53L1X.h>
#include <Wire.h>
#include <string>

//--------------------------------------------------------//

//EXTERN of Variables
extern VL53L1X Dist_sensor [8];

//--------------------------------------------------------//

//EXTERN of FUNCTION Declaration

//--------------------------------------------------------//

void test_init(){

    // for (int i = 0; i < 2; i++)
    // {
    //     char buf[32];
    //     int ret = snprintf(buf, sizeof buf, "%f", 69000.420);

    //     Serial.println("now send la");
    //     Wire.beginTransmission(NUCLEO_I2C_ADDR);
    //     Wire.write(buf);
    //     Wire.endTransmission();
    //     delay(1000);
    // }

    pinMode(DIST_XSHUT_1, OUTPUT);
    digitalWrite(DIST_XSHUT_1, LOW);

    pinMode(DIST_XSHUT_1, INPUT);
    delay(10);

    Dist_sensor[0].setTimeout(500);
    if (!Dist_sensor[0].init())
    {
      Serial.print("Failed to detect and initialize sensor ");
      while (1);
    }

    Dist_sensor[0].setAddress(DIST_SENSOR_1_I2C_ADDR);

    Dist_sensor[0].startContinuous(50);
    
}
void test_loop(){
    Serial.print(Dist_sensor[0].read());
    if (Dist_sensor[0].timeoutOccurred()) { Serial.print(" TIMEOUT"); }
    Serial.print('\t');
}

#endif