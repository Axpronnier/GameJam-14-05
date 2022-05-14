#ifndef CONSTANTES_DEPLACEMENT_HPP
#define CONSTANTES_DEPLACEMENT_HPP

enum Direction {
    Aucune,
    Gauche,
    Droite,
    Bas,
    Haut
};

const int gravite = 5;
const int dimCase = 50;
const int hauteurPerso = 1.6 * dimCase;
const int largeurPerso = dimCase;

#endif