#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include <stdio.h>
#include "struct.h"

#define MAX_MOTS_FREQUENTS 5
#define MAX_MOTS_COMMUNS 100
#define MAX_MOT_LONGUEUR 50
#define MAX_PALINDROMES 50

void ajouterMotOuIncrementer(char* mot, struct Mot** tableauMots, int* tailleTableau);

FILE* ouvrirFichierLecture(const char* chemin);

void demanderFichier(char* chemin, int taille);

void triFusion(int depart, int nombreMots, struct Mot tab[], struct Mot tmp[]);

int compterLignes(FILE* fichier);

int compterMots(FILE* fichier);

int compterCaracteres(FILE* fichier);

void analyserPhrases(FILE* fichier);

struct ResultatAnalyseComparative {
    struct {
        struct Mot motsFrequents[MAX_MOTS_FREQUENTS];
        int nombreMotsFrequents;
    } fichier1, fichier2;
    struct {
        char mot[MAX_MOT_LONGUEUR];
        int frequenceFichier1;
        int frequenceFichier2;
    } motsCommuns[MAX_MOTS_COMMUNS];
    int nombreMotsCommuns;
    struct {
        char mot[MAX_MOT_LONGUEUR];
        int frequenceFichier1;
        int frequenceFichier2;
    } palindromesCommuns[MAX_PALINDROMES];
    int nombrePalindromesCommuns;
};

struct ResultatAnalyseComparative analyseComparative(const char *fichier1, const char *fichier2);

int estPalindrome(const char* mot);

void mettreAJourFrequence(FILE* fichier, struct Mot** tableauMots, int* nombreMots, int* tailleTableau);
void sauvegarderResultats(const char* chemin, int nombreLignes, int nombreMots, int nombreCaracteres, struct Mot* tableauMots, int tailleTableau);


void afficherMotsEtFrequences(struct Mot* tableauMots, int nombreMots);
#endif