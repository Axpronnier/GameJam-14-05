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

const int gravite = 1;
const int vitesseSaut = 15;
const int vitesseLaterale = 10;
const int vitesseGrimper = 20;

#endif