#include "SDLEngine.h"

SDLEngine::SDLEngine()
{
    InitSDL();
    CreateWindow();
    CreateRenderer();
    //CreateSurface();
    CreateTexture();
}

SDLEngine::~SDLEngine()
{
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void SDLEngine::Start()
{
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        UpdateSurface();
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                // switch( e.key.keysym.sym )
                // {
                //     case SDLK_UP:
                //     gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                //     break;

                //     case SDLK_DOWN:
                //     gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                //     break;

                //     case SDLK_LEFT:
                //     gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                //     break;

                //     case SDLK_RIGHT:
                //     gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                //     break;

                //     default:
                //     gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                //     break;
                // }
            }
        }
    }
}

void SDLEngine::UpdateSurface()
{
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
}

int SDLEngine::InitSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    return 0;
}

int SDLEngine::CreateWindow()
{
    win = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    if (win == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
}

int SDLEngine::CreateRenderer()
{
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (ren == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
}

int SDLEngine::CreateSurface(const char* path)
{
    bmp = SDL_LoadBMP(path);
    if (bmp == nullptr)
    {
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
}

int SDLEngine::CreateTexture()
{
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr)
    {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return 0;
    }
    return 0;
}