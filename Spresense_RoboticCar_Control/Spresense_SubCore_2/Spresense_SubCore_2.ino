// Written by MAX (Created 07-09-2022)

/* Features :   Code for Spresense SubCore 2
                SubCore 2 -> FFT
*/
//--------------------------------------------------------//

#if (SUBCORE == 2)

//--------------------------------------------------------//

#include "Spresense_SubCore_2_TaskList.h"
#include "C:/Users/Max/Documents/Workspace/Spresense_RoboticCar_Control_2/Spresense_RoboticCar_Control/Spresense_Include_List.h"

#include <Arduino.h>
#include <MP.h>

//--------------------------------------------------------//

// Functions Declaration
float get_peak_frequency(float* FFT_result);
float length_estimation(float f_peak);
bool fft_init();

//--------------------------------------------------------//

arm_rfft_fast_instance_f32 FFT_instance;
float       phi_buffer[FFT_LEN];
float       output_buffer[FFT_LEN];
float       FFT_result[FFT_LEN];
uint16_t    FFT_countdown = FFT_LEN;
float       f_peak;
float       length_estimate;

void setup(void){
    MP.begin();
    if (!fft_init())
    {
        MPLog("Error : FFT_LEN invalid !! Please check definition of fft_init().");
    }
    for (int i = 0; i < FFT_LEN; i++)
    {
        phi_buffer[i] = 0.0;
    }
}
void loop(void){
    int8_t msgid;
    uint32_t msgdata;

    MP.Recv(&msgid, &msgdata);

    switch (msgid)
    {
    case C2_T0_FFT:{
        float temp_phi = ((float)msgdata-FFT_MIDSHIFT)/FFT_MSG_SCALE;
        for (int i = FFT_LEN-1; i > 0; i--)
        {
            phi_buffer[i] = phi_buffer[i-1];
        }
        phi_buffer[0] = temp_phi;

        if (FFT_countdown == 0)
        {
            FFT_countdown = 32;
            arm_rfft_fast_f32(&FFT_instance, phi_buffer, output_buffer, 0);
            arm_cmplx_mag_f32(output_buffer, FFT_result, FFT_LEN/2);
            f_peak = get_peak_frequency(FFT_result);
            if (f_peak < 0) // 検出失敗
            {
                MP.Send(C2_T1_NO_PEAK, C2_T1_NO_PEAK);  // メインコアに失敗を通報
            }
            length_estimate = length_estimation(f_peak);    //TODO what to do with the result
            MPLog("Length Estimate : %5.5f\n", length_estimate);
            // static bool temp = true;
            // if (temp)
            // {
            //     for (int i = 0; i < FFT_LEN; i++)
            //     {
            //         MPLog("%5.5f\n", FFT_result[i]);
            //     }
            //     temp = false;
            // }
        } else {
            FFT_countdown--;
        }
        break;
    }
    case C2_T1_NO_PEAK:{
        // Just placeholder, C2_T1_NO_PEAK is for sending back to Main core
        break;
    }
    case C2_T2_REPORT_FFT_RESULT:{
        // Just placeholder, C2_T1_NO_PEAK is for sending back to Main core
        break;
    }
    default:
        break;
    }
}

float get_peak_frequency(float* FFT_result){
    float Ts = 0.14f;
    float g_fs = 1.0f/Ts;
    uint32_t index = 0;
    float maxValue;
    float delta;
    float peakFs;

    for (int i = 1; i < FFT_LEN/2; i++){ // ピーク候補から0Hzは除外
        if( (FFT_result[i] > FFT_result[i-1]) && (FFT_result[i+1] < FFT_result[i]) ){ // 極大値
            if(FFT_result[i] > PEAK_POWER_THRESHOLD){ // 閾値以上なら有効
                index = i;
                break;  // break if found
            }
        }
    }
    if (index == 0)
    {
        return -1;
    }
    
    delta = 0.5 * (FFT_result[index-1] - FFT_result[index+1])
            / (FFT_result[index-1] + FFT_result[index+1] - (2.0f * FFT_result[index]));
    peakFs = (index + delta) * g_fs / (FFT_LEN-1);

    return peakFs;
}

float length_estimation(float f_peak){
    if (f_peak<=0){
        return -1;
    }
    return 0.5f*sqrt(kappa)/f_peak;  // l = sqrt(kappa)/(2*f_peak)
}

bool fft_init(){
     switch (FFT_LEN){
       case 32:
         arm_rfft_32_fast_init_f32(&FFT_instance);
         break;
       case 64:
         arm_rfft_64_fast_init_f32(&FFT_instance);
         break;
       case 128:
         arm_rfft_128_fast_init_f32(&FFT_instance);
         break;
       case 256:
         arm_rfft_256_fast_init_f32(&FFT_instance);
         break;
       case 512:
         arm_rfft_512_fast_init_f32(&FFT_instance);
         break;
       case 1024:
         arm_rfft_1024_fast_init_f32(&FFT_instance);
         break;
       case 2048:
         arm_rfft_2048_fast_init_f32(&FFT_instance);
         break;
       case 4096:
         arm_rfft_4096_fast_init_f32(&FFT_instance);
         break;
       default:
         puts("error!");
         return false;
         break;
     }
     return true;
}

#endif