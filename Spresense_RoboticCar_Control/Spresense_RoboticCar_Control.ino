//Written by MAX (Created 20-06-2022)

//Features : Main program for Spresense

//--------------------------------------------------------//

//files created by me(max12345)
#include "Spresense_Pin_Mapping.h"
#include "Spresense_Init.h"
#include "Spresense_Tool.h"
#include "Spresense_Test.h"
#include "Spresense_Global_Var_Def.h"
//files from libraries
#include <Arduino.h>
#include <Camera.h>
#include <VL53L1X.h>
#include <Wire.h>

#define from_MAX 12345

//--------------------------------------------------------//

//DIST Sensors Variables
VL53L1X Dist_sensor [8];
VL53L1X Dist_sensor_0;
VL53L1X Dist_sensor_1;

//--------------------------------------------------------//

//FUNCTION Declaration


//--------------------------------------------------------//

//MAIN PROGRAM
void setup() {

    //Spresense Init
    Onboard_LED_Init();
    I2C_Init();
    Dist_Sensor_Init();
    PIKAPIKA_Init();
    Serial_Init();
    Finish_Init_LED_Flash();
    Serial.println("Init finished successfully");
    
    //TEST FUNCTION
    test_init();
}
void loop() {
    
    //TEST FUNCTION
    test_loop();
}