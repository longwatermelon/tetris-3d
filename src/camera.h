#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"

struct Camera
{
    Vec3f pos;
    float ha, va;
};

struct Camera *camera_alloc(Vec3f pos, float ha, float va);
void camera_free(struct Camera *c);

#endif

