#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <locale.h> 

// Fonction pour ajouter un mot dans un tableau de mots ou incrémenter sa fréquence et mettre à jour le nombre de mots distincts
void ajouterMotOuIncrementer(char* mot, struct Mot** tableauMots, int* nombreMotsDistincts) {
    // Parcourt les mots existants dans le tableau
    for (int i = 0; i < *nombreMotsDistincts; i++) {
        if (strcmp((*tableauMots)[i].mot, mot) == 0) {
            // Si le mot existe, on incrémente sa fréquence
            (*tableauMots)[i].frequence++;
            return;
        }
    }

    // Si le mot n'existe pas, on l'ajoute au tableau
    strcpy((*tableauMots)[*nombreMotsDistincts].mot, mot);
    (*tableauMots)[*nombreMotsDistincts].frequence = 1;
    (*nombreMotsDistincts)++;
}

// Fonction pour ouvrir un fichier en mode lecture
FILE* ouvrirFichierLecture(const char* chemin) {
    printf("Tentative d'ouverture du fichier : %s\n", chemin);
    
    // Vérifier si le fichier existe
    struct stat buffer;
    if (stat(chemin, &buffer) != 0) {
        printf("Erreur : Le fichier %s n'existe pas.\n", chemin);
        return NULL;
    }

    // Vérifier si c'est un fichier régulier
    if (!S_ISREG(buffer.st_mode)) {
        printf("Erreur : %s n'est pas un fichier régulier.\n", chemin);
        return NULL;
    }

    FILE* fichier = fopen(chemin, "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", chemin);
        printf("Code d'erreur : %d\n", errno);
        printf("Description de l'erreur : %s\n", strerror(errno));
        return NULL;
    }

    printf("Fichier ouvert avec succès.\n");
    return fichier;
}

// Fonction pour compter le nombre de ligne dans le fichier
int compterLignes(FILE* fichier) {
    int nombreLignes = 0;
    int caractere = 0;

    // Vérifier s il ya  un fichier
    if (fichier == NULL) {
        return -1;  // erreur
    }

    // Lit le fichier caractère par caractère
    for(int caractere; (caractere = fgetc(fichier)) != EOF; ) {
    if(caractere == '\n') {
        nombreLignes++;
    }
}

    // Vérifier si la dernière ligne se termine par un saut de ligne
    if (caractere != '\n' && nombreLignes > 0) {
        nombreLignes++;
    }

    // Retour au debut du fichier
    rewind(fichier);

    return nombreLignes;
}

// Fonction pour compter le nombre de mots dans le fichier
int compterMots(FILE* fichier) {

    int nombreMots = 0;
    int caractere = 0;
    int dansMot = 0;

    // Vérifier s'il y a un fichier
    if (fichier == NULL) {
        return -1;  // erreur
    }

    for(; (caractere = fgetc(fichier)) != EOF; ) {
        if (caractere == ' ' || caractere == '\n' || caractere == '\t') {
            if (dansMot) {
                nombreMots++;
                dansMot = 0;
            }
        } else {
            dansMot = 1;
        }
    }

    // Compter le dernier mot si nécessaire
    if (dansMot) {
        nombreMots++;
    }
    rewind(fichier);
    return nombreMots; // retourner le nombre total de mots
}

// Fonction pour compter le nombre de caractères dans le fichier
int compterCaracteres(FILE* fichier){
    int nombreCaractere = 0;
    int caractere = 0;

    // Vérifier s ya  un fichier
    if (fichier == NULL) {
        return -1;  // erreur
    }

    // Parcour le fichier et compte les caracteres
    while ((caractere = fgetc(fichier)) != EOF) {
        if (caractere != ' ' && caractere != '\t' && caractere != '\n') {
            nombreCaractere++;
        }
    }
    rewind(fichier);

    return nombreCaractere;  
}

// Fonction pour détecter les fins de phrase
int estFinDePhrase(char c) {
    return (c == '.' || c == '!' || c == '?');
}

// Fonction pour calculer la longueur moyenne des phrases
float calculerLongueurMoyenne(Phrase* phrases, int nombrePhrases) {
    if (nombrePhrases == 0) return 0;  // Éviter la division par zéro
    int longueurTotale = 0;
    for (int i = 0; i < nombrePhrases; i++) {
        longueurTotale += phrases[i].longueur;
    }
    return (float)longueurTotale / nombrePhrases; 
}

// Fonction pour identifier la phrase la plus longue et la plus courte
void trouverPhrasesExtremes(Phrase* phrases, int nombrePhrases, Phrase* plusLongue, Phrase* plusCourte) {
    if (nombrePhrases == 0) return;  // Gérer le cas où il n'y a pas de phrases

    *plusLongue = phrases[0];
    *plusCourte = phrases[0];

    for (int i = 1; i < nombrePhrases; i++) {
        if (phrases[i].longueur > plusLongue->longueur) {
            *plusLongue = phrases[i];
        }
        if (phrases[i].longueur < plusCourte->longueur) {
            *plusCourte = phrases[i];
        }
    }
}

