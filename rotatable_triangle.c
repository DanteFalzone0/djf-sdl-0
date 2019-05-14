/* I wrote `rotatable_triangle.cpp` first, but then realized
that it didn't really need to be in C++, so I rewrote it in C
by changing a few things. */

/* Compile with the following:
   gcc rotatable_triangle.c `pkg-config --cflags --libs sdl2` -lm
   Must be in the same directory as 'cpoints.h' to compile. */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "cpoints.h"

#define GREEN 0, 255, 70
#define BLACK 0, 0, 0

int main() {
    SDL_Renderer *renderer;
    SDL_Window *main_window;

    SDL_Init(SDL_INIT_VIDEO);

    // Now I'm going to create a window, 600x600 pixels, centred in the screen
    main_window = SDL_CreateWindow(
        "C Rotatable Triangle - Hold A and D keys to rotate",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        0
    );

    // and a renderer so we can draw things on that window
    renderer = SDL_CreateRenderer(
        main_window,
        0,
        0
    );

    // Make sure that the user is properly bewildered if something goes wrong
    if (main_window == NULL || renderer == NULL) {
        printf("Error! Something went horribly wrong!\n");
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

    // Now to make some fancy variables!
    int window_open = 1;
    SDL_Event event;
    float angle_0_x = 300;
    float angle_0_y = 400 - (150 * sqrt(3));
    float angle_1_x = 150;
    float angle_1_y = 400;
    float angle_2_x = 450;
    float angle_2_y = 400;

    while (window_open) {
        SDL_SetRenderDrawColor(renderer, BLACK, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, GREEN, 255);

        SDL_RenderDrawLine(
            renderer,
            angle_0_x,
            angle_0_y,
            angle_1_x,
            angle_1_y
        );
        SDL_RenderDrawLine(
            renderer,
            angle_1_x,
            angle_1_y,
            angle_2_x,
            angle_2_y
        );
        SDL_RenderDrawLine(
            renderer,
            angle_2_x,
            angle_2_y,
            angle_0_x,
            angle_0_y
        );

        SDL_RenderPresent(renderer);

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                window_open = 0;
                break;
            case SDL_KEYUP:
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        angle_0_x = rotate_point_x(
                            300,
                            300,
                            -0.03,
                            angle_0_x,
                            angle_0_y
                        );
                        angle_0_y = rotate_point_y(
                            300,
                            300,
                            -0.03,
                            angle_0_x,
                            angle_0_y
                        );
                        angle_1_x = rotate_point_x(
                            300,
                            300,
                            -0.03,
                            angle_1_x,
                            angle_1_y
                        );
                        angle_1_y = rotate_point_y(
                            300,
                            300,
                            -0.03,
                            angle_1_x,
                            angle_1_y
                        );
                        angle_2_x = rotate_point_x(
                            300,
                            300,
                            -0.03,
                            angle_2_x,
                            angle_2_y
                        );
                        angle_2_y = rotate_point_y(
                            300,
                            300,
                            -0.03,
                            angle_2_x,
                            angle_2_y
                        );
                        break;
                    case SDLK_d:
                        angle_0_x = rotate_point_x(
                            300,
                            300,
                            0.03,
                            angle_0_x,
                            angle_0_y
                        );
                        angle_0_y = rotate_point_y(
                            300,
                            300,
                            0.03,
                            angle_0_x,
                            angle_0_y
                        );
                        angle_1_x = rotate_point_x(
                            300,
                            300,
                            0.03,
                            angle_1_x,
                            angle_1_y
                        );
                        angle_1_y = rotate_point_y(
                            300,
                            300,
                            0.03,
                            angle_1_x,
                            angle_1_y
                        );
                        angle_2_x = rotate_point_x(
                            300,
                            300,
                            0.03,
                            angle_2_x,
                            angle_2_y
                        );
                        angle_2_y = rotate_point_y(
                            300,
                            300,
                            0.03,
                            angle_2_x,
                            angle_2_y
                        );
                        break;
                }
                break;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}
