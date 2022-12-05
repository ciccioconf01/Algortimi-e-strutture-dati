#include <stdio.h>
#include "grafo.h"

int main() {
    FILE *fin;

    char vertice;
    Graph G;
    fin=fopen("grafo.txt","r");
    G = GraphLoad(G,fin);

    fin=fopen("proposta.txt","r");
    int V=ritornaV(G);
    int *proposta;

    proposta = malloc(V * sizeof(int));
    for(int i=0;i<V;i++){
        proposta[i]=-1;
    }

    int i=0;
    while (!feof(fin)){
        fscanf(fin,"%c\n",&vertice);
        proposta[i] = Acquisisci(G,vertice);
        i++;
    }
    int a=VerificaProposta(G,proposta);

    if(a==-1){
        printf("la proposta NON e' valida\n");
    }
    else{
        printf("la proposta e' valida\n");
    }

    int *sol,*Bsol, *solTrad;
    sol=malloc(V* sizeof(int));
    Bsol=malloc(V* sizeof(int));
    solTrad=malloc(V* sizeof(int));

    for(int i=0;i<V;i++){
        sol[i]=-1; Bsol[i]=-1; solTrad[i]=-1;
    }
    int pos=0; int min=10000;
    int terminazione=2;

    min = kernelMinimo(G,pos,sol,Bsol,min,solTrad);

    printf("La soluzione ottima ha cardinalita':%d, ed e' composta da:\n",min);

    for(int i=0;i<V;i++){
        if(Bsol[i]!=-1){
            printf("%c ",GraphSearch(G,i));
        }
    }
    printf("\n");

    int lunghezza=0;int max=0;
    int cardinalita=Lvet(Bsol,V);
    int pos2;
    int *vetPassati;
    vetPassati=malloc(V* sizeof(int));
    for(int i=0;i<V;i++){
        vetPassati[i]=-1;
    }

    for(int pos=0;i<V;i++){
        vetPassati[pos] = 1;
        lunghezza = MigliorCammino(G,Bsol,lunghezza,&max,pos,vetPassati,min);
    }

    printf("la lunghezza del cammino semplice che copre il maggior numero di vertici kernel e' :%d",lunghezza);






}
