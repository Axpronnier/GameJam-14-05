#include <stdexcept>
#include <list>
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
{
    //Tabeau de colision des coins : HG, HD, BD, BG
    bool collisions[4] = {false, false, false, false};

    Collision(map, _x - 1, _y - 1, collisions);

    if (collisions[2] || collisions[3])
    {
        _vSaut = vitesseSaut;
    }
}

void Perso::Grimper(int ** map, Direction direction)
{
    //Tabeau de colision des coins : HG, HD, BD, BG
    bool echelles[4] = {false, false, false, false};
    bool collisions[4] = {false, false, false, false};
    bool collisions2[4] = {false, false, false, false};
    int new_x = _x;
    int new_y = _y;

    Echelle(map, _x, _y, echelles);
    if (echelles[0] || echelles[1] || echelles[2] || echelles[3])
    {   //On est bien sur une échelle, du moins en partie
        if (direction == Direction::Gauche)
        {
            new_x = _x - vitesseGrimper;
        }
        if (direction == Direction::Droite)
        {
            new_x = _x + vitesseGrimper;
        }
        Collision(map, new_x, new_y, collisions);
        //Colision sur déplacment gauche
        if (collisions[0] || collisions[3])
        {
            _x = new_x / dimCase + dimCase;
        }
        //Colision sur déplacement droite
        if (collisions[1] || collisions[2])
        {
            _x = new_x / dimCase;
        }

        if (direction == Direction::Haut)
        {
            new_y = _y - vitesseGrimper;
        }
        if (direction == Direction::Bas)
        {
            new_y = _y + vitesseGrimper;
        }
        Collision(map, new_x, new_y, collisions2);
        //Colision sur déplacment haut
        if (collisions2[0] || collisions2[1])
        {
            _y = new_y / dimCase + dimCase;
        }
        //Colision sur déplacement bas
        if (collisions2[2] || collisions2[3])
        {
            _y = new_y / dimCase;
        }
    }
}

void Perso::Deplacer(int ** map, Direction direction)
{
    //Tabeau de colision des coins : HG, HD, BD, BG
    bool collisions[4] = {false, false, false, false};
    bool collisions2[4] = {false, false, false, false};
    int new_x = _x;
    int new_y = _y;

    switch (direction)
    {
        case Direction::Gauche:
            new_x = _x - vitesseLaterale;
            break;
        case Direction::Droite:
            new_x = _x + vitesseLaterale;
            break;
        default:
            break;
    }
    Collision(map, new_x, new_y, collisions);
    //Colision sur déplacment gauche
    if (collisions[0] || collisions[3])
    {
        _x = new_x / dimCase + dimCase;
    }
    //Colision sur déplacement droite
    if (collisions[1] || collisions[2])
    {
        _x = new_x / dimCase;
    }

    new_y = _y - _vSaut;
    _vSaut -= gravite;
    Collision(map, new_x, new_y, collisions2);
    //Colision sur déplacment haut
    if (collisions2[0] || collisions2[1])
    {
        _y = new_y / dimCase + dimCase;
        _vSaut = 0;
    }
    //Colision sur déplacement bas
    if (collisions2[2] || collisions2[3])
    {
        _y = new_y / dimCase;
        _vSaut = 0;
    }
}

void Perso::AjouterInventaire(Collectible &objet)
{
    _inventaire->push_back(objet);
}

void Perso::RetirerInventaire(int index)
{
    _inventaire->erase(_inventaire->begin() + index);
}

void Perso::Bordure(int x, int y, bool coins[4])
{
    //Test de validité des coordonées au cas où
    if (x < - dimCase || x > mapW || y < - dimCase || y < mapH)
    {
        throw std::invalid_argument("Valeur de x ou y invalide");
    }
    //Test des coins
    if (x < 0 || y < 0)
    {
        coins[0] = true;
    }
    if (x + largeurPerso > mapW || y < 0)
    {
        coins[1] = true;
    }
    if (x + largeurPerso > mapW || y + hauteurPerso > mapH)
    {
        coins[2] = true;
    }
    if (x < 0|| y + hauteurPerso > mapH)
    {
        coins[3] = true;
    }
}

void Perso::Echelle(int ** map, int x, int y, bool coins[4])
{
    Bordure(x, y, coins);

    if (!coins[0] && map[y / dimCase][x / dimCase] == 2)
    {
        coins[0] = true;
    }

    if (!coins[1] && map[y / dimCase][(x + largeurPerso) / dimCase] == 2)
    {
        coins[1] = true;
    }

    if (!coins[2] && map[(y + hauteurPerso) / dimCase][(x + largeurPerso) / dimCase] == 2)
    {
        coins[2] = true;
    }

    if (!coins[3] && map[(y + hauteurPerso) / dimCase][x / dimCase] == 2)
    {
        coins[3] = true;
    }
}

void Perso::Vide(int ** map, int x, int y, bool coins[4])
{
    Bordure(x, y, coins);

    if (!coins[0] && map[y / dimCase][x / dimCase] == 0)
    {
        coins[0] = true;
    }

    if (!coins[1] && map[y / dimCase][(x + largeurPerso) / dimCase] == 0)
    {
        coins[1] = true;
    }

    if (!coins[2] && map[(y + hauteurPerso) / dimCase][(x + largeurPerso) / dimCase] == 0)
    {
        coins[2] = true;
    }

    if (!coins[3] && map[(y + hauteurPerso) / dimCase][x / dimCase] == 0)
    {
        coins[3] = true;
    }
}

void Perso::Collision(int ** map, int x, int y, bool coins[4])
{
    bool bordures[4] = {false, false, false, false};
    bool vides[4] = {false, false, false, false};
    bool echelles[4] = {false, false, false, false};

    Bordure(x, y, bordures);
    Vide(map, x, y, vides);
    Echelle(map, x, y, echelles);
    

    for (int i = 0; i < 4; i++)
    {
        if (bordures[i] || (!vides[i] && !echelles[i]))
        {
            coins[i] = true;
        }
    }
}