#ifndef BST_H
#define BST_H

typedef struct NoeudBST {
    char titre[100];
    int livre_id;
    struct NoeudBST *gauche;
    struct NoeudBST *droit;
} NoeudBST;

void bst_inserer(NoeudBST **racine, const char *titre, int livre_id);
int bst_rechercher(NoeudBST *racine, const char *titre);
void bst_supprimer(NoeudBST **racine, const char *titre);
void bst_inordre(NoeudBST *racine);
int bst_hauteur(NoeudBST *racine);
int bst_nb_noeuds(NoeudBST *racine);
int bst_est_valide(NoeudBST *racine);
void bst_liberer(NoeudBST **racine);
void bst_suggestion(NoeudBST *racine, const char *prefixe);

#endif