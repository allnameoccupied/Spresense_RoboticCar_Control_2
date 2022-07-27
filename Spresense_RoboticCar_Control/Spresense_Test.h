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

#include <string>
#include <VL53L1X.h>
// #include <Wire.h>

//--------------------------------------------------------//

//EXTERN of Variables
extern VL53L1X Dist_sensor [8];
extern VL53L1X Dist_sensor_0;
extern VL53L1X Dist_sensor_1;

//--------------------------------------------------------//

//EXTERN of FUNCTION Declaration

//Function Declaration
void i2c_detect();

//--------------------------------------------------------//

// VL53L1X test;
void test_init(){

    i2c_detect();

    pinMode(PIN_D02, OUTPUT);
    digitalWrite(PIN_D02, LOW);
    pinMode(PIN_D03, OUTPUT);
    digitalWrite(PIN_D03, LOW);
    delay(100);

    i2c_detect();

    //-------//

    pinMode(PIN_D02, INPUT);
    delay(100);
    Dist_sensor_0.setTimeout(500);
    if (!Dist_sensor_0.init())
    {
      Serial.print("Failed to detect and initialize 0 sensor ");
      while (1);
    }
    Dist_sensor_0.setAddress(DIST_SENSOR_1_I2C_ADDR);
    Serial.println("inited 0th sensor");
    i2c_detect();

    // test

    //-------//

    pinMode(PIN_D03, INPUT);
    delay(100);
    Dist_sensor_1.setTimeout(500);
    if (!Dist_sensor_1.init())
    {
      Serial.print("Failed to detect and initialize 1 sensor ");
      while (1);
    }
    Dist_sensor_1.setAddress(DIST_SENSOR_2_I2C_ADDR);
    Serial.println("inited 1th sensor");
    i2c_detect();

    //-------//

    Dist_sensor_0.startContinuous(50);
    Dist_sensor_1.startContinuous(50);
    Serial.println("now try to read distance data");

}


// void test_init(){

//     // for (int i = 0; i < 2; i++)
//     // {
//     //     char buf[32];
//     //     int ret = snprintf(buf, sizeof buf, "%f", 69000.420);

//     //     Serial.println("now send la");
//     //     Wire.beginTransmission(NUCLEO_I2C_ADDR);
//     //     Wire.write(buf);
//     //     Wire.endTransmission();
//     //     delay(1000);
//     // }

//     i2c_detect();

//     pinMode(PIN_D02, OUTPUT);
//     digitalWrite(PIN_D02, LOW);
//     pinMode(PIN_D03, OUTPUT);
//     digitalWrite(PIN_D03, LOW);
//     delay(1000);

//     i2c_detect();

//     //-------//

//     pinMode(PIN_D02, INPUT);
//     // digitalWrite(PIN_D02, HIGH);
//     delay(100);
//     Dist_sensor[0].setTimeout(500);
//     if (!Dist_sensor[0].init())
//     {
//       Serial.print("Failed to detect and initialize 0 sensor ");
//       while (1);
//     }
//     Dist_sensor[0].setAddress(DIST_SENSOR_1_I2C_ADDR);
//     // Dist_sensor[0].setMeasurementTimingBudget(50000);
//     Serial.println("inited 0th sensor");
//     // Serial.println(Dist_sensor[0].getAddress());
//     i2c_detect();

//     //-------//

//     pinMode(PIN_D03, INPUT);
//     // digitalWrite(PIN_D03, HIGH);
//     delay(100);
//     Dist_sensor[1].setTimeout(500);
//     if (!Dist_sensor[1].init())
//     {
//       Serial.print("Failed to detect and initialize 1 sensor ");
//       while (1);
//     }
//     Dist_sensor[1].setAddress(DIST_SENSOR_2_I2C_ADDR);
//     // Dist_sensor[1].setMeasurementTimingBudget(50000);
//     Serial.println("inited 1th sensor");
//     // Serial.println(Dist_sensor[1].getAddress());
//     i2c_detect();

//     //-------//

//     // Dist_sensor[0].startContinuous(50);
//     Dist_sensor[1].startContinuous(50);
//     Serial.println("now try to read distance data");

// }
int count = 0;
void test_loop(){

  if (count<10)
  {
    Serial.print(Dist_sensor_0.read());
    if (Dist_sensor_0.timeoutOccurred()) { Serial.print("0th TIMEOUT"); }
    Serial.println('\t');
    delay(100);

    Serial.print(Dist_sensor_1.read());
    if (Dist_sensor_1.timeoutOccurred()) { Serial.print("1th TIMEOUT"); }
    Serial.println('\t');
    delay(100);

    Serial.println();

    delay(1000);
    count++;
  }
}

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