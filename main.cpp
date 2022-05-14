#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

int main(int argv, char ** argc)
{  

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *window;
    int width = 1000;
    int height = 600;

    window = SDL_CreateWindow("Inca jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        /* on peut aussi utiliser SDL_Log() */
    }
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }

    if (TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
    }

    //TTF_Font *font1;
    //TTF_Font *font2;
    //TTF_Font *font3;
    //font1 = TTF_OpenFont("../res/arial.ttf", 15);
    //font2 = TTF_OpenFont("../res/arial.ttf", 12);
    //font3 = TTF_OpenFont("../res/arial.ttf", 23);

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = 0;
    initted = IMG_Init(flags);
    if ((initted & flags) != flags)
    {
        printf("IMG_Init: Impossible d'initialiser le support des formats JPG et PNG requis!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }

    SDL_Event event;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    running = false;
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    width = event.window.data1;
                    height = event.window.data2;
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    break;
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                std::cout << event.button.x << event.button.y << std::endl;
                break;
            case SDL_QUIT:
                running = 0;
                break;
            }
            break;
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}