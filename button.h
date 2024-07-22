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
    IDLE = 0, // 空闲
    PRESS, // 按下
    RELEASE, // 抬起
    LONG_RELEASE // 长按
}KEY_STATE;





typedef struct 
{
    void (*init)(int pin);
    #if useSTM32 
        int (*read)(GPIO_TypeDef PROT ,uint16_t gpio_pin); // 读取函数
    #endif
    #if useESP32 
        int (*read)(int pin); // 读取函数
    
    #endif
    // int (*read)(int pin);
    int (*Get_millis)(void); // 获取时间
    int PIN; // 管脚
    int KEY_UP; 
    int CURRENT_TIME;// 按下时定时器
    int PRESS_DEBOUNCE_TIME; // 按下去抖时间
    int RELEASE_CURRENT_TIME;    // 抬起时定时器
    int LONG_RELEASE_TIME;    // 长按时长
    bool HAVE_LONG_PRESS; // 是否有长按
    int BUTTON_STATE; // 按键状态
    bool isPULLUP;// 是否上拉
   
}HardwareBtn_t;


#ifdef __cplusplus
extern "C" {
#endif
void hardware_btn_init(HardwareBtn_t *btn,int pin); // 初始化
void button_scan(HardwareBtn_t *btn);   // 按键扫描
void button_process(HardwareBtn_t *btn);    // 按键处理逻辑



#ifdef __cplusplus
}
#endif


#endif // BUTTON_H