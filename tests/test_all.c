#include <stdio.h>
#include "unity.h"
#include "analyseur.h"
#include "struct.h"

// test_ajouterMotOuIncrementer.c
void test_incrementer_mot_existant(void);
void test_ajouter_mot_nouveau(void);
void test_incrementer_mot_10_fois(void);

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();

    // test_ajouterMotOuIncrementer.c
    RUN_TEST(test_ajouter_mot_nouveau);
    RUN_TEST(test_incrementer_mot_existant);
    RUN_TEST(test_incrementer_mot_10_fois);

    return UNITY_END();
}