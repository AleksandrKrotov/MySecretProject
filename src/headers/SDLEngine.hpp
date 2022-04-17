#ifndef SDLENGINE_HPP
#define SDLENGINE_HPP

#include <SDL2/SDL.h>
#include "IEngine.hpp"
#include <iostream>

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

class SDLEngine : public IEngine
{
    public:
        SDL_Window *win;
        SDL_Renderer *ren;
        SDL_Surface *bmp;
        SDL_Texture *tex;

    private:
        int InitSDL();
        int CreateWindow();
        int CreateRenderer();
        int CreateSurface(const char* path);
        int CreateTexture();
        void UpdateSurface();


    public:
        SDLEngine();
        ~SDLEngine();
        void Start();
};
#endif