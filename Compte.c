#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdderf.h>
#include <ctype.h>
#include "fonction_comptage.h"

int recherche(Liste *m, char *mot) {
    for(; *m; m = &((*m)->suivant)) {
        if(strcmp((*m)->mot, mot) == 0) {
            (*m)->compteur++;
            return 1; 
        }
    }
    return 0;
}

int creation(Liste *m, char *mot, InfoMem *info) {  
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

void MotFichier(FILE *Fichier, Liste *l, InfoMem *info) { 
    char c;  
    while ((c = fgetc(Fichier)) != EOF) {
        char *mot = NULL; 
        int len = 0;

        while(c != ' ' && c != '\n' && c != EOF && (isalpha(c) || c == '-')) {
            len++;
            mot = myRealloc(mot, len + 1, info, len);  
            if (mot == NULL) {
                return;  
            }
            mot[len - 1] = c;
            c = fgetc(Fichier); 
        }
        
        if (len > 0) {
            mot[len] = '\0';  
            if (!recherche(l, mot)) {  
                creation(l, mot, info); 
            }
            myFree(mot, info, len + 1);  
        }
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

void triFusion(Liste *lst){
    if (*lst == NULL || (*lst)->suivant == NULL)
        return;

    Liste l1, l2;
    MotNode *lent = *lst;
    MotNode *rapide = (*lst)->suivant;
    for (; rapide && rapide->suivant;){
        lent = lent->suivant;
        rapide = rapide->suivant->suivant;
    }

    l1 = *lst;
    l2 = lent->suivant;
    lent->suivant = NULL;

    triFusion(&l1);
    triFusion(&l2);

    fusion(&l1, &l2);
    *lst = l1;
}
