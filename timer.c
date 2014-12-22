#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
} while (0)

typedef void       (*TIMERFUNC)(union sigval);

static void* handler(void * p)
{
	
}

static int starttimer(long long timeout)
{
        timer_t timerid;
        struct sigevent sev;
        struct itimerspec its;



        sev.sigev_notify = SIGEV_THREAD;//SIGEV_SIGNAL;
        sev.sigev_value.sival_ptr = NULL;
        sev.sigev_notify_function = (TIMERFUNC)handler;
        if (timer_create(CLOCK_REALTIME, &(sev), &(timerid)) == -1)
                errExit("timer_create");
        //printf("timer ID is 0x%lx\n", (long)p->timerid);


        /* Start the timer */
        its.it_value.tv_sec = 0;//timeout;
        its.it_value.tv_nsec = 1;
        its.it_interval.tv_sec = timeout;
        its.it_interval.tv_nsec = 0;


        if (timer_settime(timerid, 0, &its, NULL) == -1)
                errExit("timer_settime");

        return 0;
}


