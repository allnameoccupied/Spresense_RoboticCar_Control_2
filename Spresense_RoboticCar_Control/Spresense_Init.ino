//Written by MAX (Created 20-06-2022)

//Funtions : Spresense Initialization

#include "Spresense_Init.h"

#include "Spresense_Pin_Mapping.h"
#include "Spresense_Global_Var_Def.h"
#include "Spresense_Tool.h"
#include "Spresense_PikaPika_Interrupt.h"
#include <Wire.h>

//init the 4 onboard LED
void Onboard_LED_Init(){
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

//init I2C pins & I2C
void I2C_Init(){
    Wire.begin();
    Wire.setClock(TWI_FREQ_400KHZ);
}

//init Dist sensors pins
void Dist_Sensor_Init(){

}

//init PikaPika pins
void PIKAPIKA_Init(){
    pinMode(LED_PIKA, OUTPUT);
    
    pinMode(LIGHT_PIKA_0, INPUT_PULLDOWN);
    pinMode(LIGHT_PIKA_1, INPUT_PULLDOWN);
    pinMode(LIGHT_PIKA_2, INPUT_PULLDOWN);
    pinMode(LIGHT_PIKA_3, INPUT_PULLDOWN);
    pinMode(LIGHT_PIKA_4, INPUT_PULLDOWN);
    pinMode(LIGHT_PIKA_5, INPUT_PULLDOWN);
    pinMode(LIGHT_PIKA_6, INPUT_PULLDOWN);
    pinMode(LIGHT_PIKA_7, INPUT_PULLDOWN);

    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_0), PikaPika_Int_Handler_0, RISING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_1), PikaPika_Int_Handler_1, RISING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_2), PikaPika_Int_Handler_2, RISING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_3), PikaPika_Int_Handler_3, RISING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_4), PikaPika_Int_Handler_4, RISING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_5), PikaPika_Int_Handler_5, RISING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_6), PikaPika_Int_Handler_6, RISING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_PIKA_7), PikaPika_Int_Handler_7, RISING);
}

//init Serial Communication
void Serial_Init(){
    Serial.begin(DEFAULT_BAUD_RATE);
}

//--------------------------------------------------------//

void Finish_Init_LED_Flash(){
    digitalWrite(LED0, HIGH);
    delay(100);
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED2, HIGH);
    delay(100);
    digitalWrite(LED3, HIGH);
    delay(1000);

    digitalWrite(LED0, LOW);
    delay(100);
    digitalWrite(LED1, LOW);
    delay(100);
    digitalWrite(LED2, LOW);
    delay(100);
    digitalWrite(LED3, LOW);
    delay(1000);
}