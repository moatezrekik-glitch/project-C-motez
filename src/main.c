#include <stdio.h>
#include <stdlib.h>
#include "../include/catalogue.h"
#include "../include/pile.h"
#include "../include/file.h"
#include "../include/bst.h"

int main() {
    Livre *catalogue = NULL;
    Pile historique; pile_init(&historique, 10);
    File emprunts; file_init(&emprunts);
    NoeudBST *index_bst = NULL;

    // Pre-chargement demandé
    Livre *l1 = livre_creer(1, "Algorithmique", "Cormen", 2009);
    catalogue_inserer(&catalogue, l1); bst_inserer(&index_bst, l1->titre, l1->id);
    Livre *l2 = livre_creer(2, "C Programming Language", "Kernighan", 1988);
    catalogue_inserer(&catalogue, l2); bst_inserer(&index_bst, l2->titre, l2->id);

    int choix;
    do {
        printf("\n=== Mini-Gestionnaire de Bibliothèque ===\n");
        printf("[1] Ajouter un livre\n[2] Supprimer un livre\n[3] Rechercher un livre\n");
        printf("[4] Afficher catalogue normal\n[5] Afficher catalogue inverse\n[6] Afficher historique\n");
        printf("[7] Demande d'emprunt\n[8] Traiter emprunt\n[9] Afficher file\n");
        printf("[10] Afficher BST\n[11] Statistiques\n[0] Quitter\nChoix: ");
        scanf("%d", &choix);

        if (choix == 3) {
            char titre[100];
            printf("Titre a rechercher: "); scanf(" %[^\n]", titre);
            pile_empiler(&historique, titre);
            int id = bst_rechercher(index_bst, titre);
            if (id != -1) printf("Trouvé ! ID: %d\n", id);
            else printf("Introuvable.\n");
        } else if (choix == 4) catalogue_afficher(catalogue);
        else if (choix == 5) catalogue_afficher_inverse(catalogue);
        else if (choix == 6) pile_afficher(&historique);
        else if (choix == 8) file_traiter_prochain(&emprunts, catalogue);
        else if (choix == 9) file_afficher(&emprunts);
        else if (choix == 10) bst_inordre(index_bst);
        else if (choix == 11) {
            printf("Hauteur BST: %d | Total livres: %d | Demandes attente: %d\n", 
            bst_hauteur(index_bst), bst_nb_noeuds(index_bst), emprunts.taille);
        }

    } while (choix != 0);

    catalogue_liberer(&catalogue);
    pile_liberer(&historique);
    file_liberer(&emprunts);
    bst_liberer(&index_bst);
    return 0;
}