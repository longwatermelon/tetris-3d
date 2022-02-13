#include "camera.h"


struct Camera *camera_alloc(Vec3f pos, float ha, float va)
{
    struct Camera *c = malloc(sizeof(struct Camera));
    c->pos = pos;
    c->ha = ha;
    c->va = va;

    return c;
}


void camera_free(struct Camera *c)
{
    free(c);
}

