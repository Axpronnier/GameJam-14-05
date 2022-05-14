#include "dessin.hpp"

SDL_Texture *chargertexture(SDL_Renderer *renderer, const char *nom)
{
    SDL_Texture *matext;
    SDL_Surface *my_image = NULL;
    my_image = IMG_Load(nom);
    if (my_image == NULL)
        std::cout << "probleme de chargement :(" << nom << std::endl;
    matext = SDL_CreateTextureFromSurface(renderer, my_image);
    SDL_FreeSurface(my_image);
    if (matext == NULL)
        std::cout << "ca marche po" << std::endl;
    return matext;
}

SDL_Texture *creertxt(SDL_Renderer *renderer, const char *texte, TTF_Font *font, SDL_Color couleur)
{
    SDL_Texture *matext;
    SDL_Surface *surf = TTF_RenderText_Blended(font, texte, couleur);
    matext = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    return matext;
}

void afficher_map(SDL_Renderer *renderer, int **map, int posx, int posy, SDL_Texture **tab_texture)
{
    int left = posx - WSCREEN / 2 + WPERSO / 2;
    int right = left + WSCREEN;
    int up = posy - HSCREEN / 2 + HPERSO / 2;
    int down = up + HSCREEN;
    int x = left;
    int y = up;
    int xcase = 0;
    int ycase = 0;
    SDL_Rect destination;
    destination.h = SIZECELL;
    destination.w = SIZECELL;
    while (x < right+SIZECELL)
    {
        if (x > 0)
        {
            while (y < down+SIZECELL)
            {
                if (y > 0)
                {
                    xcase = x / SIZECELL;
                    ycase = y / SIZECELL;
                    destination.x = xcase * SIZECELL -left;
                    destination.y = ycase * SIZECELL - up;
                    SDL_RenderCopy(renderer, tab_texture[map[xcase][ycase]], NULL, &destination);
                }
                y = y + SIZECELL;
            }
            y = up;
        }
        x = x + SIZECELL;
    }
}