//
// Created by User on 22/11/2021.
//

#ifndef LAB_5_ESERCIZIO_3_PERSONAGGI_H
#define LAB_5_ESERCIZIO_3_PERSONAGGI_H

#include "inventario.h"

typedef struct{
    char codice[7];
    char nome[50];
    char classe[50];
    Inventario *vet[8];
    stat statistiche;
}pg;

typedef struct node *link;
struct node{
    pg val;
    link successivo;
};

link newNode(pg val, link h);
link caricafile(link h);
link inserimento_in_coda(link h,pg val);
void Stampapg(link h);
link ricerca(link h,char *codice);
link cancellazione_per_codice(link h,char *codice);
void aggiungi_oggetto(Inventario *inventario, int nInventario, link h);
void eliminaOggetto(link h,Inventario *inv, int n);
void cntstat(link personaggitesta);

#endif //LAB_5_ESERCIZIO_3_PERSONAGGI_H
