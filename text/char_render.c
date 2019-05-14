/* This program is to demonstrate the usage of 'djf-SDL-text.h',
which as of 14 May 2019 is a work in progress.
Compile with the following:
gcc char_render.c `pkg-config --cflags --libs sdl2`
Must be in the same directory as 'djf-SDL-text.h' to compile.
*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include "djf-SDL-text.h"
#define GREEN 0, 255, 70
#define BLACK 0, 0, 0

int main() {
    /* Here we set up our window and renderer */
    SDL_Renderer *rend;
    SDL_Window *main_window;
    SDL_Init(SDL_INIT_VIDEO);
    main_window = SDL_CreateWindow(
        "Character Renderer - written in C by Dante Falzone",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        0
    );
    rend = SDL_CreateRenderer(
        main_window,
        0,
        0
    );
    if (main_window == NULL || rend == NULL) {
        printf("Error! Something went horribly wrong!\n");
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

    int window_open = 1;
    SDL_Event event;
    while (window_open) {
        /* Paint our surface black */
        SDL_SetRenderDrawColor(rend, BLACK, 0);
        SDL_RenderClear(rend);
        /* Now to test character rendering */
        int i;
        /* This for loop tells the world how I feel every day lol */
        for (i=1; i<400; i+=6) {
            render_char(rend, i, 1, 'A', GREEN, 255);
        }
        render_string(
            rend, /* rendering context */
            1, /* top-left corner of the string */
            11,
            /* as of 14 May 2019 we only have uppercase
            characters and spaces so far */
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
            26, /* length of the string */
            GREEN,
            255
        );
        render_string(
            rend,
            1,
            21,
            "PROGRAMMED IN C BY DANTE FALZONE",
            32,
            GREEN,
            255
        );

        SDL_RenderPresent(rend);

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                window_open = 0;
                break;
        }
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}
