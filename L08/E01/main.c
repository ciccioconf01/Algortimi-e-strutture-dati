#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "azioni.h"
#define N 30

int main() {
    FILE *fin;
    info_data d1,d2;
    int dim,i,flag=1,scelta;
    char NomeFile[10]= "F1.txt",NomeTitolo[10];
    InfoPnt x;
    x=malloc(sizeof(InfoPnt));
    LIST L;
    L=ListInit();
    while(flag){
        printf("\nSeleziona una tra le seguenti:"
               "\n1)Acquisizione da file "
               "\n2)Ricerca di un titolo "
               "\n3)Ricerca della quotazione di un titolo PER data. "
               "\n4)Ricerca quotazione minima e massima tra un intervallo di date "
               "\n5)Ricerca della quotazione minima e massima di un titolo. "
               "\n6)Bilanciamento albero se in base alla soglia S "
               "\n7)Fine programma.\n");
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                if((fin=fopen(NomeFile,"r"))==NULL)
                    return -1;
                L=ListLoad(L,fin);
                break;
            case 2:
                printf("Inserire nome titolo che si vuole ricercare:");
                scanf("%s",NomeTitolo);
                x=RicercaTitolo(L,NomeTitolo);
                if(x!=NULL)
                    StampaTitolo(x);
                break;
            case 3:
                printf("Inserire il nome del titolo di cui si vuole trovare la quotazione: ");
                scanf("%s",NomeTitolo);
                RicercaQuotazione(L,NomeTitolo);
                break;
            case 4:
                printf("Inserire nome del titolo: ");
                scanf("%s",NomeTitolo);
                printf("Inserire la prima data (AAAA/M/G): ");
                scanf("%d/%d/%d",&d1.anno,&d1.mese,&d1.giorno);
                printf("Inserire la seconda data (AAAA/M/G): ");
                scanf("%d/%d/%d",&d2.anno,&d2.mese,&d2.giorno);
                CercaDate(L,NomeTitolo,d1,d2);
                break;
            case 5:
                printf("Inserire nome del titolo: ");
                scanf("%s",NomeTitolo);
                CercaMaxMin(L,NomeTitolo);
                break;
            case 6:Bilanciamento(L);break;
            case 7:flag=0;break;
            default:printf("inserire valori accettabili!");break;
        }
    }
    return 0;
}

