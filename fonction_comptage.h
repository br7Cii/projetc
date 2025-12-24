typedef struct MotNode {
    char * mot;
    size_t compteur;
    struct MotNode *suivant;
} MotNode, *Liste;


int recherche (Liste * m, char * mot);
int creation(Liste *m, char *mot);
void fusion(Liste *un, Liste *deux);
void triFusion(Liste *l);
