#ifndef CONTROLLERHPPJAM
#define CONTROLLERHPPJAM

#define SIZECELL 50
#define HSCREEN 600
#define WSCREEN 1000
#define HPERSO 1.6*SIZECELL
#define WPERSO 1*SIZECELL

#include "Perso.hpp"
#include "Collectible.hpp"
#include "Interactible.hpp"
#include <iostream>
#include <fstream>

class Personnage {};

class Controller {
public:
    Controller ();
    void controller(int userInput);
private:
    Perso _personnage;
    int ** _map;
    Collectible * _collectibles;
    int _ncollectibles;
    Interactible * _interactibles;
    int _ninteractibles;
};


#endif