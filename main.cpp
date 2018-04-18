#include <iostream>
#include <SDL2/SDL.h>

#include "sdlWrapper.hpp"

#define W 640
#define H 480

int newMain ( int width, int height ) {
    SDLWrapper::Session session;
    SDLWrapper::Window win ( "My wrapper SDL window!", width, height );
    SDLWrapper::Renderer ren ( win, SDL_RENDERER_ACCELERATED );
    SDLWrapper::Surface surface ( width, height, 32 );

    for ( int j = 0; j < 50; ++j ) {
        for ( int i = 0; i < 640; ++i ) {
            surface.setPixel ( i, j, 255, 0, 0, 255 );
        }
    }

    for ( int j = 60; j < 110; ++j ) {
        for ( int i = 0; i < 640; ++i ) {
            surface.setPixel ( i, j, 0, 255, 0, 255 );
        }
    }

    for ( int j = 120; j < 170; ++j ) {
        for ( int i = 0; i < 640; ++i ) {
            surface.setPixel ( i, j, 0, 0, 255, 255 );
        }
    }

    for ( int j = 180; j < 230; ++j ) {
        for ( int i = 0; i < 640; ++i ) {
            surface.setPixel ( i, j, 0, 0, 0, 255 );
        }
    }

    SDLWrapper::Texture tex ( surface, ren );

    for ( int i = 0; i < 3; ++i ) {
        SDL_RenderClear ( ren.r );

        SDL_RenderCopy ( ren.r, tex.t, NULL, NULL );

        SDL_RenderPresent ( ren.r );

        SDL_Delay ( 1000 );
    }

    return 0;
}

int main () {
    int width = W;
    int height = H;

    newMain ( width, height );
    return 0;
}
