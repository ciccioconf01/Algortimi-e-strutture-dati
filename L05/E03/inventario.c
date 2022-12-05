//
// Created by User on 22/11/2021.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "inventario.h"



Inventario *leggiInventario(Inventario *inventario, int *nInventario){
    FILE *fin;
    int n;

    fin=fopen("inventario.txt","r");
    fscanf(fin,"%d",&n);

    inventario=malloc(n* sizeof(Inventario));
    for(int i=0;i<n;i++){
        fscanf(fin,"%s %s %d %d %d %d %d %d",inventario[i].nome,inventario[i].tipo,&inventario[i].statistiche.hp,&inventario[i].statistiche.mp,&inventario[i].statistiche.atk,&inventario[i].statistiche.def,&inventario[i].statistiche.mag,&inventario[i].statistiche.spr);
    }
    *nInventario=n;

    return inventario;

}

void stampainventario(Inventario *inventario,int n){
    for (int i = 0; i < n; i++) {
        printf("%s %s %d %d %d %d %d %d\n",inventario[i].nome,inventario[i].tipo,inventario[i].statistiche.hp,inventario[i].statistiche.mp,inventario[i].statistiche.atk,inventario[i].statistiche.def,inventario[i].statistiche.mag,inventario[i].statistiche.spr);

    }

}

Inventario ricerca_per_nome(Inventario *inventario, int nInventario, char *codice){
    for (int i = 0; i < nInventario; i++) {

        if(strcmp(inventario[i].nome,codice)==0){


            return inventario[i];
        }

    }
}

void stampaOggetto(Inventario *inventario, int i){
    printf("%s %s %d %d %d %d %d %d\n",inventario[i].nome,inventario[i].tipo,inventario[i].statistiche.hp,inventario[i].statistiche.mp,inventario[i].statistiche.atk,inventario[i].statistiche.def,inventario[i].statistiche.mag,inventario[i].statistiche.spr);

}


