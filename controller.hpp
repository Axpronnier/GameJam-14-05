#ifndef CONTROLLERHPPJAM
#define CONTROLLERHPPJAM

#define SIZECELL 50
#define HPERSO 1.6
#define WPERSO 1
#define HSCREEN 600
#define WSCREEN 1000

#include "Perso.hpp"
#include "Collectible.hpp"
#include "Interactible.hpp"

class Personnage {};

class Controller {
public:
    Controller ();
    void controller(int userInput);
private:
    Personnage _personnage;
    int ** _map;
    Collectible * _collectibles;
    int _ncollectibles;
    Interactible * _interactibles;
    int _ninteractibles;
};


#endif