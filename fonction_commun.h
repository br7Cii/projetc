#ifndef FONCTION_COMMUN_H
#define FONCTION_COMMUN_H

typedef struct MotNode {
    char *mot;
    int compteur;
    struct MotNode *suivant;
} MotNode, *Liste;

#endif 