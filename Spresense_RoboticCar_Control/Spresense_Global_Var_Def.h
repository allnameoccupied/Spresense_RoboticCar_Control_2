// Written by MAX (Created 20-06-2022)

// Features : Global Variables & Constant Definitions for Spresense

//--------------------------------------------------------//

#ifndef SPRESENSE_GLOBAL_VAR_DEF_H
#define SPRESENSE_GLOBAL_VAR_DEF_H

// PI
#define PI                              3.14

// SubCore ID
#define SUBCORE_1_GENERAL_ID            1
#define SUBCORE_2_FFT_ID                2

// Serial Baud Rate
#define DEFAULT_BAUD_RATE               115200

// I2C
// -> Address of all components
#define NUCLEO_I2C_ADDR                 0x45>>1
#define DIST_SENSOR_1_I2C_ADDR          0x50
#define DIST_SENSOR_2_I2C_ADDR          0x52
#define DIST_SENSOR_3_I2C_ADDR          0x54
#define DIST_SENSOR_4_I2C_ADDR          0x56
#define DIST_SENSOR_5_I2C_ADDR          0x58
#define DIST_SENSOR_6_I2C_ADDR          0x5a
#define DIST_SENSOR_7_I2C_ADDR          0x5c
#define DIST_SENSOR_8_I2C_ADDR          0x5e
// -> Message Length
#define I2C_MSG_LENGTH                  32

// PikaPika
// -> Sensor Count
#define PIKAPIKA_SENSOR_COUNT           8
// -> Blink Duration
#define PIKAPIKA_BLINK_TIME             100     // LED点灯時間[回-dt]
// -> Light Sensor Lifetime
#define PIKAPIKA_LIGHT_SENSOR_LIFETIME  10     // [ticks]
// -> MIN Interval between Interrupts
#define PIKAPIKA_MIN_INTERRUPT_INTERVAL 75     // [ms]

#endif