#include "piece.h"


struct Piece *piece_alloc(SDL_Point pos)
{
    struct Piece *p = malloc(sizeof(struct Piece));
    p->pos = pos;

    p->cube = p->pos;
    p->render = cube_alloc((Vec3f){ pos.x - 5, pos.y - 10, 15 }, (SDL_Color){ 255, 255, 0 });

    return p;
}


void piece_free(struct Piece *p)
{
    free(p);
}


void piece_render(struct Piece *p, SDL_Renderer *rend)
{
    cube_render(p->render, rend);
}


void piece_move(struct Piece *p, SDL_Point vec)
{
    p->cube.x += vec.x;
    p->cube.y += vec.y;

    p->render->pos.x += vec.x;
    p->render->pos.y += vec.y;
}

