#include "controller.hpp"


Controller::Controller ()
{
    _personnage = * new Perso();
    ifstream mapfile;
    mapfile.open("map.txt");
    mapfile >> _mapLines; //flux.get pour récup tout, ptet getline pour récup qu'une ligne
    mapfile >> _mapCol; 
    _map = (int **) malloc(_mapLines*sizeof(int *));
    char txtLigne[_mapCol+3];
    for (int i=0;i<_mapLines;++i)
    {
        _map[i]=(int *) malloc(_mapCol*sizeof(int));
        for (int j=0;j<_mapCol;j++)
        {
            mapfile >> txtLigne;
            if (txtLigne[j]=='1') {_map[i][j]=1;}
            else {_map[i][j]=0;}
        }
    }
}

void Controller::controller(bool userInput[], int clickX, int clickY) // 0 : droite, 1 : gauche, 2: haut, 3: bas
{
    // Mouvement
    if (userInput[0])
    {
        _personnage.Deplacer(_map,Direction::Droite);
    }
    if (userInput[1])
    {
        _personnage.Deplacer(_map,Direction::Gauche);
    }
    if (userInput[2])
    {
        _personnage.Grimper(_map,Direction::Haut);
        _personnage.Sauter(_map);
    }
    if (userInput[3])
    {
        _personnage.Grimper(_map,Direction::Bas);
    }

    //afficher_map(_map,_personnage);

    // CHECK CLICK
    int clickMapX= _personnage.GetX() + WPERSO/2 - WSCREEN/2 + clickX;
    int clickMapY= _personnage.GetY() + HPERSO/2 - HSCREEN/2 + clickY;

    int clickedCellX=clickMapX/SIZECELL;
    int clickedCellY=clickMapY/SIZECELL;

    for (int c=0; c<_ncollectibles; ++c)
    {
        if (_collectibles[c].GetX()/SIZECELL==clickedCellX && _collectibles[c].GetY()/SIZECELL==clickedCellY)
        {
            _personnage.AjouterInventaire(_collectibles[c]);
            _collectibles[c].SetAfficher(false);
        }
        if (_collectibles[c].GetX()/SIZECELL<_personnage.GetX()+(2*WSCREEN/3) && _collectibles[c].GetX()/SIZECELL>_personnage.GetX()-(2*WSCREEN/3) && _collectibles[c].GetY()/SIZECELL<_personnage.GetY()+(2*HSCREEN/3) && _collectibles[c].GetY()/SIZECELL>_personnage.GetY()-(2*HSCREEN/3)) {
            //_collectibles[c].afficher(_personnage.GetX(),_personnage.GetY());
        } 
    }

    for (int i=0; i<_ninteractibles; ++i)
    {
        if (_interactibles[i].GetX()/SIZECELL==clickedCellX && _interactibles[i].GetY()/SIZECELL==clickedCellY)
        {
            //_interactibles[i].ExecEnigme();
        }
        if (_interactibles[i].GetX()/SIZECELL<_personnage.GetX()+(2*WSCREEN/3) && _interactibles[i].GetX()/SIZECELL>_personnage.GetX()-(2*WSCREEN/3) && _interactibles[i].GetY()/SIZECELL<_personnage.GetY()+(2*HSCREEN/3) && _interactibles[i].GetY()/SIZECELL>_personnage.GetY()-(2*HSCREEN/3)) {
            //_interactibles[i].afficher(_personnage.GetX(),_personnage.GetY());
        } 
    }

    //_perso.afficher();
}