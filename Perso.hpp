#ifndef PERSO_HPP
#define PERSO_HPP

#include <vector>
#include "ConstantesDeplacement.hpp"
#include "Collectible.hpp"

using namespace std;

class Perso {
    //position et vitesse du personnage en pixels
    int _x;
    int _y;
    int _vy;
    vector<Collectible> * _inventaire;

    public:
        Perso();
        Perso(int x, int y);
        Perso(int x, int y, vector<Collectible> * inventaire);

        int GetX() const { return _x; }
        int GetY() const { return _y; }
        vector<Collectible> * GetInventaire() const {return _inventaire; }
        
        void Sauter(int ** map);
        void Grimper(int ** map, Direction direction);
        void Deplacer(int ** map, Direction direction);
        void AjouterInventaire(Collectible &objet);
        void RetirerInventaire(int index);

    private:
        vector<Direction> Collision(int ** map);
};

#endif