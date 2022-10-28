// Written by MAX (Created 18-10-2022)

// Features : FFT related functions for Sub2

//--------------------------------------------------------//

#if (SUBCORE == 2)

//--------------------------------------------------------//

#include "Spresense_Sub2_FFT_Functions.h"
#include "C:/Users/Max/Documents/Workspace/Spresense_RoboticCar_Control_2/Spresense_RoboticCar_Control/Spresense_Include_List.h"

//--------------------------------------------------------//

/*  Estimate inner/outer layer
    
    return value:
    0 = inside
    1 = x-axis outside
    2 = y-axis outside
    3 = xy-axis outside (corner)*/
uint8_t inner_outer_estimate(){
    
    uint8_t final_judgement = 0;
    int dx_peak_index = 0;
    int dy_peak_index = 0;
    int half_FFT_LEN = FFT_LEN/2;

    for (int i = 1; i < half_FFT_LEN; i++) // ピーク候補から0Hzは除外
    {
        if( (dx_FFT_result[i] > dx_FFT_result[i-1]) && (dx_FFT_result[i] > dx_FFT_result[i+1]) )
        {
            if (dx_FFT_result[i] > dy_FFT_result[i])
            {            
                if (dx_FFT_result[i] < FFT_result[i])
                {
                    if (dx_FFT_result[i] > PEAK_POWER_THRESHOLD)
                    {
                        final_judgement += 1;
                        dx_peak_index = i;
                        // MPLog("%5.5f        %5.5f\n", FFT_result[i], dx_FFT_result[i]);
                        // MPLog("\n");
                        break;
                    }                    
                } else {
                    dx_peak_index = i;
                    break;
                }
            }
        }
    }
    
    for (int i = 1; i < half_FFT_LEN; i++) // ピーク候補から0Hzは除外
    {
        if( (dy_FFT_result[i] > dy_FFT_result[i-1]) && (dy_FFT_result[i] > dy_FFT_result[i+1]) )
        {
            if (dy_FFT_result[i] > dx_FFT_result[i])
            {
                if (dy_FFT_result[i] < FFT_result[i])
                {
                    if (dy_FFT_result[i] > PEAK_POWER_THRESHOLD)
                    {
                        final_judgement += 2;
                        dy_peak_index = i;
                        // MPLog("%5.5f        %5.5f\n", FFT_result[i], dy_FFT_result[i]);
                        // MPLog("\n");
                        break;
                    }                    
                } else {
                    dy_peak_index = i;
                    break;
                }
            }
        }
    }

    // MPLog("%5.5f        %5.5f\n", FFT_result[dx_peak_index], dx_FFT_result[dx_peak_index]);
    // MPLog("%d\n", dy_peak_index);
    // MPLog("%5.5f        %5.5f\n", FFT_result[dy_peak_index], dy_FFT_result[dy_peak_index]);
    // MPLog("%d\n", final_judgement);
    // MPLog("\n");

    if (final_judgement > 0)
    {
        // outside
        digitalWrite(OUTSIDE_LED, HIGH);
        digitalWrite(INSIDE_LED, LOW);
    } else {
        // inside
        digitalWrite(OUTSIDE_LED, LOW);
        digitalWrite(INSIDE_LED, HIGH);
    }

    return final_judgement;
}

// preprocessor function for FFT result
void FFT_result_processing(){
    float temp[FFT_LEN];

    temp[0] = (FFT_result[0]*2+FFT_result[1]+FFT_result[2]+FFT_result[3])/5;
    temp[1] = (FFT_result[0]+FFT_result[1]*2+FFT_result[2]+FFT_result[3]+FFT_result[4])/6;
    temp[2] = (FFT_result[0]+FFT_result[1]+FFT_result[2]*2+FFT_result[3]+FFT_result[4]+FFT_result[5])/7;
    // temp[3] = (FFT_result[0]+FFT_result[1]+FFT_result[2]+FFT_result[3]+FFT_result[4]+FFT_result[5]+FFT_result[6])/7;

    for (int i = 3; i < FFT_LEN-3; i++){
        temp[i] = (FFT_result[i-3]+FFT_result[i-2]+FFT_result[i-1]
                    +FFT_result[i]*2
                    +FFT_result[i+1]+FFT_result[i+2]+FFT_result[i+3]) /8;
    }

    temp[FFT_LEN-3] = (FFT_result[FFT_LEN-6]+FFT_result[FFT_LEN-5]+FFT_result[FFT_LEN-4]+FFT_result[FFT_LEN-3]*2+FFT_result[FFT_LEN-2]+FFT_result[FFT_LEN-1])/7;
    temp[FFT_LEN-2] = (FFT_result[FFT_LEN-5]+FFT_result[FFT_LEN-4]+FFT_result[FFT_LEN-3]+FFT_result[FFT_LEN-2]*2+FFT_result[FFT_LEN-1])/6;
    temp[FFT_LEN-1] = (FFT_result[FFT_LEN-4]+FFT_result[FFT_LEN-3]+FFT_result[FFT_LEN-2]+FFT_result[FFT_LEN-1]*2)/5;

    static int count2 = 0;
    if (count2 == 20)
    {
        count2 = 0;

        MPLog("phi FFT moving average result\n");
        for (int i = 0; i < FFT_LEN/16; i++)
        {
            MPLog("%5.5f\n", temp[i]);
        }

        MPLog("\n");
    }
    count2++;
}

