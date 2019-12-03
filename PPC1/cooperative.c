#include <8051.h>
#include "cooperative.h"

__data __at (0x30) char sp[MAXTHREADS];
__data __at (0x34) ThreadID curThread;
__data __at (0x35) char bitmap;
__data __at (0x36) ThreadID newThread;
__data __at (0x37) char i;
__data __at (0x38) char tmp;
__data __at (0x39) char tmp2;

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
	bitmap = 0b0000;
	curThread = ThreadCreate(main);
	RESTORESTATE;
}

ThreadID ThreadCreate(FunctionPtr fp) {
	
	if(bitmap == 0b1111) return -1;
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
	return newThread;
}

void ThreadYield(void) {
	SAVESTATE;
	do {
		curThread = (curThread == MAXTHREADS-1) ? 0 : curThread+1;
		if(((bitmap) & (0b0001<<curThread))) break;
	} while (1);
	RESTORESTATE;
}

void ThreadExit(void) {
	bitmap &= ~(1<<curThread);
	do {
		curThread = (curThread == 3) ? 0 : curThread+1;
		if(bitmap & (1<<curThread)) break;
	} while (1);
	RESTORESTATE;
}



