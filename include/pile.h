#ifndef PILE_H
#define PILE_H

typedef struct NoeudPile {
    char requete[150];
    struct NoeudPile *suivant;
} NoeudPile;

typedef struct {
    NoeudPile *sommet;
    int taille;
    int capacite_max;
} Pile;

void pile_init(Pile *p, int max);
int pile_empiler(Pile *p, const char *requete);
char* pile_depiler(Pile *p);
const char* pile_peek(const Pile *p);
int pile_est_vide(const Pile *p);
void pile_afficher(const Pile *p);
void pile_liberer(Pile *p);

#endif