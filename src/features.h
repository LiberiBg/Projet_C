#ifndef FEATURES_H
#define FEATURES_H
#include <stdio.h>
#include "struct.h"

void ajouterMotOuIncrementer(char* mot, struct Mot** tableauMots, int* nombreMots, int* tailleTableau);

FILE* ouvrirFichierLecture(const char* chemin);

void demanderFichier(char* chemin, int taille);

void triFusion(int depart, int nombreMots, struct Mot tab[], struct Mot tmp[]);

#endif