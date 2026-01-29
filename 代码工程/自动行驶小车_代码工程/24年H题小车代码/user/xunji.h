#ifndef __xunji_h_
#define __xunji_h_

#include "headfile.h"

#define D1 digtal(1)
#define D2 digtal(2)
#define D3 digtal(3)
#define D4 digtal(4)
#define D5 digtal(5)
#define D6 digtal(6)
#define D7 digtal(7)
#define D8 digtal(8)

extern  int last_statue;
extern   int  now_statue;
extern   int  change_flag1;

void xunji_init(void);
void track2(void);
void track4(void);
void track3(void);
unsigned char digtal(unsigned char channel);
void pid_track(void);
void track1(void);

#endif