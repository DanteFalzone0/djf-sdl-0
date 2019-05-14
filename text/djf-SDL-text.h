/* Header file for displaying characters with SDL. Written
in pure C. Work in progress as of 14 May 2019.*/
#ifndef SDL2_SDL_H
#define SDL2_SDL_H
#include <SDL2/SDL.h>
#endif

/* This function renders a single character with a renderer.
It returns 0 on success and nonzero on an error. */
int render_char(SDL_Renderer *renderer,
                float x,
                float y,
                char character,
                int r,
                int g,
                int b,
                int alpha) {
    int error_val;
    error_val += SDL_SetRenderDrawColor(renderer, r, g, b, alpha);

    /* Every character is 8 pixels tall and 5 pixels wide. */
    switch (character) {
        case 'A':
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+4, y+2);
            error_val += SDL_RenderDrawPoint(renderer, x+0, y+3);
            error_val += SDL_RenderDrawPoint(renderer, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x+4, y+4);
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+4, x+4, y+7);
            break;
        case 'B':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+3, y+3);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+4, x+4, y+6);
            break;
        case 'C':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+7);
            break;
        case 'D':
            error_val += SDL_RenderDrawLine(renderer, x+3, y, x, y);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+7, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            break;
        case 'E':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y+7);
            break;
    }
    return error_val;
}
