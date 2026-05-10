#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/catalogue.h"

Livre* livre_creer(int id, const char* titre, const char* auteur, int annee) {
    Livre *l = (Livre*)malloc(sizeof(Livre));
    if (!l) return NULL;
    l->id = id;
    strncpy(l->titre, titre, 99); l->titre[99] = '\0';
    strncpy(l->auteur, auteur, 79); l->auteur[79] = '\0';
    l->annee = annee;
    l->disponible = 1;
    l->mots_cles = NULL;
    l->prev = l->next = NULL;
    return l;
}

void catalogue_inserer(Livre **tete, Livre *l) {
    if (!l) return;
    if (!*tete) { *tete = l; return; }
    Livre *courant = *tete, *precedent = NULL;
    while (courant && strcmp(courant->titre, l->titre) < 0) {
        precedent = courant;
        courant = courant->next;
    }
    if (!precedent) {
        l->next = *tete;
        (*tete)->prev = l;
        *tete = l;
    } else {
        l->next = courant;
        l->prev = precedent;
        precedent->next = l;
        if (courant) courant->prev = l;
    }
}

int catalogue_supprimer(Livre **tete, int id) {
    Livre *courant = *tete;
    while (courant && courant->id != id) courant = courant->next;
    if (!courant) return 0;
    
    if (courant->prev) courant->prev->next = courant->next;
    else *tete = courant->next;
    if (courant->next) courant->next->prev = courant->prev;
    
    Keyword *k = courant->mots_cles;
    while (k) {
        Keyword *temp = k;
        k = k->suivant;
        free(temp);
    }
    free(courant);
    return 1;
}

Livre* catalogue_rechercher(Livre *tete, const char *titre) {
    while (tete) {
        if (strcasecmp(tete->titre, titre) == 0) return tete;
        tete = tete->next;
    }
    return NULL;
}

void catalogue_afficher(Livre *tete) {
    while (tete) {
        printf("[%d] \"%s\" | %s | %d | %s\n", tete->id, tete->titre, tete->auteur, tete->annee, tete->disponible ? "DISPONIBLE" : "EMPRUNTE");
        tete = tete->next;
    }
}

void catalogue_afficher_inverse(Livre *tete) {
    if (!tete) return;
    while (tete->next) tete = tete->next;
    while (tete) {
        printf("[%d] \"%s\" | %s | %d | %s\n", tete->id, tete->titre, tete->auteur, tete->annee, tete->disponible ? "DISPONIBLE" : "EMPRUNTE");
        tete = tete->prev;
    }
}

void catalogue_ajouter_mot_cle(Livre *l, const char *mot) {
    Keyword *k = l->mots_cles;
    while (k) {
        if (strcmp(k->mot, mot) == 0) return;
        k = k->suivant;
    }
    Keyword *nouveau = (Keyword*)malloc(sizeof(Keyword));
    if (!nouveau) return;
    strncpy(nouveau->mot, mot, 49); nouveau->mot[49] = '\0';
    nouveau->suivant = l->mots_cles;
    l->mots_cles = nouveau;
}

void catalogue_liberer(Livre **tete) {
    while (*tete) {
        Livre *temp = *tete;
        *tete = (*tete)->next;
        Keyword *k = temp->mots_cles;
        while (k) {
            Keyword *ktemp = k;
            k = k->suivant;
            free(ktemp);
        }
        free(temp);
    }
}