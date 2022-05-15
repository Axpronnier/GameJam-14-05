#include "EnigmeCase.hpp"

EnigmeCase::EnigmeCase(Interactible *objet)
{
    if (!(objet->GetResolut()))
    {
        Interactible *map[4][4];
        int left = 10000;
        int up = 10000;
        for (Interactible *e : (objet->GetElement()))
        {
            if (e->GetX() < left)
            {
                left = e->GetX();
            }
            if (e->GetY() < up)
            {
                up = e->GetY();
            }
        }
        for (Interactible *e : (objet->GetElement()))
        {
            map[(e->GetX() - left) / SIZECELL][(e->GetY() - up) / SIZECELL] = e;
        }
        //actualisation du puzzle
        int x = ((objet->GetX() - left) / SIZECELL);
        int y = ((objet->GetY() - up) / SIZECELL);
        
        if(objet->GetEtat() == 0)
        {
            for (int i = 1; i <= 3; i++)
            {   
                int y = (map[objet->GetX()][i]->GetY() - 1);
                if(y = 0)
                    y = 3;
                map[objet->GetX()][i]-> SetEtat((objet->GetX()-1)*3+y-1);
            }
        }
        else if(objet->GetEtat() == 1)
        {
            for (int i = 1; i <= 3; i++)
            {   
                int x = (map[i][objet->GetY()]->GetX() - 1);
                if(x = 0)
                    x = 3;
                map[objet->GetY()][i]-> SetEtat((x-1)*3+objet->GetY()-1);
            }
        }
        //verification de la complétion
        bool fini = true;
        for (int k = 0; k < 3; k++)
        {
            for (int i = 0; i < 3; i++)
            {
                fini = fini and (map[k][i]->GetEtat() == ((map[k][i]->GetX()-1)*3+map[k][i]->GetY()+1));
            }
        }
        if (fini)
        {
            for (int k = 0; k < 3; k++)
            {
                for (int i = 0; i < 3; i++)
                {
                    map[k][i]->SetResolut(fini);
                }
            }
        }
    }
}