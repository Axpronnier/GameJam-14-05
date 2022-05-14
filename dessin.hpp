#ifndef DESSIN_HPP
#define DESSIN_HPP

#include <iostream>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WSCREEN 1000
#define HSCREEN 600
#define SIZECELL 50
#define WPERSO 1.6*SIZECELL
#define HPERSO 1*SIZECELL 

SDL_Texture* chargertexture(SDL_Renderer *renderer, const char* nom);
SDL_Texture *creertxt(SDL_Renderer *renderer,const char* texte, TTF_Font *font, SDL_Color couleur);
void afficher_map(SDL_Renderer *renderer,int** map,int posx,int posy,SDL_Texture** tab_texture);

#endif