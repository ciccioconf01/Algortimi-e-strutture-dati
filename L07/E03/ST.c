#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"


struct symboltable {
    Item *a;
    int maxN;
    int size;
};

Item ITEMsetvoid(){
    Item x;
    strcpy(x.id_rete,"NULL");
    strcpy(x.id_elab,"NULL");
    return x;
}

ST STinit(int maxN) {
    ST st;
    st = malloc(sizeof (*st));
    if (st == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    st->a = calloc(maxN, sizeof(Item));
    if (st->a == NULL) {
        printf("Memory allocation error\n");
        free(st);
        return NULL;
    }
    for (int i=0;i<maxN;i++){
        st->a[i]=ITEMsetvoid();}

    st->maxN = maxN;
    st->size = 0;
    return st;
}

void STfree(ST st){
    if(st==NULL)
        return;
    free(st->a);
    free(st);
}

int STsize(ST st) {
    return st->size;
}

void STinsert(ST st, char *x,char *y) {
    strcpy(st->a[st->size].id_elab,x);
    strcpy(st->a[st->size].id_rete,y);
    st->size++;
}

int STsearch(ST st, char *str) {
    int i;
    for (i=0; i <st->size; i++){
        if (strcmp("NULL", st->a[i].id_elab)!=0 && strcmp(str, st->a[i].id_elab)==0)
            return i;
    }
    return -1;
}

char *STsearchByIndex(ST st, int i){
    if (i < 0 || i >= st->size)
        return NULL;
    return (st->a[i].id_elab);
}

Item GetItem(ST st, int i){
    if (i < 0 || i >= st->size)
        exit(1);
    return st->a[i];
}