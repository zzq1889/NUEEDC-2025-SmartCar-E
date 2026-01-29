#include "headfile.h"

void track_init(void)
{
  gpio_init(GPIOB, DL_GPIO_PIN_13, PB13, IN_UP);   // D1
	gpio_init(GPIOB, DL_GPIO_PIN_15, PB15, IN_UP);   // D2
	gpio_init(GPIOA, DL_GPIO_PIN_31, PA31, IN_UP);   // D3
	gpio_init(GPIOA, DL_GPIO_PIN_28, PA28, IN_UP);   // D4
	gpio_init(GPIOB, DL_GPIO_PIN_1,  PB1, IN_UP);   // D5
	gpio_init(GPIOB, DL_GPIO_PIN_4,  PB4, IN_UP);   // D6
	gpio_init(GPIOB, DL_GPIO_PIN_17, PB17, IN_UP);   // D7
	gpio_init(GPIOB, DL_GPIO_PIN_12, PB12, IN_UP);   // D8
}

int get_line_color(void)
{
	 if (gpio_get(GPIOB, DL_GPIO_PIN_13)||gpio_get(GPIOB, DL_GPIO_PIN_15)||gpio_get(GPIOA, DL_GPIO_PIN_31)||gpio_get(GPIOA, DL_GPIO_PIN_28)||gpio_get(GPIOB, DL_GPIO_PIN_1)||gpio_get(GPIOB, DL_GPIO_PIN_4)||gpio_get(GPIOB, DL_GPIO_PIN_17)||gpio_get(GPIOB, DL_GPIO_PIN_12))
	 {
		   return 1;
	 }
	 return 0;
}
