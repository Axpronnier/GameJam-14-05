#ifndef INTERACTIBLE_HPP
#define INTERACTIBLE_HPP

#include "dessin.hpp"
#include <list>

class Interactible {
    int _x;
    int _y;
    SDL_Texture ** _texture;
    int _etat;
    bool _resolut;
    int _enigme;
    std::list<Interactible*> _Element;

    public:
        Interactible(int x, int y, SDL_Texture ** texture);
        Interactible(int x, int y, SDL_Texture ** texture, int etat);
        Interactible(int x, int y, SDL_Texture ** texture, int etat, int enigme);

        int GetX() const { return _x; }
        int GetY() const { return _y; }
        SDL_Texture ** GetTexture() const { return _texture; }
        int GetEtat() const { return _etat; }
        bool GetResolut() const { return _resolut; }
        int GetEnigme() const { return _enigme; }
        void SetEtat(int etat) {_etat = etat; }
        void SetResolut(bool resolut) {_resolut=resolut;}
        std::list<Interactible*> GetElement() {return _Element;}
        void AddElement(Interactible* i) {_Element.push_back(i);}

        void Afficher(SDL_Renderer* renderer,int posx, int posy);
        void Deplacer(int x, int y);
};

#endif