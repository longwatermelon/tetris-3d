#include "cube.h"
#include "render.h"


struct Cube *cube_alloc(Vec3f pos, SDL_Color col)
{
    struct Cube *cube = malloc(sizeof(struct Cube));
    cube->pos = pos;
    cube->color = col;

    const static Vec3f tmp[8] = {
        { 0.f, 0.f, 0.f },
        { 1.f, 0.f, 0.f },
        { 1.f, 0.f, 1.f },
        { 0.f, 0.f, 1.f },
        { 0.f, 1.f, 1.f },
        { 0.f, 1.f, 0.f },
        { 1.f, 1.f, 0.f },
        { 1.f, 1.f, 1.f }
    };

    memcpy(cube->points, tmp, sizeof(cube->points));

    return cube;
}


void cube_free(struct Cube *cube)
{
    free(cube);
}


void cube_render(struct Cube *cube, SDL_Renderer *rend)
{
    SDL_SetRenderDrawColor(rend, cube->color.r, cube->color.g, cube->color.b, 255);

    for (int i = 1; i < 8; ++i)
    {
        cube_draw_line(cube, rend, i, i - 1);
    }
}


void cube_draw_line(struct Cube *cube, SDL_Renderer *rend, int i1, int i2)
{
    Vec3f adjusted_i1 = {
        cube->pos.x + cube->points[i1].x,
        cube->pos.y + cube->points[i1].y,
        cube->pos.z + cube->points[i1].z
    };

    Vec3f adjusted_i2 = {
        cube->pos.x + cube->points[i2].x,
        cube->pos.y + cube->points[i2].y,
        cube->pos.z + cube->points[i2].z
    };

    SDL_Point p1 = render_center_and_scale(render_project_point(adjusted_i1));
    SDL_Point p2 = render_center_and_scale(render_project_point(adjusted_i2));

    SDL_RenderDrawLine(rend, p1.x, p1.y, p2.x, p2.y);
}

