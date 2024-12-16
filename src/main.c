#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyseur.h"
#include "struct.h"
#include <stdio.h>

#define TAILLE_INITIALE_TABLEAU 10

void on_save_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    
    dialog = gtk_file_chooser_dialog_new("Sauvegarder les résultats",
                                       GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                       GTK_FILE_CHOOSER_ACTION_SAVE,
                                       "Annuler", GTK_RESPONSE_CANCEL,
                                       "Sauvegarder", GTK_RESPONSE_ACCEPT,
                                       NULL);
    
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
    
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        printf("Fichier sélectionné : %s\n", filename);
        // En attente de la récupération des données à sauvegarder
        g_free(filename);
    }
    
    gtk_widget_destroy(dialog);
}

void on_analyze_button_clicked(GtkWidget *widget, gpointer data) {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(data);
    char *chemin = gtk_file_chooser_get_filename(chooser);
    
    if (chemin == NULL) {
        fprintf(stderr, "Erreur : aucun fichier sélectionné\n");
        return;
    }

    FILE *fichier = ouvrirFichierLecture(chemin);
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", chemin);
        g_free(chemin);
        return;
    }
    
    printf("Fichier lu avec succès!\n");

    int nombreLigne = compterLignes(fichier);
    printf("Nombre de lignes : %d\n", nombreLigne);

    int nombreMots = compterMots(fichier);
    printf("Nombre de mots : %d\n", nombreMots);

    nombreCaracteres = compterCaracteres(fichier);
    printf("Nombre de caractères : %d\n", nombreCaracteres);

    rewind(fichier);
    
    analyserPhrases(fichier);

    struct Mot* tableauMots = malloc(nombreMots * sizeof(struct Mot));
    if (tableauMots == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer la mémoire pour tableauMots\n");
        fclose(fichier);
        return;
    }

    int tailleTableau = TAILLE_INITIALE_TABLEAU;
    mettreAJourFrequence(fichier, &tableauMots, &nombreMots, &tailleTableau);

    struct Mot* tmp = malloc(nombreMots * sizeof(struct Mot));
    if (tmp == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer la mémoire pour tmp\n");
        free(tableauMots);
        fclose(fichier);
        return;
    }

    g_free(chemin);
    fclose(fichier);

    triFusion(0, nombreMots - 1, tableauMots, tmp);

    printf("Entrez le chemin du premier fichier : ");
    if (fgets(chemin1, sizeof(chemin1), stdin) == NULL) {
        fprintf(stderr, "Erreur de lecture pour le premier fichier\n");
        free(tableauMots);
        return 1;
    }
    chemin1[strcspn(chemin1, "\n")] = 0; // Supprime le saut de ligne

    printf("Entrez le chemin du deuxième fichier : ");
    if (fgets(chemin2, sizeof(chemin2), stdin) == NULL) {
        fprintf(stderr, "Erreur de lecture pour le deuxième fichier\n");
        free(tableauMots);
        return 1;
    }
    chemin2[strcspn(chemin2, "\n")] = 0; // Supprime le saut de ligne

    struct ResultatAnalyseComparative resultat = analyseComparative(chemin1, chemin2);


    
    return 0;

}