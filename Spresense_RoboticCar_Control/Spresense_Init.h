// Written by MAX (Created 20-06-2022)

// Features : Spresense Initialization

//--------------------------------------------------------//

#ifndef SPRESENSE_INIT_H
#define SPRESENSE_INIT_H

// Init the 4 onboard LED
void Onboard_LED_Init();

// Init I2C
void I2C_Init();

// Init Distance Sensors pins
void Dist_Sensor_Init();

// Init PikaPika pins & variables
void PIKAPIKA_Init();

// Init Serial Communication
void Serial_Init();

// Init Inside/Outside LED pins
void InOut_LED_Init();

//TODO need init for fft ?
//TODO need init for multi core ?

//--------------------------------------------------------//

void Finish_Init_LED_Flash();

#endif