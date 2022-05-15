#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP

#include "dessin.hpp"

class Collectible {
    int _x;
    int _y;
    SDL_Texture * _texture;
    bool _afficher;

    public:
        Collectible(int x, int y, SDL_Texture * texture);
        Collectible(int x, int y, SDL_Texture * texture, bool afficher);

        int GetX() const { return _x; }
        int GetY() const { return _y; }
        SDL_Texture * GetTexture() const { return _texture; }
        bool GetAfficher() const { return _afficher; }
        void SetAfficher(bool afficher) {_afficher = afficher; }

        void Afficher(SDL_Renderer* renderer,int posx, int posy);
        void Deplacer(int x, int y);
};

#endif