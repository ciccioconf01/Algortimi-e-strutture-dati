#include "personaggi.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



link caricafile(link h){
    FILE *fin;
    pg personaggio;

    fin=fopen("pg.txt","r");
    while (!feof(fin)){
        fscanf(fin,"%s",personaggio.codice);
        fscanf(fin,"%s",personaggio.nome);
        fscanf(fin,"%s",personaggio.classe);
        fscanf(fin,"%d %d %d %d %d %d",&personaggio.statistiche.hp,&personaggio.statistiche.mp,&personaggio.statistiche.atk,&personaggio.statistiche.def,&personaggio.statistiche.mag,&personaggio.statistiche.spr);
        h = inserimento_in_coda(h,personaggio);
    }

    return h;
}

link newNode(pg val, link successivo ) {
    link x=malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        strcpy(x->val.codice,val.codice);
        strcpy(x->val.nome,val.nome);
        strcpy(x->val.classe,val.classe);
        x->val.statistiche.hp=val.statistiche.hp;
        x->val.statistiche.mp=val.statistiche.mp;
        x->val.statistiche.atk=val.statistiche.atk;
        x->val.statistiche.def=val.statistiche.def;
        x->val.statistiche.mag=val.statistiche.mag;
        x->val.statistiche.spr=val.statistiche.spr;

        for (int i = 0; i < 8; i++) {
            x->val.vet[i]=NULL;
        }

        x->successivo = successivo;
    }
    return x;
}

void Stampapg(link h) {

    link x;
    x=h;

    char flag='f';

    while(x!=NULL) {
        printf("%s %s %s %d %d %d %d %d %d\n", x->val.codice, x->val.nome, x->val.classe, x->val.statistiche.hp, x->val.statistiche.mp, x->val.statistiche.atk, x->val.statistiche.def, x->val.statistiche.mag, x->val.statistiche.spr);
        printf("oggetti equipaggiati:\n");
        for (int i = 0; i < 8; i++) {
            if(x->val.vet[i]!=NULL){
                printf("%s\n",x->val.vet[i]->nome);
                flag='t';
            }
        }
        if(flag=='f'){
            printf("nessun oggetto equipaggiato\n");
        }
        x=x->successivo;
    }
    printf("\n");
}




link inserimento_in_coda(link h,pg val) {
    link x;
    if (h==NULL) {
        return newNode(val,NULL);
    }
    for(x=h; x->successivo!=NULL; x=x->successivo);
    x->successivo=newNode(val,NULL);
    return h;
}

link cancellazione_per_codice(link h,char *codice) {
    link x, p;

    for (x=h, p=NULL; x!=NULL; p=x, x=x->successivo) {
        if (strcmp(x->val.codice, codice) == 0){
            if (h==x){
                h=h->successivo;

            }
            else{
                p->successivo = x->successivo;
            }

        }
    }

    return h;

}

link ricerca(link lista, char *codice){

    if(lista != NULL){
        while(lista != NULL){
            if(strcmp(codice,lista->val.codice)==0) {
                return lista;
            }
            lista = lista -> successivo;
        }
        printf("Elemento non trovato\n");
    }
    else {
        printf("LISTA VUOTA \n");
    }
}

void aggiungi_oggetto(Inventario *inventario, int nInventario,link h){
    char codice[7];
    link lista = h;
    char scelta[50];
    printf("Inserire il codice del personaggio\n");
    scanf("%s",codice);
    if(lista != NULL){
        while(lista != NULL){
            if(strcmp(codice,lista->val.codice)==0) {
                printf("Inserire il nome dell'equipaggiamento da aggiungere:\n");
                scanf("%s",scelta);
                for(int i = 0;i<nInventario;i++){
                    if(strcmp(scelta,inventario[i].nome)==0){
                        for (int j = 0; j < 8; ++j) {
                            if(lista->val.vet[j]==NULL){
                                lista->val.vet[j]=&inventario[i];
                                break;
                            }
                        }
                        break;
                    }
                }
                return;
            }
            lista = lista -> successivo;
        }
        printf("Personaggio non trovato\n");
    }


}

