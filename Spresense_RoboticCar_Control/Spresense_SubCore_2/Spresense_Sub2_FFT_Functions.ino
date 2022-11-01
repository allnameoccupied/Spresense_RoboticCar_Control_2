// Written by MAX (Created 18-10-2022)

// Features : FFT related functions for Sub2

//--------------------------------------------------------//

#if (SUBCORE == 2)

//--------------------------------------------------------//

#include "Spresense_Sub2_FFT_Functions.h"
#include "C:/Users/Max/Documents/Workspace/Spresense_RoboticCar_Control_2/Spresense_RoboticCar_Control/Spresense_Include_List.h"

//--------------------------------------------------------//

/*  Estimate inner/outer layer

    For inside robot:  1st peak of dx/dy phi should correspond to a TROUGH in phi
    For outside robot: 1st peak of dx/dy phi should correspond to a PEAK in phi
    
    return value:
    0 = inside
    1 = x-axis outside
    2 = y-axis outside
    3 = xy-axis outside (corner)*/
uint8_t inner_outer_estimate(){
    
    static const int start_index = 4;
    uint8_t final_judgement = 0;
    int dx_peak_index = 0;
    int dy_peak_index = 0;

    // dx direction
    for (int i = start_index+2; i < FFT_LEN/8; i++) // ピーク候補から0Hzは除外
    {
        if( (dx_FFT_result_processed[i] > dx_FFT_result_processed[i-1]) && (dx_FFT_result_processed[i] > dx_FFT_result_processed[i+1]) )
        {
            if (dx_FFT_result_processed[i] > dy_FFT_result_processed[i])
            {
                if ((FFT_result_processed[i]<FFT_result_processed[i-1]) && (FFT_result_processed[i]<FFT_result_processed[i+1]))
                {
                    //inside
                    dx_peak_index = i;
                    break;
                }
                if ((FFT_result_processed[i]>FFT_result_processed[i-1]) && (FFT_result_processed[i]>FFT_result_processed[i+1]))
                {
                    //outside
                    final_judgement += 1;
                    dx_peak_index = i;
                    // MPLog("%5.5f        %5.5f\n", FFT_result[i], dx_FFT_result[i]);
                    // MPLog("\n");
                    break;
                }

                int x_neighbor = 1;
                while (1)
                {
                    if ((FFT_result_processed[i-x_neighbor]<FFT_result_processed[i-x_neighbor-1]) && (FFT_result_processed[i-x_neighbor]<FFT_result_processed[i-x_neighbor+1]))
                    {
                        //inside
                        dx_peak_index = i;
                        break;
                    }
                    if ((FFT_result_processed[i-x_neighbor]>FFT_result_processed[i-x_neighbor-1]) && (FFT_result_processed[i-x_neighbor]>FFT_result_processed[i-x_neighbor+1]))
                    {
                        //outside
                        final_judgement += 1;
                        dx_peak_index = i;
                        // MPLog("%5.5f        %5.5f\n", FFT_result[i], dx_FFT_result[i]);
                        // MPLog("\n");
                        break;
                    }
                    if ((FFT_result_processed[i+x_neighbor]<FFT_result_processed[i+x_neighbor-1]) && (FFT_result_processed[i+x_neighbor]<FFT_result_processed[i+x_neighbor+1]))
                    {
                        //inside
                        dx_peak_index = i;
                        break;
                    }
                    if ((FFT_result_processed[i+x_neighbor]>FFT_result_processed[i+x_neighbor-1]) && (FFT_result_processed[i+x_neighbor]>FFT_result_processed[i+x_neighbor+1]))
                    {
                        //outside
                        final_judgement += 1;
                        dx_peak_index = i;
                        // MPLog("%5.5f        %5.5f\n", FFT_result[i], dx_FFT_result[i]);
                        // MPLog("\n");
                        break;
                    }
                    if (x_neighbor>5)
                    {
                        // default, assume outside
                        final_judgement += 1;
                        dx_peak_index = i;
                        // MPLog("%5.5f        %5.5f\n", FFT_result[i], dx_FFT_result[i]);
                        // MPLog("\n");
                        break;
                    }
                    x_neighbor++;
                }
                break;  // all possible cases handled above
            }
        }
    }
    
    // dy direction
    for (int i = start_index+2; i < FFT_LEN/8; i++) // ピーク候補から0Hzは除外
    {
        if( (dy_FFT_result_processed[i] > dy_FFT_result_processed[i-1]) && (dy_FFT_result_processed[i] > dy_FFT_result_processed[i+1]) )
        {
            if (dy_FFT_result_processed[i] > dx_FFT_result_processed[i])
            {
                if ((FFT_result_processed[i]<FFT_result_processed[i-1]) && (FFT_result_processed[i]<FFT_result_processed[i+1]))
                {
                    //inside
                    dy_peak_index = i;
                    break;
                }
                if ((FFT_result_processed[i]>FFT_result_processed[i-1]) && (FFT_result_processed[i]>FFT_result_processed[i+1]))
                {
                    //outside
                    final_judgement += 2;
                    dy_peak_index = i;
                    // MPLog("%5.5f        %5.5f\n", FFT_result[i], dy_FFT_result[i]);
                    // MPLog("\n");
                    break;
                }

                int y_neighbor = 1;
                while (1)
                {
                    if ((FFT_result_processed[i-y_neighbor]<FFT_result_processed[i-y_neighbor-1]) && (FFT_result_processed[i-y_neighbor]<FFT_result_processed[i-y_neighbor+1]))
                    {
                        //inside
                        dy_peak_index = i;
                        break;
                    }
                    if ((FFT_result_processed[i-y_neighbor]>FFT_result_processed[i-y_neighbor-1]) && (FFT_result_processed[i-y_neighbor]>FFT_result_processed[i-y_neighbor+1]))
                    {
                        //outside
                        final_judgement += 2;
                        dy_peak_index = i;
                        // MPLog("%5.5f        %5.5f\n", FFT_result[i], dy_FFT_result[i]);
                        // MPLog("\n");
                        break;
                    }
                    if ((FFT_result_processed[i+y_neighbor]<FFT_result_processed[i+y_neighbor-1]) && (FFT_result_processed[i+y_neighbor]<FFT_result_processed[i+y_neighbor+1]))
                    {
                        //inside
                        dy_peak_index = i;
                        break;
                    }
                    if ((FFT_result_processed[i+y_neighbor]>FFT_result_processed[i+y_neighbor-1]) && (FFT_result_processed[i+y_neighbor]>FFT_result_processed[i+y_neighbor+1]))
                    {
                        //outside
                        final_judgement += 2;
                        dy_peak_index = i;
                        // MPLog("%5.5f        %5.5f\n", FFT_result[i], dy_FFT_result[i]);
                        // MPLog("\n");
                        break;
                    }
                    if (y_neighbor>5)
                    {
                        // default, assume outside
                        final_judgement += 2;
                        dy_peak_index = i;
                        // MPLog("%5.5f        %5.5f\n", FFT_result[i], dy_FFT_result[i]);
                        // MPLog("\n");
                        break;
                    }
                    y_neighbor++;
                }
                break;  // all possible cases handled above
            }
        }
    }

    // make judgement (by turning on LED)
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

    // [Debug use] print out data
    static int count = 0;
    if (count == 5)
    {
        count = 0;

        // MPLog("%5.5f        %5.5f\n", FFT_result[dx_peak_index], dx_FFT_result[dx_peak_index]);
        // MPLog("%d\n", dx_peak_index);
        MPLog("%d\n", dy_peak_index);
        // MPLog("%5.5f        %5.5f\n", FFT_result[dy_peak_index], dy_FFT_result[dy_peak_index]);
        MPLog("%d\n", final_judgement);
        MPLog("\n");
    }
    count++;
    
    // return judgement
    return final_judgement;
}

