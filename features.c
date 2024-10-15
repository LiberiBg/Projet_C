#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

#define ALLOCATION_TABLEAU_MOT 2

void ajouterMotOuIncrementer(char* mot, struct Mot* tableauMots, int* nombreMots, int* tailleTableau) {
    
    for (int i = 0; i < *nombreMots; i++) {

        if (strcmp(tableauMots[i].mot, mot) == 0) {
            tableauMots[i].frequence++;
            return;
        }
    }

    if (*nombreMots >= *tailleTableau) {
        *tailleTableau *= ALLOCATION_TABLEAU_MOT;
        tableauMots = realloc(tableauMots, (*tailleTableau) * sizeof(struct Mot));
        if (tableauMots == NULL) {
            fprintf(stderr, "Erreur de réallocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    strcpy(tableauMots[*nombreMots].mot, mot);
    tableauMots[*nombreMots].frequence = 1;
    (*nombreMots)++;
}
