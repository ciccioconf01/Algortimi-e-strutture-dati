#include <stdio.h>
#include "Graph.h"

int main() {
    Graph G;
    FILE *fin;
    int scelta;
    int flag=1,FLAGlista=0;
    while(flag){
        printf("\n\nSelezionare una delle seguenti opzioni:"
               "\n1 Caricare il grafo"
               "\n2 Stampare i vertici del grafo e relativi archi in ordine alfabetico"
               "\n3 Stampare la matrice delle adiacenze"
               "\n4 Creare la lista delle adiacenze "
               "\n5 Dati 3 vertici, controllare che formino un sottografo completo"
               "\n6 Stampare la lista delle adiacenze"
               "\n7 Termina programma\n");
        scanf("%d",&scelta);
        switch(scelta){
            case 1:
                G=GRAPHload(fin);
                break;
            case 2:
                GraphPrint(G);
                break;
            case 3:
                Stampamatrice(G);
                break;
            case 4:
                CreaLista(G);
                FLAGlista=1;
                break;
            case 5:
                ControllaVertice(G);
                break;
            case 6:
                if(FLAGlista==1)
                    PrintLista(G);
                else printf("\nLista non inizializzata!");
                break;
            case 7:
                flag=0;
                break;
            default:
                printf("\nInserire un nome corretto!");
                break;
        }
    }
    return 0;
}