#include "controller.hpp"

Controller::Controller(SDL_Renderer *renderer)
{
    _personnage = * new Perso(51,51);
    ifstream mapfile;
    mapfile.open("map.txt");
    mapfile >> _mapLines; //flux.get pour récup tout, ptet getline pour récup qu'une ligne
    mapfile >> _mapCol;
    _map = (int **)malloc(_mapLines * sizeof(int *));
    char txtLigne[_mapCol + 3];
    for (int i = 0; i < _mapLines; ++i)
    {
        _map[i] = (int *)malloc(_mapCol * sizeof(int));
        mapfile >> txtLigne;
        for (int j = 0; j < _mapCol; j++)
        {
            if (txtLigne[j] == '0')
            {
                _map[i][j] = 0;
            }
            if (txtLigne[j] == '1')
            {
                _map[i][j] = 1;
            }
            if (txtLigne[j] == '2')
            {
                _map[i][j] = 2;
            }
        }
    }
    mapfile.close();

    ifstream collecfile;
    int x;
    int y;
    int type;
    char texturetext[200];
    SDL_Texture *texture;

    collecfile.open("collectible.txt");
    collecfile >> _ncollectibles;
    std::cout << _ncollectibles << std::endl;
    _collectibles = (Collectible *)malloc(_ncollectibles * sizeof(Collectible));

    for (int k = 0; k < _ncollectibles; ++k)
    {
        collecfile >> type;
        collecfile >> x;
        collecfile >> y;
        collecfile >> texturetext;
        texture = chargertexture(renderer, texturetext);
        _collectibles[k] = Collectible(x, y, texture, type);
        std::cout << x << " " << y << " " << texturetext << " " << type << std::endl;
    }
    collecfile.close();

    /*ifstream interacfile;
    interacfile.open("interactible.txt");
    interacfile >> _ninteractibles;
    std::cout << _ninteractibles << std::endl;
    _interactibles = (Interactible *)malloc(_ninteractibles * sizeof(Interactible));*/
    _ninteractibles=9;
    _interactibles = (Interactible **)malloc(9*sizeof(Interactible*));
    SDL_Texture** texturebouton = (SDL_Texture**) malloc(2*sizeof(SDL_Texture*));
    texturebouton[0]=chargertexture(renderer,"sprit/Bouton1.png");
    texturebouton[1]=chargertexture(renderer,"sprit/Bouton2.png");
    for (int k=0;k<3;k++)
    {
        for (int i=0;i<3;i++)
        {
            Interactible* temp=new Interactible((k+20)*SIZECELL,(i+20)*SIZECELL,texturebouton,rand()%2,1);
            _interactibles[3*k+i]=temp;
        }
    }
    for (int k=0;k<9;k++)
    {
        for (int i=0;i<9;i++)
        {
            _interactibles[k]->AddElement(_interactibles[i]);
        }
    }
}

void Controller::controller(bool userInput[], int clickX, int clickY, SDL_Renderer *renderer, SDL_Texture *tab_texture[2]) // 0 : droite, 1 : gauche, 2: haut, 3: bas
{
    // Mouvement

    if (_personnage.TypeDeplacement(_map))
    {
        if (userInput[2])
        {
            _personnage.Grimper(_map, Direction::Haut);
        }
        if (userInput[3])
        {
            _personnage.Grimper(_map, Direction::Bas);
        }
        if (userInput[0])
        {
            _personnage.Grimper(_map, Direction::Droite);
        }
        if (userInput[1])
        {
            _personnage.Grimper(_map, Direction::Gauche);
        }
    }
    else
    {
        if (userInput[0])
        {
            _personnage.Deplacer(_map, Direction::Droite);
        }
        if (userInput[1])
        {
            _personnage.Deplacer(_map, Direction::Gauche);
        }
        if (userInput[2])
        {
            _personnage.Sauter(_map);
        }
        if (!userInput[0] || !userInput[1])
        {
            _personnage.Deplacer(_map, Direction::Aucune);
        }
    }

    afficher_map(renderer, _map, _personnage.GetX(), _personnage.GetY(), tab_texture);

    // CHECK CLICK

    int clickMapX = _personnage.GetX() + WPERSO / 2 - WSCREEN / 2 + clickX;
    int clickMapY = _personnage.GetY() + HPERSO / 2 - HSCREEN / 2 + clickY;

    int clickedCellX = clickMapX / SIZECELL;
    int clickedCellY = clickMapY / SIZECELL;
    for (int c = 0; c < _ncollectibles; ++c)
    {
        std::cout << clickMapX << " " << _collectibles[c].GetX() << std::endl ;
        if ((clickMapX > _collectibles[c].GetX()) && (clickMapX < (_collectibles[c].GetX() + SIZECELL)) && (clickX!=-1))
        {
            _personnage.AjouterInventaire(_collectibles[c]);
            _collectibles[c].SetAfficher(false);
        }
        _collectibles[c].Afficher(renderer, _personnage.GetX(), _personnage.GetY());
        //std::cout << "forcol";
    }

    for (int i = 0; i < _ninteractibles; ++i)
    {
        if (_interactibles[i]->GetX() / SIZECELL == clickedCellX && _interactibles[i]->GetY() / SIZECELL == clickedCellY)
        {
            switch (_interactibles[i]->GetEnigme())
            {
                case 1:
                    Enigme_carre_blanc(_interactibles[i]);
                    break;
                default:
                    std::cout<< "ahahahah c'est pas un vrai truc a cliquer ohohoh" << std::endl;
            }
        }
        _interactibles[i]->Afficher(renderer,_personnage.GetX(),_personnage.GetY());
        //std::cout << "forint";
    }

    //_personnage.Afficher(renderer);
}