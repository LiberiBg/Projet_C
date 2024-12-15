#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "features.h"
#include "struct.h"
#include <ctype.h>

#define TAILLE_INITIALE_TABLEAU 10

int main() {
    struct Mot* tableauMots = malloc(TAILLE_INITIALE_TABLEAU * sizeof(struct Mot));
    int nombreMots = 0;
    struct Mot tmp[nombreMots];
    char chemin[256];
    char chemin1[256];
    char chemin2[256];
    int nombreLigne = 0;
    int nombreCaracteres = 0;

    demanderFichier(chemin, sizeof(chemin));

    FILE* fichier = ouvrirFichierLecture(chemin);
    if (fichier == NULL) {
        return 1;
    }
    
    printf("Fichier lu avec succes!\n");

    nombreLigne = compterLignes(fichier);
    printf("Nombre de lignes : %d\n", nombreLigne);

    nombreMots = compterMots(fichier);
    printf("Nombre de mots : %d\n", nombreMots);

    nombreCaracteres = compterCaracteres(fichier);
    printf("Nombre de caracteres : %d\n", nombreCaracteres);

    rewind(fichier);
    
    analyserPhrases(fichier);

    triFusion(0, nombreMots, tableauMots, tableauMots);

    printf("Entrez le chemin du premier fichier : ");
    if (fgets(chemin1, sizeof(chemin1), stdin) == NULL) {
        fprintf(stderr, "Erreur de lecture pour le premier fichier\n");
        free(tableauMots);
        return 1;
    }
    chemin1[strcspn(chemin1, "\n")] = 0; // Supprime le saut de ligne

    printf("Entrez le chemin du deuxieme fichier : ");
    if (fgets(chemin2, sizeof(chemin2), stdin) == NULL) {
        fprintf(stderr, "Erreur de lecture pour le deuxieme fichier\n");
        free(tableauMots);
        return 1;
    }
    chemin2[strcspn(chemin2, "\n")] = 0; // Supprime le saut de ligne

    struct ResultatAnalyseComparative resultat = analyseComparative(chemin1, chemin2);

    printf("Mots les plus fréquents dans le fichier 1 :\n");
    for (int i = 0; i < resultat.fichier1.nombreMotsFrequents; i++) {
        printf("%s : %d\n", resultat.fichier1.motsFrequents[i].mot, resultat.fichier1.motsFrequents[i].frequence);
    }

    printf("\nMots les plus fréquents dans le fichier 2 :\n");
    for (int i = 0; i < resultat.fichier2.nombreMotsFrequents; i++) {
        printf("%s : %d\n", resultat.fichier2.motsFrequents[i].mot, resultat.fichier2.motsFrequents[i].frequence);
    }

    printf("\nMots communs avec des fréquences différentes :\n");
    for (int i = 0; i < resultat.nombreMotsCommuns; i++) {
        printf("Mot : %s\n", resultat.motsCommuns[i].mot);
        //printf("    Fréquence dans %s : %d\n", fichier1, resultat.motsCommuns[i].frequenceFichier1);
        //printf("    Fréquence dans %s : %d\n", fichier2, resultat.motsCommuns[i].frequenceFichier2);
    }

    printf("\nDetection des palindromes :\n");
    rewind(fichier);
    char mot[256];
    while (fscanf(fichier, "%255s", mot) == 1) {
        if (estPalindrome(mot) && strlen(mot) > 1) {
            printf("%s\n", mot);
        }
    } 
    return 0;
}