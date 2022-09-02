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
#include "Spresense_SubCore_1/Spresense_SubCore_1_TaskList.h"

#include <string>
#include <MP.h>
#include <VL53L1X.h>
// #include <Wire.h>

//--------------------------------------------------------//

//EXTERN of Variables
extern VL53L1X Dist_sensor [8];
extern bool PikaPika_light_sensor [8];
extern uint64_t*** PikaPika_detected_timestamp;

//EXTERN of FUNCTION Declaration

//--------------------------------------------------------//

//Function Declaration
void i2c_detect();
void wave_test_init();
void wave_test_loop();

//--------------------------------------------------------//

// void test_init(){
//   int ret = MP.begin(SUBCORE_1_GENERAL_ID);
//   if (ret != 0){Serial.println(ret);}
  
//   digitalWrite(LED_PIKA, LOW);
//   delay(2000);
//   MP.Send(C1_T1_PIKAPIKA_LED,2000,SUBCORE_1_GENERAL_ID);
//   delay(500);
//   MP.Send(C1_T2_INSIDE_LED,2000,SUBCORE_1_GENERAL_ID);
//   delay(500);
//   MP.Send(C1_T3_OUTSIDE_LED,2000,SUBCORE_1_GENERAL_ID);
//   delay(10000);
// }
// void test_loop(){

// }

///* PikaPika test
void test_init(){
  // Serial.println("test");

  for (int i = 0; i < 4; i++)
  {
    digitalWrite(LED_PIKA, HIGH);
    delay(25);
    digitalWrite(LED_PIKA, LOW);
    delay(750);
  }

  digitalWrite(INSIDE_LED, HIGH);
  digitalWrite(OUTSIDE_LED, HIGH);
  delay(500);
  digitalWrite(INSIDE_LED, LOW);
  digitalWrite(OUTSIDE_LED, LOW);
  
  Serial.println("now start detect flash");
}
void test_loop(){
  for (int i = 0; i < 8; i++)
  {
    if (PikaPika_light_sensor[i])
    {
    Serial.print(i);
    Serial.print("\t");
    Serial.print(*PikaPika_detected_timestamp[i][0]);
    Serial.print("\t");
    Serial.print(*PikaPika_detected_timestamp[i][1]);
    Serial.print("\t");
    Serial.print(*PikaPika_detected_timestamp[i][2]);
    Serial.print("\t");
    Serial.print(*PikaPika_detected_timestamp[i][3]);
    Serial.print("\t");
    Serial.print(*PikaPika_detected_timestamp[i][4]);
    Serial.println();

    digitalWrite(LED_PIKA, HIGH);
    delay(25);
    digitalWrite(LED_PIKA, LOW);
    // delay(500);

    PikaPika_light_sensor[i] = false;

    Serial.println();
    }
  }

  // Serial.println(analogRead(PIN_A0));
  // delay(100);
}

float phase;
const float con_intensity = 0.1;
void wave_test_init(){

}
void wave_test_loop(){

}
//*/

