#ifndef INTERACTIBLE_HPP
#define INTERACTIBLE_HPP

class Interactible {
    int _x;
    int _y;
    SDL_Texture * _texture;
    int _etat;
    int _enigme;

    public:
        Interactible(int x, int y, SDL_Texture * texture);
        Interactible(int x, int y, SDL_Texture * texture, int etat);
        Interactible(int x, int y, SDL_Texture * texture, int etat, int enigme);

        int GetX() const { return _x; }
        int GetY() const { return _y; }
        SDL_Texture * GetTexture() const { return _texture; }
        int GetEtat() const { return _etat; }
        int GetEnigme() const { return _enigme; }
        void SetEtat(int etat) {_etat = etat; }

        void Deplacer(int x, int y);
};

#endif