#ifndef __PREEMPTIVE_H__
#define __PREEMPTIVE_H__

#define MAXTHREADS 4  /* not including the scheduler */
/* the scheduler does not take up a thread of its own */

typedef char ThreadID;
typedef char Semaphore;
typedef void (*FunctionPtr)(void);

ThreadID ThreadCreate(FunctionPtr);
void ThreadYield(void);
void ThreadExit(void);

#define CNAME(s) _ ## s
#define LABEL(label) label ## $
#define SemaphoreCreate(s, n) s = n
#define SemaphoreWait(s) SemaphoreWaitBody(s, __COUNTER__)
#define SemaphoreSignal(s) \
    { \
        __asm \
        inc CNAME(s) \
        __endasm; \
    }
#define SemaphoreWaitBody(S, label) \
    { \
        __asm \
    LABEL(label): \
        mov a, CNAME(S) \
        jz LABEL(label) \
        jb ACC.7, LABEL(label) \
        dec CNAME(S) \
        __endasm; \
    }

void delay(unsigned char);

#endif // __PREEMPTIVE_H__
