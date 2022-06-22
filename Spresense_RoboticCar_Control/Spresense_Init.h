//Written by MAX (Created 20-06-2022)

//Funtions : Spresense Initialization

#ifndef SPRESENSE_INIT_H
#define SPRESENSE_INIT_H

#include <Arduino.h>
#include <VL53L1X.h>

//init the 4 onboard LED
void Onboard_LED_Init();

//init I2C pins & I2C
void I2C_Init();

//init Dist sensors pins
extern VL53L1X Dist_sensor [8];
void Dist_Sensor_Init();

//init PikaPika pins
void PIKAPIKA_Init();

//init Serial Communication
void Serial_Init();

//--------------------------------------------------------//

void Finish_Init_LED_Flash();

#endif