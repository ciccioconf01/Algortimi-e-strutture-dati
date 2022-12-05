#include <stdio.h>
#include "grafo.h"
#include "ST.h"

int main() {
    FILE *fin;
    Graph G;
    fin=fopen("g.txt","r");
    G=GraphLoad(G,fin);

    fin=fopen("proposta.txt","r");
    int a=ControllaProposta(fin,G);

    if(a==-1){
        printf("la proposta NON e' valida\n");
    }
    else{
        printf("la proposta e' valida\n");
    }
    int V= ritornaNumVerticiGraph(G);
    int *vettorePartizioni; int *Bsol;
    vettorePartizioni=malloc(V* sizeof(int));
    Bsol=malloc(V* sizeof(int));
    for(int i=0;i<V;i++){
        vettorePartizioni[i]=-1;
        Bsol[i]=-1;
    }
    int pos=0;
    int cardinalita=0;
    SoluzioneOttima(G,V,vettorePartizioni,pos,cardinalita,Bsol);

    int C=controllaCardinalita(Bsol,V);

    for(int i=0;i<C;i++){
        printf("{ ");
        for(int j=0;j<V;j++){
            if(Bsol[j]==i){
                printf("%s, ",GraphSearch(G,j));
            }
        }
        printf("}\n");
    }


}
