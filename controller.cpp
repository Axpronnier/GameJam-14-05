#include "controller.hpp"

Controller::Controller () 
{

}

void Controller::controller(bool userInput[], int clickX, int clickY) // 0 : droite, 1 : gauche, 2: haut, 3: bas
{
    //deplacement


    clickMapX= _personnage.GetX() + WPERSO*SIZECELL/2 - WSCREEN/2 + clickX;
    clickMapY= _personnage.GetY() + HPERSO*SIZECELL/2 - HSCREEN/2 + clickY;

    clickedCellX=clickMapX/SIZECELL;
    clickedCellY=clickMapY/SIZECELL;

    for (int c=0; c<_ncollectibles; ++c)
    {
        if (_collectibles[c].GetX()==clickedCellX && _collectibles[c].GetY()==clickedCellY)
        {
            
        }
    }
}