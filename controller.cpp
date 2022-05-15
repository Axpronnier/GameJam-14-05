#include "controller.hpp"


Controller::Controller (SDL_Renderer *renderer)
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
        mapfile >> txtLigne;
        for (int j=0;j<_mapCol;j++)
        {
            if (txtLigne[j]=='0') {_map[i][j]=0;}
            if (txtLigne[j]=='1') {_map[i][j]=1;}
            if (txtLigne[j]=='2') {_map[i][j]=2;}
        }
    }
    mapfile.close();

    ifstream collecfile;
    int x;
    int y;
    int type;
    char texturetext[200];
    SDL_Texture * texture;

    collecfile.open("collectible.txt");
    collecfile >> _ncollectibles;
    std::cout << _ncollectibles << std::endl;
    _collectibles=(Collectible *) malloc(_ncollectibles*sizeof(Collectible));

    for (int k=0;k<_ncollectibles;++k)
    {
        collecfile >> type;
        collecfile >> x;
        collecfile >> y;
        collecfile >> texturetext;
        texture = chargertexture(renderer,texturetext);
        _collectibles[k]= Collectible(x,y,texture,type);
        std::cout << x << " " << y << " " << texturetext << " " << type << std::endl;
    }
    collecfile.close();

    ifstream interacfile;
    interacfile.open("interactible.txt");
    interacfile >> _ninteractibles;
    std::cout << _ninteractibles << std::endl;
    _interactibles=(Interactible *) malloc(_ninteractibles  *sizeof(Interactible));

}

void Controller::controller(bool userInput[], int clickX, int clickY, SDL_Renderer * renderer) // 0 : droite, 1 : gauche, 2: haut, 3: bas
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
            _collectibles[c].Afficher(renderer ,_personnage.GetX(),_personnage.GetY());
        } 
    }

    
    for (int i=0; i<_ninteractibles; ++i)
    {
        if (_interactibles[i].GetX()/SIZECELL==clickedCellX && _interactibles[i].GetY()/SIZECELL==clickedCellY)
        {
            //_interactibles[i].ExecEnigme();
        }
        if (_interactibles[i].GetX()/SIZECELL<_personnage.GetX()+(2*WSCREEN/3) && _interactibles[i].GetX()/SIZECELL>_personnage.GetX()-(2*WSCREEN/3) && _interactibles[i].GetY()/SIZECELL<_personnage.GetY()+(2*HSCREEN/3) && _interactibles[i].GetY()/SIZECELL>_personnage.GetY()-(2*HSCREEN/3)) {
            //_interactibles[i].afficher(renderer,_personnage.GetX(),_personnage.GetY());
        } 
    }
    

    //_perso.afficher();
}