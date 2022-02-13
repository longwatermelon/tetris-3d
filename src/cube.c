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
        Vec3f prev_cube = cube->points[i - 1];
        Vec3f curr_cube = cube->points[i];

        Vec3f adjusted_p = {
            cube->pos.x + prev_cube.x,
            cube->pos.y + prev_cube.y,
            cube->pos.z + prev_cube.z
        };

        Vec3f adjusted_c = {
            cube->pos.x + curr_cube.x,
            cube->pos.y + curr_cube.y,
            cube->pos.z + curr_cube.z
        };

        SDL_Point prev = render_center_and_scale(render_project_point(adjusted_p));
        SDL_Point curr = render_center_and_scale(render_project_point(adjusted_c));

        SDL_RenderDrawLine(rend, prev.x, prev.y, curr.x, curr.y);
    }
}

