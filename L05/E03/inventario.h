//
// Created by User on 22/11/2021.
//

#ifndef LAB_5_ESERCIZIO_3_INVENTARIO_H
#define LAB_5_ESERCIZIO_3_INVENTARIO_H

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat;

typedef struct {
    char nome[50];
    char tipo[50];
    stat statistiche;
}Inventario;

Inventario *leggiInventario(Inventario *inventario, int *nInventario);
void stampainventario(Inventario *inventario,int n);
Inventario ricerca_per_nome(Inventario *inventario, int nInventario, char *codice);
void stampaOggetto(Inventario *inventario, int i);

#endif //LAB_5_ESERCIZIO_3_INVENTARIO_H
