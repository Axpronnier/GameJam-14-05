#include <stdexcept>
#include <list>
#include <string>
#include <math.h>
#include "Perso.hpp"

Perso::Perso(int x, int y, vector<Collectible> * inventaire,SDL_Texture* texture):
    _x(x), _y(y), _vSaut(0), _inventaire(inventaire), _texture(texture)
{}

Perso::Perso(int x, int y):
    Perso(x, y, new vector<Collectible>(),nullptr)
{}

Perso::Perso():
    Perso(0, 0)
{}

void Perso::Sauter(int ** map)
{
    //Tabeau de colision des coins : HG, HD, BD, BG
    int cases[6];

    //cout << endl << endl << endl << endl << endl << "Pour le saut on a :" << endl;
    GetCases(map, _x + 1, _y + 1, cases);
    //cout << endl << endl << endl << endl << endl;

    if (CollisionCase(cases[3]) || CollisionCase(cases[4]))
    {
        _vSaut = vitesseSaut;
        //cout << endl << endl << endl << "!!! SAUT !!!" <<endl << endl << endl;
    }
}

int Perso::TypeDeplacement(int ** map)
{
    int cases[6];
    int res = 0;

    GetCases(map, _x, _y, cases);

    for (int i = 0; i < 6; i++)
    {
        if (cases[i] == 2)
        {   //On est sur une échelle
            res = 1;
        }
    }

    return res;
}

void Perso::Grimper(int ** map, Direction direction)
{
    int casesX[6];
    int casesY[6];
    int new_x = _x;
    int new_y = _y;
    int new_dx;
    int new_dy;

    //Deplacmeent horizontal
    if (direction == Direction::Gauche)
    {
        new_x -= vitesseGrimper;
    }
    else if (direction == Direction::Droite)
    {
        new_x += vitesseGrimper;
    }
    GetCases(map, new_x, new_y, casesX);
    //cout << "x = " << new_x << " et x + largeur = " << new_x + largeurPerso << endl;
    //cout << "y = " << new_y << " et y + taille = " << new_y + hauteurPerso << endl;
    if (direction == Direction::Gauche && (CollisionCase(casesX[0]) || CollisionCase(casesX[4]) || CollisionCase(casesX[5])))
    {   //Collision gauche
        new_dx = dimCase - new_x % dimCase;
        new_x += new_dx;
        //cout << "Collision gauche" << endl;
    }
    else if (direction == Direction::Droite && (CollisionCase(casesX[1]) || CollisionCase(casesX[2]) || CollisionCase(casesX[3])))
    {   //Collision droite le cas super chiant
        new_dx = (new_x + largeurPerso) % dimCase;
        new_x -= new_dx;
        //cout << "Collision droite" << endl;
    }

    //deplacement vertical
    if (direction == Direction::Haut)
    {
        new_y -= vitesseGrimper;
    }
    else if (direction == Direction::Bas)
    {
        new_y += vitesseGrimper;
    }
    GetCases(map, new_x, new_y, casesY);
    //cout << "x = " << new_x << " et x + taille = " << new_x + largeurPerso << endl;
    //cout << "y = " << new_y << " et y + taille = " << new_y + hauteurPerso << endl;
    if (CollisionCase(casesY[0]) || CollisionCase(casesY[1]))
    {   //Collision au plafond
        new_dy = dimCase - new_y % dimCase;
        new_y += new_dy;
        _vSaut = 0;
        //cout << "Collision plafond" << endl;
    }
    else if (CollisionCase(casesY[3]) || CollisionCase(casesY[4]))
    {   //Collision au sol, le cas super chiant
        new_dy = (new_y + hauteurPerso) % dimCase;
        new_y -= new_dy;
        _vSaut = 0;
        //cout << "Collision sol" << endl;
    }

    _x = new_x;
    _y = new_y;
}

