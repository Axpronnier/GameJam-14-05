#include "controller.hpp"

Controller::Controller () 
{

}

void Controller::controller(bool userInput[], int clickX, int clickY) // 0 : droite, 1 : gauche, 2: haut, 3: bas
{
    //deplacement


    clickMapX= _personnage.GetX() + WPERSO/2 - WSCREEN/2 + clickX;
    clickMapY= _personnage.GetY() + HPERSO/2 - HSCREEN/2 + clickY;

    clickedCellX=clickMapX/SIZECELL;
    clickedCellY=clickMapY/SIZECELL;

    for (int c=0; c<_ncollectibles; ++c)
    {
        if (_collectibles[c].GetX()==clickedCellX && _collectibles[c].GetY()==clickedCellY)
        {
            //et mettre dans le sac et desafficher
        }
        //check affichage 
    }

    for (int i=0; i<_interactibles; ++i)
    {
        if (interactibles[i].GetX()==clickedCellX && interactibles[i].GetY()==clickedCellY)
        {
            //et utiliser enigme
        }
        //check affichage 
    }
}