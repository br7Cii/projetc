#include <stdio.h>

typedef struct MotNode {
    char *mot;
    int compteur;
    struct MotNode *suivant;
} MotNode, *Liste;
