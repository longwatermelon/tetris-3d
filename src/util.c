#include "util.h"


float util_timediff(struct timespec *t1, struct timespec *t2)
{
    return (t2->tv_sec - t1->tv_sec) + (t2->tv_nsec - t1->tv_nsec) / 1e9;
}


int util_coords_to_index(SDL_Point coords, int w)
{
    return coords.y * w + coords.x;
}

