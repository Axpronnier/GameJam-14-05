#include "Enigme.hpp"

void Enigme_carre_blanc(Interactible *objet)
{
    if (!(objet->GetResolut()))
    {
        Interactible *map[3][3];
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
            map[((e->GetX() - left) / SIZECELL) - 1][((e->GetY() - up) / SIZECELL) - 1] = e;
        }
        //actualisation du puzzle
        int x = ((objet->GetX() - left) / SIZECELL) - 1;
        int y = ((objet->GetY() - up) / SIZECELL) - 1;
        for (int k = -1; k <= 1; k++)
        {
            if (x + k >= 0 and x + k <= 2)
            {
                for (int i = -1; i <= 1; i++)
                {
                    if (y + i >= 0 and y + i <= 2)
                    {
                        if (map[x + k][y + i]->GetEtat() == 0)
                        {
                            map[x + k][y + i]->SetEtat(1);
                        }
                        else
                        {
                            map[x + k][y + i]->SetEtat(0);
                        }
                    }
                }
            }
        }
        //verification de la complétion
        bool fini = true;
        for (int k = 0; k < 3; k++)
        {
            for (int i = 0; i < 3; i++)
            {
                fini = fini and (map[k][i]->GetEtat() == 1);
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