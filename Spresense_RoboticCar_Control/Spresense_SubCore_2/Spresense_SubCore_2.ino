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
float get_peak_frequency(float* FFT_result_inScope);
float length_estimation(float f_peak_inScope);
bool fft_init();

float* cal_power_spectrum(float* FFT_result_inScope);   // really need(?)
uint8_t inner_outer(float* power_spectrum_inScope);

//--------------------------------------------------------//

arm_rfft_fast_instance_f32 FFT_instance;
float       phi_buffer[FFT_LEN];
float       input_buffer[FFT_LEN];
float       output_buffer[FFT_LEN];
float       FFT_result[FFT_LEN];
float       power_spectrum[FFT_LEN/2];
uint16_t    FFT_countdown_sub2 = FFT_LEN;
float       f_peak;
float       length_estimate;

float       dx_phi_buffer[FFT_LEN];
float       dx_input_buffer[FFT_LEN];
float       dx_output_buffer[FFT_LEN];
float       dx_FFT_result[FFT_LEN];
float       dx_power_spectrum[FFT_LEN/2];

float       dy_phi_buffer[FFT_LEN];
float       dy_input_buffer[FFT_LEN];
float       dy_output_buffer[FFT_LEN];
float       dy_FFT_result[FFT_LEN];
float       dy_power_spectrum[FFT_LEN/2];

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
        // get phi
        float temp_phi = ((float)msgdata-FFT_MIDSHIFT)/FFT_MSG_SCALE;
        for (int i = FFT_LEN-1; i > 0; i--)
        {
            phi_buffer[i] = phi_buffer[i-1];
        }
        phi_buffer[0] = temp_phi;
        for (int i = 0; i < FFT_LEN-1; i++)
        {
            input_buffer[i] = phi_buffer[i];
        }

        // get dx_phi
        float temp_dx_phi;
        MP.Recv(&msgid, &msgdata);
        if (msgid == C2_T2_DXPHI)
        {
            temp_dx_phi = ((float)msgdata-FFT_MIDSHIFT)/FFT_MSG_SCALE;
        }
        for (int i = FFT_LEN-1; i > 0; i--)
        {
            dx_phi_buffer[i] = dx_phi_buffer[i-1];
        }
        dx_phi_buffer[0] = temp_dx_phi;
        for (int i = 0; i < FFT_LEN-1; i++)
        {
            dx_input_buffer[i] = dx_phi_buffer[i];
        }
        
        //get dy_phi
        float temp_dy_phi;
        MP.Recv(&msgid, &msgdata);
        if (msgid == C2_T3_DYPHI)
        {
            temp_dy_phi = ((float)msgdata-FFT_MIDSHIFT)/FFT_MSG_SCALE;
        }
        for (int i = FFT_LEN-1; i > 0; i--)
        {
            dy_phi_buffer[i] = dy_phi_buffer[i-1];
        }
        dy_phi_buffer[0] = temp_dy_phi;
        for (int i = 0; i < FFT_LEN-1; i++)
        {
            dy_input_buffer[i] = dy_phi_buffer[i];
        }
        
        // FFT calculation
        if (FFT_countdown_sub2 == 0)
        {
            FFT_countdown_sub2 = 32;
            arm_rfft_fast_f32(&FFT_instance, input_buffer, output_buffer, 0);
            arm_cmplx_mag_f32(output_buffer, FFT_result, FFT_LEN/2);
            // arm_rfft_fast_f32(&FFT_instance, dx_input_buffer, dx_output_buffer, 0);
            // arm_cmplx_mag_f32(dx_output_buffer, dx_FFT_result, FFT_LEN/2);
            arm_rfft_fast_f32(&FFT_instance, dy_input_buffer, dy_output_buffer, 0);
            arm_cmplx_mag_f32(dy_output_buffer, dy_FFT_result, FFT_LEN/2);
            f_peak = get_peak_frequency(FFT_result);
            if (f_peak < 0) // 検出失敗
            {
                MP.Send(C2_T1_NO_PEAK, C2_T1_NO_PEAK);  // メインコアに失敗を通報
            }
            length_estimate = length_estimation(f_peak);
            MPLog("Length Estimate : %4.2f\n", length_estimate);

            static int temp = 0;
            if (temp==15 || temp==50)
            {
                // MPLog("phi input buffer\n");
                // for (int i = 0; i < FFT_LEN; i++)
                // {
                //     MPLog("%5.5f\n", input_buffer[i]);
                // }

                // MPLog("phi output buffer\n");
                // for (int i = 0; i < FFT_LEN/2; i++)
                // {
                //     MPLog("%5.5f        %5.5f\n", output_buffer[2*i], output_buffer[2*i+1]);
                // }

                MPLog("phi FFT result\n");
                for (int i = 0; i < FFT_LEN/2; i++)
                {
                    MPLog("%5.5f\n", FFT_result[i]);
                }

                // MPLog("dy phi input buffer\n");
                // for (int i = 0; i < FFT_LEN; i++)
                // {
                //     MPLog("%5.5f\n", dy_input_buffer[i]);
                // }

                // MPLog("dy phi output buffer\n");
                // for (int i = 0; i < FFT_LEN/2; i++)
                // {
                //     MPLog("%5.5f        %5.5f\n", dy_output_buffer[2*i], dy_output_buffer[2*i+1]);
                // }

                MPLog("dy phi FFT result\n");
                for (int i = 0; i < FFT_LEN/2; i++)
                {
                    MPLog("%5.5f\n", dy_FFT_result[i]);
                }
            }
            temp++;

        } else {
            FFT_countdown_sub2--;
        }
        break;
    }
    case C2_T1_NO_PEAK:{
        // Just placeholder, C2_T1_NO_PEAK is for sending back to Main core
        break;
    }
    // case C2_T2_DXPHI:    // not for here
    // case C2_T3_DYPHI:    // not for here
    default:
        break;
    }
}

