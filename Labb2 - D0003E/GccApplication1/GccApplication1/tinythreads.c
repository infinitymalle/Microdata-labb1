#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "tinythreads.h"

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
                        *((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4

struct thread_block {
    void (*function)(int);   // code to run
    int arg;                 // argument to the above
    thread next;             // for use in linked lists
    jmp_buf context;         // machine state
    char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];

struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;

static void initialize(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

    initialized = 1;
	
	/*
		Interrupts are enabled on the 7th pin of PORTB
	*/
	PCMSK1 = (1 << PCINT15);
	EIMSK = (1 << PCIE1);
	
	/*
		Enables Joystick
	*/
	PORTB = (1 << PB7) | (1 << PB4);
	
	/*
		Sets OC1A to compare match
		Sets timer to CTC mode
	*/
	TCCR1A = (1 << COM1A1) | (1 << COM1A0);
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
	
	/*
		Timer compare A match interrupt: Enabled
	*/
	TIMSK1 = (1 << OCIE1A);
	
	/*
		8MHz/(1024*20) = 50ms
		Set TCNT1 = 0
	*/
	OCR1A = 8000000/(1024 * 20);
	TCNT1 = 0x0;
}

static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
            q = q->next;
        q->next = p;
    }
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
    }
    return p;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

void spawn(void (* function)(int), int arg) {
    thread newp;

    DISABLE();
    if (!initialized) initialize();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        ENABLE();
        current->function(current->arg);
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    SETSTACK(&newp->context, &newp->stack);

    enqueue(newp, &readyQ);
    ENABLE();
}

// Interrupt handler for button
ISR(PCINT1_vect) {
	if (PINB >> 7 == 0) {
		yield();
	}
}

// Should be interrupt handler for sequential interrupts
ISR(TIMER1_COMPA_vect) {
	yield();
}

// Change thread
void yield(void) {
	DISABLE();
	enqueue(current, &readyQ);
	dispatch(dequeue(&readyQ));
	ENABLE();
}

void lock(mutex *m) {
	DISABLE();
	
	// If it's unlocked, lock it
	if(m->locked == 0){
		m->locked = 1;
	}
	
	// Else - put the current thread in the back of the line of the waitQ
	// and run the first thread in the readyQ
	else{
		enqueue(current, &(m->waitQ));
		dispatch(dequeue(&readyQ));
	}
	ENABLE();
}

void unlock(mutex *m) {
	
	DISABLE();
	
	// If threads are available in the waitQ, put the current thread in the last position of the readyQ
	// and run the first thread in the waitQ
	if(m->waitQ != NULL){
		enqueue(current, &readyQ);
		dispatch(dequeue(&(m->waitQ)));
	}
	
	// Else - unlock (put the locked flag to 0)
	else{
		m->locked = 0;
	}
	
	ENABLE();
}


// If an interrupt were to happen inside enqueue or dispatch, the threads 
// might be put in the wrong order or a thread might be lost