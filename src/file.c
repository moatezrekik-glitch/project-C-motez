#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file.h"

void file_init(File *f) {
    f->tete = f->queue = NULL;
    f->taille = 0;
}

int file_enfiler(File *f, int livre_id, const char *emprunteur) {
    Demande *nouvelle = (Demande*)malloc(sizeof(Demande));
    if (!nouvelle) return 0;
    nouvelle->livre_id = livre_id;
    strncpy(nouvelle->emprunteur, emprunteur, 79); nouvelle->emprunteur[79] = '\0';
    nouvelle->suivant = NULL;
    
    if (!f->queue) {
        f->tete = f->queue = nouvelle;
    } else {
        f->queue->suivant = nouvelle;
        f->queue = nouvelle;
    }
    f->taille++;
    return 1;
}

Demande* file_defiler(File *f) {
    if (!f->tete) return NULL;
    Demande *temp = f->tete;
    f->tete = f->tete->suivant;
    if (!f->tete) f->queue = NULL;
    f->taille--;
    return temp;
}

int file_est_vide(const File *f) {
    return f->taille == 0;
}

int file_traiter_prochain(File *f, Livre *tete_catalogue) {
    if (file_est_vide(f)) return 0;
    Demande *d = file_defiler(f);
    Livre *courant = tete_catalogue;
    while (courant && courant->id != d->livre_id) courant = courant->next;
    
    if (courant && courant->disponible) {
        courant->disponible = 0;
        printf(">>> Emprunt accordé pour le livre #%d a %s\n", d->livre_id, d->emprunteur);
        free(d);
        return 1;
    } else {
        printf(">>> Livre #%d indisponible, demande remise en fin de file.\n", d->livre_id);
        file_enfiler(f, d->livre_id, d->emprunteur);
        free(d);
        return -1;
    }
}

void file_afficher(const File *f) {
    Demande *courant = f->tete;
    int i = 1;
    while (courant) {
        printf("[%d] -> Livre #%d | Emprunteur: %s\n", i++, courant->livre_id, courant->emprunteur);
        courant = courant->suivant;
    }
}

void file_liberer(File *f) {
    while (f->tete) {
        Demande *temp = f->tete;
        f->tete = f->tete->suivant;
        free(temp);
    }
    f->queue = NULL;
    f->taille = 0;
}