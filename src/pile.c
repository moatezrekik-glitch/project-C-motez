#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pile.h"

void pile_init(Pile *p, int max) {
    p->sommet = NULL;
    p->taille = 0;
    p->capacite_max = max;
}

int pile_empiler(Pile *p, const char *requete) {
    if (p->taille == p->capacite_max) {
        NoeudPile *courant = p->sommet, *precedent = NULL;
        while (courant->suivant) {
            precedent = courant;
            courant = courant->suivant;
        }
        if (precedent) precedent->suivant = NULL;
        free(courant);
        p->taille--;
    }
    NoeudPile *nouveau = (NoeudPile*)malloc(sizeof(NoeudPile));
    if (!nouveau) return 0;
    strncpy(nouveau->requete, requete, 149); nouveau->requete[149] = '\0';
    nouveau->suivant = p->sommet;
    p->sommet = nouveau;
    p->taille++;
    return 1;
}

char* pile_depiler(Pile *p) {
    if (!p->sommet) return NULL;
    NoeudPile *temp = p->sommet;
    p->sommet = temp->suivant;
    char *requete = strdup(temp->requete);
    free(temp);
    p->taille--;
    return requete;
}

const char* pile_peek(const Pile *p) {
    return p->sommet ? p->sommet->requete : NULL;
}

int pile_est_vide(const Pile *p) {
    return p->taille == 0;
}

void pile_afficher(const Pile *p) {
    NoeudPile *courant = p->sommet;
    int i = 1;
    while (courant) {
        printf("#%d %s\n", i++, courant->requete);
        courant = courant->suivant;
    }
}

void pile_liberer(Pile *p) {
    while (p->sommet) {
        NoeudPile *temp = p->sommet;
        p->sommet = p->sommet->suivant;
        free(temp);
    }
    p->taille = 0;
}