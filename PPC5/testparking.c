#include <8051.h>
#include "preemptive.h"

__data __at (0x20) Semaphore mutex;
__data __at (0x21) Semaphore full;
__data __at (0x22) Semaphore empty;
__data __at (0x23) Semaphore sem;
__data __at (0x24) Semaphore spotsSync;
__data __at (0x25) char spots[2];
__data __at (0x26) char head;
__data __at (0x27) char tail;
__data __at (0x28) char i;
__data __at (0x29) char buf[7];
__data __at (0x3E) unsigned char now;
__code __at (0x70) char op[15] = {'C','A','R',':','@','[',',',']','\n'};

void Car1(void){
	SemaphoreWait(sem);

	__critical{
		SemaphoreWait(mutex);
		if(spots[0]=='X') {
			spots[0] = '1';
		} else {
			spots[1] = '1';
		}
		buf[0] = '1';
		buf[1] = ' ';
		buf[2] = 'I';
		buf[3] = 'N';
		buf[4] = spots[0];
		buf[5] = spots[1];
		buf[6] = now;
		SemaphoreSignal(mutex);
	}

	delay(7);

	__critical{
		SemaphoreWait(mutex);
		if(spots[0]=='1') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		op[3] = '1';
		op[5] = 'O';
		op[6] = 'U';
		op[7] = 'T';
		op[10] = spots[0];
		op[12] = spots[1];
		for(i=0; i<15; i++) {
			buf[head] = op[i];
			head = (head==15) ? 0 : head + 1;
		}
		SemaphoreSignal(mutex);
	}

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car2(void){
	SemaphoreWait(sem);

	__critical{
		SemaphoreWait(mutex);
		if(spots[0]=='X') {
			spots[0] = '2';
		} else {
			spots[1] = '2';
		}
		op[3] = '2';
		op[5] = ' ';
		op[6] = 'I';
		op[7] = 'N';
		op[10] = spots[0];
		op[12] = spots[1];
		for(i=0; i<15; i++) {
			buf[head] = op[i];
			head = (head==15) ? 0 : head + 1;
		}
		SemaphoreSignal(mutex);
	}

	delay(6);

	__critical{
		SemaphoreWait(mutex);
		if(spots[0]=='2') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		op[3] = '2';
		op[5] = 'O';
		op[6] = 'U';
		op[7] = 'T';
		op[10] = spots[0];
		op[12] = spots[1];
		for(i=0; i<15; i++) {
			buf[head] = op[i];
			head = (head==15) ? 0 : head + 1;
		}
		SemaphoreSignal(mutex);
	}

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car3(void){
	SemaphoreWait(sem);

	__critical{
		SemaphoreWait(mutex);
		if(spots[0]=='X') {
			spots[0] = '3';
		} else {
			spots[1] = '3';
		}
		op[3] = '3';
		op[5] = ' ';
		op[6] = 'I';
		op[7] = 'N';
		op[10] = spots[0];
		op[12] = spots[1];
		for(i=0; i<15; i++) {
			buf[head] = op[i];
			head = (head==15) ? 0 : head + 1;
		}
		SemaphoreSignal(mutex);
	}

	delay(5);

	__critical{
		SemaphoreWait(mutex);
		if(spots[0]=='3') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		op[3] = '3';
		op[5] = 'O';
		op[6] = 'U';
		op[7] = 'T';
		op[10] = spots[0];
		op[12] = spots[1];
		for(i=0; i<15; i++) {
			buf[head] = op[i];
			head = (head==15) ? 0 : head + 1;
		}
		SemaphoreSignal(mutex);
	}

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car4(void){
	SemaphoreWait(sem);

	__critical{
		SemaphoreWait(mutex);
		if(spots[0]=='X') {
			spots[0] = '4';
		} else {
			spots[1] = '4';
		}
		op[3] = '4';
		op[5] = ' ';
		op[6] = 'I';
		op[7] = 'N';
		op[10] = spots[0];
		op[12] = spots[1];
		for(i=0; i<15; i++) {
			buf[head] = op[i];
			head = (head==15) ? 0 : head + 1;
		}
		SemaphoreSignal(mutex);
	}

	delay(4);

	__critical{
		SemaphoreWait(mutex);
		if(spots[0]=='4') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		op[3] = '4';
		op[5] = 'O';
		op[6] = 'U';
		op[7] = 'T';
		op[10] = spots[0];
		op[12] = spots[1];
		for(i=0; i<15; i++) {
			buf[head] = op[i];
			head = (head==15) ? 0 : head + 1;
		}
		SemaphoreSignal(mutex);
	}

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car5(void){
	SemaphoreWait(sem);

	__critical{
		SemaphoreWait(mutex);
		if(spots[0]=='X') {
			spots[0] = '5';
		} else {
			spots[1] = '5';
		}
		op[3] = '5';
		op[5] = ' ';
		op[6] = 'I';
		op[7] = 'N';
		op[10] = spots[0];
		op[12] = spots[1];
		for(i=0; i<15; i++) {
			buf[head] = op[i];
			head = (head==15) ? 0 : head + 1;
		}
		SemaphoreSignal(mutex);
	}

	delay(3);

	__critical{
		SemaphoreWait(mutex);
		if(spots[0]=='5') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		op[3] = '5';
		op[5] = 'O';
		op[6] = 'U';
		op[7] = 'T';
		op[10] = spots[0];
		op[12] = spots[1];
		for(i=0; i<15; i++) {
			buf[head] = op[i];
			head = (head==) ? 0 : head + 1;
		}
		SemaphoreSignal(mutex);
	}

	SemaphoreSignal(sem);

	ThreadExit();

}


void Consumer(void) {
	TMOD |= 0x20;
	TH1 = -6;
	SCON = 0x50;
	TR1 = 1;
	while (1) {
		__critical{
			SemaphoreWait(mutex);
			while(head != tail){
				SBUF = buf[tail];
				while(!TI);
				TI = 0;
				tail = (tail == 6) ? 0 : tail + 1;
			}
			SemaphoreSignal(mutex);
		}
	}
}

void main(void) {
	__critical{
		buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = '\0';
		head = 0;
		tail = 0;
		spots[0] = spots[1] = 'X';
		SemaphoreCreate(mutex, 1);
		SemaphoreCreate(full, 0);
		SemaphoreCreate(empty, 16);
		SemaphoreCreate(sem,2);
		SemaphoreCreate(spotsSync,1);
	}
	ThreadCreate(Car1);
	ThreadCreate(Car2);
	ThreadCreate(Car3);
	ThreadCreate(Car4);
	Car5();
	ThreadExit();
}

void _sdcc_gsinit_startup(void) {
    __asm
        ljmp  _Bootstrap
    __endasm;
}

void _mcs51_genRAMCLEAR(void) {}
void _mcs51_genXINIT(void) {}
void _mcs51_genXRAMCLEAR(void) {}

void timer0_ISR(void) __interrupt(1) {
	__asm
		ljmp _myTimer0Handler
	__endasm;
}

		
		