// function for checking existence of peak in FFT result
bool peak_check(){
    bool has_peak_flag = false;
    bool all_zero_flag = true;
    
    // phi FFT result
    for (int i = 1; i < FFT_LEN/2; i++)
    {
        if (FFT_result[i] != 0.0)
        {
            all_zero_flag = false;
        }
        if ( (FFT_result[i] > FFT_result[i-1]) && (FFT_result[i] > FFT_result[i+1]) )
        {
            if (FFT_result[i] > PEAK_POWER_THRESHOLD)
            {
                has_peak_flag = true;
            }
        }
    }
    if (!has_peak_flag && !all_zero_flag)
    {
        return false;
    }
    
    // dx phi FFT result
    has_peak_flag = false;
    all_zero_flag = true;
    for (int i = 1; i < FFT_LEN/2; i++)
    {
        if (dx_FFT_result[i] != 0.0)
        {
            all_zero_flag = false;
        }
        if ( (dx_FFT_result[i] > dx_FFT_result[i-1]) && (dx_FFT_result[i] > dx_FFT_result[i+1]) )
        {
            if (dx_FFT_result[i] > PEAK_POWER_THRESHOLD)
            {
                has_peak_flag = true;
            }
        }
    }
    if (!has_peak_flag && !all_zero_flag)
    {
        return false;
    }

    // dy phi FFT result
    has_peak_flag = false;
    all_zero_flag = true;
    for (int i = 1; i < FFT_LEN/2; i++)
    {
        if (dy_FFT_result[i] != 0.0)
        {
            all_zero_flag = false;
        }
        if ( (dy_FFT_result[i] > dy_FFT_result[i-1]) && (dy_FFT_result[i] > dy_FFT_result[i+1]) )
        {
            if (dy_FFT_result[i] > PEAK_POWER_THRESHOLD)
            {
                has_peak_flag = true;
            }
        }
    }
    if (!has_peak_flag && !all_zero_flag)
    {
        return false;
    }

    // all has peak or is zero array, return true
    return true;
}

// helper function for displaying variable value
void fft_data_print_out(){
    static int count = 0;
    if (count == 20)
    {
        count = 0;
        
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
        for (int i = 0; i < FFT_LEN/16; i++)
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

        // MPLog("dy phi FFT result\n");
        // for (int i = 0; i < FFT_LEN/16; i++)
        // {
        //     MPLog("%5.5f\n", dy_FFT_result[i]);
        // }

        MPLog("\n");
    }
    count++;
}

// helper function for updating phi
void phi_update(uint32_t msgdata){
    for (int i = FFT_LEN-1; i > 0; i--)
    {
        phi_buffer[i] = phi_buffer[i-1];
    }
    phi_buffer[0] = ((float)msgdata-FFT_MIDSHIFT)/FFT_MSG_SCALE;
    for (int i = 0; i < FFT_LEN; i++)
    {
        input_buffer[i] = phi_buffer[i];
    }
}

// helper function for updating dx_phi
void dx_phi_update(uint32_t msgdata){
    for (int i = FFT_LEN-1; i > 0; i--)
    {
        dx_phi_buffer[i] = dx_phi_buffer[i-1];
    }
    dx_phi_buffer[0] = ((float)msgdata-FFT_MIDSHIFT)/FFT_MSG_SCALE;
    for (int i = 0; i < FFT_LEN; i++)
    {
        dx_input_buffer[i] = dx_phi_buffer[i];
    }
}

// helper function for updating dy_phi
void dy_phi_update(uint32_t msgdata){
    for (int i = FFT_LEN-1; i > 0; i--)
    {
        dy_phi_buffer[i] = dy_phi_buffer[i-1];
    }
    dy_phi_buffer[0] = ((float)msgdata-FFT_MIDSHIFT)/FFT_MSG_SCALE;
    for (int i = 0; i < FFT_LEN; i++)
    {
        dy_input_buffer[i] = dy_phi_buffer[i];
    }
}

// init all phi arrays
void phi_init(){
    for (int i = 0; i < FFT_LEN; i++)
    {
        //phi
        phi_buffer[i] = 0.0;
        input_buffer[i] = 0.0;
        output_buffer[i] = 0.0;
        FFT_result[i] = 0.0;
        //dx phi
        dx_phi_buffer[i] = 0.0;
        dx_input_buffer[i] = 0.0;
        dx_output_buffer[i] = 0.0;
        dx_FFT_result[i] = 0.0;
        //dy phi
        dy_phi_buffer[i] = 0.0;
        dy_input_buffer[i] = 0.0;
        dy_output_buffer[i] = 0.0;
        dy_FFT_result[i] = 0.0;
    }
}

// init FFT_calculation class
void arm_fft_init(){
    bool isok = true;
    
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
        isok = false;
        break;
    }

    if (!isok)
    {
        MPLog("Error : FFT_LEN invalid !! Please check definition of fft_init().");
    }
    
}

// (from Origane san) get peak index & calc frequency
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

// (from Origane san) calc swarm size
float length_estimation(float f_peak_inScope){
    if (f_peak_inScope<=0){
        return -1;
    }
    return 0.5f*sqrt(kappa)/f_peak_inScope;  // l = sqrt(kappa)/(2*f_peak)
}

#endif