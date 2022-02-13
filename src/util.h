#ifndef UTIL_H
#define UTIL_H

#include <time.h>

typedef struct
{
    float x, y, z;
} Vec3f;

float util_timediff(struct timespec *t1, struct timespec *t2);

#endif

