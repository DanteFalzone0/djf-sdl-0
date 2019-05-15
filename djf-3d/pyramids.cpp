// A simple demostration of the first component of
// Dante's C++ 3d graphics library. Compile with:
//      g++ pyramids.cpp `pkg-config --cflags --libs sdl2`
// Must be in the same directory as 'djf-3d-points.hpp'
// to compile.

#include <SDL2/SDL.h>
#include <iostream>
#include "djf-3d-points.hpp"
#define GREEN 0, 255, 70
#define BLACK 0, 0, 0

// It is assumed that the reader is familiar with the SDL2 API.

// Here I'm going to define a Pyramid class, from which we'll
// build four equilateral triangular pyramids.
class Pyramid {
    // Since this Pyramid class is only implemented in this
    // program, I'm just going to make all of its methods and
    // members public for the sake of ease.
    public:
        // The vertices of a Pyramid are instances of the
        // class ThreeDeePoint, which is defined
        // in the file 'djf-3d-points.hpp'. A ThreeDeePoint
        // has various methods for calculating where on the
        // screen to display it based on its x, y, and z
        // coordinates.
        ThreeDeePoint corner_0; // top of the pyramid
        ThreeDeePoint corner_1; // bottom left
        ThreeDeePoint corner_2; // bottom right
        ThreeDeePoint corner_3; // bottom back

        // This method is for deciding where the vanishing
        // point for eprspective rendering is. The methods
        // in a ThreeDeePoint only support single-point
        // perspective.
        void set_center(float x, float y) {
            corner_0.set_display_centerpoint(x, y);
            corner_1.set_display_centerpoint(x, y);
            corner_2.set_display_centerpoint(x, y);
            corner_3.set_display_centerpoint(x, y);
        }

        void set_pyramid_pos(float x, float y, float z) {
            // The coordinates of a ThreeDeePoint are private
            // variables, but it has public methods for getting
            // and setting them.
            corner_0.set_position(x, y, z);
            corner_1.set_position(x-50, y+100, z-50);
            corner_2.set_position(x+50, y+100, z-50);
            corner_3.set_position(x, y+100, z+50);
        }

        // Though I'm using SDL here, djf-3d-points.hpp could
        // just as well be used with most any other graphics
        // library.
        void draw_self(SDL_Renderer *rend) {
            SDL_RenderDrawLine(
                rend,
                corner_0.apparent_x(),
                corner_0.apparent_y(),
                corner_1.apparent_x(),
                corner_1.apparent_y()
            );
            SDL_RenderDrawLine(
                rend,
                corner_0.apparent_x(),
                corner_0.apparent_y(),
                corner_2.apparent_x(),
                corner_2.apparent_y()
            );
            SDL_RenderDrawLine(
                rend,
                corner_0.apparent_x(),
                corner_0.apparent_y(),
                corner_3.apparent_x(),
                corner_3.apparent_y()
            );
            SDL_RenderDrawLine(
                rend,
                corner_1.apparent_x(),
                corner_1.apparent_y(),
                corner_2.apparent_x(),
                corner_2.apparent_y()
            );
            SDL_RenderDrawLine(
                rend,
                corner_2.apparent_x(),
                corner_2.apparent_y(),
                corner_3.apparent_x(),
                corner_3.apparent_y()
            );
            SDL_RenderDrawLine(
                rend,
                corner_3.apparent_x(),
                corner_3.apparent_y(),
                corner_1.apparent_x(),
                corner_1.apparent_y()
            );
        }
};

int main() {
    SDL_Renderer *rend;
    SDL_Window *main_win;
    SDL_Init(SDL_INIT_VIDEO);
    main_win = SDL_CreateWindow(
        "Up and down arrow keys to change depth, WASD to move",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        0
    );
    rend = SDL_CreateRenderer(main_win, 0, 0);
    if (main_win == NULL || rend == NULL) {
        std::cout << "There was a problem!\n";
        std::cout << "Error: " << SDL_GetError() << '\n';
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(main_win);
        SDL_Quit();
        return 1;
    }

    // Rather than have to create each Pyramid individually and
    // call their methods one by one, we can just make an array
    // of Pyramids and iterate over it.
    Pyramid pyramids[4];
    for (int i=0; i<4; ++i) {
        pyramids[i].set_center(300, 300);
    }
    pyramids[0].set_pyramid_pos(100, 100, 100);
    pyramids[1].set_pyramid_pos(500, 100, 100);
    pyramids[2].set_pyramid_pos(100, 500, 100);
    pyramids[3].set_pyramid_pos(500, 500, 100);

    SDL_Event event;
    bool running = true;
    while (running) {
        SDL_SetRenderDrawColor(rend, BLACK, 0);
        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend, GREEN, 255);
        for (int i=0; i<4; ++i) {
            pyramids[i].draw_self(rend);
        }
        SDL_RenderPresent(rend);
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYUP:
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_DOWN:
                        for (int i=0; i<4; ++i) {
                            pyramids[i].set_pyramid_pos(
                                pyramids[i].corner_0.get_x_pos(),
                                pyramids[i].corner_0.get_y_pos(),
                                pyramids[i].corner_0.get_z_pos() + 1
                            );
                        }
                        break;
                    case SDLK_UP:
                        for (int i=0; i<4; ++i) {
                            pyramids[i].set_pyramid_pos(
                                pyramids[i].corner_0.get_x_pos(),
                                pyramids[i].corner_0.get_y_pos(),
                                pyramids[i].corner_0.get_z_pos() - 1
                            );
                        }
                        break;
                    case SDLK_a:
                        for (int i=0; i<4; ++i) {
                            pyramids[i].set_pyramid_pos(
                                pyramids[i].corner_0.get_x_pos() - 4,
                                pyramids[i].corner_0.get_y_pos(),
                                pyramids[i].corner_0.get_z_pos()
                            );
                        }
                        break;
                    case SDLK_d:
                        for (int i=0; i<4; ++i) {
                            pyramids[i].set_pyramid_pos(
                                pyramids[i].corner_0.get_x_pos() + 4,
                                pyramids[i].corner_0.get_y_pos(),
                                pyramids[i].corner_0.get_z_pos()
                            );
                        }
                        break;
                    case SDLK_w:
                        for (int i=0; i<4; ++i) {
                            pyramids[i].set_pyramid_pos(
                                pyramids[i].corner_0.get_x_pos(),
                                pyramids[i].corner_0.get_y_pos() - 4,
                                pyramids[i].corner_0.get_z_pos()
                            );
                        }
                        break;
                    case SDLK_s:
                        for (int i=0; i<4; ++i) {
                            pyramids[i].set_pyramid_pos(
                                pyramids[i].corner_0.get_x_pos(),
                                pyramids[i].corner_0.get_y_pos() + 4,
                                pyramids[i].corner_0.get_z_pos()
                            );
                        }
                        break;
                }
                break;
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(main_win);
    SDL_Quit();
    return 0;
}
