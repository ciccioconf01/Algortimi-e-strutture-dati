#ifndef ST_H
#define ST_H

typedef struct{
    char id_elab[30];
    char id_rete[30];
}Item;

typedef struct symboltable *ST;

ST    STinit(int maxN);
void  STfree(ST st);
int   STsize(ST st);
void  STinsert(ST st, char *x, char *y);
int   STsearch(ST st, char *str);
char *STsearchByIndex(ST st, int i);
Item ITEMsetvoid();
Item GetItem(ST st, int i);
#endif