// Fonction pour analyser les phrases dans un fichier
void analyserPhrases(FILE* fichier) {

    if (fichier == NULL) {
        printf("Erreur : Fichier non valide.\n");
        return;
    }

    Phrase phrases[MAX_PHRASES];
    int nombrePhrases = 0;
    Phrase plusLongue, plusCourte;

    char c;
    int longueurPhrase = 0;
    char phrase[MAX_PHRASE_LENGTH];

    while ((c = fgetc(fichier)) != EOF && nombrePhrases < MAX_PHRASES) {
        if (estFinDePhrase(c) || longueurPhrase == MAX_PHRASE_LENGTH - 1) {
            phrase[longueurPhrase] = c;
            phrase[longueurPhrase + 1] = '\0';
            phrases[nombrePhrases].longueur = longueurPhrase + 1;
            strcpy(phrases[nombrePhrases].phrase, phrase);
            nombrePhrases++;
            longueurPhrase = 0;
        } else {
            phrase[longueurPhrase++] = c;
        }
    }

    // Traitement de la dernière phrase si elle n'est pas terminée par un point
    if (longueurPhrase > 0 && nombrePhrases < MAX_PHRASES) {
        phrase[longueurPhrase] = '\0';
        phrases[nombrePhrases].longueur = longueurPhrase;
        strcpy(phrases[nombrePhrases].phrase, phrase);
        nombrePhrases++;
    }

    if (nombrePhrases == 0) {
        printf("Aucune phrase trouvée dans le fichier.\n");
        return;
    }

    trouverPhrasesExtremes(phrases, nombrePhrases, &plusLongue, &plusCourte);

}

// Fonction pour comparer deux mots selon leur fréquence
int comparerMots(const void* a, const void* b) {
    return ((struct Mot*)b)->frequence - ((struct Mot*)a)->frequence;
}

// Fonction pour trouver un mot dans un tableau de mots
struct Mot* trouverMot(struct Mot* tableau, int taille, const char* mot) {
    for (int i = 0; i < taille; i++) {
        if (strcmp(tableau[i].mot, mot) == 0) {
            return &tableau[i];
        }
    }
    return NULL;
}

// Fonction pour calculer la fréquence des mots dans un fichier
void mettreAJourFrequence(FILE* fichier, struct Mot** tableauMots, int* nombreMotsDistincts) {
    char mot[100];
    char motFiltre[100];
    int j;

    rewind(fichier);

    while (fscanf(fichier, "%99s", mot) == 1) {
        j = 0;
        for (int i = 0; mot[i]; i++) {
            if (isalpha(mot[i]) || mot[i] == '\'' || mot[i] == '-') {
                motFiltre[j++] = tolower(mot[i]);
            }
        }
        motFiltre[j] = '\0'; // Terminer la chaîne filtrée
        if (j > 0) { // Ajouter seulement si le mot filtré n'est pas vide
            ajouterMotOuIncrementer(motFiltre, tableauMots, nombreMotsDistincts);
        }
    }
}

// Fonction qui vérifie si un mot est un palindrome
int estPalindrome(const char* mot) {
    int debut = 0;
    int fin = strlen(mot) - 1;

    while (debut < fin && !isalnum((unsigned char)mot[debut])) debut++;
    while (debut < fin && !isalnum((unsigned char)mot[fin])) fin--;

    if (debut >= fin) return 0;

    while (debut < fin) {
        while (debut < fin && !isalnum((unsigned char)mot[debut])) debut++;
        while (debut < fin && !isalnum((unsigned char)mot[fin])) fin--;

        // Comparer les caractères correspondants
        if (tolower((unsigned char)mot[debut]) != tolower((unsigned char)mot[fin])) {
            return 0; // Ce n'est pas un palindrome
        }

        debut++;
        fin--;
    }

    return 1; // C'est un palindrome
}


// Fonction pour analyser deux fichiers
struct ResultatAnalyseComparative analyseComparative(const char* fichier1, const char* fichier2) {
    struct ResultatAnalyseComparative resultat = {0};  // Initialise tous les champs à zéro

    // Ouverture des fichiers en mode lecture
    FILE *f1 = ouvrirFichierLecture(fichier1);
    FILE *f2 = ouvrirFichierLecture(fichier2);
    if (f1 == NULL || f2 == NULL) {
        return resultat;  // Retourne une structure vide en cas d'erreur
    }

    // Allocation dynamique des tableaux de mots pour chaque fichier
    struct Mot *mots1 = malloc(compterMots(f1) * sizeof(struct Mot));
    struct Mot *mots2 = malloc(compterMots(f2) * sizeof(struct Mot));
    