void Perso::Deplacer(int ** map, Direction direction)
{
    int casesX[6];
    int casesY[6];
    int new_x = _x;
    int new_y = _y;
    int new_dx;
    int new_dy;

    //Deplacmeent horizontal
    if (direction == Direction::Gauche)
    {
        new_x -= vitesseLaterale;
    }
    else if (direction == Direction::Droite)
    {
        new_x += vitesseLaterale;
    }
    GetCases(map, new_x, new_y, casesX);
    //cout << "x = " << new_x << " et x + largeur = " << new_x + largeurPerso << endl;
    //cout << "y = " << new_y << " et y + taille = " << new_y + hauteurPerso << endl;
    if (direction == Direction::Gauche && (CollisionCase(casesX[0]) || CollisionCase(casesX[4]) || CollisionCase(casesX[5])))
    {   //Collision gauche
        new_dx = dimCase - new_x % dimCase;
        new_x += new_dx;
        //cout << "Collision gauche" << endl;
    }
    else if (direction == Direction::Droite && (CollisionCase(casesX[1]) || CollisionCase(casesX[2]) || CollisionCase(casesX[3])))
    {   //Collision droite le cas super chiant
        new_dx = (new_x + largeurPerso) % dimCase;
        new_x -= new_dx;
        //cout << "Collision droite" << endl;
    }

    //deplacement vertical
    _vSaut = max(_vSaut - gravite, - dimCase);
    //cout << "vSaut = " << _vSaut << endl;
    new_y -= _vSaut;
    GetCases(map, new_x, new_y, casesY);
    //cout << "x = " << new_x << " et x + taille = " << new_x + largeurPerso << endl;
    //cout << "y = " << new_y << " et y + taille = " << new_y + hauteurPerso << endl;
    if (CollisionCase(casesY[0]) || CollisionCase(casesY[1]))
    {   //Collision au plafond
        new_dy = dimCase - new_y % dimCase;
        new_y += new_dy;
        _vSaut = 0;
        //cout << "Collision plafond" << endl;
    }
    else if (CollisionCase(casesY[3]) || CollisionCase(casesY[4]))
    {   //Collision au sol, le cas super chiant
        new_dy = (new_y + hauteurPerso) % dimCase;
        new_y -= new_dy;
        _vSaut = 0;
        //cout << "Collision sol" << endl;
    }

    _x = new_x;
    _y = new_y;
}

void Perso::Afficher(SDL_Renderer *renderer)
{
    SDL_Rect destination;
    destination.x=WSCREEN/2-WPERSO/2;
    destination.y=HSCREEN/2-HPERSO/2;
    destination.w=WPERSO;
    destination.h=HPERSO;
    SDL_RenderCopy(renderer,_texture,NULL,&destination);
}

void Perso::AjouterInventaire(Collectible &objet)
{
    _inventaire->push_back(objet);
}

void Perso::RetirerInventaire(int index)
{
    _inventaire->erase(_inventaire->begin() + index);
}

void Perso::GetCases(int ** map, int x, int y, int cases[6])
{
    int case_x = x / dimCase;
    int case_y = y / dimCase;

    for (int i = 0; i < 6; i++)
    {
        cases[i] = -1;
    }

    if (y % dimCase + hauteurPerso <= 2 * dimCase)
    {   
        if (x % dimCase + largeurPerso <= dimCase)
        {   //Perso sur 2 cases (0, 4)
            cases[0] = map[case_y][case_x];
            cases[4] = map[case_y + 1][case_x];
        }
        else
        {   //Perso sur 4 cases (0, 1, 3, 4)
            cases[0] = map[case_y][case_x];
            cases[1] = map[case_y][case_x + 1];
            cases[3] = map[case_y + 1][case_x + 1];
            cases[4] = map[case_y + 1][case_x];
        }
    }
    else
    {
        if (x % dimCase + largeurPerso <= dimCase)
        {   //Perso sur 3 cases (0, 4, 5)
            cases[0] = map[case_y][case_x];
            cases[4] = map[case_y + 2][case_x];
            cases[5] = map[case_y + 1][case_x];
        }
        else
        {   //Perso sur 6 cases (0, 1, 2, 3, 4, 5)
            cases[0] = map[case_y][case_x];
            cases[1] = map[case_y][case_x + 1];
            cases[2] = map[case_y + 1][case_x + 1];
            cases[3] = map[case_y + 2][case_x + 1];
            cases[4] = map[case_y + 2][case_x];
            cases[5] = map[case_y + 1][case_x];
        } 
    }
    //cout << "cases = " << cases[0] << "," << cases[1] << "," << cases[2] << "," << cases[3] << "," << cases[4] << "," << cases[5] << endl;
}

bool Perso::CollisionCase(int valCase)
{
    return valCase == 1;
}