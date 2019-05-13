// Compile with the following:
// g++ spaceship0.cpp `pkg-config --cflags --libs sdl2`

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
        "Dante's C++ Videogame -- Use WASD to move",
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

    // Variables for defining the "spaceship" location
    float x = 300;
    float y = 300;
    float x_vel = 0;
    float y_vel = 0;
    int cycle = 0;

    while (window_open) {
        if (cycle < 10) {
            cycle++;
        } else {
            cycle = 0;
        }

        if (x > 602) x = -2;
        if (x < -2)  x = 602;
        if (y > 602) y = -2;
        if (y < -2)  y = 602;
        if (x_vel > 1.5)  x_vel = 1.5;
        if (x_vel < -1.5) x_vel = -1.5;
        if (y_vel > 1.5)  y_vel = 1.5;
        if (y_vel < -1.5) y_vel = -1.5;

        SDL_SetRenderDrawColor(renderer, BLACK, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, GREEN, 255);
        SDL_RenderDrawPoint(renderer, x, y);
        SDL_RenderDrawPoint(renderer, x-2, y);
        SDL_RenderDrawPoint(renderer, x+2, y);
        SDL_RenderDrawPoint(renderer, x, y-2);
        SDL_RenderDrawPoint(renderer, x, y+2);
        x += x_vel;
        y += y_vel;
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
                    case SDLK_w:
                        y_vel -= 0.11;
                        break;
                    case SDLK_a:
                        x_vel -= 0.1;
                        break;
                    case SDLK_s:
                        y_vel += 0.1;
                        break;
                    case SDLK_d:
                        x_vel += 0.11;
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
