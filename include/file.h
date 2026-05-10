#ifndef FILE_H
#define FILE_H
#include "catalogue.h"

typedef struct Demande {
    int livre_id;
    char emprunteur[80];
    struct Demande *suivant;
} Demande;

typedef struct {
    Demande *tete;
    Demande *queue;
    int taille;
} File;

void file_init(File *f);
int file_enfiler(File *f, int livre_id, const char *emprunteur);
Demande* file_defiler(File *f);
int file_est_vide(const File *f);
int file_traiter_prochain(File *f, Livre *tete_catalogue);
void file_afficher(const File *f);
void file_liberer(File *f);

#endif