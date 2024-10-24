#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void ajouterMotOuIncrementer(char* mot, struct Mot** tableauMots, int* nombreMots, int* tailleTableau) {
    // Parcourt les mots existants dans le tableau
    for (int i = 0; i < *nombreMots; i++) {
        if (strcmp((*tableauMots)[i].mot, mot) == 0) {
            // Si le mot existe, on incrémente sa fréquence
            (*tableauMots)[i].frequence++;
            return;
        }
    }

    // Si le tableau est plein, on double sa taille
    if (*nombreMots >= *tailleTableau) {
        *tailleTableau *= 2;  // Double la taille du tableau

        // realloc retourne un void*, on le caste en struct Mot*
        struct Mot* temp = realloc(*tableauMots, (*tailleTableau) * sizeof(struct Mot));
        if (temp == NULL) {
            perror("Erreur lors du redimensionnement du tableau de mots.");
            exit(EXIT_FAILURE);
        }
        *tableauMots = temp;  // Mise à jour du pointeur tableauMots
    }

    // Si le mot n'existe pas, on l'ajoute au tableau
    strcpy((*tableauMots)[*nombreMots].mot, mot);
    (*tableauMots)[*nombreMots].frequence = 1;
    (*nombreMots)++;
}

FILE* ouvrirFichierLecture(const char* chemin) {
    printf("Tentative d'ouverture du fichier : %s\n", chemin);
    FILE* fichier = fopen(chemin, "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", chemin);
        perror("Raison");
        exit(1);
    }
    return fichier;
}

void demanderFichier(char* chemin, int taille) {
    printf("Entrez le chemin du fichier : ");
    if (fgets(chemin, taille, stdin) == NULL) {
        printf("Erreur de lecture du chemin\n");
        exit(1);
    }
    chemin[strcspn(chemin, "\n")] = 0; // Supprime le saut de ligne
}