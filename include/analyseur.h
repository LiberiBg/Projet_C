#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include <stdio.h>
#include "struct.h"

void ajouterMotOuIncrementer(char* mot, struct Mot** tableauMots, int* nombreMots, int* tailleTableau);

FILE* ouvrirFichierLecture(const char* chemin);

void demanderFichier(char* chemin, int taille);

void triFusion(int depart, int nombreMots, struct Mot tab[], struct Mot tmp[]);

int compterLignes(FILE* fichier);

int compterMots(FILE* fichier);

int compterCaracteres(FILE* fichier);

void analyserPhrases(FILE* fichier);

void analyseComparative(const char *fichier1, const char *fichier2);

void mettreAJourFrequence(FILE* fichier, struct Mot** tableauMots, int* nombreMots, int* tailleTableau);
void sauvegarderResultats(const char* chemin, int nombreLignes, int nombreMots, int nombreCaracteres, struct Mot* tableauMots, int tailleTableau);

void afficherTableauMots(struct Mot* tableau, int taille);

#endif