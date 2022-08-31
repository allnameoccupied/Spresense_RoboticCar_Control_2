//Written by MAX (Created 20-06-2022)

/*Features :    Which Spresense pins are used & 
                What are their usages
*/

//Pin location (Extension Board): https://static.developer.sony.com/images/image/s3/uploads/2019/07/overview_hardware_extboard_signal-1.jpg?v=783850&jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ3aGl0ZWxpc3RTaXplcyI6WyIxMjAweEFVVE8iLCIxMDB4NjUiLCIxMDB4QVVUTyIsIjExMHg4MiIsIjc1MHhBVVRPIiwiMTAwMHhBVVRPIiwiMTIwMHhBVVRPIiwiMTIwMHg4MDAiLCIxOTIweEFVVE8iLCIxOTIweDEwMDAiLCIyMDB4MTUwIiwiMjI1eDE3MCIsIjIyNXhBVVRPIiwiMjI5eDMwMCIsIjM2OHhBVVRPIiwiNDUweDM0MCIsIjUwMHhBVVRPIiwiNzUweDUwMCIsIjd4MTAiLCI3eDEyIiwiN3gxNiIsIjd4MyIsIjd4NCIsIjd4NSIsIjd4NiIsIjd4NyIsIjd4OCIsIjd4OSJdLCJpbWFnZVZlcnNpb24iOiJ2NiIsImV4cCI6MTkwNDY4ODAwMDAwMH0.TWmRV6gNzeipUt0QoKyQXGF1gCXiJZEDTmKUYov7hv8

#ifndef SPRESENSE_PINMAP_H
#define SPRESENSE_PINMAP_H

//--------------------------------------------------------//

//PIN defined in library, duplicated here for reference
// #define LED0
// #define LED1
// #define LED2
// #define LED3

//--------------------------------------------------------//

#define I2C_M_SDA_PIN   PIN_D14
#define I2C_M_SCL_PIN   PIN_D15

//--------------------------------------------------------//

//Dist sensor XSHUT
#define DIST_XSHUT_0    PIN_D08
#define DIST_XSHUT_1    PIN_D09
#define DIST_XSHUT_2    PIN_D10
#define DIST_XSHUT_3    PIN_D11
#define DIST_XSHUT_4    PIN_D12
#define DIST_XSHUT_5    PIN_D13
#define DIST_XSHUT_6    PIN_D16
#define DIST_XSHUT_7    PIN_D17

//--------------------------------------------------------//

//PikaPika pins

#define LED_PIKA        PIN_D08

#define LIGHT_PIKA_0    PIN_D00
#define LIGHT_PIKA_1    PIN_D01
#define LIGHT_PIKA_2    PIN_D02
#define LIGHT_PIKA_3    PIN_D03
#define LIGHT_PIKA_4    PIN_D04
#define LIGHT_PIKA_5    PIN_D05
#define LIGHT_PIKA_6    PIN_D06
#define LIGHT_PIKA_7    PIN_D07

//--------------------------------------------------------//

//Inside / Outside LED pins

#define INSIDE_LED      PIN_D18     //GREEN
#define OUTSIDE_LED     PIN_D19     //RED

#endif