#ifndef STRUCT_H
#define STRUCT_H

#define TAILLE_MAX_MOT 100
#define MAX_MOTS_FREQUENTS 100
#define MAX_MOT_LONGUEUR 50
#define MAX_MOTS_COMMUNS 100
#define MAX_PALINDROMES 100
#define MAX_PHRASES 1000
#define MAX_PHRASE_LENGTH 1000
#define TAILLE_INITIALE_TABLEAU 10
#define MAX_CHEMIN 1024


struct Mot {
    char mot[TAILLE_MAX_MOT];
    int frequence;
};

typedef struct {
    char phrase[MAX_PHRASE_LENGTH];
    int longueur;
} Phrase;

struct ResultatAnalyseFichier {
    int nombreLignes;
    int nombreMots;
    int nombreCaracteres;
    int nombreMotsDistincts;
    struct Mot* motsFrequents;  // Tableau des mots triés par fréquence
    int nombreMotsFrequents;
};

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

#endif
