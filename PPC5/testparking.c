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
__data __at (0x29) char buf[7];
__data __at (0x35) char bitmap;
__data __at (0x3F) unsigned char now;
__code __at (0x70) char op[15] = {'C','A','R',':','@','[',',',']','\n'};

void Car1(void){
	SemaphoreWait(sem);
	
	__critical{
		SemaphoreWait(spotsSync);
		if(spots[0]=='X') {
			spots[0] = '1';
		} else {
			spots[1] = '1';
		}
		SemaphoreSignal(spotsSync);
	}

	delay(7);
	
	__critical{
		SemaphoreWait(spotsSync);
		if(spots[0]=='1') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		SemaphoreSignal(spotsSync);
	}

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car2(void){
	SemaphoreWait(sem);
	
	__critical{
		SemaphoreWait(spotsSync);
		if(spots[0]=='X') {
			spots[0] = '2';
		} else {
			spots[1] = '2';
		}
		SemaphoreSignal(spotsSync);
	}

	delay(6);
	
	__critical{
		SemaphoreWait(spotsSync);
		if(spots[0]=='2') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		SemaphoreSignal(spotsSync);
	}

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car3(void){
	SemaphoreWait(sem);
	
	__critical{
		SemaphoreWait(spotsSync);
		if(spots[0]=='X') {
			spots[0] = '3';
		} else {
			spots[1] = '3';
		}
		SemaphoreSignal(spotsSync);
	}

	delay(5);
	
	__critical{
		SemaphoreWait(spotsSync);
		if(spots[0]=='3') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		SemaphoreSignal(spotsSync);
	}

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car4(void){
	SemaphoreWait(sem);
	
	__critical{
		SemaphoreWait(spotsSync);
		if(spots[0]=='X') {
			spots[0] = '4';
		} else {
			spots[1] = '4';
		}
		SemaphoreSignal(spotsSync);
	}

	delay(7);
	
	__critical{
		SemaphoreWait(spotsSync);
		if(spots[0]=='4') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		SemaphoreSignal(spotsSync);
	}

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car5(void){
	SemaphoreWait(sem);
	
	__critical{
		SemaphoreWait(spotsSync);
		if(spots[0]=='X') {
			spots[0] = '5';
		} else {
			spots[1] = '5';
		}
		SemaphoreSignal(spotsSync);
	}

	delay(3);
	
	__critical{
		SemaphoreWait(spotsSync);
		if(spots[0]=='5') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		SemaphoreSignal(spotsSync);
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
	do{ delay(2); } while(bitmap==0x0F);
	ThreadCreate(Car2);
	do{ delay(2); } while(bitmap==0x0F);
	ThreadCreate(Car3);
	do{ delay(2); } while(bitmap==0x0F);
	ThreadCreate(Car4);
	do{ delay(2); } while(bitmap==0x0F);
	Car5();
	do{ delay(2); } while(bitmap==0x0F);
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

		
		
