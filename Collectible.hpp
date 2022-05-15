#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP

#include "dessin.hpp"

class Collectible {
    int _x;
    int _y;
    SDL_Texture * _texture;
    bool _afficher;
    int _type;

    public:
        Collectible(int x, int y, SDL_Texture * texture, int type);
        Collectible(int x, int y, SDL_Texture * texture, bool afficher, int type);

        int GetX() const { return _x; }
        int GetY() const { return _y; }
        int GetType() const {return _type; }
        SDL_Texture * GetTexture() const { return _texture; }
        bool GetAfficher() const { return _afficher; }
        void SetAfficher(bool afficher) {_afficher = afficher; }

        void Afficher(SDL_Renderer* renderer,int posx, int posy);
        void Deplacer(int x, int y);
};

#endif