#include <iostream>
#include <tuple>
#include <SDL2/SDL.h>

#include "Logger.hpp"
#include "sdlWrapper.hpp"

static Logger logger ( std::cout, Logger::LogLevel::INFO );

void SDLWrapper::logSDLError ( std::string msg ) {
    logger.e ( msg + " error: " + SDL_GetError() );
}

SDLWrapper::Session::Session () {
    if ( SDL_Init ( SDL_INIT_VIDEO ) != 0 ) {
        logSDLError ( "SDL_Init" );
        throw std::runtime_error ( "SDL_Init" );
    }

    logger.d ( "Constructed session" );
}

SDLWrapper::Session::~Session () {
    SDL_Quit();

    logger.d ( "Destroyed session" );
}

SDLWrapper::Window::Window ( std::string title, int width, int height ) {
    w = SDL_CreateWindow ( title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_SHOWN );
    if ( w == nullptr ) {
        logSDLError ( "SDL_CreateWindow" );
        throw std::runtime_error ( "SDL_CreateWindow" );
    }

    logger.d ( "Constructed window" );
}

SDLWrapper::Window::~Window () {
    SDL_DestroyWindow ( w );

    logger.d ( "Destroyed window" );
}


SDLWrapper::Renderer::Renderer ( SDLWrapper::Window & window,
        Uint32 flags = SDL_RENDERER_ACCELERATED ) {
    r = SDL_CreateRenderer ( window.w, -1, flags );
    if ( r == nullptr ) {
        logSDLError ( "SDL_CreateRenderer" );
        throw std::runtime_error ( "SDL_CreateRenderer" );
    }

    logger.d ( "Constructed renderer" );
}

SDLWrapper::Renderer::~Renderer () {
    SDL_DestroyRenderer ( r );

    logger.d ( "Destroyed renderer" );
}

SDLWrapper::Surface::Surface ( int width, int height, int bitDepth = 32 ) {
    s = SDL_CreateRGBSurface ( 0,
            width,
            height,
            bitDepth,
            rmask,
            gmask,
            bmask,
            amask );
    if ( s == nullptr ) {
        logSDLError ( "SDL_CreateRGBSurface" );
        throw std::runtime_error ( "SDL_CreateRGBSurface" );
    }

    logger.d ( "Constructed surface" );
}

SDLWrapper::Surface::~Surface () {
    SDL_FreeSurface ( s );

    logger.d ( "Destroyed surface" );
}

void SDLWrapper::Surface::setPixel ( int x, int y, int r, int g, int b, int a ) {

    Uint32 pixel = SDL_MapRGBA ( s->format, r, g, b, a );

    switch ( s->format->BytesPerPixel ) {
        case 4:
            *( ( ( Uint32 * )( s->pixels ) ) + x + ( y * s->w ) ) = ( Uint32 )pixel;
            break;
        case 3:
            std::cerr <<
                "Could not set pixel on surface with 24 bit pixels. Bug the author to implement this" <<
                std::endl;
            break;
        case 2:
            *( ( ( Uint16 * )( s->pixels ) ) + x + ( y * s->w ) ) = ( Uint16 )pixel;
            break;
        case 1:
            *( ( ( Uint8 * )( s->pixels ) ) + x + ( y * s->w ) ) = ( Uint8 )pixel;
            break;
        default:
            std::cerr <<
                "Could not set pixel on surface with unknown bit depth." <<
                std::endl;
            break;
    }
}

void SDLWrapper::Surface::setPixel ( int x, int y, std::tuple < Uint8, Uint8, Uint8, Uint8 > & rgbaPixel ) {
    setPixel ( x,
            y,
            std::get < 0 > ( rgbaPixel ),
            std::get < 1 > ( rgbaPixel ),
            std::get < 2 > ( rgbaPixel ),
            std::get < 3 > ( rgbaPixel ) );
}

std::tuple < Uint8, Uint8, Uint8, Uint8 > SDLWrapper::Surface::getPixel ( int x, int y ) {
    Uint32 pixel = 0;
    switch ( s->format->BytesPerPixel ) {
        case 4:
            pixel = *( Uint32 * )( s->pixels ) + x + ( y * s->w );

            break;
        case 3:
            std::cerr <<
                "Could not get pixel on surface with 24 bit pixels. Bug the author to implement this" <<
                std::endl;

            break;
        case 2:
            pixel = ( Uint32 )( *( Uint16 * )( s->pixels ) + x + ( y * s->w ) );
            pixel &= 0x0000FFFF;

            break;
        case 1:
            pixel = ( Uint32 )( *( Uint8 * )( s->pixels ) + x + ( y * s->w ) );
            pixel &= 0x000000FF;

            break;
        default:
            std::cerr <<
                "Could not get pixel on surface with unknown bit depth." <<
                std::endl;

            break;
    }

    Uint8 r = 0, g = 0, b = 0, a = 0;

    SDL_GetRGBA ( pixel, s->format, &r, &g, &b, &a );

    std::tuple < Uint8, Uint8, Uint8, Uint8 > rgbaPixel = { r, g, b, a };

    return rgbaPixel;
}

SDLWrapper::Texture::Texture ( SDLWrapper::Surface & surface, SDLWrapper::Renderer & ren ) {
    t = SDL_CreateTextureFromSurface ( ren.r, surface.s );
    if ( t == nullptr ) {
        logSDLError ( "SDL_CreateTextureFromSurface" );
        throw std::runtime_error ( "SDL_CreateTextureFromSurface" );
    }

    logger.d ( "Constructed texture" );
}

SDLWrapper::Texture::~Texture () {
    SDL_DestroyTexture ( t );

    logger.d ( "Destroyed texture" );
}
