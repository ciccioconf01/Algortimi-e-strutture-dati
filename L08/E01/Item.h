#ifndef LISTAPROVA_ITEM_H
#define LISTAPROVA_ITEM_H

#include <stdio.h>
#include "date.h"
#define MAXC 11

typedef struct {
    float num;
    float den;
    info_data data;
} Item;

Item    ITEMsetNull();//inizializza un ITEM nullo
int     ITEMcheckNull(Item val);//controlla che un item sia nullo
void    ITEMstore(Item val);
int     KEYcmp(info_data k1, info_data k2);//0: uguali;1: k1>k2;-1:k2>k1
info_data     KEYget(Item val);

#endif //LISTAPROVA_ITEM_H