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