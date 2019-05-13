// Compile with the following:
//  g++ game.cpp `pkg-config --cflags --libs sdl2`

#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window;
    window = SDL_CreateWindow("Dante's Game", 0, 0, 640, 480, 0);
    if (window == NULL) {
        printf("Error! Unable to create window for some reason!\n");
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }


    SDL_Delay(5000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
