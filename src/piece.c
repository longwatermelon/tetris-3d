#include "piece.h"


struct Piece *piece_alloc(SDL_Point pos)
{
    struct Piece *p = malloc(sizeof(struct Piece));
    p->cube = pos;
    p->render = cube_alloc((Vec3f){ pos.x - 5, pos.y - 10, 15 }, (SDL_Color){ rand() % 255, rand() % 255, rand() % 255 });

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


bool piece_move(struct Piece *p, char *board, SDL_Point vec)
{
    return piece_move_cube(p, board, vec);
}


bool piece_move_cube(struct Piece *p, char *board, SDL_Point vec)
{
    SDL_Point prev = p->cube;

    p->cube.x += vec.x;
    p->cube.y += vec.y;

    int index = util_coords_to_index(p->cube, 10);

    if (index < 0 || index >= strlen(board) || board[index] != '.')
    {
        p->cube = prev;
        return false;
    }

    p->render->pos.x += vec.x;
    p->render->pos.y += vec.y;

    board[util_coords_to_index(prev, 10)] = '.';
    board[index] = '#';

    return true;
}

