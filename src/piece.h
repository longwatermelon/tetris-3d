#ifndef PIECE_H
#define PIECE_H

#include "cube.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

struct Piece
{
    SDL_Point cubes[4];
    struct Cube *renders[4];
};

struct Piece *piece_alloc(SDL_Point pos);
void piece_free(struct Piece *p);

void piece_render(struct Piece *p, SDL_Renderer *rend);

bool piece_move(struct Piece *p, char *board, SDL_Point vec);
bool piece_move_cube(struct Piece *p, char *board, SDL_Point vec, int idx);

#endif

