#include "invArray.h"
#include <string.h>

typedef struct invArray_s{
    inv_t inv;
};

invArray_t invArray_init(int n){
    invArray_t x;
    x = malloc(n*sizeof (inv_t));
    return x;
}

void invArray_free(invArray_t invArray){
    free(invArray);
}

invArray_t invArray_read(FILE *fp,invArray_t invArray,int n){

    inv_t inv;
    int i;
    invArray=invArray_init(n);
    for ( i = 0; i < n; i++){
        invArray[i].inv=inv_read(fp,inv);

    }
    return invArray;
}

int leggiN(FILE *fp){
    int n;
    fscanf(fp,"%d",&n);
    return n;
}

void invArray_print(FILE *fp, invArray_t invArray, int n){
    int i;
    for (i = 0; i < n ; i++){
        inv_print(fp, invArray+i);
    }

}

void invArray_printByIndex(FILE *fp, invArray_t *invArray, int index){
    inv_print(fp,invArray[index]);
}

struct invArray_s * invArray_getByIndex(invArray_t invArray, int index){
    return &invArray[index];
}

int invArray_searchByName(invArray_t invArray, char *name){
    int trovato = 0;
    int i=0;
    while (trovato == 0){
        if(strcmp(name,invArray[i].inv.nome)==0){
            return i;
        }
        i++;
    }
}