/* distance sensor test

// VL53L1X test;
bool use_dist_0 = true;
bool use_dist_1 = true;
bool use_dist_2 = true;
bool use_dist_3 = true;
bool use_dist_4 = true;
bool use_dist_5 = true;
bool use_dist_6 = true;
bool use_dist_7 = true;
void test_init(){
  
    for (int i = 0; i < 2; i++)
    {
        char buf[32];
        // int ret = snprintf(buf, sizeof buf, "%f", 69000.420);
        int ret = snprintf(buf, sizeof buf, "%f %d", 123.456, i);

        Serial.println("now send la");
        Wire.beginTransmission(NUCLEO_I2C_ADDR);
        Wire.write(buf);
        Wire.endTransmission();
        delay(250);
    }

    //-------//

    i2c_detect();

    pinMode(PIN_D02, OUTPUT);
    digitalWrite(PIN_D02, LOW);
    pinMode(PIN_D03, OUTPUT);
    digitalWrite(PIN_D03, LOW);
    pinMode(PIN_D04, OUTPUT);
    digitalWrite(PIN_D04, LOW);
    pinMode(PIN_D05, OUTPUT);
    digitalWrite(PIN_D05, LOW);
    pinMode(PIN_D06, OUTPUT);
    digitalWrite(PIN_D06, LOW);
    pinMode(PIN_D07, OUTPUT);
    digitalWrite(PIN_D07, LOW);
    pinMode(PIN_D08, OUTPUT);
    digitalWrite(PIN_D08, LOW);
    pinMode(PIN_D09, OUTPUT);
    digitalWrite(PIN_D09, LOW);
    delay(100);

    i2c_detect();

    //-------//

    if(use_dist_0){
      pinMode(PIN_D02, INPUT);
      delay(100);
      i2c_detect();
      Dist_sensor[0].setTimeout(500);
      if (!Dist_sensor[0].init())
      {
        Serial.print("Failed to detect and initialize 0 sensor ");
        while (1);
      }
      Dist_sensor[0].setAddress(DIST_SENSOR_1_I2C_ADDR);
      Serial.println("inited 0th sensor\n");
      i2c_detect();
    }

    //-------//

    if(use_dist_1){
      pinMode(PIN_D03, INPUT);
      delay(100);
      i2c_detect();
      Dist_sensor[1].setTimeout(500);
      if (!Dist_sensor[1].init())
      {
        Serial.print("Failed to detect and initialize 1 sensor ");
        while (1);
      }
      Dist_sensor[1].setAddress(DIST_SENSOR_2_I2C_ADDR);
      Serial.println("inited 1th sensor\n");
      i2c_detect();
    }

    //-------//

    if(use_dist_2){
      pinMode(PIN_D04, INPUT);
      delay(100);
      i2c_detect();
      Dist_sensor[2].setTimeout(500);
      if (!Dist_sensor[2].init())
      {
        Serial.print("Failed to detect and initialize 2 sensor ");
        while (1);
      }
      Dist_sensor[2].setAddress(DIST_SENSOR_3_I2C_ADDR);
      Serial.println("inited 2th sensor\n");
      i2c_detect();
    }

    //-------//

    if(use_dist_3){
      pinMode(PIN_D05, INPUT);
      delay(100);
      i2c_detect();
      Dist_sensor[3].setTimeout(500);
      if (!Dist_sensor[3].init())
      {
        Serial.print("Failed to detect and initialize 3 sensor ");
        while (1);
      }
      Dist_sensor[3].setAddress(DIST_SENSOR_4_I2C_ADDR);
      Serial.println("inited 3th sensor\n");
      i2c_detect();
    }

    //-------//

    if(use_dist_4){
      pinMode(PIN_D06, INPUT);
      delay(100);
      i2c_detect();
      Dist_sensor[4].setTimeout(500);
      if (!Dist_sensor[4].init())
      {
        Serial.print("Failed to detect and initialize 4 sensor ");
        while (1);
      }
      Dist_sensor[3].setAddress(DIST_SENSOR_5_I2C_ADDR);
      Serial.println("inited 4th sensor\n");
      i2c_detect();
    }

    //-------//

    if(use_dist_5){
      pinMode(PIN_D07, INPUT);
      delay(100);
      i2c_detect();
      Dist_sensor[5].setTimeout(500);
      if (!Dist_sensor[5].init())
      {
        Serial.print("Failed to detect and initialize 5 sensor ");
        while (1);
      }
      Dist_sensor[5].setAddress(DIST_SENSOR_6_I2C_ADDR);
      Serial.println("inited 5th sensor\n");
      i2c_detect();
    }

    //-------//

    if(use_dist_6){
      pinMode(PIN_D08, INPUT);
      delay(100);
      i2c_detect();
      Dist_sensor[6].setTimeout(500);
      if (!Dist_sensor[6].init())
      {
        Serial.print("Failed to detect and initialize 6 sensor ");
        while (1);
      }
      Dist_sensor[6].setAddress(DIST_SENSOR_7_I2C_ADDR);
      Serial.println("inited 6th sensor\n");
      i2c_detect();
    }

    //-------//

    if(use_dist_7){
      pinMode(PIN_D09, INPUT);
      delay(100);
      i2c_detect();
      Dist_sensor[7].setTimeout(500);
      if (!Dist_sensor[7].init())
      {
        Serial.print("Failed to detect and initialize 7 sensor ");
        while (1);
      }
      Dist_sensor[7].setAddress(DIST_SENSOR_8_I2C_ADDR);
      Serial.println("inited 7th sensor\n");
      i2c_detect();
    }

    //-------//

    if(use_dist_0){
      Dist_sensor[0].startContinuous(50);
    }
    if(use_dist_1){
      Dist_sensor[1].startContinuous(50);
    }
    if(use_dist_2){
      Dist_sensor[2].startContinuous(50);
    }
    if(use_dist_3){
      Dist_sensor[3].startContinuous(50);
    }
    if(use_dist_4){
      Dist_sensor[4].startContinuous(50);
    }
    if(use_dist_5){
      Dist_sensor[5].startContinuous(50);
    }
    if(use_dist_6){
      Dist_sensor[6].startContinuous(50);
    }
    if(use_dist_7){
      Dist_sensor[7].startContinuous(50);
    }
    Serial.println("now try to read distance data");

}
int count = 0;
void test_loop(){

  if (count<10)
  {
    if(use_dist_0){
      Serial.print(Dist_sensor[0].read());
      if (Dist_sensor[0].timeoutOccurred()) { Serial.print("0th TIMEOUT"); }
      Serial.println('\t');
      delay(100);
    }

    if(use_dist_1){
      Serial.print(Dist_sensor[1].read());
      if (Dist_sensor[1].timeoutOccurred()) { Serial.print("1th TIMEOUT"); }
      Serial.println('\t');
      delay(100);
    }

    if(use_dist_2){
      Serial.print(Dist_sensor[2].read());
      if (Dist_sensor[2].timeoutOccurred()) { Serial.print("2th TIMEOUT"); }
      Serial.println('\t');
      delay(100);
    }

    if(use_dist_3){
      Serial.print(Dist_sensor[3].read());
      if (Dist_sensor[3].timeoutOccurred()) { Serial.print("3th TIMEOUT"); }
      Serial.println('\t');
      delay(100);
    }

    if(use_dist_4){
      Serial.print(Dist_sensor[4].read());
      if (Dist_sensor[4].timeoutOccurred()) { Serial.print("4th TIMEOUT"); }
      Serial.println('\t');
      delay(100);
    }

    if(use_dist_5){
      Serial.print(Dist_sensor[5].read());
      if (Dist_sensor[5].timeoutOccurred()) { Serial.print("5th TIMEOUT"); }
      Serial.println('\t');
      delay(100);
    }

    if(use_dist_6){
      Serial.print(Dist_sensor[6].read());
      if (Dist_sensor[6].timeoutOccurred()) { Serial.print("6th TIMEOUT"); }
      Serial.println('\t');
      delay(100);
    }

    if(use_dist_7){
      Serial.print(Dist_sensor[7].read());
      if (Dist_sensor[7].timeoutOccurred()) { Serial.print("7th TIMEOUT"); }
      Serial.println('\t');
      delay(100);
    }

    Serial.println();

    delay(1000);
    count++;
  }
}

*/

void i2c_detect(){
  byte error, address; //variable for error and I2C address
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.print(" ");
      Serial.print(address);
      Serial.println("  !");
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}

#endif