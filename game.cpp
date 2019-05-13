// Compile with the following:
//  g++ game.cpp `pkg-config --cflags --libs sdl2`

#include <SDL2/SDL.h>
#include <stdio.h>

/* All this program does at the moment is create a black GUI window that goes away after 5 seconds. */
int main() {
    // We don't really need everything, but meh, this works for now
    SDL_Init(SDL_INIT_EVERYTHING);

    // Ooh, spooky pointers!
    SDL_Window *main_window;
    main_window = SDL_CreateWindow("Dante's Game", 0, 0, 640, 480, 0);
    if (main_window == NULL) {
        printf("Error! Unable to create window for some reason!\n");
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

    // We're going to keep our window open for a little bit
    SDL_Delay(5000);

    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}
