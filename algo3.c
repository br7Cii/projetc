#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "fonction_allocation.h"
#include "algo3.h"

Liste* dichotomie(Liste *l, char *mot, int len){
    if (len == 0) {
        return l;  
    }
    
    int gauche = 0;
    int droite = len - 1;
    
    while(gauche <= droite){
        int milieu = (gauche + droite) / 2;
        Liste *position = l;
        for (int i = 0; i < milieu; i++){ 
            position = &((*position)->suivant);
        }
        
        int compare = strcmp((*position)->mot, mot);
        
        if(compare == 0){
            (*position)->compteur++;
            return NULL;  
        }
        else if(compare < 0){
            gauche = milieu + 1;
        }
        else {
            droite = milieu - 1;
        }
    }
    
    Liste *position = l;
    for (int i = 0; i < gauche && *position != NULL; i++){
        position = &((*position)->suivant);
    }
    
    return position;
}

int creation3(Liste *m, char *mot, InfoMem *info){  
    MotNode *tmp = myMalloc(sizeof(MotNode), info);  
    if (tmp == NULL) {
        printf("Erreur d'allocation\n");
        return 0;
    }
    tmp->mot = myMalloc(strlen(mot) + 1, info);  
    if (tmp->mot == NULL) {
        printf("Erreur d'allocation\n");
        myFree(tmp, info, sizeof(MotNode));  
        return 0; 
    }
    strcpy(tmp->mot, mot);
    tmp->compteur = 1;
    tmp->suivant = *m;  
    *m = tmp;
    return 1; 
}

