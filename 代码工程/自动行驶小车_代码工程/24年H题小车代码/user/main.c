#include "headfile.h"
#include "_pid.h"
#include "key.h"

int left_pwm,right_pwm,left_angle_pwm,right_angle_pwm;
int base_left_pwm,base_right_pwm,angle_pwm,angle_pwm1;
int cur_state,last_state,pre_state;
unsigned int Temp[2] = { 0 };
int turn_pwm,cnt;
//int mode,set;

uint8_t KeyNum;

int main(void)
{
		system_init();  // 系统初始化 系统频率80MHZ 必须加
		delay_ms(500);  // 延时0.5s 等待电源稳定
		OLED_Init();
	  imu_init();     // imu初始化 其实就是初始化串口 这里是串口1 
    key_init();

		motor_init();
		encoder_init();
	  uart0_init();
	  xunji_init();
//	track_init();
    buzzer_light_init(); 
		tim_interrupt_ms_init(TIMG8, 10, 1);   // 定时器中断初始化 中断内放电机PID控制程序
     
	  pid_init(&motorA,DELTA_PID,10,10,5);  
    pid_init(&motorB,DELTA_PID,10,10,5);
	  pid_init(&angle,POSITION_PID,0.04117,0,0.102);   //0.0405  0.1
		 
    while (1) 
	 {
			 if(imu_flag)
			{
				imu_flag=0;
				imu_analysis();  //获取角度值存放在  yaw_angle_int
			}
			
		  KeyNum = key_GetNum();
		  if (KeyNum == 1)			
		 {
		   mode++;
       if(mode==5)
			 {mode=1;}
       if(set==1)
       {set=0; }				 
		 }
		  if (KeyNum == 2)			
		 {
			 set=1;
		 }
			
			OLED_ShowString(1, 1, "mode:");
			OLED_ShowString(2, 1, "set:");
			OLED_ShowString(3, 1, "yaw:");
			OLED_ShowNum(1, 6, mode,3);
			OLED_ShowNum(2, 6, set,1);
		  OLED_ShowSignedNum(3, 6, yaw_angle_int,3);
   }
}

void TIMG8_IRQHandler()
{
	   if(DL_TimerG_getPendingInterrupt(TIMG8) == DL_TIMER_IIDX_LOAD)
	  {
        left_encoder=-read_encoder1();  
		    right_encoder=-read_encoder2();

		    if(mode==1&&set==1)
		   {
          track1();
		   }
			 	if(mode==2&&set==1)
		   {
          track2();
		   }
			 	if(mode==3&&set==1)
		   {
          track3();
		   }
			 	if(mode==4&&set==1)
		   {
          track4();
		   }	
	  } 
}









