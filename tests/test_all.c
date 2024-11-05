#include <stdio.h>
#include "unity.h"
#include "features.h"
#include "struct.h"

// test_ajouterMotOuIncrementer.c
void test_incrementer_mot_existant(void);
void test_ajouter_mot_nouveau(void);
void test_incrementer_mot_10_fois(void);
void test_redimensionnement(void);

// test_triFusion.c
void test_triFusion_mots_differents(void);
void test_triFusion_mots_deja_tries(void);
void test_triFusion_un_seul_mot(void);

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();

    // test_ajouterMotOuIncrementer.c
    RUN_TEST(test_ajouter_mot_nouveau);
    RUN_TEST(test_incrementer_mot_existant);
    RUN_TEST(test_incrementer_mot_10_fois);
    RUN_TEST(test_redimensionnement);

    // test_triFusion.c
    RUN_TEST(test_triFusion_mots_differents);
    RUN_TEST(test_triFusion_mots_deja_tries);
    RUN_TEST(test_triFusion_un_seul_mot);
    

    return UNITY_END();
}