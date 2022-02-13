#include "render.h"


SDL_FPoint render_project_point(Vec3f p, struct Camera *c)
{
    SDL_FPoint proj;

    p.x -= c->pos.x;
    p.y -= c->pos.y;

    float rotx[3][3] = {
        { 1, 0, 0 },
        { 0, cosf(c->va), sinf(c->va) },
        { 0, -sinf(c->va), cosf(c->va) }
    };

    float roty[3][3] = {
        { cosf(c->ha), 0, sinf(c->ha) },
        { 0, 1, 0 },
        { -sinf(c->ha), 0, cosf(c->ha) }
    };

    p = util_matrix_mul(roty, p);
    p = util_matrix_mul(rotx, p);

    if (p.z != 0.f)
    {
        proj.x = p.x / p.z;
        proj.y = p.y / p.z;
    }

    return proj;
}


SDL_Point render_center_and_scale(SDL_FPoint p)
{
    return (SDL_Point){
        (p.x + 1.f) * 400.f,
        (p.y + 1.f) * 400.f
    };
}

