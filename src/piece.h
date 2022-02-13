#ifndef PIECE_H
#define PIECE_H

#include "cube.h"
#include <SDL2/SDL.h>

struct Piece
{
    SDL_Point pos;

    SDL_Point cube;
    struct Cube *render;
};

struct Piece *piece_alloc(SDL_Point pos);
void piece_free(struct Piece *p);

void piece_render(struct Piece *p, SDL_Renderer *rend);

void piece_move(struct Piece *p, SDL_Point vec);

#endif

