//Written by MAX (Created 20-06-2022)

//Features : Main program for Spresense

//--------------------------------------------------------//

//files created by me(max12345)
#include "Spresense_Pin_Mapping.h"
#include "Spresense_Init.h"
#include "Spresense_Tool.h"
#include "Spresense_Test.h"
#include "Spresense_Global_Var_Def.h"
//files from libraries
#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>
#include <Camera.h>

#define from_MAX 12345

//--------------------------------------------------------//

//PIN Variables

//--------------------------------------------------------//

//FUNCTION Declaration


//--------------------------------------------------------//

//MAIN PROGRAM
void setup() {

    //Spresense Init
    Onboard_LED_Init();
    I2C_Init();
    PIKAPIKA_Init();
    Serial_Init();
    Finish_Init_LED_Flash();
    Serial.println("Init finished successfully");
    
    //TEST FUNCTION
    test_init();
}
void loop() {
    
    //TEST FUNCTION
    test_loop();
    
}

// 3.5. I2Cの使用方法
// Spresenseではメインボードと拡張ボードにそれぞれI2C接続に使用できる端子が１系統用意されています。

// インターフェース電圧はメインボードが1.8V、拡張ボードが5Vまたは3.3Vになります。
// 通信速度は最大で400kbpsとなります。

// メインボードと拡張ボードはI2Cとしては同一の系統となりますが、接続するデバイスのスレーブアドレスを変更することにより、同時に使用することが可能です。

// メインボードでは4.7kΩで1.8Vに、拡張ボードでは1kΩで5Vまたは3.3Vにプルアップされています。



// 16.3.4. GPIO 割り込み設定
// GPIO 割り込みを使用する場合は次のように行います。

// static int gpio_handler(int irq, FAR void *context, FAR void *arg)
// {
//   /* 割り込みハンドラ */
// }

//   /* 割り込み設定 */

//   board_gpio_intconfig(PIN_XXX, INT_HIGH_LEVEL,  false, gpio_handler); 
//   board_gpio_intconfig(PIN_XXX, INT_LOW_LEVEL,   false, gpio_handler); 
//   board_gpio_intconfig(PIN_XXX, INT_RISING_EDGE,  true, gpio_handler); 
//   board_gpio_intconfig(PIN_XXX, INT_FALLING_EDGE, true, gpio_handler); 
//   board_gpio_intconfig(PIN_XXX, INT_BOTH_EDGE,    true, gpio_handler); 

//   board_gpio_int(PIN_XXX, false); 
//   board_gpio_int(PIN_XXX, true);  
// PIN_XXX を HIGH レベル割り込みを設定し、割り込みハンドラを登録します。
// PIN_XXX を LOW レベル割り込みを設定、割り込みハンドラを登録します。
// PIN_XXX を立ち上がりエッジ割り込みを設定し、割り込みハンドラを登録します。ノイズフィルタを有効にしています。
// PIN_XXX を立ち下がりエッジ割り込みを設定し、割り込みハンドラを登録します。ノイズフィルタを有効にしています。
// PIN_XXX を両エッジ割り込みを設定し、割り込みハンドラを登録します。ノイズフィルタを有効にしています。
// PIN_XXX の割り込みを禁止します。
// PIN_XXX の割り込みを許可します。