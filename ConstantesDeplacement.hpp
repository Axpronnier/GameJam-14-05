#ifndef CONSTANTES_DEPLACEMENT_HPP
#define CONSTANTES_DEPLACEMENT_HPP

enum Direction {
    Aucune,
    Gauche,
    Droite,
    Bas,
    Haut
};

const int dimCase = 50;
const int hauteurPerso = 1.6 * dimCase;
const int largeurPerso = dimCase;
const int mapH = 600;
const int mapW = 1000;
const int mapMaxColumn = mapW / dimCase;
const int mapMaxRow = mapH / dimCase;

const int gravite = 5;
const int vitesseSaut = 30;
const int vitesseLaterale = 5;
const int vitesseGrimper = 5;

#endif