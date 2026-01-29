#ifndef _IMU_H_
#define _IMU_H_
#include "headfile.h"

 
struct Angle
{
	short Angle[3];
	short T;
};

void imu_init(void);
void imu_uart_callback(void);
void imu_analysis(void);

extern double yaw_angle;
extern uint8_t imu_flag;
extern int yaw_angle_int;

#endif