    if (mots1 == NULL || mots2 == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    int nombreMotsDistincts1 = 0, nombreMotsDistincts2 = 0;

    // Lecture et comptage des mots dans chaque fichier
    mettreAJourFrequence(f1, &mots1, &nombreMotsDistincts1);
    mettreAJourFrequence(f2, &mots2, &nombreMotsDistincts2);

    // Tri des mots par fréquence décroissante
    qsort(mots1, nombreMotsDistincts1, sizeof(struct Mot), comparerMots);
    qsort(mots2, nombreMotsDistincts2, sizeof(struct Mot), comparerMots);

    //Stockage des 5 mots les plus fréquents dans le résultat
    for (int i = 0; i < MAX_MOTS_FREQUENTS && i < nombreMotsDistincts1; i++) {
        resultat.fichier1.motsFrequents[i] = mots1[i];
        resultat.fichier1.nombreMotsFrequents++;
    }
    for (int i = 0; i < MAX_MOTS_FREQUENTS && i < nombreMotsDistincts2; i++) {
        resultat.fichier2.motsFrequents[i] = mots2[i];
        resultat.fichier2.nombreMotsFrequents++;
    }

    // Recherche des mots communs avec des fréquences différentes
    for (int i = 0; i < nombreMotsDistincts1 && resultat.nombreMotsCommuns < MAX_MOTS_COMMUNS; i++) {
        struct Mot* motCommun = trouverMot(mots2, nombreMotsDistincts2, mots1[i].mot);
        if (motCommun && motCommun->frequence != mots1[i].frequence) {
            strcpy(resultat.motsCommuns[resultat.nombreMotsCommuns].mot, mots1[i].mot);
            resultat.motsCommuns[resultat.nombreMotsCommuns].frequenceFichier1 = mots1[i].frequence;
            resultat.motsCommuns[resultat.nombreMotsCommuns].frequenceFichier2 = motCommun->frequence;
            resultat.nombreMotsCommuns++;
        }
    }

    // Comptage des palindromes en commun
    resultat.nombrePalindromesCommuns = 0;
    for (int i = 0; i < nombreMotsDistincts1 && resultat.nombrePalindromesCommuns < MAX_PALINDROMES; i++) {
        if (estPalindrome(mots1[i].mot)) {
            // Chercher si le palindrome existe dans le second fichier
            struct Mot* motCommun = trouverMot(mots2, nombreMotsDistincts2, mots1[i].mot);
            if (motCommun && estPalindrome(motCommun->mot)) {
                strcpy(resultat.palindromesCommuns[resultat.nombrePalindromesCommuns].mot, mots1[i].mot);
                resultat.palindromesCommuns[resultat.nombrePalindromesCommuns].frequenceFichier1 = mots1[i].frequence;
                resultat.palindromesCommuns[resultat.nombrePalindromesCommuns].frequenceFichier2 = motCommun->frequence;
                resultat.nombrePalindromesCommuns++;
            }
        }
    }

    // Fermeture des fichiers et libération de la mémoire
    fclose(f1);
    fclose(f2);
    free(mots1);
    free(mots2);

    return resultat;
}

// Fonctioner pour sauvegarder un string dans un fichier
void sauvegarderResultats(const char* cheminSortie, const char* contenu) {
    if (cheminSortie == NULL || contenu == NULL) {
        fprintf(stderr, "Erreur : paramètres invalides pour la sauvegarde\n");
        return;
    }

    FILE* fichier = fopen(cheminSortie, "w");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s : %s\n", 
                cheminSortie, strerror(errno));
        return;
    }

    // Écriture du contenu
    if (fputs(contenu, fichier) == EOF) {
        fprintf(stderr, "Erreur lors de l'écriture dans le fichier %s\n", cheminSortie);
        fclose(fichier);
        return;
    }

    fclose(fichier);
    printf("Résultats sauvegardés avec succès dans : %s\n", cheminSortie);
}

// Fonction pour analyser un seul fichier
struct ResultatAnalyseFichier analyserFichier(FILE* fichier) {
    struct ResultatAnalyseFichier resultat = {0};

    // Analyse basique du fichier
    resultat.nombreLignes = compterLignes(fichier);
    resultat.nombreMots = compterMots(fichier);
    resultat.nombreCaracteres = compterCaracteres(fichier);
    
    rewind(fichier);
    
    // Allocation et analyse des mots
    struct Mot* tableauMots = malloc(resultat.nombreMots * sizeof(struct Mot));
    if (tableauMots == NULL) {
        fclose(fichier);
        return resultat;
    }

    // Mise à jour des fréquences
    mettreAJourFrequence(fichier, &tableauMots, &resultat.nombreMotsDistincts);

    // Tri des mots
    qsort(tableauMots, resultat.nombreMotsDistincts, sizeof(struct Mot), comparerMots);

    resultat.motsFrequents = tableauMots;
    resultat.nombreMotsFrequents = resultat.nombreMotsDistincts;

    // Fonction Palindrome
    int nombrePalindromes = 0;
    for (int i = 0; i < resultat.nombreMotsDistincts; i++) {
        if (estPalindrome(tableauMots[i].mot)) {
            nombrePalindromes++;
        }
    }
    resultat.nombrePalindromes = nombrePalindromes;

    fclose(fichier);
    return resultat;
}
