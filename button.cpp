#include "button.h"


void button_scan(HardwareBtn_t *btn)
{   

    /* 通过结构体内的isPULLUP 判断闭合时用 1 还是 0 */
    int KEY_CLOSE , KEY_OPEN ;
    if(btn->isPULLUP){
         KEY_CLOSE = 0 ;
         KEY_OPEN = 1 ;
    }else{
         KEY_CLOSE = 1 ;
         KEY_OPEN = 0 ;
    }



    if (btn->read(btn->PIN) == KEY_CLOSE && btn->KEY_UP == 1)
    {
        if (btn->Get_millis() - btn->CURRENT_TIME > btn->PRESS_DEBOUNCE_TIME)
        {
            if (btn->BUTTON_STATE == IDLE)
            {
                btn->BUTTON_STATE = PRESS;
                btn->KEY_UP = 0;
                btn->RELEASE_CURRENT_TIME = btn->Get_millis();
            }
        }
    }
    else if (btn->read(btn->PIN) == KEY_OPEN && btn->KEY_UP == 0)
    {
        if (btn->BUTTON_STATE == PRESS)
        {
            if (btn->Get_millis() - btn->RELEASE_CURRENT_TIME > btn->LONG_RELEASE_TIME && btn->HAVE_LONG_PRESS == true)
            {
                btn->BUTTON_STATE = LONG_RELEASE;
                btn->KEY_UP = 1;
                btn->CURRENT_TIME = btn->Get_millis();
                
            }else if(btn->Get_millis() - btn->RELEASE_CURRENT_TIME >btn -> PRESS_DEBOUNCE_TIME)
            {
                btn->BUTTON_STATE = RELEASE;
                btn->KEY_UP = 1;
                btn->CURRENT_TIME = btn->Get_millis();
            }   
        }

    }
}

