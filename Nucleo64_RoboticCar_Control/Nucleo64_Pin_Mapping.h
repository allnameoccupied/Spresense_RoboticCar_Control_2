//Written by MAX (Created 12-06-2022)

/*Features :    Which Nucleo-64 pins are used & 
                What are their usages
*/

#ifndef NUCLEO_PINMAP_H
#define NUCLEO_PINMAP_H

#include "mbed.h"

//--------------------------------------------------------//

//PIN defined in library, duplicated here for reference
// #define LED1         PA_5
// #define BUTTON1      PC_13
// #define CONSOLE_TX   PA_2
// #define CONSOLE_RX   PA_3

//--------------------------------------------------------//

#define I2C_M_SDA_PIN   PB_9
#define I2C_M_SCL_PIN   PB_8

//--------------------------------------------------------//

//DIR 1 -> forward
//DIR 2 -> backward

#define M1_PWM_PIN      PA_8
#define M1_DIR_1_PIN    PIM_DUMP
#define M1_DIR_2_PIN    PIM_DUMP
#define M1_HALL_1_PIN   PIM_DUMP
#define M1_HALL_2_PIN   PIM_DUMP

#define M2_PWM_PIN      PA_0
#define M2_DIR_1_PIN    PIM_DUMP
#define M2_DIR_2_PIN    PIM_DUMP
#define M2_HALL_1_PIN   PIM_DUMP
#define M2_HALL_2_PIN   PIM_DUMP

#define M3_PWM_PIN      PA_6
#define M3_DIR_1_PIN    PIM_DUMP
#define M3_DIR_2_PIN    PIM_DUMP
#define M3_HALL_1_PIN   PIM_DUMP
#define M3_HALL_2_PIN   PIM_DUMP

#define M4_PWM_PIN      PB_6
#define M4_DIR_1_PIN    PIM_DUMP
#define M4_DIR_2_PIN    PIM_DUMP
#define M4_HALL_1_PIN   PIM_DUMP
#define M4_HALL_2_PIN   PIM_DUMP

//--------------------------------------------------------//

#define PIM_DUMP        PA_1

#endif