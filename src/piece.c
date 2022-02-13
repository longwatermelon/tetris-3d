#include "piece.h"


struct Piece *piece_alloc(SDL_Point pos)
{
    struct Piece *p = malloc(sizeof(struct Piece));

    const SDL_Point cubes[4] = {
        { pos.x, pos.y },
        { pos.x + 1, pos.y },
        { pos.x + 2, pos.y },
        { pos.x + 3, pos.y }
    };

    memcpy(p->cubes, cubes, sizeof(p->cubes));

    SDL_Color col = { rand() % 255, rand() % 255, rand() % 255 };

    for (int i = 0; i < 4; ++i)
        p->renders[i] = cube_alloc((Vec3f){ cubes[i].x - 5, cubes[i].y - 10, 15 }, col);

    return p;
}


void piece_free(struct Piece *p)
{
    free(p);
}


void piece_render(struct Piece *p, SDL_Renderer *rend)
{
    for (int i = 0; i < 4; ++i)
        cube_render(p->renders[i], rend);
}


bool piece_move(struct Piece *p, char *board, SDL_Point vec)
{
    for (int i = 0; i < 4; ++i)
        if (!piece_move_cube(p, board, vec, i))
        {
            SDL_Point invert = { -vec.x, -vec.y };
            for (int j = 0; j < i; ++j)
                piece_move_cube(p, board, invert, j);

            return false;
        }

    return true;
}


bool piece_move_cube(struct Piece *p, char *board, SDL_Point vec, int idx)
{
    SDL_Point prev = p->cubes[idx];

    p->cubes[idx].x += vec.x;
    p->cubes[idx].y += vec.y;

    int index = util_coords_to_index(p->cubes[idx], 10);

    if (index < 0 || index >= strlen(board) || board[index] != '.' ||
        p->cubes[idx].x < 0 || p->cubes[idx].x >= 10)
    {
        p->cubes[idx] = prev;
        return false;
    }

    p->renders[idx]->pos.x += vec.x;
    p->renders[idx]->pos.y += vec.y;

//    board[util_coords_to_index(prev, 10)] = '.';
//    board[index] = '#';

    return true;
}

