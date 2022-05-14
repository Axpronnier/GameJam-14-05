#ifndef INTERACTIBLE_HPP
#define INTERACTIBLE_HPP

#include "dessin.hpp"
#include <list>

class Interactible {
    int _x;
    int _y;
    SDL_Texture * _texture;
    int _etat;
    void (*_enigme)(Interactible&);
    std::list<Interactible*> Element;

    public:
        Interactible(int x, int y, SDL_Texture * texture);
        Interactible(int x, int y, SDL_Texture * texture, int etat);
        Interactible(int x, int y, SDL_Texture * texture, int etat, int enigme);

        int GetX() const { return _x; }
        int GetY() const { return _y; }
        SDL_Texture * GetTexture() const { return _texture; }
        int GetEtat() const { return _etat; }
        void ExecEnigme() { _enigme(*this); }
        void SetEtat(int etat) {_etat = etat; }

        void afficher(SDL_Renderer* renderer,int posx, int posy);
        void Deplacer(int x, int y);
};

#endif