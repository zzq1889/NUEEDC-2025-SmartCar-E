#include "headfile.h"


uint8_t imu_flag;
uint8_t orginal_data;
double yaw_angle;   //偏航角
int yaw_angle_int;  //偏航角取整
struct Angle YawAngle;

void imu_init()
{
	uart_init(UART1,9600,1);
}

void imu_uart_callback()
{
  static unsigned char imu_rx_buffer[250];   //存储原始数据的缓冲区
	static unsigned char counter = 0;	      
	
	orginal_data=uart_getbyte(UART1);      //获取陀螺仪原始数据
	imu_rx_buffer[counter++]=orginal_data;	//将收到的数据存入缓冲区中
	if (imu_rx_buffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		counter=0;
		return;
	}
	if (counter<11) {return;}//数据不满11个，则返回
	else
	{
		if(imu_rx_buffer[1]==0x53) //判断是否是z轴角度数据
		{
			memcpy(&YawAngle,&imu_rx_buffer[2],8);  //memcpy为编译器自带的内存拷贝函数,将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
      imu_flag=1;
		}
		counter=0;//清空缓存区
	}
}

void imu_analysis()
{
		yaw_angle = (float)YawAngle.Angle[2]/32768*180;  //z轴 偏航角  解算值
		
		yaw_angle_int=(int)(yaw_angle);
        
}

