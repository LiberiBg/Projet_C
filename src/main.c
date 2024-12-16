#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyseur.h"
#include "struct.h"
#include <gtk/gtk.h>

#define TAILLE_INITIALE_TABLEAU 10

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

    int nombreCaracteres = compterCaracteres(fichier);
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

    free(tableauMots);
    free(tmp);
    
}

void on_compare_button_clicked(GtkWidget *widget, gpointer data) {
    GtkFileChooser **choosers = (GtkFileChooser **)data;
    char *chemin1 = gtk_file_chooser_get_filename(choosers[0]);
    char *chemin2 = gtk_file_chooser_get_filename(choosers[1]);

    if (chemin1 == NULL || chemin2 == NULL) {
        fprintf(stderr, "Erreur : veuillez sélectionner deux fichiers\n");
        g_free(chemin1);
        g_free(chemin2);
        return;
    }

    FILE *fichier1 = ouvrirFichierLecture(chemin1);
    FILE *fichier2 = ouvrirFichierLecture(chemin2);
    
    if (fichier1 == NULL || fichier2 == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir les fichiers\n");
        if (fichier1) fclose(fichier1);
        if (fichier2) fclose(fichier2);
        g_free(chemin1);
        g_free(chemin2);
        return;
    }

    analyseComparative(chemin1, chemin2);

    g_free(chemin1);
    g_free(chemin2);
    fclose(fichier1);
    fclose(fichier2);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *chooser1;
    GtkWidget *chooser2;
    GtkWidget *analyze_button;
    GtkWidget *compare_button;
    GtkWidget *vbox;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Analyse de fichiers");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    label = gtk_label_new("Sélectionnez un ou deux fichiers à analyser");
    
    // Créer les sélecteurs de fichiers
    chooser1 = gtk_file_chooser_button_new("Sélectionner le premier fichier", GTK_FILE_CHOOSER_ACTION_OPEN);
    chooser2 = gtk_file_chooser_button_new("Sélectionner le deuxième fichier", GTK_FILE_CHOOSER_ACTION_OPEN);

    // Créer les boutons
    analyze_button = gtk_button_new_with_label("Analyser un fichier");
    g_signal_connect(analyze_button, "clicked", G_CALLBACK(on_analyze_button_clicked), chooser1);

    compare_button = gtk_button_new_with_label("Comparer deux fichiers");
    GtkFileChooser *choosers[2] = {GTK_FILE_CHOOSER(chooser1), GTK_FILE_CHOOSER(chooser2)};
    g_signal_connect(compare_button, "clicked", G_CALLBACK(on_compare_button_clicked), choosers);

    // Organisation verticale
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), chooser1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), chooser2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), analyze_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), compare_button, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    gtk_main();
    return 0;

    // Ajout de la demande de chemin pour sauvegarder les résultats
    printf("Entrez le chemin du fichier de sortie : ");
    if (fgets(cheminSortie, sizeof(cheminSortie), stdin) == NULL) {
        fprintf(stderr, "Erreur de lecture pour le fichier de sortie\n");
        free(tableauMots);
        return 1;
    }
    cheminSortie[strcspn(cheminSortie, "\n")] = 0; // Supprime le saut de ligne

    // Appel à la fonction sauvegarderResultats
    sauvegarderResultats(cheminSortie, nombreLigne, nombreMots, nombreCaracteres, tableauMots, nombreMots);
}