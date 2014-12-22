#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "timer.h"

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
} while (0)

typedef void       (*TIMERFUNC)(union sigval);

static void* handler(void * p)
{
	
}


static timer_t get_ptimerid(struct cctimer_t * self)
{
	return	self->p_tid;
}

static TIMEOUT get_handler(struct cctimer_t * self)
{
	return self->timeout;
}

static long long get_interval(struct cctimer_t * self)
{
	return self->interval;
}

int starttimer(struct cctimer_t * self)
{
        struct sigevent sev;
        struct itimerspec its;



        sev.sigev_notify = SIGEV_THREAD;//SIGEV_SIGNAL;
        sev.sigev_value.sival_ptr = NULL;
        sev.sigev_notify_function = (TIMERFUNC)get_handler(self);
        if (timer_create(CLOCK_REALTIME, &(sev), &get_ptimerid(self)) == -1)
                errExit("timer_create");
        //printf("timer ID is 0x%lx\n", (long)p->timerid);


        /* Start the timer */
        its.it_value.tv_sec = 0;//timeout;
        its.it_value.tv_nsec = 1;
        its.it_interval.tv_sec = get_interval(self);
        its.it_interval.tv_nsec = 0;


        if (timer_settime(*get_ptimerid(self), 0, &its, NULL) == -1)
                errExit("timer_settime");

        return 0;
}

int reset_timer(struct cctimer_t * self )
{
        struct itimerspec its;

        its.it_value.tv_sec = get_interval(self);
        its.it_value.tv_nsec =0;
        its.it_interval.tv_sec = get_interval(self);
        its.it_interval.tv_nsec = 0;

        if (timer_settime(get_ptimerid(self), 0, &its, NULL) == -1)
              errExit("timer_settime");
        return 1;
}