void Conversion3(char *str){
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int MotFichier3(FILE *Fichier, Liste *l, InfoMem *info, int *nb_uniques, int longueur_min){ 
    char c;
    int longueur_liste = 0;
    int nb_total = 0;

    while ((c = fgetc(Fichier)) != EOF) {
        char *mot = NULL; 
        int len = 0;
        
        // Ignorer les espaces
        while (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            c = fgetc(Fichier);
            if (c == EOF) {
                *nb_uniques = longueur_liste;
                return nb_total;
            }
        }
        
        // Lire le mot
        while(c != ' ' && c != '\n' && c != '\t' && c != '\r' && c != EOF && 
              c != '\'' && (isalpha((unsigned char)c) || c == '-' || (unsigned char)c >= 128)){
            len++;
            mot = myRealloc(mot, len + 1, info, len);  
            if (mot == NULL){
                *nb_uniques = longueur_liste;
                return nb_total;  
            }
            mot[len - 1] = c;
            c = fgetc(Fichier); 
        }
        
        // Gérer l'apostrophe
        if (c == '\'' && len > 0){
            len++;
            mot = myRealloc(mot, len + 1, info, len);
            if (mot == NULL){
                *nb_uniques = longueur_liste;
                return nb_total;
            }
            mot[len - 1] = '\'';
            c = fgetc(Fichier);
            
            while(c != ' ' && c != '\n' && c != '\t' && c != '\r' && c != EOF && 
                  (isalpha((unsigned char)c) || c == '-' || (unsigned char)c >= 128)){
                len++;
                mot = myRealloc(mot, len + 1, info, len);
                if (mot == NULL){
                    *nb_uniques = longueur_liste;
                    return nb_total;
                }
                mot[len - 1] = c;
                c = fgetc(Fichier);
            }
        }
        
        if (len > 0){
            mot[len] = '\0';
            
            // Filtrer les mots trop courts
            if (len >= longueur_min) {
                Conversion3(mot);
                
                Liste *adresse = dichotomie(l, mot, longueur_liste);
                if (adresse != NULL) {
                    creation3(adresse, mot, info);
                    longueur_liste++; 
                }
                nb_total++;
            }
            
            myFree(mot, info, len + 1);
        }
    }
    *nb_uniques = longueur_liste;
    return nb_total;
}

void AfficherResultat3(Liste l, int n){
    int count;
    for(count = 0; l && count < n; count++){
        printf("%s %d\n", l->mot, l->compteur);
        l = l->suivant;
    }
}

void libererListe3(Liste *m, InfoMem *info){
    for(; *m; ) {
        MotNode *tmp = *m;
        *m = (*m)->suivant;
        
        size_t taille_mot = strlen(tmp->mot) + 1;
        myFree(tmp->mot, info, taille_mot);
        myFree(tmp, info, sizeof(MotNode));
    }
}

void fusion3(Liste *un, Liste *deux){
    Liste resultat = NULL;
    Liste *queue = &resultat;

    for (; *un && *deux;) {
        if ((*un)->compteur >= (*deux)->compteur) {
            *queue = *un;
            *un = (*un)->suivant;
        } else {
            *queue = *deux;
            *deux = (*deux)->suivant;
        }
        queue = &((*queue)->suivant);
    }

    for (; *un;) {
        *queue = *un;
        *un = (*un)->suivant;
        queue = &((*queue)->suivant);
    }

    for (; *deux;) {
        *queue = *deux;
        *deux = (*deux)->suivant;
        queue = &((*queue)->suivant);
    }

    *un = resultat;
    *deux = NULL;
}

void triFusion3(Liste *l){
    if (*l == NULL || (*l)->suivant == NULL)
        return;

    Liste l1, l2;
    MotNode *lent = *l;
    MotNode *rapide = (*l)->suivant;
    for (; rapide && rapide->suivant;){
        lent = lent->suivant;
        rapide = rapide->suivant->suivant;
    }

    l1 = *l;
    l2 = lent->suivant;
    lent->suivant = NULL;

    triFusion3(&l1);
    triFusion3(&l2);

    fusion3(&l1, &l2);
    *l = l1;
}

void ecrireFichier3(Liste m, int n, const char *nomFichier){
    FILE *f = fopen(nomFichier, "w");
    if (!f) {
        printf("Erreur ouverture fichier\n");
        return;
    }
    
    int count = 0;
    while (m && count < n) {
        fprintf(f, "%s %d\n", m->mot, m->compteur);
        m = m->suivant;
        count++;
    }
    
    fclose(f);
}

void ecrirePerformances3(InfoMem *info, double temps, int nb_total, int nb_uniques, const char *fichier){
    FILE *f = fopen(fichier, "a"); 
    if (!f) return;
    
    fprintf(f, "%d,%d,%zu,%zu,%zu,%f,Algo3\n",  
            nb_total,
            nb_uniques,
            info->cumul_alloc, 
            info->cumul_desalloc, 
            info->max_alloc, 
            temps);
    
    fclose(f);
}

void algo3(const char *fichierEntree, int n, InfoMem *info, 
           const char *fichierSortie, int afficher, int longueur_min){
    
    clock_t debut = clock();
    
    // Ouvrir fichier
    FILE *f = fopen(fichierEntree, "r");
    if (!f) {
        printf("Erreur ouverture fichier\n");
        return;
    }
    
    // Construire la liste avec dichotomie (ordre alphabétique)
    Liste liste = NULL;
    int nb_uniques = 0;
    int nb_total = MotFichier3(f, &liste, info, &nb_uniques, longueur_min);
    fclose(f);
    
    triFusion3(&liste);
    
    clock_t fin = clock();
    double temps = (double)(fin - debut) / CLOCKS_PER_SEC;

    if (afficher) {
        AfficherResultat3(liste, n);
    }
    
    printf("\n=== PERFORMANCES ALGO 3 ===\n");
    printf("Nombre de mots total : %d\n", nb_total);
    printf("Nombre de mots uniques : %d\n", nb_uniques);
    printf("Cumul allocation : %zu octets\n", info->cumul_alloc);
    printf("Cumul désallocation : %zu octets\n", info->cumul_desalloc);
    printf("Allocation max : %zu octets\n", info->max_alloc);
    printf("Temps d'exécution : %.6f secondes\n", temps);
    printf("===========================\n");
    if (fichierSortie) {
        ecrireFichier3(liste, n, fichierSortie);
    }
    ecrirePerformances3(info, temps, nb_total, nb_uniques, "performances_algo3.csv");
}
