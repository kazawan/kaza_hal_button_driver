# 测试简易移植按键库

version v0.3

v0.3 
  * 增加适配上下拉    
  * 增加中文注释    
v0.2
  * 增加适配STM32 HAL    
v0.1
  * 暂时只适配 arduino esp32   


## 配置管脚 api

生成`button_config.h`

```c
#include "button.h"

void  btn_init(int pin)
{
    gpio_num_t gpio_num = (gpio_num_t)pin;
    gpio_config_t ioConfig = {
        .pin_bit_mask = 1ULL << gpio_num,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&ioConfig);
}

int btn_read(int pin)
{
    gpio_num_t gpio_num = (gpio_num_t)pin;
    return gpio_get_level(gpio_num);
}

int get_millis()
{
    return millis();
}


void hardware_btn_init(HardwareBtn_t *btn,int pin)
{
    gpio_num_t gpio_num = (gpio_num_t)pin;
    btn->read = btn_read;
    btn->init = btn_init;
    btn->Get_millis = get_millis;
    btn->PIN = gpio_num;


    btn->CURRENT_TIME = 0;
    btn->RELEASE_CURRENT_TIME = 0;
    btn->PRESS_DEBOUNCE_TIME = 50; // 按下去抖时间
    btn->LONG_RELEASE_TIME = 2000; // 长按时长
    btn->HAVE_LONG_PRESS = true;
    btn->BUTTON_STATE = IDLE;
    btn->KEY_UP = 1;

    #if useSTM32 == 0
    btn->init(pin);
    #endif

}

```

## 使用

`main.cpp`

配置 `button_process(HardwareBtn_t *btn)` 函数

```c
void button_process(HardwareBtn_t *btn)
{
  {
    switch (btn->PIN)
    {
    case button1:
      key_opt_state(&btn1); // 按键1处理逻辑
      break;
    case button2:
      key_opt2_state(&btn2); // 按键2处理逻辑
      break;
    }
  }
}
```

## 初始化方法

先抽象按键

```c
HardwareBtn_t btn1 ;
```

### 第一种



```c
  btn1.init = btn_init;   // 初始化
  btn1.read = btn_read;  // 读取按键状态
  btn1.Get_millis =get_millis; // 获取时间
  btn1.PIN = button1; // 按键引脚
  btn1.KEY_UP = 1; // 按键状态
  btn1.CURRENT_TIME = 0; // 按下时定时器
  btn1.RELEASE_CURRENT_TIME = 0; // 抬起时定时器
  btn1.PRESS_DEBOUNCE_TIME = 50; // 按下去抖时间
  btn1.LONG_RELEASE_TIME = 2000; // 长按时长
  btn1.HAVE_LONG_PRESS = false; // 是否有长按
  btn1.BUTTON_STATE = IDLE; // 按键状态
  btn1.init(button1); // 初始化按键

```

### 第二种

在`button_config.h` 配置 `void hardware_btn_init(HardwareBtn_t *btn,int pin)` 函数

```c

void hardware_btn_init(HardwareBtn_t *btn,int pin)
{
    gpio_num_t gpio_num = (gpio_num_t)pin; // 类型转换
    btn->read = btn_read; // 读取函数
    btn->init = btn_init; // 初始化函数
    btn->Get_millis = get_millis;  // 获取时间函数
    btn->PIN = gpio_num; // 管脚


    btn->CURRENT_TIME = 0; // 按下时定时器
    btn->RELEASE_CURRENT_TIME = 0; // 抬起时定时器
    btn->PRESS_DEBOUNCE_TIME = 50; // 按下去抖时间
    btn->LONG_RELEASE_TIME = 2000; // 长按时长
    btn->HAVE_LONG_PRESS = true; // 是否有长按
    btn->BUTTON_STATE = IDLE; // 按键状态
    btn->KEY_UP = 1; // 按键状态

    #if useSTM32 == 0
    btn->init(pin); // 初始化
    #endif

}
```

## 使用

```c
  button_scan(&btn1);
  button_process(&btn1);

```
