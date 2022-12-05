#ifndef INVARRAY_H_DEFINED
#define INVARRAY_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"

/* ADT di prima classe collezione di oggetti di inventario */
typedef struct invArray_s *invArray_t;

/* creatore e disruttore */
invArray_t invArray_init(int n);
void invArray_free(invArray_t invArray);

/* lettura e scrittura su file */
invArray_t invArray_read(FILE *fp,invArray_t invArray,int n);
void invArray_print(FILE *fp, invArray_t invArray,int n);
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t *invArray, int index);
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
invArray_t invArray_getByIndex(invArray_t invArray, int index);
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name);

/* Si possono aggiungere altre funzioni se ritenute necessarie */
int leggiN(FILE *fp);
#endif
