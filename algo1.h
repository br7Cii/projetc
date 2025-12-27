#include <stdio.h>
#include "fonction_allocation.h"
#include "fonction_commun.h"

int recherche(Liste *m, char *mot);
int creation(Liste *m, char *mot, InfoMem *info);
void Conversion(char *str);
void MotFichier(FILE *Fichier, Liste *l, InfoMem *info);
void AfficherResultat(Liste l, int n);
void libererListe(Liste *m, InfoMem *info);
void fusion(Liste *un, Liste *deux);
void triFusion(Liste *l);
void ecrireFichier(Liste m, int n, const char *nomFichier);
void ecrirePerformances(InfoMem *info, double temps, const char *fichier);
void algo1(const char *fichierEntree, int n, InfoMem *info, const char *fichierSortie, int afficher);
