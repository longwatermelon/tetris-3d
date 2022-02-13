#ifndef PROG_H
#define PROG_H

#include <stdbool.h>
#include <SDL2/SDL.h>

struct Prog
{
    bool running;

    SDL_Window *window;
    SDL_Renderer *rend;

    char *board;

    struct Piece *piece;
    struct Piece **pieces;
    size_t npieces;
};

struct Prog *prog_alloc(SDL_Window *w, SDL_Renderer *r);
void prog_free(struct Prog *p);

void prog_mainloop(struct Prog *p);
void prog_handle_events(struct Prog *p, SDL_Event *evt);

#endif

