#include "render.h"


SDL_FPoint render_project_point(Vec3f p)
{
    SDL_FPoint proj;

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

