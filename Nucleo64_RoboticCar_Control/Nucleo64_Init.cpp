//Written by MAX (Created 12-06-2022)

//Funtions : Nucleo-64 Initialization

#include "Nucleo64_init.h"

#include "mbed.h"
#include "Nucleo64_Pin_Mapping.h"
#include "Nucleo64_Tool.h"
#include <cstdint>

//init the 2 onboard components, simply that
void Onboard_LED_Init(DigitalOut*& LED){
    LED = new DigitalOut(LED1);
}
void Onboard_Button_Init(DigitalIn*& Button){
    Button = new DigitalIn(BUTTON1);
    Button->mode(PullDown);
}

//init I2C pins & I2C
void I2C_Init(I2C*& I2C_M){
    I2C_M = new I2C(I2C_M_SDA_PIN,I2C_M_SCL_PIN);
}

//init the pins for Motor Control
void Motor_PWM_Pin_Init(PwmOut* motor_PWM[]){       //1x4 pins
    motor_PWM[0] = new PwmOut(M1_PWM_PIN);
    motor_PWM[1] = new PwmOut(M2_PWM_PIN);
    motor_PWM[2] = new PwmOut(M3_PWM_PIN);
    motor_PWM[3] = new PwmOut(M4_PWM_PIN);
}
void Motor_DIR_Pin_Init(DigitalOut* motor_DIR[]){   //2x4 pins
    motor_DIR[0] = new DigitalOut(M1_DIR_1_PIN);
    motor_DIR[1] = new DigitalOut(M1_DIR_2_PIN);
    motor_DIR[2] = new DigitalOut(M2_DIR_1_PIN);
    motor_DIR[3] = new DigitalOut(M2_DIR_2_PIN);
    motor_DIR[4] = new DigitalOut(M3_DIR_1_PIN);
    motor_DIR[5] = new DigitalOut(M3_DIR_2_PIN);
    motor_DIR[6] = new DigitalOut(M4_DIR_1_PIN);
    motor_DIR[7] = new DigitalOut(M4_DIR_2_PIN);
}
void Motor_HALL_Pin_Init(InterruptIn* motor_HALL[],
                            uint16_t* motor_HALL_count[]){  //2x4 pins
    motor_HALL[0] = new InterruptIn(M1_HALL_1_PIN, PullDown);
    motor_HALL[0]->rise(&M1_HALL_1_handler);
    motor_HALL[1] = new InterruptIn(M1_HALL_2_PIN, PullDown);
    motor_HALL[1]->rise(&M1_HALL_2_handler);
    motor_HALL[2] = new InterruptIn(M2_HALL_1_PIN, PullDown);
    motor_HALL[2]->rise(&M2_HALL_1_handler);
    motor_HALL[3] = new InterruptIn(M2_HALL_2_PIN, PullDown);
    motor_HALL[3]->rise(&M2_HALL_2_handler);
    motor_HALL[4] = new InterruptIn(M3_HALL_1_PIN, PullDown);
    motor_HALL[4]->rise(&M3_HALL_1_handler);
    motor_HALL[5] = new InterruptIn(M3_HALL_2_PIN, PullDown);
    motor_HALL[5]->rise(&M3_HALL_2_handler);
    motor_HALL[6] = new InterruptIn(M4_HALL_1_PIN, PullDown);
    motor_HALL[6]->rise(&M4_HALL_1_handler);
    motor_HALL[7] = new InterruptIn(M4_HALL_2_PIN, PullDown);
    motor_HALL[7]->rise(&M4_HALL_2_handler);

    motor_HALL_count[0] = new uint16_t(0);
    motor_HALL_count[1] = new uint16_t(0);
    motor_HALL_count[2] = new uint16_t(0);
    motor_HALL_count[3] = new uint16_t(0);
}

//init Serial Communication
void Serial_Init(BufferedSerial*& Serial_M){
    Serial_M = new BufferedSerial(CONSOLE_TX,CONSOLE_RX);
    Serial_M->set_baud(9600);
    Serial_M->set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );
}

//--------------------------------------------------------//

//HALL Pin Interrupt Handler
void M1_HALL_1_handler(){
    *(motor_HALL_count[0])+=1;
    // serial_println("1");
    }
void M1_HALL_2_handler(){
    *(motor_HALL_count[1])+=1;
    // serial_println("2");
    }
void M2_HALL_1_handler(){*(motor_HALL_count[2])+=1;}
void M2_HALL_2_handler(){*(motor_HALL_count[3])+=1;}
void M3_HALL_1_handler(){*(motor_HALL_count[4])+=1;}
void M3_HALL_2_handler(){*(motor_HALL_count[5])+=1;}
void M4_HALL_1_handler(){*(motor_HALL_count[6])+=1;}
void M4_HALL_2_handler(){*(motor_HALL_count[7])+=1;}

//--------------------------------------------------------//

void Nucleo64_Init_Finished_Successfully(DigitalOut* LED){
    int dur = 60*1000;

    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur*3);

    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur*3);

    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur*3);

    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur*3);

    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur*3);

    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur*3);

    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur*3);
    LED->write(0);
    wait_us(dur*3);

    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur);
    LED->write(1);
    wait_us(dur);
    LED->write(0);
    wait_us(dur*3);
}