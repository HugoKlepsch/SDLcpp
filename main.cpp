#include <tuple>
#include <iostream>
#include <SDL2/SDL.h>

#include "sdlWrapper.hpp"

#define W 640
#define H 480

void printPixel ( std::tuple < Uint8, Uint8, Uint8, Uint8 > rgbaPixel ) {
    std::cout << "Pixel at (0, 0): r(" << 
        static_cast < int > ( std::get < 0 > ( rgbaPixel ) ) << ") g(" <<
        static_cast < int > ( std::get < 1 > ( rgbaPixel ) ) << ") b(" <<
        static_cast < int > ( std::get < 2 > ( rgbaPixel ) ) << ") a(" <<
        static_cast < int > ( std::get < 3 > ( rgbaPixel ) ) << ")" << std::endl;
}

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

    auto rgbaPixel = surface.getPixel ( 0, 0 );

    printPixel ( rgbaPixel );

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
