// Written by MAX (Created 18-10-2022)

// Features : FFT related functions for Sub2

//--------------------------------------------------------//

#if (SUBCORE == 2)

//--------------------------------------------------------//

#ifndef SPRESENSE_SUB2_FFT_FUNC
#define SPRESENSE_SUB2_FFT_FUNC

/*  Estimate inner/outer layer
    
    return value:
    0 = inside
    1 = x-axis outside
    2 = y-axis outside
    3 = xy-axis outside (corner)*/
uint8_t inner_outer_estimate();

// preprocessor function for FFT result
void FFT_result_processing();

// function for checking existence of peak in FFT result
bool peak_check();

// helper function for displaying variable value
void fft_data_print_out();

// helper function for updating phi
void phi_update(uint32_t msgdata);

// helper function for updating dx_phi
void dx_phi_update(uint32_t msgdata);

// helper function for updating dy_phi
void dy_phi_update(uint32_t msgdata);

// init all phi arrays
void phi_init();

// init FFT_calculation class
void arm_fft_init();

// (from Origane san) get peak index & calc frequency
float get_peak_frequency(float* FFT_result_inScope);

// (from Origane san) calc swarm size
float length_estimation(float f_peak_inScope);

#endif
#endif