// Compile with the following:
// g++ game.cpp `pkg-config --cflags --libs sdl2`

#include <SDL2/SDL.h>
#include <iostream>

// gonna define some fun colours to use
#define GREEN 0, 255, 70
#define BLACK 0, 0, 0
#define RED 255, 0, 0
#define BLUE 20, 20, 255

int main() {
    SDL_Renderer *renderer;
    SDL_Window *main_window;

    SDL_Init(SDL_INIT_VIDEO);

    // Now I'm going to create a window, 600x600 pixels, centred in the screen
    main_window = SDL_CreateWindow(
        "Dante's C++ Videogame",
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

    /* I'm making a line that will move side to side.
    These two integers are for describing how I want to move
    that line. */
    int offset = -99;
    int direction = 1;

    while (window_open) {
        SDL_SetRenderDrawColor(renderer, BLACK, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, GREEN, 255);
        SDL_RenderDrawLine(
            renderer,
            (300 + (offset * -1)),
            50,
            (300 + offset),
            550
        );

        SDL_RenderPresent(renderer);

        offset += direction;
        if (offset == 100) {
            direction *= -1;
        } else if (offset == -100) {
            direction *= -1;
        }

        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            window_open = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}

/* SDL isn't that hard to use! I find it much easier than fiddling with ggez in Rust.
I must admit to a *bit* of scepticism about the prospect of Rust overthrowing the
longstanding reign of C++. */
