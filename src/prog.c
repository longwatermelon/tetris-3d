#include "prog.h"
#include "cube.h"
#include "piece.h"


struct Prog *prog_alloc(SDL_Window *w, SDL_Renderer *r)
{
    struct Prog *p = malloc(sizeof(struct Prog));
    p->running = true;

    p->window = w;
    p->rend = r;

    // Board is 10x20
    p->board = calloc(10 * 20 + 1, sizeof(char));

    for (int i = 0; i < 20; ++i)
        strcat(p->board, "..........");

    p->piece = 0;
    p->pieces = 0;
    p->npieces = 0;

    return p;
}


void prog_free(struct Prog *p)
{
    for (size_t i = 0; i < p->npieces; ++i)
        piece_free(p->pieces[i]);

    piece_free(p->piece);

    free(p->board);
    free(p);
}


void prog_mainloop(struct Prog *p)
{
    SDL_Event evt;

    struct timespec last_moved, now;
    clock_gettime(CLOCK_MONOTONIC, &last_moved);
    clock_gettime(CLOCK_MONOTONIC, &now);

    while (p->running)
    {
        prog_handle_events(p, &evt);

        SDL_RenderClear(p->rend);

        if (!p->piece)
            p->piece = piece_alloc((SDL_Point){ 5, 0 });

        if (util_timediff(&last_moved, &now) > 0.1f)
        {
            if (!piece_move(p->piece, p->board, (SDL_Point){ 0, 1 }))
            {
                for (int i = 0; i < 4; ++i)
                    p->board[util_coords_to_index(p->piece->cubes[i], 10)] = '#';

                p->pieces = realloc(p->pieces, sizeof(struct Piece*) * ++p->npieces);
                p->pieces[p->npieces - 1] = p->piece;

                p->piece = piece_alloc((SDL_Point){ 5, 0 });
            }

            clock_gettime(CLOCK_MONOTONIC, &last_moved);
        }

        for (size_t i = 0; i < p->npieces; ++i)
            piece_render(p->pieces[i], p->rend);

        if (p->piece)
            piece_render(p->piece, p->rend);

        SDL_SetRenderDrawColor(p->rend, 0, 0, 0, 255);
        SDL_RenderPresent(p->rend);

        clock_gettime(CLOCK_MONOTONIC, &now);
    }
}


void prog_handle_events(struct Prog *p, SDL_Event *evt)
{
    while (SDL_PollEvent(evt))
    {
        switch (evt->type)
        {
        case SDL_QUIT:
            p->running = false;
            break;
        case SDL_KEYDOWN:
        {
            switch (evt->key.keysym.sym)
            {
            case SDLK_RIGHT: piece_move(p->piece, p->board, (SDL_Point){ 1, 0 }); break;
            case SDLK_LEFT: piece_move(p->piece, p->board, (SDL_Point){ -1, 0 }); break;
            case SDLK_UP: piece_rotate(p->piece); break;
            }
        } break;
        }
    }
}

