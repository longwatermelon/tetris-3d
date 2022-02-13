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

    return p;
}


void prog_free(struct Prog *p)
{
    free(p->board);
    free(p);
}


void prog_mainloop(struct Prog *p)
{
    SDL_Event evt;
    struct Piece *piece = 0;

    struct Piece **pieces = 0;
    size_t npieces = 0;

    struct timespec last_moved, now;
    clock_gettime(CLOCK_MONOTONIC, &last_moved);
    clock_gettime(CLOCK_MONOTONIC, &now);

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

        if (!piece)
            piece = piece_alloc((SDL_Point){ 5, 0 });

        if (util_timediff(&last_moved, &now) > 0.1f)
        {
            if (!piece_move(piece, p->board, (SDL_Point){ 0, 1 }))
            {
                pieces = realloc(pieces, sizeof(struct Piece*) * ++npieces);
                pieces[npieces - 1] = piece;

                piece = piece_alloc((SDL_Point){ 5, 0 });
            }

            clock_gettime(CLOCK_MONOTONIC, &last_moved);
        }

        for (size_t i = 0; i < npieces; ++i)
            piece_render(pieces[i], p->rend);

        if (piece)
            piece_render(piece, p->rend);

        SDL_SetRenderDrawColor(p->rend, 0, 0, 0, 255);
        SDL_RenderPresent(p->rend);

        clock_gettime(CLOCK_MONOTONIC, &now);
    }

    for (size_t i = 0; i < npieces; ++i)
        piece_free(pieces[i]);

    piece_free(piece);
}

