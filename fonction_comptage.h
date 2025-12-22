typedef struct MotNode {
    char *mot;
    size_t compteur;
    struct MotNode *suivant;
} MotNode;