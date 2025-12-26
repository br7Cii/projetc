#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "algo1.h"


int recherche(Liste *m, char *mot) {
    for(; *m; m = &((*m)->suivant)) {
        if(strcmp((*m)->mot, mot) == 0) {
            (*m)->compteur++;
            return 1; 
        }
    }
    return 0;
}

int creation(Liste *m, char *mot, InfoMem *info){  
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

void Conversion(char *str){
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void MotFichier(FILE *Fichier, Liste *l, InfoMem *info){ 
    char c;  
    while ((c = fgetc(Fichier)) != EOF) {
        char *mot = NULL; 
        int len = 0;
        while (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            c = fgetc(Fichier);
            if (c == EOF) {
                return;
            }
        }
        while(c != ' ' && c != '\n' && c != '\t' && c != '\r' && c != EOF && 
              c != '\'' && (isalpha((unsigned char)c) || c == '-' || (unsigned char)c >= 128)){
            len++;
            mot = myRealloc(mot, len + 1, info, len);  
            if (mot == NULL){
                return;  
            }
            mot[len - 1] = c;
            c = fgetc(Fichier); 
        }
        if (c == '\'' && len > 0){
            len++;
            mot = myRealloc(mot, len + 1, info, len);
            if (mot == NULL){
                return;
            }
            mot[len - 1] = '\'';
            c = fgetc(Fichier);
            while(c != ' ' && c != '\n' && c != '\t' && c != '\r' && c != EOF && 
                  (isalpha((unsigned char)c) || c == '-' || (unsigned char)c >= 128)){
                len++;
                mot = myRealloc(mot, len + 1, info, len);
                if (mot == NULL){
                    return;
                }
                mot[len - 1] = c;
                c = fgetc(Fichier);
            }
        }
        
        if (len > 0){
            mot[len] = '\0';
            Conversion(mot); 
            if (!recherche(l, mot)){  
                creation(l, mot, info); 
            }
            myFree(mot, info, len + 1);  
        }
    }
}

void AfficherResultat(Liste l, int n){
    int count;
    for(count = 0; l && count < n; count++){
        printf("%s %d\n", l->mot, l->compteur);
        l = l->suivant;
    }
}

void libererListe(Liste *m, InfoMem *info){
    for(; *m; ) {
        MotNode *tmp = *m;
        *m = (*m)->suivant;
        
        size_t taille_mot = strlen(tmp->mot) + 1;
        myFree(tmp->mot, info, taille_mot);
        myFree(tmp, info, sizeof(MotNode));
    }
}

void fusion(Liste *un, Liste *deux){
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

void triFusion(Liste *l){
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

    triFusion(&l1);
    triFusion(&l2);

    fusion(&l1, &l2);
    *l = l1;
}

void ecrireFichier(Liste m, int n, const char *nomFichier){
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

void ecrirePerformances(InfoMem *info, double temps, const char *fichier){
    FILE *f = fopen(fichier, "a"); 
    if (!f) return;
    
    fprintf(f, "%zu,%zu,%zu,%f\n", 
            info->cumul_alloc, 
            info->cumul_desalloc, 
            info->max_alloc, 
            temps);
    
    fclose(f);
}

void algo1(const char *fichierEntree, int n, InfoMem *info, 
           const char *fichierSortie, int afficher){
    
    clock_t debut = clock();
    FILE *f = fopen(fichierEntree, "r");
    if (!f) {
        printf("Erreur ouverture fichier\n");
        return;
    }
    Liste liste = NULL;
    MotFichier(f, &liste, info);
    fclose(f);
    triFusion(&liste);
    clock_t fin = clock();
    double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
    if (afficher) {
        AfficherResultat(liste, n);
    }
    printf("Temps d'exécution : %.6f secondes\n", temps);
    if (fichierSortie) {
        ecrireFichier(liste, n, fichierSortie);
    }
    ecrirePerformances(info, temps, "performances.csv");
    libererListe(&liste, info);
}
