#include <8051.h>
#include "preemptive.h"

__data __at (0x21) Semaphore sem;
__data __at (0x22) Semaphore spotsSync;
__data __at (0x23) char spots[2];
__data __at (0x25) unsigned char CarIn[5];
__data __at (0x4A) unsigned char CarOut[5];
__data __at (0x5A) unsigned char CarSpot[5];
__data __at (0x35) char bitmap;
__data __at (0x3F) unsigned char now;
__code __at (0x700) char Car[5] = "Car ";
__code __at (0x710) char GotSpot[11] = " got spot ";
__code __at (0x720) char TimeUnit[16] = " at time unit: ";
__code __at (0x730) char ExitSpot[7] = " exits";


void Car1(void){
	SemaphoreWait(sem);
	
	EA=0;
		SemaphoreWait(spotsSync);
		if(spots[0]=='X') {
			spots[0] = '1';
			CarSpot[0] = '0';
		} else {
			spots[1] = '1';
			CarSpot[0] = '1';
		}
		CarIn[0] = now;
		SemaphoreSignal(spotsSync);
	EA=1;

	delay(7);
	
	EA=0;
		SemaphoreWait(spotsSync);
		if(spots[0]=='1') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		CarOut[0] = now;
		SemaphoreSignal(spotsSync);
	EA=1;

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car2(void){
	SemaphoreWait(sem);
	
	EA=0;
		SemaphoreWait(spotsSync);
		if(spots[0]=='X') {
			spots[0] = '2';
			CarSpot[1] = '0';
		} else {
			spots[1] = '2';
			CarSpot[1] = '1';
		}
		CarIn[1] = now;
		SemaphoreSignal(spotsSync);
	EA=1;

	delay(6);
	
	EA=0;
		SemaphoreWait(spotsSync);
		if(spots[0]=='2') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		CarOut[1] = now;
		SemaphoreSignal(spotsSync);
	EA=1;

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car3(void){
	SemaphoreWait(sem);
	
	EA=0;
		SemaphoreWait(spotsSync);
		if(spots[0]=='X') {
			spots[0] = '3';
			CarSpot[2] = '0';
		} else {
			spots[1] = '3';
			CarSpot[2] = '1';
		}
		CarIn[2] = now;
		SemaphoreSignal(spotsSync);
	EA=1;

	delay(5);
	
	EA=0;
		SemaphoreWait(spotsSync);
		if(spots[0]=='3') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		CarOut[2] = now;
		SemaphoreSignal(spotsSync);
	EA=1;

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car4(void){
	SemaphoreWait(sem);
	
	EA=0;
		SemaphoreWait(spotsSync);
		if(spots[0]=='X') {
			spots[0] = '4';
			CarSpot[3] = '0';
		} else {
			spots[1] = '4';
			CarSpot[3] = '1';
		}
		CarIn[3] = now;
		SemaphoreSignal(spotsSync);
	EA=1;

	delay(7);
	
	EA=0;
		SemaphoreWait(spotsSync);
		if(spots[0]=='4') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		CarOut[3] = now;
		SemaphoreSignal(spotsSync);
	EA=1;

	SemaphoreSignal(sem);

	ThreadExit();

}

void Car5(void){
	SemaphoreWait(sem);
	
	EA=0;
		SemaphoreWait(spotsSync);
		if(spots[0]=='X') {
			spots[0] = '5';
			CarSpot[4] = '0';
		} else {
			spots[1] = '5';
			CarSpot[4] = '1';
		}
		CarIn[4] = now;
		SemaphoreSignal(spotsSync);
	EA=1;

	delay(3);
	
	EA=0;
		SemaphoreWait(spotsSync);
		if(spots[0]=='5') {
			spots[0] = 'X';
		} else {
			spots[1] = 'X';
		}
		CarOut[4] = now;
		SemaphoreSignal(spotsSync);
	EA=1;

	SemaphoreSignal(sem);

	ThreadExit();

}

void Consumer(void) {
	TMOD |= 0x20;
	TH1 = -6;
	SCON = 0x50;
	TR1 = 1;
	EA = 0;
	for(char i=0; i<5; i++){
		for(char j=0; j<5; j++) {
			SBUF = Car[j];
			while(!TI);
			TI = 0;
		}

		SBUF = '1' + i;
		while(!TI);
		TI = 0;

		for(char j=0; j<11; j++) {
			SBUF = GotSpot[j];
			while(!TI);
			TI = 0;
		}

		SBUF = CarSpot[i];
		while(!TI);
		TI = 0;

		for(char j=0; j<16; j++) {
			SBUF = TimeUnit[j];
			while(!TI);
			TI = 0;
		}

		if(CarIn[i]>9) {
			SBUF = '0' + (CarIn[i]/10);
			while(!TI);
			TI = 0;
		}

		SBUF = '0' + (CarIn[i]%10);
		while(!TI);
		TI = 0;

		SBUF = '\n';
		while(!TI);
		TI = 0;

		for(char j=0; j<5; j++) {
			SBUF = Car[j];
			while(!TI);
			TI = 0;
		}

		SBUF = '1' + i;
		while(!TI);
		TI = 0;

		for(char j=0; j<7; j++) {
			SBUF = ExitSpot[j];
			while(!TI);
			TI = 0;
		}

		for(char j=0; j<16; j++) {
			SBUF = TimeUnit[j];
			while(!TI);
			TI = 0;
		}

		if(CarOut[i]>9) {
			SBUF = '0' + (CarOut[i]/10);
			while(!TI);
			TI = 0;
		}
		SBUF = '0' + (CarOut[i]%10);
		while(!TI);
		TI = 0;

		SBUF = '\n';
		while(!TI);
		TI = 0;

	}
	EA = 1;
}

void main(void) {
	EA=0;
//		head = 0;
//		tail = 0;
		spots[0] = spots[1] = 'X';
//		SemaphoreCreate(mutex, 1);
//		SemaphoreCreate(full, 0);
//		SemaphoreCreate(empty, 16);
		SemaphoreCreate(sem,2);
		SemaphoreCreate(spotsSync,1);
	EA=1;
	
	ThreadCreate(Car1);
	do{ delay(2); } while(bitmap==0x0F);
	ThreadCreate(Car2);
	do{ delay(2); } while(bitmap==0x0F);
	ThreadCreate(Car3);
	do{ delay(2); } while(bitmap==0x0F);
	ThreadCreate(Car4);
	do{ delay(2); } while(bitmap==0x0F);
	ThreadCreate(Car5);
	do{ delay(2); } while(spots[0] != 'X' || spots[1] != 'X');

	Consumer();


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

		
		