void cntstat(link personaggitesta){
    while(personaggitesta!=NULL) {
        int cnthp=0,cntmp=0,cntatk=0,cntdef=0,cntmag=0,cntspr=0;
        for(int i = 0;i < 8 ; i++){
            if(personaggitesta->val.vet[i]!=NULL){
                cnthp = cnthp + personaggitesta->val.vet[i]->statistiche.hp;
                cntmp = cntmp + personaggitesta->val.vet[i]->statistiche.mp;
                cntatk = cntatk + personaggitesta->val.vet[i]->statistiche.atk;
                cntdef = cntdef + personaggitesta->val.vet[i]->statistiche.def;
                cntmag = cntmag + personaggitesta->val.vet[i]->statistiche.mag;
                cntspr = cntspr + personaggitesta->val.vet[i]->statistiche.spr;
            }
        }
        if((cnthp+personaggitesta->val.statistiche.hp) < 0) cnthp = -personaggitesta->val.statistiche.hp;
        if((cntmp+personaggitesta->val.statistiche.mp) < 0) cntmp = -personaggitesta->val.statistiche.mp;
        if((cntatk+personaggitesta->val.statistiche.atk) < 0) cntatk = -personaggitesta->val.statistiche.atk;
        if((cntdef+personaggitesta->val.statistiche.def) < 0) cntdef = -personaggitesta->val.statistiche.def;
        if((cntmag+personaggitesta->val.statistiche.mag) < 0) cntmag = -personaggitesta->val.statistiche.mag;
        if((cntspr+personaggitesta->val.statistiche.spr) < 0) cntspr = -personaggitesta->val.statistiche.spr;
        printf("%s %s %s %d %d %d %d %d %d\n", personaggitesta->val.codice, personaggitesta->val.nome, personaggitesta->val.classe, personaggitesta->val.statistiche.hp + cnthp, personaggitesta->val.statistiche.mp + cntmp, personaggitesta->val.statistiche.atk + cntatk, personaggitesta->val.statistiche.def + cntdef, personaggitesta->val.statistiche.mag + cntmag, personaggitesta->val.statistiche.spr + cntspr);
        personaggitesta=personaggitesta->successivo;
    }
    printf("\n");
}

void eliminaOggetto(link h,Inventario *inv, int n){
    char codice[7];
    link lista = h;
    char scelta[50];
    printf("Inserire il codice del personaggio:\n");
    scanf("%s",codice);
    while(lista != NULL){
        if(strcmp(codice,lista->val.codice)==0) {
            printf("Personaggio:\n%s %s %s %d %d %d %d %d %d\n\n", lista->val.codice,lista->val.nome,lista->val.classe,lista->val.statistiche.hp,lista->val.statistiche.mp,lista->val.statistiche.atk,lista->val.statistiche.def,lista->val.statistiche.mag,lista->val.statistiche.spr);
            for(int i = 0;i < 8 ; i++){
                if(lista->val.vet[i]!=NULL){
                    printf("|->%s %s %d %d %d %d %d %d\n",lista->val.vet[i]->nome,lista->val.vet[i]->tipo,lista->val.vet[i]->statistiche.hp,lista->val.vet[i]->statistiche.mp,lista->val.vet[i]->statistiche.atk,lista->val.vet[i]->statistiche.def,lista->val.vet[i]->statistiche.mag,lista->val.vet[i]->statistiche.spr);
                }
            }
            printf("\n");
            printf("Inserire il nome dell'equipaggiamento da eliminare:\n");
            scanf("%s",scelta);
            for(int i = 0;i<n;i++) {
                if(strcmp(scelta,lista->val.vet[i]->nome)==0){
                    lista->val.vet[i]=NULL;
                    break;
                }
            }
            return;
        }
        lista = lista -> successivo;
    }
}

