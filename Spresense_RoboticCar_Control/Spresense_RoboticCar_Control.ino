// Written by MAX (Created 20-06-2022)

// Features : Main program for Spresense

//--------------------------------------------------------//

#define from_MAX 12345

//--------------------------------------------------------//

// Files created by me(max12345)
#include "Spresense_Include_List.h"
#include "Spresense_Test.h"
// Files from libraries
#include <Arduino.h>
#include <MP.h>

#include <Camera.h>
#include <VL53L1X.h>
#include <Wire.h>

//--------------------------------------------------------//

// Global Variables

// -> DIST Sensors Variables
VL53L1X Dist_sensor [8];

// -> PikaPika Variables
bool PikaPika_light_sensor [8] = {false, false, false, false, false, false, false, false};
uint64_t*** PikaPika_detected_timestamp = new uint64_t** [8];

//--------------------------------------------------------//

// Functions Declaration

//--------------------------------------------------------//

// For TESTING

//--------------------------------------------------------//

// MAIN PROGRAM
void setup() {

    // Spresense Init
    Onboard_LED_Init();
    I2C_Init();
    Dist_Sensor_Init();
    PIKAPIKA_Init();
    Serial_Init();
    InOut_LED_Init();
    Finish_Init_LED_Flash();
    Serial.println("Init finished successfully");
    
    // TEST FUNCTION
    test_init();
}
void loop() {
    
    // TEST FUNCTION
    test_loop();
}