#include "Interactible.hpp"

void Interactible::afficher(SDL_Renderer *renderer, int posx, int posy)
{
    SDL_Rect destination;
    SDL_QueryTexture(_texture, NULL, NULL, &destination.w, &destination.h);
    destination.x = posx - _x + WSCREEN / 2 - WPERSO / 2;
    destination.y = posy - _y + HSCREEN / 2 - HPERSO / 2;
    SDL_RenderCopy(renderer, _texture, NULL, &destination);
}