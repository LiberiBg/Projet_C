#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyseur.h"
#include "struct.h"
#include <stdio.h>

#define TAILLE_INITIALE_TABLEAU 10

int main(int argc, char *argv[]) {

    struct Mot* tableauMots = malloc(TAILLE_INITIALE_TABLEAU * sizeof(struct Mot));
    int nombreMots = 0;
    struct Mot* tmp = malloc(TAILLE_INITIALE_TABLEAU * sizeof(struct Mot));
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
    
    printf("Fichier lu avec succès!\n");

    nombreLigne = compterLignes(fichier);
    printf("Nombre de lignes : %d\n", nombreLigne);

    nombreMots = compterMots(fichier);
    printf("Nombre de mots : %d\n", nombreMots);

    nombreCaracteres = compterCaracteres(fichier);
    printf("Nombre de caractères : %d\n", nombreCaracteres);

    rewind(fichier);
    
    analyserPhrases(fichier);

    triFusion(0, nombreMots, tableauMots, tmp);

    printf("Entrez le chemin du premier fichier : ");
    if (fgets(chemin1, sizeof(chemin1), stdin) == NULL) {
        fprintf(stderr, "Erreur de lecture pour le premier fichier\n");
        free(tableauMots);
        return 1;
    }
    chemin1[strcspn(chemin1, "\n")] = 0; // Supprime le saut de ligne

    printf("Entrez le chemin du deuxième fichier : ");
    if (fgets(chemin2, sizeof(chemin2), stdin) == NULL) {
        fprintf(stderr, "Erreur de lecture pour le deuxième fichier\n");
        free(tableauMots);
        return 1;
    }
    chemin2[strcspn(chemin2, "\n")] = 0; // Supprime le saut de ligne

    analyseComparative(chemin1, chemin2);


    
    return 0;
}