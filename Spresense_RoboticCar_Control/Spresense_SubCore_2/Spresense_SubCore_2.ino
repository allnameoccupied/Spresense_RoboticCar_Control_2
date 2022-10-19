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

//--------------------------------------------------------//

void setup(void){
    MP.begin();
    arm_fft_init();
    phi_init();    
}
void loop(void){
    int8_t msgid;
    uint32_t msgdata;

    MP.Recv(&msgid, &msgdata);

    switch (msgid)
    {
    case C2_T0_FFT:{
        // get phi
        phi_update(msgdata);

        // get dx_phi
        MP.Recv(&msgid, &msgdata);
        if (msgid != C2_T1_DXPHI){break;}
        dx_phi_update(msgdata);
        
        //get dy_phi
        MP.Recv(&msgid, &msgdata);
        if (msgid != C2_T2_DYPHI){break;}
        dy_phi_update(msgdata);
        
        // FFT calculation
        static uint16_t FFT_countdown_sub2 = FFT_LEN;
        if (FFT_countdown_sub2 == 0)
        {
            // reset count
            FFT_countdown_sub2 = FFT_CALC_RATE;
            
            // FFT & Power Spectrum
            // ->-> rfft->FFT, cmplx_mag->complex magnitude
            // -> phi
            arm_rfft_fast_f32(&FFT_instance, input_buffer, output_buffer, 0);
            arm_cmplx_mag_f32(output_buffer, FFT_result, FFT_LEN/2);
            // -> dx_phi
            arm_rfft_fast_f32(&FFT_instance, dx_input_buffer, dx_output_buffer, 0);
            arm_cmplx_mag_f32(dx_output_buffer, dx_FFT_result, FFT_LEN/2);
            // -> dy_phi
            arm_rfft_fast_f32(&FFT_instance, dy_input_buffer, dy_output_buffer, 0);
            arm_cmplx_mag_f32(dy_output_buffer, dy_FFT_result, FFT_LEN/2);

            // determine if need to self-excite by finding peak
            float f_peak = get_peak_frequency(FFT_result);
            if (f_peak < 0) // 検出失敗
            {
                MP.Send(C2_T3_NO_PEAK, C2_T3_NO_PEAK);  // メインコアに失敗を通報
            }
            // determine swarm size (not used now)
            // float length_estimate = length_estimation(f_peak);
            // MPLog("Length Estimate : %4.2f\n", length_estimate);

            // estimate inner/outer layer  ********
            inner_outer_estimate();

            // print out data to Serial Monitor
            fft_data_print_out();

        } else {
            FFT_countdown_sub2--;
        }
        break;
    }
    // case C2_T1_DXPHI:    // not for receiving
    // case C2_T2_DYPHI:    // not for receiving
    // case C2_T3_NO_PEAK:  // not for receiving
    default:
        break;
    }
}

#endif