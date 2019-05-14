// Compile with the following:
// g++ rotatable_triangle.cpp `pkg-config --cflags --libs sdl2`
// Must be in the same directory as 'points.hpp' to compile.

#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include "points.hpp"

#define GREEN 0, 255, 70
#define BLACK 0, 0, 0

int main() {
    SDL_Renderer *renderer;
    SDL_Window *main_window;

    SDL_Init(SDL_INIT_VIDEO);

    // Now I'm going to create a window, 600x600 pixels, centred in the screen
    main_window = SDL_CreateWindow(
        "C++ Rotatable Triangle - Hold A and D keys to rotate",
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
        std::cout << "Error! Something went horribly wrong!\n";
        std::cout << "Error: " << SDL_GetError() << '\n';
        return 1;
    }

    // Now to make some fancy variables!
    bool window_open = true;
    SDL_Event event;
    Point angle_0 {300, (400 - (150 * sqrt(3)))};
    Point angle_1 {150, 400};
    Point angle_2 {450, 400};

    while (window_open) {
        SDL_SetRenderDrawColor(renderer, BLACK, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, GREEN, 255);

        SDL_RenderDrawLine(
            renderer,
            angle_0.x,
            angle_0.y,
            angle_1.x,
            angle_1.y
        );
        SDL_RenderDrawLine(
            renderer,
            angle_1.x,
            angle_1.y,
            angle_2.x,
            angle_2.y
        );
        SDL_RenderDrawLine(
            renderer,
            angle_2.x,
            angle_2.y,
            angle_0.x,
            angle_0.y
        );

        SDL_RenderPresent(renderer);

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                window_open = false;
                break;
            case SDL_KEYUP:
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        angle_0 = rotate_point(
                            300,
                            300,
                            -0.03,
                            angle_0
                        );
                        angle_1 = rotate_point(
                            300,
                            300,
                            -0.03,
                            angle_1
                        );
                        angle_2 = rotate_point(
                            300,
                            300,
                            -0.03,
                            angle_2
                        );
                        break;
                    case SDLK_d:
                        angle_0 = rotate_point(
                            300,
                            300,
                            0.03,
                            angle_0
                        );
                        angle_1 = rotate_point(
                            300,
                            300,
                            0.03,
                            angle_1
                        );
                        angle_2 = rotate_point(
                            300,
                            300,
                            0.03,
                            angle_2
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
