#include <8051.h>
#include "preemptive.h"

__data __at (0x30) char sp[MAXTHREADS];
__data __at (0x34) ThreadID curThread;
__data __at (0x35) char bitmap;
__data __at (0x36) ThreadID newThread;
__data __at (0x37) char i;
__data __at (0x38) char tmp;
__data __at (0x39) char tmp2;
__data __at (0x3A) char checkAlive[MAXTHREADS];
__data __at (0x3E) unsigned char cnt;
__data __at (0x3F) unsigned char now;
__data __at (0x2C) unsigned char delayid[4];

#define SAVESTATE \
	{ \
	__asm \
	push ACC \
	push B \
	push DPL \
	push DPH \
	push PSW \
	__endasm; \
	sp[curThread] = SP; \
	}

#define RESTORESTATE \
	{ \
	SP = sp[curThread]; \
	__asm \
	pop PSW \
	pop DPH \
	pop DPL \
	pop B \
	pop ACC \
	__endasm; \
	}

extern void main(void);

void Bootstrap(void) {
	cnt = 0;
	now = 0;
	TMOD = 0;
	IE = 0x82;
	TR0 = 1;
	bitmap = 0b0000;
	checkAlive[0] = 0b0001; checkAlive[1] = 0b0010; checkAlive[2] = 0b0100; checkAlive[3] = 0b1000;
	delayid[0] = delayid[1] = delayid[2] = delayid[3] = 0;
	curThread = ThreadCreate(main);
	RESTORESTATE;
}

ThreadID ThreadCreate(FunctionPtr fp) {
	if(bitmap == 0b1111) return -1;
	__critical{
		for(i=0; i<MAXTHREADS; i++) {
			if(((bitmap) & (0b0001<<i)) == 0) {
				bitmap |= (0b0001<<i);
				newThread = i;
				break;
			}
		}
		tmp = SP;
		SP = 0x3F + (i<<4);
		__asm
			push DPL
			push DPH
			mov A, #0
			push A
			push A
			push A
			push A
		__endasm;

		tmp2 = (i<<3);
		
		__asm
			push _tmp2
		__endasm;
		
		sp[newThread] = SP;
		SP = tmp;
	}
	return newThread;
}

void ThreadYield(void) {
	__critical{
		SAVESTATE;
		do {
			curThread = (curThread == MAXTHREADS-1) ? 0 : curThread+1;
			if(bitmap & checkAlive[curThread]) break;
		} while (1);
		RESTORESTATE;
	}
}

void ThreadExit(void) {
	__critical{
		__asm 
		mov A, #0
		push A 
		push A 
		push A 
		push A
		push A
		push A
		push A
		push A
		__endasm; 
		sp[curThread] = 0;
		bitmap &= ~(1<<curThread);
		do {
			curThread = (curThread == MAXTHREADS-1) ? 0 : curThread+1;
			if(bitmap & checkAlive[curThread]) break;
		} while (1);
		RESTORESTATE;
	}
}

void myTimer0Handler(void) {
	EA=0;
		
		SAVESTATE;
		__asm
			mov ACC, r1
			mov B, r2
			mov DPL, r3
			mov DPH, r4
			mov _i, r5
			mov _tmp, r6
			mov _tmp2, r7
		__endasm;
		do {
			curThread = (curThread == MAXTHREADS-1) ? 0 : curThread+1;
			if(bitmap & checkAlive[curThread]) break;
		} while (1);
		cnt++;
		if(cnt==4) {
			cnt = 0;
			now++;
		}
		__asm
			mov r1, ACC
			mov r2, B
			mov r3, DPL
			mov r4, DPH
			mov r5, _i
			mov r6, _tmp
			mov r7, _tmp2
		__endasm;
		RESTORESTATE;
	EA=1;
		__asm
			reti
		__endasm;
	
}

void delay(unsigned char n) {
	delayid[curThread] = now + n;
	while(now != delayid[curThread]) EA=1;
	delayid[curThread] = 0;
}


