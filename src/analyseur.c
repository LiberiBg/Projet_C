#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#define MAX_NOM_LENGTH 1024
#define MAX_NOMS_PER_PHRASE 1000
#define TAILLE_INITIALE_TABLEAU 100
#define MAX_MOT_LONGUEUR 50
#define MAX_PHRASE_LENGTH 1000
#define MAX_PHRASES 1000

void ajouterMotOuIncrementer(char* mot, struct Mot** tableauMots, int* nombreMots, int* nombreMotsDistincts) {
    // Parcourt les mots existants dans le tableau
    for (int i = 0; i < *nombreMots; i++) {
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

void demanderFichier(char* chemin, int taille) {
    printf("Entrez le chemin du fichier : ");
    if (fgets(chemin, taille, stdin) == NULL) {
        printf("Erreur de lecture du chemin\n");
        exit(1);
    }
    chemin[strcspn(chemin, "\n")] = 0; // Supprime le saut de ligne
}

void triFusion(int i, int j, struct Mot tab[], struct Mot tmp[]) {
    if (j <= i) {
        return;
    }

    int m = (i + j) / 2;

    triFusion(i, m, tab, tmp);     // trier la moitié gauche récursivement
    triFusion(m + 1, j, tab, tmp); // trier la moitié droite récursivement
    int pg = i;     // pg pointe au début du sous-tableau de gauche
    int pd = m + 1; // pd pointe au début du sous-tableau de droite
    int c;          // compteur

    // on boucle de i à j pour remplir chaque élément du tableau final fusionné
    for (c = i; c <= j; c++) {
        if (pg == m + 1) { // le pointeur du sous-tableau de gauche a atteint la limite
            tmp[c] = tab[pd];
            pd++;
        } else if (pd == j + 1) { // le pointeur du sous-tableau de droite a atteint la limite
            tmp[c] = tab[pg];
            pg++;
        } else if (tab[pg].frequence > tab[pd].frequence) { // le pointeur du sous-tableau de gauche pointe vers un élément plus petit
            tmp[c] = tab[pg];
            pg++;
        } else {  // le pointeur du sous-tableau de droite pointe vers un élément plus petit
            tmp[c] = tab[pd];
            pd++;
        }
    }
    for (c = i; c <= j; c++) {  // copier les éléments de tmp[] à tab[]
        tab[c] = tmp[c];
    }
}

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

// Définition d'une structure pour représenter une phrase
typedef struct {
    char phrase[MAX_PHRASE_LENGTH];
    int longueur; 
} Phrase;

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

    float longueurMoyenne = calculerLongueurMoyenne(phrases, nombrePhrases);
    trouverPhrasesExtremes(phrases, nombrePhrases, &plusLongue, &plusCourte);

    // printf("Nombre de phrases analysées : %d\n", nombrePhrases);
    // printf("Longueur moyenne des phrases : %.2f\n", longueurMoyenne);
    // printf("Phrase la plus longue (%d caractères) : %s\n", plusLongue.longueur, plusLongue.phrase);
    // printf("Phrase la plus courte (%d caractères) : %s\n", plusCourte.longueur, plusCourte.phrase);
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

#define MAX_MOTS_FREQUENTS 5
#define MAX_MOTS_COMMUNS 100

struct ResultatAnalyseComparative {
    struct {
        struct Mot motsFrequents[MAX_MOTS_FREQUENTS];
        int nombreMotsFrequents;
    } fichier1, fichier2;
    struct {
        char mot[MAX_MOT_LONGUEUR];
        int frequenceFichier1;
        int frequenceFichier2;
    } motsCommuns[MAX_MOTS_COMMUNS];
    int nombreMotsCommuns;
};

struct ResultatAnalyseComparative analyseComparative(const char* fichier1, const char* fichier2) {
    struct ResultatAnalyseComparative resultat = {0};  // Initialise tous les champs à zéro

    // Ouverture des fichiers en mode lecture
    FILE *f1 = ouvrirFichierLecture(fichier1);
    FILE *f2 = ouvrirFichierLecture(fichier2);
    if (f1 == NULL || f2 == NULL) {
        return resultat;  // Retourne une structure vide en cas d'erreur
    }

    // Allocation dynamique des tableaux de mots pour chaque fichier
    struct Mot *mots1 = malloc(TAILLE_INITIALE_TABLEAU * sizeof(struct Mot));
    struct Mot *mots2 = malloc(TAILLE_INITIALE_TABLEAU * sizeof(struct Mot));
    
    if (mots1 == NULL || mots2 == NULL) {
    perror("Erreur d'allocation mémoire");
    exit(EXIT_FAILURE);
    }

    int nombreMots1 = 0, nombreMots2 = 0;
    int tailleTableau1 = TAILLE_INITIALE_TABLEAU, tailleTableau2 = TAILLE_INITIALE_TABLEAU;

    // Lecture et comptage des mots dans chaque fichier
    char mot[MAX_MOT_LONGUEUR];
    while (fscanf(f1, "%s", mot) == 1) {
        ajouterMotOuIncrementer(mot, &mots1, &nombreMots1, &tailleTableau1);
    }
    while (fscanf(f2, "%s", mot) == 1) {
        ajouterMotOuIncrementer(mot, &mots2, &nombreMots2, &tailleTableau2);
    }

    // Tri des mots par fréquence décroissante
    qsort(mots1, nombreMots1, sizeof(struct Mot), comparerMots);
    qsort(mots2, nombreMots2, sizeof(struct Mot), comparerMots);

    // Stockage des 5 mots les plus fréquents dans le résultat
    for (int i = 0; i < MAX_MOTS_FREQUENTS && i < nombreMots1; i++) {
        resultat.fichier1.motsFrequents[i] = mots1[i];
        resultat.fichier1.nombreMotsFrequents++;
    }
    for (int i = 0; i < MAX_MOTS_FREQUENTS && i < nombreMots2; i++) {
        resultat.fichier2.motsFrequents[i] = mots2[i];
        resultat.fichier2.nombreMotsFrequents++;
    }

    // Recherche des mots communs avec des fréquences différentes
    for (int i = 0; i < nombreMots1 && resultat.nombreMotsCommuns < MAX_MOTS_COMMUNS; i++) {
        struct Mot* motCommun = trouverMot(mots2, nombreMots2, mots1[i].mot);
        if (motCommun && motCommun->frequence != mots1[i].frequence) {
            strcpy(resultat.motsCommuns[resultat.nombreMotsCommuns].mot, mots1[i].mot);
            resultat.motsCommuns[resultat.nombreMotsCommuns].frequenceFichier1 = mots1[i].frequence;
            resultat.motsCommuns[resultat.nombreMotsCommuns].frequenceFichier2 = motCommun->frequence;
            resultat.nombreMotsCommuns++;
        }
    }

    // Fermeture des fichiers et libération de la mémoire
    fclose(f1);
    fclose(f2);
    free(mots1);
    free(mots2);

    return resultat;
}

int estPalindrome(const char* mot) {
    int debut = 0;
    int fin = strlen(mot) - 1;
    while (debut < fin) {
        while (debut < fin && !isalpha(mot[debut])) debut++;
        while (debut < fin && !isalpha(mot[fin])) fin--;
        if (tolower(mot[debut]) != tolower(mot[fin])) {
            return 0;
        }
        debut++;
        fin--;
    }
    return 1;
}

void sauvegarderResultats(const char* cheminSortie, int nombreLignes, int nombreMots, int nombreCaracteres, struct Mot* tableauMots, int nombreMotsDistincts) {
    FILE* fichier = fopen(cheminSortie, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return;
    }

    // Écrire les résultats dans le fichier
    fprintf(fichier, "Analyse du fichier :\n");
    fprintf(fichier, "Nombre de lignes : %d\n", nombreLignes);
    fprintf(fichier, "Nombre de mots : %d\n", nombreMots);
    fprintf(fichier, "Nombre de caractères : %d\n", nombreCaracteres);
    fprintf(fichier, "Nombre de mots distincts : %d\n", nombreMotsDistincts);
    fprintf(fichier, "\nListe des mots et leur fréquence :\n");

    // Trier les mots par fréquence avant de les afficher
    qsort(tableauMots, nombreMotsDistincts, sizeof(struct Mot), comparerMots);

    // Affichage des mots et leur fréquence
    for (int i = 0; i < nombreMotsDistincts; i++) {
        fprintf(fichier, "%s : %d\n", tableauMots[i].mot, tableauMots[i].frequence);
    }

    fclose(fichier);
    printf("Les résultats ont été sauvegardés dans le fichier : %s\n", cheminSortie);
}

void mettreAJourFrequence(FILE* fichier, struct Mot** tableauMots, int* nombreMots, int* nombreMotsDistincts) {
    char mot[100];
    int index = 0;

    rewind(fichier);

    while (fscanf(fichier, "%99s", mot) == 1) {
        // Convertir le mot en minuscules pour éviter les doublons dus à la casse
        for (int i = 0; mot[i]; i++) {
            mot[i] = tolower(mot[i]);
        }
        ajouterMotOuIncrementer(mot, tableauMots, nombreMots, nombreMotsDistincts);
    }
}
