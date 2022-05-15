#ifndef CONTROLLERHPPJAM
#define CONTROLLERHPPJAM

#include "dessin.hpp"
#include "Perso.hpp"
#include "Collectible.hpp"
#include "Interactible.hpp"
#include <iostream>
#include <fstream>

class Personnage {};

class Controller {
public:
    Controller (SDL_Renderer*);
    void controller(bool *, int, int, SDL_Renderer*);
    int ** _map;
    Perso _personnage;
    int _mapLines;
    int _mapCol;
    Collectible * _collectibles;
    int _ncollectibles;
    Interactible * _interactibles;
    int _ninteractibles;
};


#endif