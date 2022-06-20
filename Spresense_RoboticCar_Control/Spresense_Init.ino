//Written by MAX (Created 20-06-2022)

//Funtions : Spresense Initialization

#include "Spresense_Init.h"

#include "Spresense_Pin_Mapping.h"
#include "Spresense_Global_Var_Def.h"
#include "Spresense_Tool.h"

//init the 4 onboard LED
void Onboard_LED_Init(){
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

//init I2C pins & I2C
void I2C_Init(){

}

//init PikaPika pins
void PIKAPIKA_Init(){

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