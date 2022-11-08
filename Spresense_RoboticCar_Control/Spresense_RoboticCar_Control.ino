// Written by MAX (Created 20-06-2022)

// Features : Main program for Spresense

//--------------------------------------------------------//

#define from_MAX 12345

//--------------------------------------------------------//

// Only for Main Core
#ifndef SUBCORE

// Files created by me(max12345)
#include "Spresense_Include_List.h"
#include "Spresense_Test.h"
// Files from libraries
#include <Arduino.h>
#include <MP.h>

#include <Camera.h>
#include <VL53L1X.h>
#include <Wire.h>

//--------------------------------------------------------//

// Global Variables

// -> FFT Variables


// -> DIST Sensors Variables
VL53L1X Dist_sensor [8];

//--------------------------------------------------------//

// Functions Declaration
unsigned int FFT_PikaPika_Routine();

//--------------------------------------------------------//

// For TESTING

//--------------------------------------------------------//

// MAIN PROGRAM
void setup() {

    // Spresense Init
    Onboard_LED_Init();
    I2C_Init();
    Dist_Sensor_Init();
    PIKAPIKA_Init();
    Serial_Init();
    InOut_LED_Init();
    MP_Init();
    FFT_Init();
    Finish_Init_LED_Flash();
    Serial.println("Init finished successfully");
    
    // TEST FUNCTION
    // test_init();
}
void loop() {

    // Listen for message from other cores
    int8_t msgid;
    uint32_t msgdata;
    MP.Recv(&msgid, &msgdata, SUBCORE_2_FFT_ID);
    switch (msgid)
    {
        case C2_T3_NO_PEAK:{
            is_Self_Excitation = true;
            MPLog("now self excite\n");
        }
    }
    
    // TEST FUNCTION
    // test_loop();
}

//--------------------------------------------------------//
unsigned int FFT_PikaPika_Routine(){
    //******** 関数内変数定義 ***********  
    static int PikaPika_LED_countdown = 0;
    static int FFT_countdown = FFT_PROCESS_PERIOD_US;
    static double last_phi = 0.0;
    static double last_mod_varphi = 0.0;
    //******** 関数内変数定義ここまで********

    //******** 位相更新 ***********     楕円型（振動相互作用）
    static int ttcount = FFT_PROCESS_PERIOD_US * 800;
    // static float test_self_excite = 0.0;
    // static float test_self_excite2 = 0.0;
    // if (is_Self_Excitation)
    if (ttcount == 0)
    {
      // MPLog("now real self excite la\n");
      if (!is_Self_Excitation)  // 自励処理
      {
        last_phi = 0.0;
        last_mod_varphi = 0.0;
        // phi_bar = 0.0;
        phi = 0.0;
        varphi = 0.0;
        mod_varphi = 0.0;
      }
      // test_self_excite = 0.025;
      // test_self_excite2 = 1.0;
      // is_Self_Excitation = false;
      ttcount = FFT_PROCESS_PERIOD_US * 800;
      is_Self_Excitation = false;
      // delay(30);
    } else {
      // test_self_excite = GAMMA;
      // test_self_excite2 = kappa;
      ttcount--;
    }

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
        // dx_phi += DXPHI_MULTIPLIER * -1.0 * dphi[i] * PikaPika_radian_cos[i];  // multiplier = 1.0
        dx_phi += -1.0 * dphi[i] * PikaPika_radian_cos[i];
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
        // dy_phi += DYPHI_MULTIPLIER * -1.0 * dphi[i] * PikaPika_radian_sin[i];  // multiplier = 1.0
        dy_phi += -1.0 * dphi[i] * PikaPika_radian_sin[i];
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

#endif