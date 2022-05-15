#include "Interactible.hpp"

Interactible::Interactible(int x, int y, SDL_Texture ** texture):
    _x(x),_y(y),_texture(texture)
{}

Interactible::Interactible(int x, int y, SDL_Texture ** texture, int etat, int enigme):
    _x(x),_y(y),_texture(texture),_etat(etat),_enigme(enigme),_resolut(false),_Element()
{}

void Interactible::Afficher(SDL_Renderer *renderer, int posx, int posy)
{
    SDL_Rect destination;
    destination.x=_x-posx+WSCREEN/2-WPERSO/2;
    destination.y=_y-posy+HSCREEN/2-HPERSO/2;
    destination.w=SIZECELL;
    destination.h=SIZECELL;
    SDL_RenderCopy(renderer,_texture[_etat],NULL,&destination);
}

void Interactible::Deplacer(int x, int y)
{
    _x = x;
    _y = y;
}