// Written by MAX (Created 20-06-2022)

// Features : Spresense Initialization

//--------------------------------------------------------//

#include "Spresense_Init.h"
#include "Spresense_Include_List.h"

#include <VL53L1X.h>
#include <Wire.h>

// Init the 4 onboard LED
void Onboard_LED_Init(){
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

// Init I2C
void I2C_Init(){
    Wire.begin();
    Wire.setClock(TWI_FREQ_400KHZ);
}

// Init Distance Sensors pins
extern VL53L1X Dist_sensor [8];
void Dist_Sensor_Init(){

}

// Init PikaPika pins & variables
extern uint64_t*** PikaPika_detected_timestamp;
void PIKAPIKA_Init(){
    pinMode(LED_PIKA, OUTPUT);
    
    pinMode(LIGHT_PIKA_0, INPUT);
    pinMode(LIGHT_PIKA_1, INPUT);
    pinMode(LIGHT_PIKA_2, INPUT);
    pinMode(LIGHT_PIKA_3, INPUT);
    pinMode(LIGHT_PIKA_4, INPUT);
    pinMode(LIGHT_PIKA_5, INPUT);
    pinMode(LIGHT_PIKA_6, INPUT);
    pinMode(LIGHT_PIKA_7, INPUT);

    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_0), PikaPika_Int_Handler_0, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_1), PikaPika_Int_Handler_1, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_2), PikaPika_Int_Handler_2, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_3), PikaPika_Int_Handler_3, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_4), PikaPika_Int_Handler_4, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_5), PikaPika_Int_Handler_5, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_6), PikaPika_Int_Handler_6, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_7), PikaPika_Int_Handler_7, FALLING);

    for (int i = 0; i < 8; i++)
    {
        PikaPika_detected_timestamp[i] = new uint64_t* [5];
        for (int j = 0; j < 5; j++)
        {
            PikaPika_detected_timestamp[i][j] = new uint64_t (0);
        }
        
    }
    
}

// Init Serial Communication
void Serial_Init(){
    Serial.begin(DEFAULT_BAUD_RATE);
}

// Init Inside/Outside LED pins
void InOut_LED_Init(){
    pinMode(INSIDE_LED, OUTPUT);
    pinMode(OUTSIDE_LED, OUTPUT);
}

//--------------------------------------------------------//

void Finish_Init_LED_Flash(){
    digitalWrite(LED0, HIGH);
    delay(50);
    digitalWrite(LED1, HIGH);
    delay(50);
    digitalWrite(LED2, HIGH);
    delay(50);
    digitalWrite(LED3, HIGH);
    delay(500);

    digitalWrite(LED0, LOW);
    delay(50);
    digitalWrite(LED1, LOW);
    delay(50);
    digitalWrite(LED2, LOW);
    delay(50);
    digitalWrite(LED3, LOW);
    // delay(500);
}