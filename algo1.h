#include <stdio.h>
#include "fonction_allocation.h"
#include "fonction_commun.h"

int recherche(Liste *m, char *mot);
int creation(Liste *m, char *mot, InfoMem *info);
void Conversion(char *str);
int MotFichier(FILE *Fichier, Liste *l, InfoMem *info, int *nb_uniques);
void AfficherResultat(Liste l, int n);
void libererListe(Liste *m, InfoMem *info);
void fusion(Liste *un, Liste *deux);
void triFusion(Liste *l);
void ecrireFichier(Liste m, int n, const char *nomFichier);
void ecrirePerformances(InfoMem *info, double temps, int nb_total, int nb_uniques, const char *fichier);
void algo1(const char *fichierEntree, int n, InfoMem *info, const char *fichierSortie, int afficher);
