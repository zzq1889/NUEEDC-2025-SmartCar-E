#include "headfile.h"
#include "ml_gpio.h"
#include "xunji.h"
#include "ml_motor.h"
#include "pid.h"
#include "buzzer_light.h"

//int left_encoder,right_encoder,left_pwm,right_pwm,left_angle_pwm,right_angle_pwm;
//int base_left_pwm,base_right_pwm,angle_pwm;

int now_statue,last_statue,change_flag1;


void xunji_init()
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

unsigned char digtal(unsigned char channel)//1-8	  获取X通道数字值
{
	uint8_t value = 0;
	switch(channel) 
	{
		case 1:  
			if (gpio_get(GPIOB, DL_GPIO_PIN_13)) value = 0;
			else value = 1;  
			break;  
		case 2: 
			if(gpio_get(GPIOB, DL_GPIO_PIN_15)) value = 0;
			else value = 1;  
			break;  
		case 3: 
			if(gpio_get(GPIOA, DL_GPIO_PIN_31)) value = 0;
			else value = 1;  
			break;   
		case 4:  
			if(gpio_get(GPIOA, DL_GPIO_PIN_28)) value = 0;
			else value = 1;  
			break;   
		case 5:
			if(gpio_get(GPIOB, DL_GPIO_PIN_1)) value = 0;
			else value = 1;  
			break;
		case 6:  
			if(gpio_get(GPIOB, DL_GPIO_PIN_4)) value = 0;
			else value = 1;  
			break;  
		case 7: 
			if(gpio_get(GPIOB, DL_GPIO_PIN_17)) value = 0;
			else value = 1;  
			break;  
 		case 8: 
 			if(gpio_get(GPIOB, DL_GPIO_PIN_12)) value = 0;
 			else value = 1;  
 			break;   
	}
	return value; 
}

void track1(void)
{
       if(D1==0|D2==0|D3==0|D4==0|D5==0|D6==0|D7==0|D8==0)
	   { Set_right_pwm(0);	Set_left_pwm(0); beep(); }             //STOP          
	     else 
	    { 
          turn_pid(10,0);
			}                          //PID
	 
}

