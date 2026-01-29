#include "headfile.h"

void buzzer_light_init()
{
	  gpio_init(GPIOB, DL_GPIO_PIN_8, PB8, OUT);      // buzzer
  	gpio_init(GPIOB, DL_GPIO_PIN_26, PB26, OUT);    //light
    gpio_set(GPIOB, DL_GPIO_PIN_8,  1);
	  gpio_set(GPIOB, DL_GPIO_PIN_26, 0);	            
}

void beep()
{
    gpio_set(GPIOB, DL_GPIO_PIN_8,  0);
	  gpio_set(GPIOB, DL_GPIO_PIN_26, 1);
    tim_interrupt_ms_init(TIMG7, 500, 4);
}