#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "algo2.h"

int initTableau(TableauDynamique *tab, size_t capaciteInitiale, InfoMem *info) {
    tab->taille = 0;
    tab->capacite = capaciteInitiale;
    tab->elements = (MotTab *)myMalloc(tab->capacite * sizeof(MotTab), info);
    
    if (tab->elements == NULL) {
        printf("Erreur d'allocation initiale du tableau\n");
        return 0; 
    }
    return 1; 
}

void libererTableau(TableauDynamique *tab, InfoMem *info) {
    if (tab->elements != NULL) {
        for (size_t i = 0; i < tab->taille; i++) {
            size_t taille_mot = strlen(tab->elements[i].mot) + 1;
            myFree(tab->elements[i].mot, info, taille_mot);
        }
        myFree(tab->elements, info, tab->capacite * sizeof(MotTab));
        tab->elements = NULL;
    }
    tab->taille = 0;
    tab->capacite = 0;
}

void Conversion2(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int rechercheTab(TableauDynamique *tab, char *mot) {
    for (size_t i = 0; i < tab->taille; i++) {
        if (strcmp(tab->elements[i].mot, mot) == 0) {
            tab->elements[i].compteur++; 
            return 1;
        }
    }
    return 0;
}

int creationTab(TableauDynamique *tab, char *mot, InfoMem *info) {
    if (tab->taille >= tab->capacite) {
        size_t ancienneCapacite = tab->capacite;
        size_t nouvelleCapacite = ancienneCapacite * 2; 
        if (nouvelleCapacite == 0) nouvelleCapacite = 10; 

        MotTab *nouveauxElements = (MotTab *)myRealloc(
            tab->elements, 
            nouvelleCapacite * sizeof(MotTab), 
            info, 
            ancienneCapacite * sizeof(MotTab)
        );

        if (nouveauxElements == NULL) {
            printf("Erreur de réallocation du tableau\n");
            return 0; 
        }

        tab->elements = nouveauxElements;
        tab->capacite = nouvelleCapacite;
    }

    size_t len = strlen(mot);
    char *motStocke = (char *)myMalloc(len + 1, info);
    if (motStocke == NULL) {
        printf("Erreur d'allocation pour le mot\n");
        return 0;
    }
    strcpy(motStocke, mot);

    tab->elements[tab->taille].mot = motStocke;
    tab->elements[tab->taille].compteur = 1;
    tab->taille++;

    return 1;
}

int MotFichierTab(FILE *Fichier, TableauDynamique *tab, InfoMem *info) {
    char c;
    int nb_total = 0;
    
    while ((c = fgetc(Fichier)) != EOF) {
        while (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            c = fgetc(Fichier);
            if (c == EOF) return nb_total;
        }

        char *mot = NULL;
        int len = 0;

        while (c != EOF && (isalpha((unsigned char)c) || c == '-' || (unsigned char)c >= 128)) {
            len++;
            mot = myRealloc(mot, len + 1, info, len);
            if (!mot) return nb_total; 
            
            mot[len - 1] = c;
            c = fgetc(Fichier);
        }

        if (c == '\'' && len > 0) {
             len++;
             mot = myRealloc(mot, len + 1, info, len);
             if (!mot) return nb_total;
             mot[len - 1] = '\'';
             
             c = fgetc(Fichier);
             while (c != EOF && (isalpha((unsigned char)c) || c == '-' || (unsigned char)c >= 128)) {
                len++;
                mot = myRealloc(mot, len + 1, info, len);
                if (!mot) return nb_total;
                mot[len - 1] = c;
                c = fgetc(Fichier);
             }
        }

        if (len > 0) {
            mot[len] = '\0';
            
            Conversion2(mot);
            if (!rechercheTab(tab, mot)) {
                creationTab(tab, mot, info);
            }
            
            myFree(mot, info, len + 1);
            nb_total++;
        }
    }
    return nb_total;
}

int comparerMots(const void *a, const void *b) {
    MotTab *motA = (MotTab *)a;
    MotTab *motB = (MotTab *)b;
    return motB->compteur - motA->compteur;
}

void AfficherResultatTab(TableauDynamique *tab, int n) {
    for (size_t i = 0; i < tab->taille && i < (size_t)n; i++) {
        printf("%s %d\n", tab->elements[i].mot, tab->elements[i].compteur);
    }
}

void ecrireFichierTab(TableauDynamique *tab, int n, const char *nomFichier) {
    FILE *f = fopen(nomFichier, "w");
    if (!f) {
        printf("Erreur ouverture fichier sortie\n");
        return;
    }
    
    for (size_t i = 0; i < tab->taille && i < (size_t)n; i++) {
        fprintf(f, "%s %d\n", tab->elements[i].mot, tab->elements[i].compteur);
    }
    
    fclose(f);
}

void ecrirePerformancesTab(InfoMem *info, double temps, int nb_total, int nb_uniques, const char *fichier){
    FILE *f = fopen(fichier, "a"); 
    if (!f) return;
    
    fprintf(f, "%d,%d,%zu,%zu,%zu,%f,Algo2\n",  
            nb_total,
            nb_uniques,
            info->cumul_alloc, 
            info->cumul_desalloc, 
            info->max_alloc, 
            temps);
    
    fclose(f);
}

void algo2(const char *fichierEntree, int n, InfoMem *info, const char *fichierSortie, int afficher) {
    clock_t debut = clock();
    
    FILE *f = fopen(fichierEntree, "r");
    if (!f) {
        printf("Erreur ouverture fichier entrée\n");
        return;
    }

    TableauDynamique tab;
    if (!initTableau(&tab, 100, info)) {
        fclose(f);
        return;
    }

    int nb_total = MotFichierTab(f, &tab, info);
    fclose(f);

    qsort(tab.elements, tab.taille, sizeof(MotTab), comparerMots);

    clock_t fin = clock();
    double temps = (double)(fin - debut) / CLOCKS_PER_SEC;

    if (afficher) {
        AfficherResultatTab(&tab, n);
    }

    printf("\n=== PERFORMANCES ALGO 2 ===\n");
    printf("Nombre de mots total : %d\n", nb_total);
    printf("Nombre de mots uniques : %zu\n", tab.taille);
    printf("Cumul allocation : %zu octets\n", info->cumul_alloc);
    printf("Cumul désallocation : %zu octets\n", info->cumul_desalloc);
    printf("Allocation max : %zu octets\n", info->max_alloc);
    printf("Temps d'exécution : %.6f secondes\n", temps);
    printf("===========================\n");

    if (fichierSortie) {
        ecrireFichierTab(&tab, n, fichierSortie);
    }

    ecrirePerformancesTab(info, temps, nb_total, (int)tab.taille, "performances_algo2.csv");

    
    libererTableau(&tab, info);
}

