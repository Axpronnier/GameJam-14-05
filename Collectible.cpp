#include "Collectible.hpp"

Collectible::Collectible(int x, int y, SDL_Texture * texture, int type) :
    _x{x}, _y{y}, _texture{texture}, _afficher{true}, _type{type} {};

Collectible::Collectible(int x, int y, SDL_Texture * texture, bool afficher, int type):
    _x{x}, _y{y}, _texture{texture}, _afficher{afficher}, _type{type} {};

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