float get_peak_frequency(float* FFT_result_inScope){
    float Ts = 0.14f;
    float g_fs = 1.0f/Ts;
    uint32_t index = 0;
    float maxValue;
    float delta;
    float peakFs;

    for (int i = 1; i < FFT_LEN/2; i++){ // ピーク候補から0Hzは除外
        if( (FFT_result_inScope[i] > FFT_result_inScope[i-1]) && (FFT_result_inScope[i+1] < FFT_result_inScope[i]) ){ // 極大値
            if(FFT_result_inScope[i] > PEAK_POWER_THRESHOLD){ // 閾値以上なら有効
                index = i;
                break;  // break if found
            }
        }
    }
    if (index == 0)  // ピーク検出失敗時，-1を返す
    {
        return -1;
    }
    
    delta = 0.5 * (FFT_result_inScope[index-1] - FFT_result_inScope[index+1])
            / (FFT_result_inScope[index-1] + FFT_result_inScope[index+1] - (2.0f * FFT_result_inScope[index]));
    peakFs = (index + delta) * g_fs / (FFT_LEN-1);

    // MPLog("index : %d\n", index);
    // MPLog("peakFs : %4.2f\n", peakFs);

    return peakFs;
}

float length_estimation(float f_peak_inScope){
    if (f_peak_inScope<=0){
        return -1;
    }
    return 0.5f*sqrt(kappa)/f_peak_inScope;  // l = sqrt(kappa)/(2*f_peak)
}

float* cal_power_spectrum(float* FFT_result_inScope){
    int half_FFT_LEN = FFT_LEN/2;
    for (int i = 0; i < half_FFT_LEN; i++)
    {
        power_spectrum[i] = FFT_result_inScope[i] * FFT_result_inScope[i] / half_FFT_LEN / half_FFT_LEN;
    }
    return power_spectrum;
}

/* return value:
   0 = inside
   1 = x-axis outside
   2 = y-axis outside
   3 = xy-axis outside (corner)
*/
uint8_t inner_outer(float* power_spectrum_inScope, float* dx_power_spectrum_inScope, float* dy_power_spectrum_inScope){
    
    int half_FFT_LEN = FFT_LEN/2;   
    // int 

    // // assume peak exist
    // // no threshold requirement
    // for (int i = 1; i < FFT_LEN/2; i++){ // ピーク候補から0Hzは除外
    //     if( (FFT_result_inScope[i] > FFT_result_inScope[i-1]) && (FFT_result_inScope[i+1] < FFT_result_inScope[i]) ){ // 極大値
    //         index = i;
    //         break;  // break if found
    //     }
    // }

    return 0;
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