void track2(void)
{
	  if(D1==1 && D2==1 && D3==1 && D4==0 && D5==0 && D6==1 && D7==1 && D8==1)     //11100111
	{
//		sensor_bias = 0;
		Set_right_pwm(3000); Set_left_pwm(3000); 
	}
	
	 else if(D1==1 && D2==1 && D3==0 && D4==0 && D5==1 && D6==1 && D7==1 && D8==1) //11001111
	{
//		sensor_bias = -15;
		Set_right_pwm(4000); Set_left_pwm(1800); 
	}
   else if(D1==1 && D2==0 && D3==0 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //10011111
	{
//		sensor_bias = -25;
		Set_right_pwm(5000); Set_left_pwm(1000); 
	}
	 else if(D1==0 && D2==0 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //00111111
	{
//		sensor_bias = -35;
		Set_right_pwm(5200); Set_left_pwm(700); 
	}
	 else if(D1==0 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //01111111
	{
//		sensor_bias = -45;
		Set_right_pwm(5600); Set_left_pwm(400); 
	}
	
	 // danglu
	 	else if(D1==1 && D2==1 && D3==1 && D4==0 && D5==1 && D6==1 && D7==1 && D8==1) //11101111
	{
//		sensor_bias = -5;
		Set_right_pwm(3500); Set_left_pwm(2500); 
	}
   else if(D1==1 && D2==1 && D3==0 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)   //11011111
	{
//		sensor_bias = -20;
		Set_right_pwm(4200); Set_left_pwm(2000); 
	}
	 else if(D1==1 && D2==0 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)   //10111111
	{
//		sensor_bias = -30;
		Set_right_pwm(4800); Set_left_pwm(1000); 
	}
	
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==0 && D6==1 && D7==1 && D8==1)  //11110111
	{
//		sensor_bias = 10;
		Set_right_pwm(2500); Set_left_pwm(3500);  
	}
   else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==0 && D7==1 && D8==1)   //11111011
	{
//		sensor_bias = 20;
		Set_right_pwm(2000); Set_left_pwm(4000);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==0 && D8==1)   //11111101
	{
//		sensor_bias = 30;
		Set_right_pwm(1200); Set_left_pwm(4800); 
	}

	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==0 && D6==0 && D7==1 && D8==1)  //11110011
	{
//		sensor_bias = 15;
		Set_right_pwm(1800); Set_left_pwm(4300);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==0 && D7==0 && D8==1)  //11111001
	{
//		sensor_bias = 25;
		Set_right_pwm(1400); Set_left_pwm(4500);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==0 && D5==0 && D6==1 && D7==0 && D8==0)  //11111100
	{
//		sensor_bias = 35;
		Set_right_pwm(1200);  Set_left_pwm(4800);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==0)  //11111110
	{
//		sensor_bias = 45;
		Set_right_pwm(800); Set_left_pwm(5200);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //11111111
   {
//	   sensor_bias = 0;
		  last_statue=now_statue;
		  now_statue=0;
   }
	   if(D1==0|D2==0|D3==0|D4==0|D5==0|D6==0|D7==0|D8==0)
	 {
		    last_statue=now_statue;
		    now_statue=1;
	 }
	        
	 		    if(now_statue!=last_statue) 
	       {
			     change_flag1++;
           beep();	
		     }
				 
				   if(change_flag1==0)
			    {
				    turn_pid(10,0);
		      }	 
					
           if(change_flag1==2)
			    {
						check(177);
				    turn_pid(10,177); 
		      }	 
			     if(change_flag1==4)
			    {
			    	Set_left_pwm(0);
   		      Set_right_pwm(0);
				    change_flag1++;
			    }
}
void track3(void)
{
	  if(D1==1 && D2==1 && D3==1 && D4==0 && D5==0 && D6==1 && D7==1 && D8==1)     //11100111
	{
//		sensor_bias = 0;
		Set_right_pwm(3000); Set_left_pwm(3000); 
	}
	
	 else if(D1==1 && D2==1 && D3==0 && D4==0 && D5==1 && D6==1 && D7==1 && D8==1) //11001111
	{
//		sensor_bias = -15;
//    Set_right_pwm(3500); Set_left_pwm(2200); 
		Set_right_pwm(4200); Set_left_pwm(1400); 
	}
   else if(D1==1 && D2==0 && D3==0 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //10011111
	{
//		sensor_bias = -25;
		Set_right_pwm(4700); Set_left_pwm(1000); 
	}
	 else if(D1==0 && D2==0 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //00111111
	{
//		sensor_bias = -35; 
			if(yaw_angle_int>-120&&yaw_angle_int<-90)
		{
			Set_right_pwm(700);  Set_left_pwm(5400);  
		}
		 else
		 { Set_right_pwm(5400);  Set_left_pwm(700); } 
		             //5000               800
	}
	
	 else if(D1==0 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //01111111
	{
			if(yaw_angle_int>-120&&yaw_angle_int<-90)
		{
			Set_right_pwm(200);  Set_left_pwm(6200);  
		}
		 else
		 { Set_right_pwm(6200);  Set_left_pwm(200); } 
		              //5500              500
	 }
	 // danglu
	 	else if(D1==1 && D2==1 && D3==1 && D4==0 && D5==1 && D6==1 && D7==1 && D8==1) //11101111
	{
//		sensor_bias = -5;
		Set_right_pwm(3500); Set_left_pwm(2500); 
	}
   else if(D1==1 && D2==1 && D3==0 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)   //11011111
	{
//		sensor_bias = -20;
		Set_right_pwm(4500); Set_left_pwm(1000); 
	}
	 else if(D1==1 && D2==0 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)   //10111111
	{
     	 if(yaw_angle_int>-120&&yaw_angle_int<-90)
		{
			Set_right_pwm(200);  Set_left_pwm(6200);  
		}
		 else
		 { Set_right_pwm(6200);  Set_left_pwm(200); } 
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==0 && D6==1 && D7==1 && D8==1)  //11110111
	{    
//		sensor_bias = 10;
		 Set_right_pwm(1500); Set_left_pwm(4500);  
	}
   else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==0 && D7==1 && D8==1)   //11111011
	{
//		sensor_bias = 20;
		Set_right_pwm(800); Set_left_pwm(5200);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==0 && D8==1)   //11111101
	{
//		sensor_bias = 30;
			if(yaw_angle_int>-60&&yaw_angle_int<-20)
		{
			Set_right_pwm(6200);  Set_left_pwm(200);  
		}
		 else
		 { Set_right_pwm(200);  Set_left_pwm(6200);} 
	}

	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==0 && D6==0 && D7==1 && D8==1)  //11110011
	{
//		sensor_bias = 15;
		Set_right_pwm(1200); Set_left_pwm(4800);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==0 && D7==0 && D8==1)  //11111001
	{
//		sensor_bias = 25;
		Set_right_pwm(1000); Set_left_pwm(5000);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==0 && D8==0)  //11111100
	{
		if(yaw_angle_int>-60&&yaw_angle_int<-20)
		{
			Set_right_pwm(5800);  Set_left_pwm(600);  
		}
//		sensor_bias = 35;
		 else
		 { Set_right_pwm(600);  Set_left_pwm(5800);} 
	}
	
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==0)  //11111110
	{
//		sensor_bias = 45;
			if(yaw_angle_int>-60&&yaw_angle_int<-20)
		{
			Set_right_pwm(6200);  Set_left_pwm(200);  
		}
		 else
		 { Set_right_pwm(200);  Set_left_pwm(6200);} 
		  
	}
	
	  else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //11111111
   {
		  last_statue=now_statue;
		  now_statue=0;
   }
	 
	   if(D1==0|D2==0|D3==0|D4==0|D5==0|D6==0|D7==0|D8==0)
	 {
		    last_statue=now_statue;
		    now_statue=1;
	 }
	        
	 		    if(now_statue!=last_statue) 
	       {
			     change_flag1++;
           beep();	
		     }
/****************************************************************************************
				                          第一圈
*****************************************************************************************/
			 if(change_flag1==0) {turn_pid(10,-42);}	 
			 if(change_flag1==2){check(-137); turn_pid(10,-137);}	 
					
					  if(change_flag1==4)
			    {
			    	Set_left_pwm(0);
   		      Set_right_pwm(0);
				    change_flag1++;
			    }
}

void track4(void)
{
	  if(D1==1 && D2==1 && D3==1 && D4==0 && D5==0 && D6==1 && D7==1 && D8==1)     //11100111
	{
//		sensor_bias = 0;
		Set_right_pwm(3000); Set_left_pwm(3000); 
	}
	
	 else if(D1==1 && D2==1 && D3==0 && D4==0 && D5==1 && D6==1 && D7==1 && D8==1) //11001111
	{
//		sensor_bias = -15;
//    Set_right_pwm(3500); Set_left_pwm(2200); 
		Set_right_pwm(4200); Set_left_pwm(1400); 
	}
   else if(D1==1 && D2==0 && D3==0 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //10011111
	{
//		sensor_bias = -25;
		Set_right_pwm(4700); Set_left_pwm(1000); 
	}
	 else if(D1==0 && D2==0 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //00111111
	{
//		sensor_bias = -35; 
			if(yaw_angle_int>-120&&yaw_angle_int<-90)
		{
			Set_right_pwm(700);  Set_left_pwm(5400);  
		}
		 else
		 { Set_right_pwm(5400);  Set_left_pwm(700); } 
		             //5000               800
	}
	
	 else if(D1==0 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //01111111
	{
			if(yaw_angle_int>-120&&yaw_angle_int<-90)
		{
			Set_right_pwm(200);  Set_left_pwm(6200);  
		}
		 else
		 { Set_right_pwm(6200);  Set_left_pwm(200); } 
		              //5500              500
	 }
	 // danglu
	 	else if(D1==1 && D2==1 && D3==1 && D4==0 && D5==1 && D6==1 && D7==1 && D8==1) //11101111
	{
//		sensor_bias = -5;
		Set_right_pwm(3500); Set_left_pwm(2500); 
	}
   else if(D1==1 && D2==1 && D3==0 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)   //11011111
	{
//		sensor_bias = -20;
		Set_right_pwm(4500); Set_left_pwm(1000); 
	}
	 else if(D1==1 && D2==0 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)   //10111111
	{
     	 if(yaw_angle_int>-120&&yaw_angle_int<-90)
		{
			Set_right_pwm(200);  Set_left_pwm(6200);  
		}
		 else
		 { Set_right_pwm(6200);  Set_left_pwm(200); } 
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==0 && D6==1 && D7==1 && D8==1)  //11110111
	{    
//		sensor_bias = 10;
		 Set_right_pwm(1500); Set_left_pwm(4500);  
	}
   else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==0 && D7==1 && D8==1)   //11111011
	{
//		sensor_bias = 20;
		Set_right_pwm(800); Set_left_pwm(5200);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==0 && D8==1)   //11111101
	{
//		sensor_bias = 30;
			if(yaw_angle_int>-60&&yaw_angle_int<-20)
		{
			Set_right_pwm(6200);  Set_left_pwm(200);  
		}
		 else
		 { Set_right_pwm(200);  Set_left_pwm(6200);} 
	}

	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==0 && D6==0 && D7==1 && D8==1)  //11110011
	{
//		sensor_bias = 15;
		Set_right_pwm(1200); Set_left_pwm(4800);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==0 && D7==0 && D8==1)  //11111001
	{
//		sensor_bias = 25;
		Set_right_pwm(1000); Set_left_pwm(5000);  
	}
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==0 && D8==0)  //11111100
	{
		if(yaw_angle_int>-60&&yaw_angle_int<-20)
		{
			Set_right_pwm(4500);  Set_left_pwm(2000);  
		}
//		sensor_bias = 35;
		 else
		 { Set_right_pwm(600);  Set_left_pwm(5800);} 
	}
	
	 else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==0)  //11111110
	{
//		sensor_bias = 45;
			if(yaw_angle_int>-60&&yaw_angle_int<-20)
		{
			Set_right_pwm(4500);  Set_left_pwm(2000);  
		}
		 else
		 { Set_right_pwm(200);  Set_left_pwm(6200);} 
		  
	}
	
	  else if(D1==1 && D2==1 && D3==1 && D4==1 && D5==1 && D6==1 && D7==1 && D8==1)  //11111111
   {
		  last_statue=now_statue;
		  now_statue=0;
   }
	 
	   if(D1==0|D2==0|D3==0|D4==0|D5==0|D6==0|D7==0|D8==0)
	 {
		    last_statue=now_statue;
		    now_statue=1;
	 }
	        
	 		    if(now_statue!=last_statue) 
	       {
			     change_flag1++;
           beep();	
		     }
/****************************************************************************************
				                          第一圈
*****************************************************************************************/
			 if(change_flag1==0) {turn_pid(10,-42);}	 
			 if(change_flag1==2) {check(-138); turn_pid(10,-138);}	 
			 
/****************************************************************************************
				                          第二圈
*****************************************************************************************/			 
			     if(change_flag1==4) {turn_pid(10,-46);}
			                                  //45 
			 	   if(change_flag1==6) //****** 白多
					{
						check(-141);     
				    turn_pid(10,-141); //137 138
				  }
					
/****************************************************************************************
				                          第三圈
*****************************************************************************************/	
		 if(change_flag1==8)  { turn_pid(10,-47);  }  //-45
		 if(change_flag1==10) { check(-142); turn_pid(10,-142);}
					
					
/****************************************************************************************
				                          第四圈
*****************************************************************************************/						
         
           if(change_flag1==12)
			    {
          turn_pid(10,-50);  //-45
			    }
					 if(change_flag1==14)
					{
						check(-142); turn_pid(10,-142); 
					}
					
					  if(change_flag1==16)
			    {
			    	Set_left_pwm(0);
   		      Set_right_pwm(0);
				    change_flag1++;
			    }
}

