// Written by MAX (Created 20-06-2022)

/* Features : Write test functions here, 
              so main program will not be messy
*/

// *** ONLY CASE WHICH FUNCTIONS ARE DEFINED IN HEADER *** 

//--------------------------------------------------------//

#ifndef SPRESENSE_TEST_H
#define SPRESENSE_TEST_H

#include "Spresense_Include_List.h"
#include "Spresense_SubCore_1/Spresense_SubCore_1_TaskList.h"

#include <Arduino.h>
#include <MP.h>

#include <VL53L1X.h>
// #include <Wire.h>

//--------------------------------------------------------//

//EXTERN of stuff from Main file

// -> Variables
extern VL53L1X Dist_sensor [8];

// -> Functions

//--------------------------------------------------------//

// Functions Declaration
void i2c_detect();
unsigned int FFT_PikaPika_Routine();

//--------------------------------------------------------//

///* PikaPika FFT test
void test_init(){
  int ret = MP.begin(SUBCORE_2_FFT_ID);
  if (ret<0) {
    MPLog("MP.begin(%d) error = %d\n", SUBCORE_2_FFT_ID, ret);
  }

  attachTimerInterrupt(FFT_PikaPika_Routine, FFT_UPDATE_PERIOD_US);
}
void test_loop(){
  uint8_t msgid;
  uint32_t recv;
  // Serial.println("qwer");
  // int ret = MP.Recv(&msgid, &recv, SUBCORE_2_FFT_ID);
  // Serial.println("asdf");
  if ((msgid == C2_T1_NO_PEAK) && (recv == C2_T1_NO_PEAK)){  // ピーク検知失敗
    is_Self_Excitation = true;  // 自励処理
  }

  delay(20);
}
int PikaPika_LED_countdown = 0;
int FFT_countdown = FFT_PROCESS_PERIOD_US;
double last_phi = 0.0;
double last_mod_varphi = 0.0;
unsigned int FFT_PikaPika_Routine(){
  //******** 位相更新 ***********//     楕円型（振動相互作用）
  phi_bar += Omega_0 * dt;    // 進行位相は等角速度
  phi_bar += is_Self_Excitation * SELF_EXITATION_INTENSITY;   // 自励処理
  is_Self_Excitation = false;   // 一度行ったら自励はオフ

  sum_dphi = 0.0;
  adaptive_gamma = GAMMA_CONST_1;
  for (int i = 0; i < PIKAPIKA_SENSOR_COUNT; i++)
  {
    sum_dphi += dphi[i];
    adaptive_gamma += (PikaPika_light_sensor_life[i] > 0) * GAMMA_CONST_2;
  }
  c_fft = adaptive_gamma * 0.5 * dt + 1;
  double temp_phi = ( 2 * phi
                      + (adaptive_gamma * dt * 0.5 - 1) * last_phi
                      + dt * dt * (-kappa * sum_dphi))  /c_fft;
  last_phi = phi;
  phi = temp_phi;
  varphi = phi_bar + phi;
  //******** 位相更新ここまで********//

  //******** 2pi周期性と発光の処理********//
  mod_varphi = fmod(varphi, 2*PI);
  if ((mod_varphi >= PI) && (last_mod_varphi < PI))
  {
    PikaPika_LED_countdown = PIKAPIKA_BLINK_TIME;
    for (int i = 0; i < PIKAPIKA_SENSOR_COUNT; i++)
    {
      PikaPika_light_sensor_life[i] -= 1;
      if (PikaPika_light_sensor_life[i] == 0)
      {
        dphi[i] = 0.0;
      }
    }
  }
  last_mod_varphi = mod_varphi;

  if (PikaPika_LED_countdown > 0)
  {
    digitalWrite(PIKAPIKA_LED, HIGH);
    PikaPika_LED_countdown--;
  } else {
    digitalWrite(PIKAPIKA_LED, LOW);
  }
  
  //****** サブコアへの位相通知処理 *********//
  FFT_countdown--;
  if (FFT_countdown == 0)
  {
    MP.Send(C2_T0_FFT, (uint32_t)(FFT_MSG_SCALE * phi + FFT_MIDSHIFT), SUBCORE_2_FFT_ID);
  }

  return FFT_UPDATE_PERIOD_US;  // https://developer.sony.com/develop/spresense/docs/arduino_developer_guide_ja.html#_attachtimerinterrupt
}
//*/

/* Multi Robots test
// Robot 1 (Receiver + Serial Communication)
void test_init(){
  // Serial.println("test");

  for (int i = 0; i < 4; i++)
  {
    digitalWrite(PIKAPIKA_LED, HIGH);
    delay(25);
    digitalWrite(PIKAPIKA_LED, LOW);
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

    digitalWrite(INSIDE_LED, HIGH);
    delay(25);
    digitalWrite(INSIDE_LED, LOW);
    // delay(500);

    PikaPika_light_sensor[i] = false;

    Serial.println();
    }
  }
}
// Robot 2 (Blinker)
// void test_init(){

// }
// void test_loop(){
//   while(1){
//     digitalWrite(PIKAPIKA_LED, HIGH);
//     delay(25);
//     digitalWrite(PIKAPIKA_LED, LOW);
//     delay(750);
//   }
// }
*/

/* Multicore test
void test_init(){
  int ret = MP.begin(SUBCORE_1_GENERAL_ID);
  if (ret != 0){Serial.println(ret);}
  
  digitalWrite(PIKAPIKA_LED, LOW);
  delay(2000);
  MP.Send(C1_T1_PIKAPIKA_LED,2000,SUBCORE_1_GENERAL_ID);
  delay(500);
  MP.Send(C1_T2_INSIDE_LED,2000,SUBCORE_1_GENERAL_ID);
  delay(500);
  MP.Send(C1_T3_OUTSIDE_LED,2000,SUBCORE_1_GENERAL_ID);
  delay(10000);
}
void test_loop(){

}
*/

/* PikaPika test
bool PikaPika_light_sensor [8] = {false, false, false, false, false, false, false, false};
uint64_t*** PikaPika_detected_timestamp = new uint64_t** [8];
void test_init(){
  // Serial.println("test");

  for (int i = 0; i < 4; i++)
  {
    digitalWrite(PIKAPIKA_LED, HIGH);
    delay(25);
    digitalWrite(PIKAPIKA_LED, LOW);
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

    digitalWrite(PIKAPIKA_LED, HIGH);
    delay(25);
    digitalWrite(PIKAPIKA_LED, LOW);
    // delay(500);

    PikaPika_light_sensor[i] = false;

    Serial.println();
    }
  }

  // Serial.println(analogRead(PIN_A0));
  // delay(100);
}
*/

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