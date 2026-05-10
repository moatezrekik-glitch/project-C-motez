#ifndef CATALOGUE_H
#define CATALOGUE_H

typedef struct Keyword {
    char mot[50];
    struct Keyword *suivant;
} Keyword;

typedef struct Livre {
    int id;
    char titre[100];
    char auteur[80];
    int annee;
    int disponible;
    Keyword *mots_cles;
    struct Livre *prev;
    struct Livre *next;
} Livre;

Livre* livre_creer(int id, const char* titre, const char* auteur, int annee);
void catalogue_inserer(Livre **tete, Livre *l);
int catalogue_supprimer(Livre **tete, int id);
Livre* catalogue_rechercher(Livre *tete, const char *titre);
void catalogue_afficher(Livre *tete);
void catalogue_afficher_inverse(Livre *tete);
void catalogue_ajouter_mot_cle(Livre *l, const char *mot);
void catalogue_liberer(Livre **tete);

#endif