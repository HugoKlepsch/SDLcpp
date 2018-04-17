namespace SDLWrapper {

    void logSDLError ( std::ostream & os, std::string unit );

    class Session {
        public:
            Session ();
            ~Session ();
    };

    class Window {
        public:
            SDL_Window * w;
            Window ( std::string title, int width, int height );
            ~Window();
    };

    class Renderer {
        public:
            SDL_Renderer * r;
            Renderer ( SDLWrapper::Window & window, Uint32 flags );
            ~Renderer();
    };

    class Surface {
        public:
            SDL_Surface * s;
            Surface ( int width, int height, int bitDepth );
            ~Surface();

            void setPixel ( int x, int y, int r, int g, int b, int a );
            void setPixel ( int x, int y, std::tuple < Uint8, Uint8, Uint8, Uint8 > & rgbaPixel );
            std::tuple < Uint8, Uint8, Uint8, Uint8 > getPixel ( int x, int y );

        private:
            /* SDL interprets each pixel as a 32-bit number, so our masks must depend
               on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            static const Uint32 rmask = 0xff000000;
            static const Uint32 gmask = 0x00ff0000;
            static const Uint32 bmask = 0x0000ff00;
            static const Uint32 amask = 0x000000ff;
#else
            static const Uint32 rmask = 0x000000ff;
            static const Uint32 gmask = 0x0000ff00;
            static const Uint32 bmask = 0x00ff0000;
            static const Uint32 amask = 0xff000000;
#endif
    };

    class Texture {
        public:
            SDL_Texture * t;
            Texture ( SDLWrapper::Surface & surface, SDLWrapper::Renderer & ren );
            ~Texture();
    };

}
