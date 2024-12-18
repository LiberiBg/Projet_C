#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include <stdio.h>
#include "struct.h"

void ajouterMotOuIncrementer(char* mot, struct Mot** tableauMots, int* tailleTableau);

FILE* ouvrirFichierLecture(const char* chemin);

void demanderFichier(char* chemin, int taille);

int compterLignes(FILE* fichier);

int compterMots(FILE* fichier);

int compterCaracteres(FILE* fichier);

void analyserPhrases(FILE* fichier);

struct ResultatAnalyseComparative analyseComparative(const char *fichier1, const char *fichier2);

int estPalindrome(const char* mot);

void mettreAJourFrequence(FILE* fichier, struct Mot** tableauMots, int* nombreMots, int* tailleTableau);

void sauvegarderResultats(const char* cheminSortie, const char* contenu);

void afficherMotsEtFrequences(struct Mot* tableauMots, int nombreMots);

int comparerMots(const void* a, const void* b);

struct ResultatAnalyseFichier analyserFichier(FILE* fichier);

#endif