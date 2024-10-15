#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "features.h"
#include "struct.h"


#define TAILLE_INITIALE_TABLEAU 10

int main() {
    //Setup - ajouterMotOuIncrementer
    int tailleTableau = TAILLE_INITIALE_TABLEAU;
    int nombreMots = 0;
    struct Mot* tableauMots = malloc(tailleTableau * sizeof(struct Mot));
    if (tableauMots == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        return EXIT_FAILURE; //Erreur fatale si l'allocation mémoire a échoué
    }

    // Exemple d'utilisation
    ajouterMotOuIncrementer("bonjour", tableauMots, &nombreMots, &tailleTableau);
    ajouterMotOuIncrementer("monde", tableauMots, &nombreMots, &tailleTableau);
    ajouterMotOuIncrementer("bonjour", tableauMots, &nombreMots, &tailleTableau);

    // Afficher les mots et leurs fréquences
    for (int i = 0; i < nombreMots; i++) {
        printf("%s: %d\n", tableauMots[i].mot, tableauMots[i].frequence);
    }

    free(tableauMots);
    return 0;
}