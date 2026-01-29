#include "headfile.h"

int Encoder_count1=0;
int Encoder_count2=0;

int mode,set;

void encoder_init(void)
{	
//		exti_init(EXTI_PA12, FALLING, 1);
//		gpio_init(GPIOA, DL_GPIO_PIN_13, PA13, IN_UP);
//		exti_init(EXTI_PA14, FALLING, 1);
//		gpio_init(GPIOA, DL_GPIO_PIN_15, PA15, IN_UP);
	
	  exti_init(EXTI_PA12, RISING, 0);                          //左轮A   PA12
	  exti_init(EXTI_PA13, FALLING,  0);			                     //左轮B  PA13
		gpio_init(GPIOA, DL_GPIO_PIN_12, PA12, IN_UP);           //上升沿 上拉
	  gpio_init(GPIOA, DL_GPIO_PIN_13, PA13, IN_DOWN);  			 //下降沿  下拉
	
		exti_init(EXTI_PA24, RISING, 0);													 //右轮A    PA24
	  exti_init(EXTI_PA15, FALLING, 0);													 //右轮B	  PA15
		gpio_init(GPIOA, DL_GPIO_PIN_24, PA24, IN_UP);            
	  gpio_init(GPIOA, DL_GPIO_PIN_15, PA15, IN_DOWN);                  
}

//读取编码器计数值
int read_encoder1(void)
{
	int num;
	num = Encoder_count1; //读取计数值
	Encoder_count1 = 0;   //计数值清零
	return num;
}

int read_encoder2(void)
{
	int num;
	num = Encoder_count2; //读取计数值
	Encoder_count2 = 0;   //计数值清零
	return num;
}



// 外部中断
void GROUP1_IRQHandler(void)//Group1的中断服务函数
{
	
  if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_12) // PA12外部中断   A上升沿
		{
			if(gpio_get(GPIOA, DL_GPIO_PIN_13)==0)       //B 逻辑低
			{
				Encoder_count1 ++;
			}
			else
			{
				Encoder_count1 --;
			}

			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_12; // 清除中断标志位
		}
		
		  if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_13) // PA13外部中断   B相下降沿
		{
			if(gpio_get(GPIOA, DL_GPIO_PIN_12)==0)   // A 逻辑低
			{
				Encoder_count1 ++;
			}
			else
			{
				Encoder_count1 --;
			}

			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_13; // 清除中断标志位
		}
		
		if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_24) // PA24外部中断   A相上升沿
		{
			if(gpio_get(GPIOA, DL_GPIO_PIN_15)==0)      	//B逻辑低
			{
				Encoder_count2 ++;
			}
			else
			{
				Encoder_count2 --;
			}

			
			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_24; // 清除中断标志位
		}
		
			if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_15) // PA15外部中断   B相下降沿
		{
			if(gpio_get(GPIOA, DL_GPIO_PIN_24)==0)    //A逻辑低
			{
				Encoder_count2 ++;
			}
			else
			{
				Encoder_count2 --;
			}
			
			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_15; // 清除中断标志位
		}
		
			 if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_17) // PA14外部中断
		 {
         delay_ms(10);
			   mode++;
			   set=0;
			   if(mode==5)
		    {
			     mode=1;
			  }
		  
			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_17; // 清除中断标志位
		}
		
		  if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_27) // PA14外部中断
		{
			delay_ms(10);
			if(set==0)
        set=1;
			else set=0;
			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_27; // 清除中断标志位
		}
}

	
	