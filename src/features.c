#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

#define MAX_PHRASE_LENGTH 1024


void ajouterMotOuIncrementer(char* mot, struct Mot** tableauMots, int* nombreMots, int* tailleTableau) {
    // Parcourt les mots existants dans le tableau
    for (int i = 0; i < *nombreMots; i++) {
        if (strcmp((*tableauMots)[i].mot, mot) == 0) {
            // Si le mot existe, on incrémente sa fréquence
            (*tableauMots)[i].frequence++;
            return;
        }
    }

    // Si le tableau est plein, on double sa taille
    if (*nombreMots >= *tailleTableau) {
        *tailleTableau *= 2;  // Double la taille du tableau

        // realloc retourne un void*, on le caste en struct Mot*
        struct Mot* temp = realloc(*tableauMots, (*tailleTableau) * sizeof(struct Mot));
        if (temp == NULL) {
            perror("Erreur lors du redimensionnement du tableau de mots.");
            exit(EXIT_FAILURE);
        }
        *tableauMots = temp;  // Mise à jour du pointeur tableauMots
    }

    // Si le mot n'existe pas, on l'ajoute au tableau
    strcpy((*tableauMots)[*nombreMots].mot, mot);
    (*tableauMots)[*nombreMots].frequence = 1;
    (*nombreMots)++;
}

FILE* ouvrirFichierLecture(const char* chemin) {
    printf("Tentative d'ouverture du fichier : %s\n", chemin);
    FILE* fichier = fopen(chemin, "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", chemin);
        perror("Raison");
        exit(1);
    }
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

    for(int caractere; (caractere = fgetc(fichier)) != EOF; ) {
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
    for(int caractere; (caractere = fgetc(fichier)) != EOF; ) {
        nombreCaractere++;
    }

    return nombreCaractere;  
}


// Définition d'une structure pour représenter une phrase
typedef struct {
    char phrase[MAX_PHRASE_LENGTH]; // tableau de caractères pour stocker la phrase
    int longueur; 
} Phrase;

// Fonction pour détecter les fins de phrase
// Retourne 1 si le caractère est un point, un point d'exclamation ou un point d'interrogation, 0 sinon
int estFinDePhrase(char c) {
    return (c == '.' || c == '!' || c == '?');
}

// Fonction pour calculer la longueur moyenne des phrases
// Retourne la longueur moyenne des phrases
float calculerLongueurMoyenne(Phrase* phrases, int nombrePhrases) {
    int longueurTotale = 0; // variable pour stocker la longueur totale des phrases
    for (int i = 0; i < nombrePhrases; i++) {
        longueurTotale += phrases[i].longueur; // additionne la longueur de chaque phrase
    }
    return (float)longueurTotale / nombrePhrases; 
}

// Fonction pour identifier la phrase la plus longue et la plus courte
// Prend en entrée un tableau de phrases, le nombre de phrases et des pointeurs vers les phrases les plus longues et les plus courtes
void trouverPhrasesExtremes(Phrase* phrases, int nombrePhrases, Phrase* plusLongue, Phrase* plusCourte) {
    plusLongue->longueur = 0; 
    plusCourte->longueur = MAX_PHRASE_LENGTH; 

    for (int i = 0; i < nombrePhrases; i++) {
        if (phrases[i].longueur > plusLongue->longueur) { // si la longueur de la phrase courante est supérieure à la longueur de la phrase la plus longue
            strcpy(plusLongue->phrase, phrases[i].phrase); // copie la phrase courante dans la phrase la plus longue
            plusLongue->longueur = phrases[i].longueur; // met à jour la longueur de la phrase la plus longue
        }
        if (phrases[i].longueur < plusCourte->longueur) { // si la longueur de la phrase courante est inférieure à la longueur de la phrase la plus courte
            strcpy(plusCourte->phrase, phrases[i].phrase); // copie la phrase courante dans la phrase la plus courte
            plusCourte->longueur = phrases[i].longueur; // met à jour la longueur de la phrase la plus courte
        }
    }
}

// Fonction pour analyser les phrases dans un fichier
// Prend en entrée un pointeur vers un fichier
void analyserPhrases(FILE* fichier) {
    Phrase phrases[MAX_PHRASE_LENGTH]; // tableau pour stocker les phrases
    int nombrePhrases = 0; 
    Phrase plusLongue, plusCourte; 

    char c; 
    int longueurPhrase = 0; 
    char phrase[MAX_PHRASE_LENGTH]; 

    for (c = fgetc(fichier); c != EOF; c = fgetc(fichier)) { // boucle pour lire les caractères du fichier
        if (estFinDePhrase(c)) { // si le caractère est un point, un point d'exclamation ou un point d'interrogation
            phrase[longueurPhrase] = '\0'; 
            phrases[nombrePhrases].longueur = longueurPhrase; // stocke la longueur de la phrase courante
            strcpy(phrases[nombrePhrases].phrase, phrase); // copie la phrase courante dans le tableau de phrases
            nombrePhrases++; 

            longueurPhrase = 0; 
        } else {
            phrase[longueurPhrase++] = c; // ajoute le caractère courant à la phrase courante
        }
    }
    float longueurMoyenne = calculerLongueurMoyenne(phrases, nombrePhrases); // calcule la longueur moyenne des phrases
    trouverPhrasesExtremes(phrases, nombrePhrases, &plusLongue, &plusCourte); // identifie les phrases les plus longues et les plus courtes

    printf("Longueur moyenne des phrases : %.2f\n", longueurMoyenne); 
    printf("Phrase la plus longue : %s\n", plusLongue.phrase); 
    printf("Phrase la plus courte : %s\n", plusCourte.phrase); 
}