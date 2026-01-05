#ifndef FONCTION_ALLOCATION_H
#define FONCTION_ALLOCATION_H

#include <stddef.h>

typedef struct {
    size_t cumul_alloc;    // champ obligatoire : cumul de l'espace mémoire alloué
    size_t cumul_desalloc; // champ obligatoire : cumul de l'espace mémoire
                           // désalloué
    size_t max_alloc;      // pic d'allocation (diff max des deux cumuls)

} InfoMem;

void Init(InfoMem * infoMem); 
// Initialise la structure InfoMem pour la gestion de la mémoire.

void *myMalloc(size_t size, InfoMem *infoMem); 
// Alloue dynamiquement un bloc de mémoire de taille 'size'. 
// Retourne un pointeur vers le bloc alloué.
 
void *myRealloc(void *ptr, size_t new_size, InfoMem *infoMem, size_t old_size);
// Redimensionne un bloc de mémoire précédemment alloué.
// 'old_size' est la taille précédente du bloc.
// Retourne un pointeur vers le nouveau bloc (peut être différent).
 
void myFree(void *ptr, InfoMem *infoMem, size_t old_size);
// Libère un bloc de mémoire précédemment alloué.
// 'old_size' est la taille du bloc à libérer.

#endif // FONCTION_ALLOCATION_H
