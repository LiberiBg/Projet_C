#ifndef STRUCT_H
#define STRUCT_H

#define TAILLE_MAX_MOT 100

struct Mot {
    char mot[TAILLE_MAX_MOT];
    int frequence;
};

struct ResultatAnalyseFichier {
    int nombreLignes;
    int nombreMots;
    int nombreCaracteres;
    int nombreMotsDistincts;
    struct Mot* motsFrequents;  // Tableau des mots triés par fréquence
    int nombreMotsFrequents;
};

#endif
