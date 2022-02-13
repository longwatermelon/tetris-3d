#include "prog.h"
#include "cube.h"


struct Prog *prog_alloc(SDL_Window *w, SDL_Renderer *r)
{
    struct Prog *p = malloc(sizeof(struct Prog));
    p->running = true;

    p->window = w;
    p->rend = r;

    return p;
}


void prog_free(struct Prog *p)
{
    free(p);
}


void prog_mainloop(struct Prog *p)
{
    SDL_Event evt;
    struct Cube *c = cube_alloc((Vec3f){ 1, 1, 3 }, (SDL_Color){ 255, 0, 0 });

    while (p->running)
    {
        while (SDL_PollEvent(&evt))
        {
            switch (evt.type)
            {
            case SDL_QUIT:
                p->running = false;
                break;
            }
        }

        SDL_RenderClear(p->rend);

        cube_render(c, p->rend);

        SDL_SetRenderDrawColor(p->rend, 0, 0, 0, 255);
        SDL_RenderPresent(p->rend);
    }
}

