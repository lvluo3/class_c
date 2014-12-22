typedef void (*TIMEOUT)(void * p);

struct cctimer_t
{
	timer_t * p_tid;
	long long interval;
	TIMEOUT timeout;
};

int starttimer(struct cctimer_t * self);
int reset_timer(struct cctimer_t * self );
