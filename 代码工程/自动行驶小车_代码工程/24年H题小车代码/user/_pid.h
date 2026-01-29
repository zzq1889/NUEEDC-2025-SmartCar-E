#ifndef __PID_h_
#define __PID_h_
#include "headfile.h"

enum
{
  POSITION_PID = 0,  // 位置式
  DELTA_PID,         // 增量式
};

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	
	uint32_t pid_mode;

}pid_t;

void pid_cal(pid_t *pid);
void pid_control(void);
void pid_init(pid_t *pid, uint32_t mode, float p, float i, float d);
void motor_target_set(int spe1, int spe2);
void pid_out_limit(pid_t *pid);
void turn_pid(int base,int target);
void check(int target);
extern pid_t motorA;
extern pid_t motorB;
extern pid_t angle;

#endif
