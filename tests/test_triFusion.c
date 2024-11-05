#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "features.h"
#include "struct.h"
#include <stdlib.h>

void triFusion(int depart, int nombreMots, struct Mot tab[], struct Mot tmp[]);

// Test pour trier un tableau de mots
void test_triFusion_mots_differents(void) {
    int tailleTableau = 10;
    int nombreMots = 10;
    struct Mot tableauMots[] = {
        {"pikachu", 2},
        {"carapuce", 5},
        {"salamèche", 3},
        {"bulbizarre", 8},
        {"ronflex", 1},
        {"dracaufeu", 7},
        {"mewtwo", 6},
        {"evoli", 4},
        {"rondoudou", 9},
        {"magicarpe", 10}
    };
    struct Mot tmp[nombreMots];

    triFusion(0, nombreMots - 1, tableauMots, tmp);

    TEST_ASSERT_EQUAL_STRING("magicarpe", tableauMots[0].mot);
    TEST_ASSERT_EQUAL(10, tableauMots[0].frequence);
    TEST_ASSERT_EQUAL_STRING("rondoudou", tableauMots[1].mot);
    TEST_ASSERT_EQUAL(9, tableauMots[1].frequence);
    TEST_ASSERT_EQUAL_STRING("bulbizarre", tableauMots[2].mot);
    TEST_ASSERT_EQUAL(8, tableauMots[2].frequence);
    TEST_ASSERT_EQUAL_STRING("dracaufeu", tableauMots[3].mot);
    TEST_ASSERT_EQUAL(7, tableauMots[3].frequence);
    TEST_ASSERT_EQUAL_STRING("mewtwo", tableauMots[4].mot);
    TEST_ASSERT_EQUAL(6, tableauMots[4].frequence);
    TEST_ASSERT_EQUAL_STRING("carapuce", tableauMots[5].mot);
    TEST_ASSERT_EQUAL(5, tableauMots[5].frequence);
    TEST_ASSERT_EQUAL_STRING("evoli", tableauMots[6].mot);
    TEST_ASSERT_EQUAL(4, tableauMots[6].frequence);
    TEST_ASSERT_EQUAL_STRING("salamèche", tableauMots[7].mot);
    TEST_ASSERT_EQUAL(3, tableauMots[7].frequence);
    TEST_ASSERT_EQUAL_STRING("pikachu", tableauMots[8].mot);
    TEST_ASSERT_EQUAL(2, tableauMots[8].frequence);
    TEST_ASSERT_EQUAL_STRING("ronflex", tableauMots[9].mot);
    TEST_ASSERT_EQUAL(1, tableauMots[9].frequence);
}

// Test pour trier un tableau de mots déjà trié
void test_triFusion_mots_deja_tries(void) {
    int tailleTableau = 3;
    int nombreMots = 3;
    struct Mot tableauMots[] = {
        {"carapuce", 5},
        {"salamèche", 3},
        {"pikachu", 2}
    };
    struct Mot tmp[nombreMots];

    triFusion(0, nombreMots - 1, tableauMots, tmp);

    TEST_ASSERT_EQUAL_STRING("carapuce", tableauMots[0].mot);
    TEST_ASSERT_EQUAL(5, tableauMots[0].frequence);
    TEST_ASSERT_EQUAL_STRING("salamèche", tableauMots[1].mot);
    TEST_ASSERT_EQUAL(3, tableauMots[1].frequence);
    TEST_ASSERT_EQUAL_STRING("pikachu", tableauMots[2].mot);
    TEST_ASSERT_EQUAL(2, tableauMots[2].frequence);
}

// Test pour trier un tableau de mots avec un seul élément
void test_triFusion_un_seul_mot(void) {
    int tailleTableau = 1;
    int nombreMots = 1;
    struct Mot tableauMots[] = {
        {"pikachu", 2}
    };
    struct Mot tmp[nombreMots];

    triFusion(0, nombreMots - 1, tableauMots, tmp);

    TEST_ASSERT_EQUAL_STRING("pikachu", tableauMots[0].mot);
    TEST_ASSERT_EQUAL(2, tableauMots[0].frequence);
}

