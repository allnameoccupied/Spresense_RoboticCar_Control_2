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
#include "Spresense_SubCore_2/Spresense_SubCore_2_TaskList.h"

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

//--------------------------------------------------------//

///* PikaPika FFT test
unsigned int FFT_PikaPika_Routine(){
    //******** 関数内変数定義 ***********  
    static int PikaPika_LED_countdown = 0;
    static int FFT_countdown = FFT_PROCESS_PERIOD_US;
    static double last_phi = 0.0;
    static double last_mod_varphi = 0.0;
    //******** 関数内変数定義ここまで********

    //******** 位相更新 ***********     楕円型（振動相互作用）
    // static int ttcount = FFT_PROCESS_PERIOD_US * 800;
    // static float test_self_excite = 0.0;
    // static float test_self_excite2 = 0.0;
    // // if (is_Self_Excitation)
    // if (ttcount == 0)
    // {
    //   // MPLog("now real self excite la\n");
    //   if (!is_Self_Excitation)
    //   {
    //     last_phi = 0.0;
    //     last_mod_varphi = 0.0;
    //     // phi_bar = 0.0;
    //     phi = 0.0;
    //     varphi = 0.0;
    //     mod_varphi = 0.0;
    //   }
    //   // test_self_excite = 0.025;
    //   // test_self_excite2 = 1.0;
    //   // is_Self_Excitation = false;
    //   ttcount = FFT_PROCESS_PERIOD_US * 800;
    //   is_Self_Excitation = false;
    //   // delay(30);
    // } else {
    //   // test_self_excite = GAMMA;
    //   // test_self_excite2 = kappa;
    //   ttcount--;
    // }

    phi_bar += Omega_0 * dt;    // 進行位相は等角速度
    // phi_bar += is_Self_Excitation * SELF_EXITATION_INTENSITY;   // 自励処理
    // phi_bar += test_self_excite * SELF_EXITATION_INTENSITY;   // 自励処理
    // is_Self_Excitation = false;   // 一度行ったら自励はオフ

    sum_dphi = 0.0;

    adaptive_gamma = GAMMA_CONST_1;
    // adaptive_gamma = test_self_excite;
    for (int i = 0; i < PIKAPIKA_SENSOR_COUNT; i++)
    {
        sum_dphi += dphi[i];
        adaptive_gamma += (PikaPika_light_sensor_life[i] > 0) * GAMMA_CONST_2;
        // adaptive_gamma += (PikaPika_light_sensor_life[i] > 0) * test_self_excite;
    }
    c_fft = adaptive_gamma * 0.5 * dt + 1;
    double temp_phi = ( 2 * phi
                        + (adaptive_gamma * dt * 0.5 - 1) * last_phi
                        + dt * dt * (-kappa * sum_dphi))  /c_fft;
                        // + dt * dt * (-test_self_excite2 * sum_dphi))  /c_fft;
    last_phi = phi;
    phi = temp_phi;
    varphi = phi_bar + phi;
    // varphi = phi_bar;
    //******** 位相更新ここまで********

    //******** dphi/dx & dphi/dy の計算********
    const float PikaPika_radian_sin[8] = {0.0, 0.7071067812, 1.0, 0.7071067812, 0.0, -0.7071067812, -1.0, -0.7071067812};
    const float PikaPika_radian_cos[8] = {1.0, 0.7071067812, 0.0, -0.7071067812, -1.0, -0.7071067812, 0.0, 0.7071067812};

    float dx_phi = 0.0;
    float dxi = 0.0;
    for (int i = 0; i < 8; i++)
    {
        if (PikaPika_light_sensor_life[i] > 0)
        {
            dxi += abs(PikaPika_radian_cos[i]);
        }
        dx_phi += DXPHI_MULTIPLIER * -1.0 * dphi[i] * PikaPika_radian_cos[i];
    }
    if (dxi == 0.0)
    {
        dx_phi = 0;
    } else {
        dx_phi = dx_phi / dxi;
    }
    
    float dy_phi = 0.0;
    float dyi = 0.0;
    for (int i = 0; i < 8; i++)
    {
        if (PikaPika_light_sensor_life[i] > 0)
        {
            dyi += abs(PikaPika_radian_sin[i]);
        }
        dy_phi += DYPHI_MULTIPLIER * -1.0 * dphi[i] * PikaPika_radian_sin[i];
    }
    if (dyi == 0.0)
    {
        dy_phi = 0;
    } else {
        dy_phi = dy_phi / dyi;
    }
    //******** dphi/dx & dphi/dy の計算ここまで********

    // static int count=0;
    // // if (count == 10000)
    // if (count == 100000)
    // {
    //     count = 0;
    //     // count = 100001;
    //     // MPLog("%5.5f\n", dx_phi);
    //     // MPLog("%5.5f\n", dy_phi);
    //     // MPLog("%5.5f\n", dyi);
    //     // for (int i = 0; i < 8; i++){MPLog("%5.5f\n", abs(PikaPika_radian_cos[i]));}
    //     // for (int i = 0; i < 8; i++){MPLog("%5.5f\n", abs(PikaPika_radian_sin[i]));}
    //     // for (int i = 0; i < 8; i++){MPLog("PikaPika_light_sensor_life[i] > 0 %d\n", PikaPika_light_sensor_life[i] > 0);}
    //     for (int i = 0; i < 8; i++){MPLog("dphi %5.5f\n", dphi[i]);}
    //     // MPLog("sum_dphi %5.5f\n", sum_dphi);
    //     // for (int i = 0; i < 8; i++){MPLog("PikaPika_light_sensor_life %d\n", PikaPika_light_sensor_life[i]);}
    //     // MPLog("adaptive_gamma %5.5f\n", adaptive_gamma);
    //     // MPLog("phi %5.5f\n", phi);
    //     // MPLog("varphi %5.5f\n", varphi);
    //     MPLog("\n");
    // } else{
    //     count++;
    // }

    //******** 2pi周期性と発光の処理********
    mod_varphi = fmod(varphi, 2*PI);
    if ((mod_varphi >= PI) && (last_mod_varphi < PI))
    {
        PikaPika_LED_countdown = PIKAPIKA_BLINK_TIME;
        for (int i = 0; i < PIKAPIKA_SENSOR_COUNT; i++)
        {
        if (PikaPika_light_sensor_life[i] > 0)
        {
            PikaPika_light_sensor_life[i] -= 1;
        }
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
    
    //****** サブコアへの位相通知処理 *********
    FFT_countdown--;
    if (FFT_countdown == 0)
    {
        FFT_countdown = FFT_PROCESS_PERIOD_US;
        MP.Send(C2_T0_FFT, (uint32_t)(FFT_MSG_SCALE * phi + FFT_MIDSHIFT), SUBCORE_2_FFT_ID);
        MP.Send(C2_T1_DXPHI, (uint32_t)(FFT_MSG_SCALE * dx_phi + FFT_MIDSHIFT), SUBCORE_2_FFT_ID);
        MP.Send(C2_T2_DYPHI, (uint32_t)(FFT_MSG_SCALE * dy_phi + FFT_MIDSHIFT), SUBCORE_2_FFT_ID);
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