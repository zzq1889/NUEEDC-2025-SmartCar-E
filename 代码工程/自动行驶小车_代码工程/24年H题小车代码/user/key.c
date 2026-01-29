#include "headfile.h"

extern int mode;
extern int set;

void key_init()
{
   set=0;
	 mode=0;
	 gpio_init(GPIOA, DL_GPIO_PIN_17, PA17, IN_UP); 
	 gpio_init(GPIOA, DL_GPIO_PIN_27, PA27, IN_UP); 
}


uint8_t key_GetNum(void)
{
	uint8_t KeyNum = 0;		
	
	if (gpio_get(GPIOA, DL_GPIO_PIN_17) == 0)			
	{
		delay_ms(20);											
		while (gpio_get(GPIOA, DL_GPIO_PIN_17) == 0);	
		delay_ms(20);											
		KeyNum = 1;												
	}
	
	if (gpio_get(GPIOA, DL_GPIO_PIN_27) == 0)			
	{
		delay_ms(20);										
		while (gpio_get(GPIOA, DL_GPIO_PIN_27) == 0);	
		delay_ms(20);											
		KeyNum = 2;											
	}
	
	  return KeyNum;		
}