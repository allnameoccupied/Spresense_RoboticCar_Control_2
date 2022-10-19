// Written by MAX (Created 07-09-2022)

// Features : Parameters & Settings for FFT

// Important: Each core share different of variable, even if same address

//--------------------------------------------------------//

#ifndef SPRESENSE_FFT_PARAM_H
#define SPRESENSE_FFT_PARAM_H

#include "Spresense_Include_List.h"

/* Use CMSIS library */
#define ARM_MATH_CM4
#define __FPU_PRESENT 1U
#include <cmsis/arm_math.h>

//--------------------------------------------------------//

// FFT Program Parameter
// -> Time related
#define FFT_UPDATE_PERIOD_US            100     // 制御周期[us] 100us -> 10kHz
#define FFT_TIME_RESOLUTION             0.000001
// -> Period - How often does main core sends phi data to FFT core (so that data is taken at correct interval)
#define FFT_PROCESS_PERIOD_US           (2.0*PI/Omega_0/2.0)/FFT_TIME_RESOLUTION/FFT_UPDATE_PERIOD_US      // 通報周期[us]
// -> Period - How often does FFt core actually carry out FFT
#define FFT_CALC_RATE                   4

// FFT Hyperparameter
arm_rfft_fast_instance_f32  FFT_instance;
#define FFT_MSG_SCALE       10000.0
#define FFT_MIDSHIFT        100000000.0
// #define FFT_LEN             256    //original
#define FFT_LEN             512
#define FFT_MAX_CHANNEL_NUM 1

// FFT Parameter
#define dt                  FFT_TIME_RESOLUTION * FFT_UPDATE_PERIOD_US
// #define Omega_0             20.0            // 固有角速度 [rad\s]（振動）    //original
#define Omega_0             20.0            // 固有角速度 [rad\s]（振動）
// #define kappa               0.65             // 結合強度（振動型）    //original
#define kappa               0.65             // 結合強度（振動型）
#define my_gamma            0.20            // 粘性係数
// #define PEAK_POWER_THRESHOLD        3.0     // 観測している位相のピークパワーがこれを下回ったら検出扱いにしない    //original
#define PEAK_POWER_THRESHOLD        3.0     // 観測している位相のピークパワーがこれを下回ったら検出扱いにしない
#define SELF_EXITATION_INTENSITY    2.0     // 自励入力の大きさ
// #define GAMMA_CONST_1       0.09            // 動的粘性の定数項      //original
// #define GAMMA_CONST_2       0.09            // 動的粘性のエッジ数に比例する項    //original
#define GAMMA_CONST_1       0.09            // 動的粘性の定数項
#define GAMMA_CONST_2       0.09            // 動的粘性のエッジ数に比例する項
#define DXPHI_MULTIPLIER    0.525
// #define DYPHI_MULTIPLIER    0.525    //original
#define DYPHI_MULTIPLIER    0.525

// FFT Variables
double  mod_varphi          = 0.0;
double  varphi              = 0.0;          // 出力位相 phi+phi_bar [rad]
double  phi_bar             = 0.0;          // 相互作用無しの位相 [rad]
double  phi                 = 0.0;          // 相互作用位相 [rad]
double  sum_dphi            = 0.0;
double  adaptive_gamma      = GAMMA_CONST_1;// 定数項
double  dphi[PIKAPIKA_SENSOR_COUNT] =       // 各方向の位相差 [rad]
            {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}; 
double  c_fft               = 0.0;

// FFT Runtime Variables
bool    is_Self_Excitation = false;
uint8_t PikaPika_light_sensor_life[PIKAPIKA_SENSOR_COUNT] = {0,0,0,0,0,0,0,0};
// -> phi
float   phi_buffer[FFT_LEN];
float   input_buffer[FFT_LEN];
float   output_buffer[FFT_LEN];
float   FFT_result[FFT_LEN];
// -> dx phi
float   dx_phi_buffer[FFT_LEN];
float   dx_input_buffer[FFT_LEN];
float   dx_output_buffer[FFT_LEN];
float   dx_FFT_result[FFT_LEN];
// -> dy phi
float   dy_phi_buffer[FFT_LEN];
float   dy_input_buffer[FFT_LEN];
float   dy_output_buffer[FFT_LEN];
float   dy_FFT_result[FFT_LEN];

#endif