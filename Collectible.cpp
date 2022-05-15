#include "Collectible.hpp"

void Collectible::Afficher(SDL_Renderer* renderer,int posx, int posy)
{
    SDL_Rect destination;
    destination.x=_x-posx+WSCREEN/2-WPERSO/2;
    destination.y=_y-posy+HSCREEN/2-HPERSO/2;
    destination.w=SIZECELL;
    destination.h=SIZECELL;
    SDL_RenderCopy(renderer,_texture,NULL,&destination);
}

void Collectible::Deplacer(int x, int y)
{
    _x = x;
    _y = y;
}