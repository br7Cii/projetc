#include <stdio.h>
#include "fonction_allocation.h"
#include "fonction_commun.h"

Liste * dichotomie(Liste *m, char *mot, int len);
int creation3(Liste *m, char *mot, InfoMem *info);
void Conversion3(char *str);
int MotFichier3(FILE *Fichier, Liste *l, InfoMem *info, int *nb_uniques);
void AfficherResultat3(Liste l, int n);
void libererListe3(Liste *m, InfoMem *info);
void fusion3(Liste *un, Liste *deux);
void triFusion3(Liste *l);
void ecrireFichier3(Liste m, int n, const char *nomFichier);
void ecrirePerformances3(InfoMem *info, double temps, int nb_total, int nb_uniques, const char *fichier);
void algo3(const char *fichierEntree, int n, InfoMem *info, const char *fichierSortie, int afficher);
