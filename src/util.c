#include "util.h"


float util_timediff(struct timespec *t1, struct timespec *t2)
{
    return (t2->tv_sec - t1->tv_sec) + (t2->tv_nsec - t1->tv_nsec) / 1e9;
}

