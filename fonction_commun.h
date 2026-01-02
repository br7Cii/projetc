#ifndef FONCTION_COMMUN_H
#define FONCTION_COMMUN_H

#include <stdio.h>

typedef struct MotNode {
    char *mot;
    int compteur;
    struct MotNode *suivant;
} MotNode, *Liste;

#endif // FONCTION_COMMUN_H
