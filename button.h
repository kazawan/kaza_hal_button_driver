#ifndef BUTTON_H
#define BUTTON_H


//! 选择模式 here  
// STM32 使用cubuxMX 不用配置init方法
// Arduino 使用Arduino.h
// ESP32 配置 driver/gpio.h
// 选择模式
#define useArduino 1    
#define useSTM32 0 
#define useESP32 1
//! Include here
#if useArduino  
#include <Arduino.h>
#endif

#if useSTM32
#include "stm32f1xx_hal.h"
#endif

#if useESP32
#include "driver/gpio.h"
#endif



// enum KEY_STATE
enum
{
    IDLE = 0,
    PRESS,
    RELEASE,
    LONG_RELEASE
}KEY_STATE;



typedef struct 
{
    void (*init)(int pin);
    #if useSTM32 
        int (*read)(GPIO_TypeDef PROT ,uint16_t gpio_pin);
    #endif
    #if useESP32 
        int (*read)(int pin);
    
    #endif
    // int (*read)(int pin);
    int (*Get_millis)(void);
    int PIN;
    int KEY_UP;
    int CURRENT_TIME;// 按下时定时器
    int PRESS_DEBOUNCE_TIME; // 按下去抖时间
    int RELEASE_CURRENT_TIME;    // 抬起时定时器
    int LONG_RELEASE_TIME;    // 长按时长
    bool HAVE_LONG_PRESS;
    int BUTTON_STATE;
   
}HardwareBtn_t;


#ifdef __cplusplus
extern "C" {
#endif
void hardware_btn_init(HardwareBtn_t *btn,int pin);
void button_scan(HardwareBtn_t *btn);   // 按键扫描
void button_process(HardwareBtn_t *btn);    // 按键处理逻辑



#ifdef __cplusplus
}
#endif


#endif // BUTTON_H