/* preprocessor function for FFT result
   
   Current method : Savitzky–Golay filter (window size = 7) -> Moving average (window size = 3)
   
//    Peak   -> FFT_peak_trough_pos[i] = 2
//    Trough -> FFT_peak_trough_pos[i] = 1
//    Other  -> FFT_peak_trough_pos[i] = 0*/
void FFT_result_processing(){
    static const int start_index = 4;

    // process data
    // process to FFT_LEN/8 only as peak/trough should appear in this range already
    for (int i = start_index; i < FFT_LEN/8; i++)
    {
        // phi
        FFT_result_processed[i] = ( 5*FFT_result[i-4] -25*FFT_result[i-3] +50*FFT_result[i-2] +176*FFT_result[i-1]
                                    +281*FFT_result[i]
                                    +176*FFT_result[i+1] +50*FFT_result[i+2] -25*FFT_result[i+3] +5*FFT_result[i+4])/693;

        // dx_phi
        dx_FFT_result_processed[i] = ( 5*dx_FFT_result[i-4] -25*dx_FFT_result[i-3] +50*dx_FFT_result[i-2] +176*dx_FFT_result[i-1]
                                    +281*dx_FFT_result[i]
                                    +176*dx_FFT_result[i+1] +50*dx_FFT_result[i+2] -25*dx_FFT_result[i+3] +5*dx_FFT_result[i+4])/693;

        // dy_phi
        dy_FFT_result_processed[i] = ( 5*dy_FFT_result[i-4] -25*dy_FFT_result[i-3] +50*dy_FFT_result[i-2] +176*dy_FFT_result[i-1]
                                    +281*dy_FFT_result[i]
                                    +176*dy_FFT_result[i+1] +50*dy_FFT_result[i+2] -25*dy_FFT_result[i+3] +5*dy_FFT_result[i+4])/693;
    }

    // //look for peak/trough
    // for (int i = start_index+1; i < FFT_LEN/8; i++)
    // {
    //     // phi
    //     if ((FFT_result_processed[i]>FFT_result_processed[i-1]) && (FFT_result_processed[i]>FFT_result_processed[i+1]))
    //     {
    //         FFT_peak_trough_pos[i] = 2;
    //     }
    //     if ((FFT_result_processed[i]<FFT_result_processed[i-1]) && (FFT_result_processed[i]<FFT_result_processed[i+1]))
    //     {
    //         FFT_peak_trough_pos[i] = 1;
    //     }

    //     // dx_phi
    //     if ((dx_FFT_result_processed[i]>dx_FFT_result_processed[i-1]) && (dx_FFT_result_processed[i]>dx_FFT_result_processed[i+1]))
    //     {
    //         dx_FFT_peak_trough_pos[i] = 2;
    //     }
    //     if ((dx_FFT_result_processed[i]<dx_FFT_result_processed[i-1]) && (dx_FFT_result_processed[i]<dx_FFT_result_processed[i+1]))
    //     {
    //         dx_FFT_peak_trough_pos[i] = 1;
    //     }

    //     // dy_phi
    //     if ((dy_FFT_result_processed[i]>dy_FFT_result_processed[i-1]) && (dy_FFT_result_processed[i]>dy_FFT_result_processed[i+1]))
    //     {
    //         dy_FFT_peak_trough_pos[i] = 2;
    //     }
    //     if ((dy_FFT_result_processed[i]<dy_FFT_result_processed[i-1]) && (dy_FFT_result_processed[i]<dy_FFT_result_processed[i+1]))
    //     {
    //         dy_FFT_peak_trough_pos[i] = 1;
    //     }
    // }   
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
    if (count == 5)
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

        MPLog("FFT_result\n");
        for (int i = 0; i < FFT_LEN/32; i++)
        {
            MPLog("%5.5f\n", FFT_result[i]);
        }

        MPLog("FFT_result_processed\n");
        for (int i = 0; i < FFT_LEN/32; i++)
        {
            MPLog("%5.5f\n", FFT_result_processed[i]);
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

        MPLog("dy_FFT_result_processed result\n");
        for (int i = 0; i < FFT_LEN/32; i++)
        {
            MPLog("%5.5f\n", dy_FFT_result_processed[i]);
        }

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
        FFT_result_processed[i] = 0.0;
        FFT_peak_trough_pos[i] = 0;
        //dx phi
        dx_phi_buffer[i] = 0.0;
        dx_input_buffer[i] = 0.0;
        dx_output_buffer[i] = 0.0;
        dx_FFT_result[i] = 0.0;
        dx_FFT_result_processed[i] = 0.0;
        dx_FFT_peak_trough_pos[i] = 0;
        //dy phi
        dy_phi_buffer[i] = 0.0;
        dy_input_buffer[i] = 0.0;
        dy_output_buffer[i] = 0.0;
        dy_FFT_result[i] = 0.0;
        dy_FFT_result_processed[i] = 0.0;
        dy_FFT_peak_trough_pos[i] = 0;
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