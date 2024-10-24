#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "features.h"
#include "struct.h"

#define TAILLE_INITIALE_TABLEAU 10

int main() {
    
     char chemin[256];
    demanderFichier(chemin, sizeof(chemin));

    FILE* fichier = ouvrirFichierLecture(chemin);
    if (fichier == NULL) {
        return 1;
    }
    fclose(fichier);
    printf("Fichier lu avec succès!\n");
    return 0;
}