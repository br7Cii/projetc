#include <stdio.h>
#include <stdlib.h>
#include "fonction_allocation.h"
#include "algo1.h"
#include "algo2.h"  // À ajouter
#include "algo3.h"  // À ajouter

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <algorithme (1/2/3)> <fichier_entree> <nombre_mots> <afficher (0/1)> [fichier_sortie]\n", argv[0]);
        return 1;
    }

    int algorithme = atoi(argv[1]);
    const char *fichierEntree = argv[2];
    int n = atoi(argv[3]);
    int afficher = atoi(argv[4]);
    const char *fichierSortie = NULL;

    if (argc >= 6) {
        fichierSortie = argv[5];
    }

    // Validation de l'algorithme
    if (algorithme < 1 || algorithme > 3) {
        printf("Erreur: L'algorithme doit être 1, 2 ou 3\n");
        return 1;
    }

    // Initialiser la structure de suivi mémoire
    InfoMem info;
    info.cumul_alloc = 0;
    info.cumul_desalloc = 0;
    info.max_alloc = 0;

    // Lancer l'algorithme choisi
    printf("=== Lancement de l'algorithme %d ===\n\n", algorithme);
    
    switch(algorithme) {
        case 1:
            algo1(fichierEntree, n, &info, fichierSortie, afficher);
            break;
        case 2:
            algo2(fichierEntree, n, &info, fichierSortie, afficher);
            break;
        case 3:
            algo3(fichierEntree, n, &info, fichierSortie, afficher);
            break;
    }

    return 0;
}