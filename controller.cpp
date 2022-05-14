#include "controller.hpp"

Controller::Controller () 
{

}

void Controller::controller(bool userInput[], int clickX, int clickY) // 0 : droite, 1 : gauche, 2: haut, 3: bas
{
    // Mouvement
    if (userInput[0])
    {
        _personnage.Deplacer(_map,Direction::Droite)
    }
    if (userInput[1])
    {
        _personnage.Deplacer(_map,Direction::Gauche)
    }
    if (userInput[2])
    {
        _personnage.Grimper(_map,Direction::Haut)
        _personnage.Sauter(_map)
    }
    if (userInput[3])
    {
        _personnage.Grimper(_map,Direction::Bas)
    }


    // CHECK CLICK
    clickMapX= _personnage.GetX() + WPERSO/2 - WSCREEN/2 + clickX;
    clickMapY= _personnage.GetY() + HPERSO/2 - HSCREEN/2 + clickY;

    clickedCellX=clickMapX/SIZECELL;
    clickedCellY=clickMapY/SIZECELL;

    for (int c=0; c<_ncollectibles; ++c)
    {
        if (_collectibles[c].GetX()/SIZECELL==clickedCellX && _collectibles[c].GetY()/SIZECELL==clickedCellY)
        {
            _personnage.AjouterInventaire(_collectibles[c])
            _collectibles[c].setAffiche(false);
        }
        if (_collectibles[c].GetX()/SIZECELL<_personnage.getX()+(2*WSCREEN/3) && _collectibles[c].GetX()/SIZECELL>_personnage.getX()-(2*WSCREEN/3) && _collectibles[c].GetY()/SIZECELL<_personnage.getY()+(2*HSCREEN/3) && _collectibles[c].GetY()/SIZECELL>_personnage.getY()-(2*HSCREEN/3)) {
            _collectibles[c].afficher(_personnage.GetX(),_personnage.GetY())
        } 
    }

    for (int i=0; i<_interactibles; ++i)
    {
        if (_interactibles[i].GetX()/SIZECELL==clickedCellX && _interactibles[i].GetY()/SIZECELL==clickedCellY)
        {
            _interactibles[i].enigme()
        }
        if (_interactibles[i].GetX()/SIZECELL<_personnage.getX()+(2*WSCREEN/3) && _interactibles[i].GetX()/SIZECELL>_personnage.getX()-(2*WSCREEN/3) && _interactibles[i].GetY()/SIZECELL<_personnage.getY()+(2*HSCREEN/3) && _interactibles[i].GetY()/SIZECELL>_personnage.getY()-(2*HSCREEN/3)) {
            _interactibles[i].afficher(_personnage.GetX(),_personnage.GetY())
        } 
    }
}