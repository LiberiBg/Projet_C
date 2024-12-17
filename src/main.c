#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "analyseur.h"
#include "struct.h"
#include <ctype.h>

#define TAILLE_INITIALE_TABLEAU 10
#define MAX_CHEMIN 1024

// Variables globales
int nombreCaracteres;
char chemin1[MAX_CHEMIN];
char chemin2[MAX_CHEMIN];


typedef struct AppWidgets {
    GtkWidget *text_view;
    GtkTextBuffer *buffer;
} AppWidgets;

void effacer_resultats(AppWidgets *widgets) {
    gtk_text_buffer_set_text(widgets->buffer, "", -1);
}

void afficher_resultat(AppWidgets *widgets, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(widgets->buffer, &iter);
    gtk_text_buffer_insert(widgets->buffer, &iter, buffer, -1);
    gtk_text_buffer_insert(widgets->buffer, &iter, "\n", -1);
}

void on_save_button_clicked(GtkWidget *widget, gpointer data) {
    struct AppWidgets *app_widgets = (AppWidgets *)data;
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
    struct AppWidgets *app_widgets = (AppWidgets *)data;

    GtkWidget *window = gtk_widget_get_toplevel(widget);
    GtkWidget *chooser1 = GTK_WIDGET(g_object_get_data(G_OBJECT(window), "chooser1"));
    char *chemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser1));
    
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

    afficher_resultat(app_widgets, "Fichier lu avec succès!");
    afficher_resultat(app_widgets, "Nombre de lignes : %d", compterLignes(fichier));
    int nombreMots = compterMots(fichier);
    afficher_resultat(app_widgets, "Nombre de mots : %d", nombreMots);
    afficher_resultat(app_widgets, "Nombre de caractères : %d", compterCaracteres(fichier));

    rewind(fichier);
    
    analyserPhrases(fichier);

    struct Mot* tableauMots = malloc(nombreMots * sizeof(struct Mot));
    if (tableauMots == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer la mémoire pour tableauMots\n");
        fclose(fichier);
        g_free(chemin);
        return;
    }

    int tailleTableau = TAILLE_INITIALE_TABLEAU;
    mettreAJourFrequence(fichier, &tableauMots, &nombreMots, &tailleTableau);

    struct Mot* tmp = malloc(nombreMots * sizeof(struct Mot));
    if (tmp == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer la mémoire pour tmp\n");
        free(tableauMots);
        fclose(fichier);
        g_free(chemin);
        return;
    }

    fclose(fichier);
    g_free(chemin);

    triFusion(0, nombreMots - 1, tableauMots, tmp);

    free(tableauMots);
    free(tmp);
}

void on_compare_button_clicked(GtkWidget *widget, gpointer data) {
    struct AppWidgets *app_widgets = (AppWidgets *)data;
    effacer_resultats(app_widgets);

    GtkWidget *window = gtk_widget_get_toplevel(widget);
    GtkWidget *chooser1 = GTK_WIDGET(g_object_get_data(G_OBJECT(window), "chooser1"));
    GtkWidget *chooser2 = GTK_WIDGET(g_object_get_data(G_OBJECT(window), "chooser2"));

    if (!GTK_IS_FILE_CHOOSER(chooser1) || !GTK_IS_FILE_CHOOSER(chooser2)) {
        afficher_resultat(app_widgets, "Erreur : les sélecteurs de fichiers ne sont pas valides");
        return;
    }

    char *chemin1 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser1));
    char *chemin2 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser2));

    if (chemin1 == NULL || chemin2 == NULL) {
        afficher_resultat(app_widgets, "Erreur : veuillez sélectionner deux fichiers");
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

    GtkWidget *window, *vbox, *label;
    GtkWidget *chooser1, *chooser2;
    GtkWidget *analyze_button, *compare_button, *save_button;
    GtkWidget *scrolled_window;
    AppWidgets *app_widgets;

    // Création fenêtre principale
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Analyse de fichiers");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Création des widgets
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    
    label = gtk_label_new("Sélectionnez un ou deux fichiers à analyser");
    chooser1 = gtk_file_chooser_button_new("Sélectionner le premier fichier", GTK_FILE_CHOOSER_ACTION_OPEN);
    chooser2 = gtk_file_chooser_button_new("Sélectionner le deuxième fichier", GTK_FILE_CHOOSER_ACTION_OPEN);
    analyze_button = gtk_button_new_with_label("Analyser un fichier");
    compare_button = gtk_button_new_with_label("Comparer deux fichiers");
    save_button = gtk_button_new_with_label("Sauvegarder les résultats");

    // Initialisation app_widgets
    app_widgets = g_new(AppWidgets, 1);
    app_widgets->text_view = gtk_text_view_new();
    app_widgets->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app_widgets->text_view));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(app_widgets->text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(app_widgets->text_view), GTK_WRAP_WORD);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolled_window, -1, 200);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), 
                                 GTK_POLICY_AUTOMATIC, 
                                 GTK_POLICY_AUTOMATIC);

    // Organisation des widgets
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_add(GTK_CONTAINER(scrolled_window), app_widgets->text_view);
    
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), chooser1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), chooser2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), analyze_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), compare_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), save_button, FALSE, FALSE, 0);

    // Connexion des signaux
    g_object_set_data(G_OBJECT(window), "chooser1", chooser1);
    g_object_set_data(G_OBJECT(window), "chooser2", chooser2);
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(analyze_button, "clicked", G_CALLBACK(on_analyze_button_clicked), app_widgets);
    g_signal_connect(compare_button, "clicked", G_CALLBACK(on_compare_button_clicked), app_widgets);
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_button_clicked), app_widgets);

    // Launch
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
