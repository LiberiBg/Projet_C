#include <stdio.h>
#include <string.h>
#include "unity.h"  
#include "features.h"
#include "struct.h"  
#include <stdlib.h>

#define TAILLE_TABLEAU_MOTS 2

void ajouterMotOuIncrementer(char* mot, struct Mot** tableauMots, int* nombreMots, int* tailleTableau);

void setUp(void) {}
void tearDown(void) {}

// Ajouter un nouveau mot dans une liste vide et l'initialiser à 1
void test_ajouter_mot_nouveau(void) {
    int tailleTableau = TAILLE_TABLEAU_MOTS;
    int nombreMots = 0;
    struct Mot* tableauMots = malloc(tailleTableau * sizeof(struct Mot));
    char* mot = "pikachu";

    ajouterMotOuIncrementer(mot, &tableauMots, &nombreMots, &tailleTableau);

    TEST_ASSERT_EQUAL_STRING(mot, tableauMots[0].mot);
    TEST_ASSERT_EQUAL(1, tableauMots[0].frequence);
    TEST_ASSERT_EQUAL(1, nombreMots);

    free(tableauMots); 
}

// Ajouter un mot déjà existant
void test_incrementer_mot_existant(void) {
    int tailleTableau = TAILLE_TABLEAU_MOTS;
    int nombreMots = 1;
    struct Mot* tableauMots = malloc(tailleTableau * sizeof(struct Mot));

    strcpy(tableauMots[0].mot, "pikachu");
    tableauMots[0].frequence = 1;

    ajouterMotOuIncrementer("pikachu", &tableauMots, &nombreMots, &tailleTableau);

    TEST_ASSERT_EQUAL(2, tableauMots[0].frequence);
    TEST_ASSERT_EQUAL(1, nombreMots);

    free(tableauMots);
}


// Ajouter un mot plein de fois
void test_incrementer_mot_10_fois(void) {
    int tailleTableau = TAILLE_TABLEAU_MOTS;
    int nombreMots = 0;
    struct Mot* tableauMots = malloc(tailleTableau * sizeof(struct Mot));

    for (size_t i = 0; i < 10; i++){
        ajouterMotOuIncrementer("pikachu", &tableauMots, &nombreMots, &tailleTableau);
    }

    TEST_ASSERT_EQUAL(10, tableauMots[0].frequence);
    TEST_ASSERT_EQUAL(1, nombreMots);

    free(tableauMots);
}

// Test du redimensionnement
void test_redimensionnement(void) {
    int tailleTableau = TAILLE_TABLEAU_MOTS;
    int nombreMots = 0;
    struct Mot* tableauMots = malloc(tailleTableau * sizeof(struct Mot));

    ajouterMotOuIncrementer("pikachu", &tableauMots, &nombreMots, &tailleTableau);
    ajouterMotOuIncrementer("carapuce", &tableauMots, &nombreMots, &tailleTableau);
    ajouterMotOuIncrementer("salamèche", &tableauMots, &nombreMots, &tailleTableau);

    TEST_ASSERT_EQUAL_STRING("pikachu", tableauMots[0].mot);
    TEST_ASSERT_EQUAL_STRING("carapuce", tableauMots[1].mot);
    TEST_ASSERT_EQUAL_STRING("salamèche", tableauMots[2].mot);

    TEST_ASSERT_EQUAL(3, nombreMots);
    TEST_ASSERT_GREATER_OR_EQUAL(3, tailleTableau);
    free(tableauMots);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_ajouter_mot_nouveau);
    RUN_TEST(test_incrementer_mot_existant);
    RUN_TEST(test_incrementer_mot_10_fois);
    RUN_TEST(test_redimensionnement);

    return UNITY_END();
}
