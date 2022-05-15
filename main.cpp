#include "controller.hpp"
#include <random>

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

    //mon test pour l'affichage de la map
    SDL_Texture* tab_texture[3];
    tab_texture[0]=chargertexture(renderer, "sprit/Fond.png");
    tab_texture[1]=chargertexture(renderer, "sprit/Mur.png");
    tab_texture[2]=chargertexture(renderer,"sprit/Echelle.png");
    SDL_Texture* textureperso=chargertexture(renderer,"sprit/personnage.webp");
    SDL_Texture* texturebouton[2];
    texturebouton[0]=chargertexture(renderer,"sprit/bouton.jpeg");
    texturebouton[1]=chargertexture(renderer,"sprit/boutonb.jpeg");

    int** map=(int**)malloc(50*sizeof(int*));
    for (int k=0;k<50;k++)
    {
        map[k]=(int*)malloc(50*sizeof(int*));
        for (int i=0;i<50;i++)
        {
            map[k][i]=rand()%3;
        }
    }
    Interactible* stock[9];
    for (int k=0;k<3;k++)
    {
        for (int i=0;i<3;i++)
        {
            Interactible* temp=new Interactible((k+2)*SIZECELL,(i+2)*SIZECELL,texturebouton,0,1);
            stock[3*k+i]=temp;
        }
    }

    for (int k=0;k<9;k++)
    {
        for (int i=0;i<9;i++)
        {
            stock[k]->AddElement(stock[i]);
        }
    }
    Controller control(renderer);
    int posx=50;
    int posy=100;
    Perso perso(posx,posy,nullptr,textureperso);
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
    bool user_input[4]={false,false,false,false}; //{droite,gauche,haut,bas}
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
                case SDLK_RIGHT:
                    user_input[0]=true;
                    break;
                case SDLK_d:
                    user_input[0]=true;
                    break;
                case SDLK_LEFT:
                    user_input[1]=true;
                    break;
                case SDLK_q:
                    user_input[1]=true;
                    break;
                case SDLK_UP:
                    user_input[2]=true;
                    break;
                case SDLK_z:
                    user_input[2]=true;
                    break;
                case SDLK_DOWN:
                    user_input[3]=true;
                    break;
                case SDLK_s:
                    user_input[3]=true;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                std::cout << event.button.x << event.button.y << std::endl;
                for (int k=0;k<9;k++)
                {
                    if (event.button.x>stock[k]->GetX() and event.button.x<(stock[k]->GetX()+SIZECELL))
                    {
                        if (event.button.y>stock[k]->GetY() and event.button.y<(stock[k]->GetY()+SIZECELL))
                        {
                            Enigme_carre_blanc(stock[k]);
                        }
                    }
                }
                break;
            case SDL_QUIT:
                running = 0;
                break;
            }
            break;
        }
        afficher_map(renderer,control._map,posx,posy,tab_texture);
        for (int k=0;k<9;k++)
        {
            stock[k]->Afficher(renderer,posx,posy);
        }
        perso.Afficher(renderer);
        SDL_RenderPresent(renderer);
        for (int k=0;k<4;k++) user_input[k]=false;
        posx++;
        posy++;
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    for (int k = 0; k < 2; k++) SDL_DestroyTexture(tab_texture[k]);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}