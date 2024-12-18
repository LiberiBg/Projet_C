#include <stdio.h>
#include <string.h>
#include "unity.h"  
#include "analyseur.h"
#include "struct.h"  
#include <stdlib.h>

#define TAILLE_TABLEAU_MOTS 2

void ajouterMotOuIncrementer(char* mot, struct Mot** tableauMots, int* tailleTableau);

// Ajouter un nouveau mot dans une liste vide et l'initialiser à 1
void test_ajouter_mot_nouveau(void) {
    int nombreMotsDistincts = 0;
    struct Mot* tableauMots = malloc(1 * sizeof(struct Mot));
    char* mot = "pikachu";

    ajouterMotOuIncrementer(mot, &tableauMots, &nombreMotsDistincts);

    TEST_ASSERT_EQUAL_STRING(mot, tableauMots[0].mot);
    TEST_ASSERT_EQUAL(1, tableauMots[0].frequence);

    free(tableauMots); 
}

// Ajouter un mot déjà existant
void test_incrementer_mot_existant(void) {
    int nombreMotsDistincts = 1;
    struct Mot* tableauMots = malloc(1 * sizeof(struct Mot));

    strcpy(tableauMots[0].mot, "pikachu");
    tableauMots[0].frequence = 1;

    ajouterMotOuIncrementer("pikachu", &tableauMots, &nombreMotsDistincts);

    TEST_ASSERT_EQUAL(2, tableauMots[0].frequence);
    TEST_ASSERT_EQUAL(1, nombreMotsDistincts);
    free(tableauMots);
}


// Ajouter un mot plein de fois
void test_incrementer_mot_10_fois(void) {
    int nombreMotsDistincts = 0;
    struct Mot* tableauMots = malloc(10 * sizeof(struct Mot));

    for (size_t i = 0; i < 10; i++){
        ajouterMotOuIncrementer("pikachu", &tableauMots, &nombreMotsDistincts);
    }

    TEST_ASSERT_EQUAL(10, tableauMots[0].frequence);
    TEST_ASSERT_EQUAL(1, nombreMotsDistincts);

    free(tableauMots);
}
