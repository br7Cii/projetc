#include <stdio.h>
#include "fonction_allocation.h"

typedef struct {
    char *mot;
    int compteur;
} MotTab;

typedef struct {
    MotTab *elements;
    size_t taille;
    size_t capacite;
} TableauDynamique;

int initTableau(TableauDynamique *tab, size_t capaciteInitiale, InfoMem *info);
void libererTableau(TableauDynamique *tab, InfoMem *info);
void Conversion2(char *str);
int creationTab(TableauDynamique *tab, char *mot, InfoMem *info);
int rechercheTab(TableauDynamique *tab, char *mot);
void MotFichierTab(FILE *Fichier, TableauDynamique *tab, InfoMem *info);
void AfficherResultatTab(TableauDynamique *tab, int n);
void ecrireFichierTab(TableauDynamique *tab, int n, const char *nomFichier);
void ecrirePerformancesTab(InfoMem *info, double temps, const char *fichier);
int comparerMots(const void *a, const void *b);
void algo2(const char *fichierEntree, int n, InfoMem *info, const char *fichierSortie, int afficher);
