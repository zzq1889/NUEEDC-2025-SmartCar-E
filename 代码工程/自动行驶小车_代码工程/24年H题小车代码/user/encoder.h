#ifndef __ENCODER_H__
#define __ENCODER_H__

extern int left_encoder;
extern int right_encoder;

void encoder_init(void);
int read_encoder1(void);
int read_encoder2(void);


#endif

