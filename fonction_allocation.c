#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include <ctype.h>
#include "fonction_allocation.h"


void Init(InfoMem * infoMem){
    infoMem->cumul_alloc = 0;
    infoMem->cumul_desalloc = 0;
    infoMem->max_alloc = 0;
}

void *myMalloc(size_t size, InfoMem *infoMem) {
    void * ptr = malloc(size);
    if (!ptr){
        printf("Erreur d'allocation\n");
        return NULL;
    }

    infoMem->cumul_alloc += size;
    size_t courant = infoMem->cumul_alloc - infoMem->cumul_desalloc;
    if (courant > infoMem->max_alloc){
        infoMem->max_alloc = courant;
    }
    return ptr;
}

void *myRealloc(void *ptr, size_t new_size, InfoMem *infoMem, size_t old_size){
    void * nouv_ptr = realloc(ptr, new_size);
    if(!nouv_ptr){
        printf("Erreur d'allocation");
        return NULL;
    }
    if (nouv_ptr == ptr){
        if(new_size > old_size){
            infoMem->cumul_alloc += (new_size - old_size);
        }
        else if(new_size < old_size){
            infoMem->cumul_desalloc += (old_size - new_size);
        }
    }
    else {
        infoMem->cumul_alloc += new_size;
        infoMem->cumul_desalloc += old_size;
    }
    size_t courant = infoMem->cumul_alloc - infoMem->cumul_desalloc;
    if (courant > infoMem->max_alloc){
        infoMem->max_alloc = courant;
    }
    return nouv_ptr;
}

void myFree(void *ptr, InfoMem *infoMem, size_t old_size){
    if(!ptr){
        return;
    }
    free(ptr);
    infoMem->cumul_desalloc += old_size;
}
