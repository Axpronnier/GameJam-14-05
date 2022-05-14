#include "Perso.hpp"

Perso::Perso(int x, int y, vector<Collectible> * inventaire):
    _x(x), _y(y), _inventaire(inventaire)
{}

Perso::Perso(int x, int y):
    Perso(x, y, new vector<Collectible>())
{}

Perso::Perso():
    Perso(0, 0)
{}

void Perso::Sauter(int ** map)
{}

Direction Collision(int ** map, int x, int y)
{
    vector<Direction> collisions;

    int index_x = x / dimCase;
    int index_y = y / dimCase;
}