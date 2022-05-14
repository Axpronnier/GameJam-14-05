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
    Controller ();
    void controller(bool *, int, int);
private:
    Perso _personnage;
    int _mapLines;
    int _mapCol;
    int ** _map;
    Collectible * _collectibles;
    int _ncollectibles;
    Interactible * _interactibles;
    int _ninteractibles;
};


#endif