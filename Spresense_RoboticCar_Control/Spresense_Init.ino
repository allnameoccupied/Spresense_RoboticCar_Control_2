// Written by MAX (Created 20-06-2022)

// Features : Spresense Initialization

//--------------------------------------------------------//

#include "Spresense_Init.h"
#include "Spresense_Include_List.h"

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
void PIKAPIKA_Init(){
    pinMode(PIKAPIKA_LED, OUTPUT);
    
    pinMode(PIKAPIKA_LIGHT_0, INPUT);
    pinMode(PIKAPIKA_LIGHT_1, INPUT);
    pinMode(PIKAPIKA_LIGHT_2, INPUT);
    pinMode(PIKAPIKA_LIGHT_3, INPUT);
    pinMode(PIKAPIKA_LIGHT_4, INPUT);
    pinMode(PIKAPIKA_LIGHT_5, INPUT);
    pinMode(PIKAPIKA_LIGHT_6, INPUT);
    pinMode(PIKAPIKA_LIGHT_7, INPUT);

    attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_0), PikaPika_Int_Handler_0, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_1), PikaPika_Int_Handler_1, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_2), PikaPika_Int_Handler_2, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_3), PikaPika_Int_Handler_3, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_4), PikaPika_Int_Handler_4, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_5), PikaPika_Int_Handler_5, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_6), PikaPika_Int_Handler_6, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_7), PikaPika_Int_Handler_7, FALLING);    
}

// Init Serial Communication
void Serial_Init(){
    Serial.begin(DEFAULT_BAUD_RATE);
}

// Init Inside/Outside LED pins
void InOut_LED_Init(){
    pinMode(INSIDE_LED, OUTPUT);
    pinMode(OUTSIDE_LED, OUTPUT);

    digitalWrite(INSIDE_LED, LOW);
    digitalWrite(OUTSIDE_LED, LOW);
}

// Init SubCores
void MP_Init(){
    MP.RecvTimeout(MP_RECV_BLOCKING);

    int ret = MP.begin(SUBCORE_1_GENERAL_ID);
    if (ret<0) {
        MPLog("MP.begin(%d) error = %d\n", SUBCORE_1_GENERAL_ID, ret);
    }
    ret = MP.begin(SUBCORE_2_FFT_ID);
    if (ret<0) {
        MPLog("MP.begin(%d) error = %d\n", SUBCORE_2_FFT_ID, ret);
    }
    // ret = MP.begin(SUBCORE_3_MOTOR_ENCODER_ID);
    // if (ret<0) {
    //     MPLog("MP.begin(%d) error = %d\n", SUBCORE_3_MOTOR_ENCODER_ID, ret);
    // }
}

// Init FFT related stuff
void FFT_Init(){
    attachTimerInterrupt(&FFT_PikaPika_Routine, FFT_UPDATE_PERIOD_US);
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