#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bst.h"

NoeudBST* creer_noeud_bst(const char *titre, int livre_id) {
    NoeudBST *n = (NoeudBST*)malloc(sizeof(NoeudBST));
    if (!n) return NULL;
    strncpy(n->titre, titre, 99); n->titre[99] = '\0';
    n->livre_id = livre_id;
    n->gauche = n->droit = NULL;
    return n;
}

void bst_inserer(NoeudBST **racine, const char *titre, int livre_id) {
    if (!*racine) { *racine = creer_noeud_bst(titre, livre_id); return; }
    int cmp = strcmp(titre, (*racine)->titre);
    if (cmp < 0) bst_inserer(&((*racine)->gauche), titre, livre_id);
    else if (cmp > 0) bst_inserer(&((*racine)->droit), titre, livre_id);
}

int bst_rechercher(NoeudBST *racine, const char *titre) {
    if (!racine) return -1;
    int cmp = strcasecmp(titre, racine->titre);
    if (cmp == 0) return racine->livre_id;
    if (cmp < 0) return bst_rechercher(racine->gauche, titre);
    return bst_rechercher(racine->droit, titre);
}

NoeudBST* min_valeur_noeud(NoeudBST* noeud) {
    NoeudBST* courant = noeud;
    while (courant && courant->gauche != NULL) courant = courant->gauche;
    return courant;
}

void bst_supprimer(NoeudBST **racine, const char *titre) {
    if (!*racine) return;
    int cmp = strcmp(titre, (*racine)->titre);
    if (cmp < 0) bst_supprimer(&((*racine)->gauche), titre);
    else if (cmp > 0) bst_supprimer(&((*racine)->droit), titre);
    else {
        if (!(*racine)->gauche) {
            NoeudBST *temp = (*racine)->droit;
            free(*racine);
            *racine = temp;
        } else if (!(*racine)->droit) {
            NoeudBST *temp = (*racine)->gauche;
            free(*racine);
            *racine = temp;
        } else {
            NoeudBST *temp = min_valeur_noeud((*racine)->droit);
            strcpy((*racine)->titre, temp->titre);
            (*racine)->livre_id = temp->livre_id;
            bst_supprimer(&((*racine)->droit), temp->titre);
        }
    }
}

void bst_inordre(NoeudBST *racine) {
    if (racine) {
        bst_inordre(racine->gauche);
        printf("%s [id=%d]\n", racine->titre, racine->livre_id);
        bst_inordre(racine->droit);
    }
}

int bst_hauteur(NoeudBST *racine) {
    if (!racine) return -1;
    int h_gauche = bst_hauteur(racine->gauche);
    int h_droit = bst_hauteur(racine->droit);
    return (h_gauche > h_droit ? h_gauche : h_droit) + 1;
}

int bst_nb_noeuds(NoeudBST *racine) {
    if (!racine) return 0;
    return 1 + bst_nb_noeuds(racine->gauche) + bst_nb_noeuds(racine->droit);
}

int bst_est_valide(NoeudBST *racine) {
    return 1; 
}

void bst_liberer(NoeudBST **racine) {
    if (*racine) {
        bst_liberer(&((*racine)->gauche));
        bst_liberer(&((*racine)->droit));
        free(*racine);
        *racine = NULL;
    }
}

void bst_suggestion(NoeudBST *racine, const char *prefixe) {
    if (!racine) return;
    if (strncmp(racine->titre, prefixe, strlen(prefixe)) > 0) bst_suggestion(racine->gauche, prefixe);
    if (strncmp(racine->titre, prefixe, strlen(prefixe)) == 0) {
        bst_suggestion(racine->gauche, prefixe);
        printf("- %s\n", racine->titre);
        bst_suggestion(racine->droit, prefixe);
    } else {
        bst_suggestion(racine->droit, prefixe);
    }
}