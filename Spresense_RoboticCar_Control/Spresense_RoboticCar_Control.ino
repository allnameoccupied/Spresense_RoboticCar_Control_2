//functions and classes by Max
#include "Board_init.h"
#include "LED.h"
#include "Motor.h"
#include "Motor_controller.h"
//for camera, tft LCD, SD card
#include <Arduino.h>
#include <Camera.h>
#include <SPI.h>
#include <SDHCI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <gfxfont.h>
#include <Adafruit_ILI9341.h>


#define from_MAX 12345

//Base definition of program behaviour
#define IS_USE_MOTOR        true       //use motor == not use tft_LCD

//PWM pin DEFINE
#define TOP_LEFT_PWM        PIN_D03
#define TOP_RIGHT_PWM       PIN_D05
#define BOT_LEFT_PWM        PIN_D06
#define BOT_RIGHT_PWM       PIN_D09
static const uint8_t PWM_pins[4] = {PIN_D06, PIN_D05, PIN_D09, PIN_D03};    //order of pin according to CXD5602 pwm pin order

//Direction pin DEFINE
//Currently using same pins for TOP & BOTTOM motors (7-4-2022)
//If use NOT gate, 2 more pins can be saved (7-4-2022)
#define TOP_LEFT_AHEAD      PIN_D02
#define TOP_LEFT_BACK       PIN_D04
#define TOP_RIGHT_AHEAD     PIN_D07
#define TOP_RIGHT_BACK      PIN_D08
#define BOT_LEFT_AHEAD      TOP_LEFT_AHEAD //PIN_D10
#define BOT_LEFT_BACK       TOP_LEFT_BACK //PIN_D11
#define BOT_RIGHT_AHEAD     TOP_RIGHT_AHEAD //PIN_D12
#define BOT_RIGHT_BACK      TOP_RIGHT_BACK //PIN_D13
static const uint8_t DIR_pins[4] = {PIN_D02, PIN_D04, PIN_D07, PIN_D08};
// static const uint8_t DIR_pins[8] = {PIN_D02, PIN_D04, PIN_D07, PIN_D08, PIN_D10, PIN_D11, PIN_D12, PIN_D13};

//Hall sensor pin DEFINE
//placeholder pin at this moment (9-4-2022)
#define TOP_LEFT_HALL_1     PIN_D00
#define TOP_LEFT_HALL_2     PIN_D00
#define TOP_RIGHT_HALL_1    PIN_D00
#define TOP_RIGHT_HALL_2    PIN_D00
#define BOT_LEFT_HALL_1     PIN_D00
#define BOT_LEFT_HALL_2     PIN_D00
#define BOT_RIGHT_HALL_1    PIN_D00
#define BOT_RIGHT_HALL_2    PIN_D00
static const uint8_t HALL_pins[1] = {PIN_D00};

//4 motors, initialized in setup()
//Disabled, directly controlled by motor controller (7-4-2022)
// static MotorM* top_left_motor = nullptr;
// static MotorM* top_right_motor = nullptr;
// static MotorM* bottom_left_motor = nullptr;
// static MotorM* bottom_right_motor = nullptr;

//Motor Controller, initialized in setup()
static MotorController* Motor_Controller = nullptr;

//TFT LCD, initialized in setup()
static Adafruit_ILI9341* TFT_LCD = nullptr;

//SD card, initialized in setup()
static SDClass SDcard;

//Camera, initialized in setup()
static CameraClass* Camera_Spresense = nullptr;


//MAIN PROGRAM
void setup() {
    //init Spresense
    LED_init();
    PIN_init_motor(IS_USE_MOTOR,PWM_pins,DIR_pins,HALL_pins);

    //init custom motor controller & program variables
    Motor_Controller = new MotorController( TOP_LEFT_AHEAD, TOP_LEFT_BACK, TOP_LEFT_PWM, TOP_LEFT_HALL_1, TOP_LEFT_HALL_2,
                                            TOP_RIGHT_AHEAD, TOP_RIGHT_BACK, TOP_RIGHT_PWM, TOP_RIGHT_HALL_1, TOP_RIGHT_HALL_2,
                                            BOT_LEFT_AHEAD, BOT_LEFT_BACK, BOT_LEFT_PWM, BOT_LEFT_HALL_1, BOT_LEFT_HALL_2,
                                            BOT_RIGHT_AHEAD, BOT_RIGHT_BACK, BOT_RIGHT_PWM, BOT_RIGHT_HALL_1, BOT_RIGHT_HALL_2);
    //Disabled (7-4-2022)
    // top_left_motor = Motor_Controller->get_top_left_motor();
    // top_right_motor = Motor_Controller->get_top_right_motor();
    // bottom_left_motor = Motor_Controller->get_bottom_left_motor();
    // bottom_right_motor = Motor_Controller->get_bottom_right_motor();

    //init Serial communication
    SERIAL_init();

    //init SD card
    SDcard_init(&SDcard);

    //init TFT LCD, also init 4 pins for buttons
    TFT_LCD = TFTLCD_init(!IS_USE_MOTOR);

    //init Camera
    Camera_init(&Camera_Spresense);

    //FOR TESTING USE
    init_test();

    //init finished
    Serial.println("init finished");
    LED_flash_init();
}
void loop() {
    // demo motor function
    // motor_controller->demo(1500,MAX_SPEED);
    // delay(1000);
    // motor_controller->demo(1500,MAX_SPEED/3);
    // delay(3000);

    //FOR TESTING USE
    loop_test();

    //blinks LED0 to show that system is not hanging
    LED_toggle_loop();
}


//FUNCTION for easier & clearer testing in init() & loop()
void init_test(){
    
}
void loop_test(){
    
}


//SUPPLEMENTARY FUNCTION

//make sure system not hanging
void LED_toggle_loop(){
    LED_TOGGLE(LED0);
    delay(100);
}
//show that init finished
void LED_flash_init() {
    LED_ON(LED0);
    delay(100);
    LED_ON(LED1);
    delay(100);
    LED_ON(LED2);
    delay(100);
    LED_ON(LED3);
    delay(1000);

    LED_OFF(LED0);
    delay(100);
    LED_OFF(LED1);
    delay(100);
    LED_OFF(LED2);
    delay(100);
    LED_OFF(LED3);
    delay(1000);
}