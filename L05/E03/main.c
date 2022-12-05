#include <stdio.h>
#include "personaggi.h"

int main() {
    int scelta,x=1;
    pg personaggio;
    link h=NULL;
    int nInventario;
    Inventario *inventario;
    while (x==1){
        printf("Inserire:\n1 per caricare in una lista i personaggi da file\n"
               "2 per caricare in un vettore di struct l'inventario degli oggetti\n"2
               "3 per aggiungere un personaggio\n4 per eliminare un personaggio\n"
               "5 per aggiungere un oggetto all' equipaggiamento di un personaggio\n"
               "6 per rimuovere un oggetto dall' equipaggiamento di un personaggio\n"
               "7 per aggiornare le statistiche dopo il caricamento di un equipaggiamento\n"
               "8 stampa\n9 per concludere\n");
        scanf("%d",&scelta);
        switch(scelta){
            case 1:
                h = caricafile(h);
                break;
            case 2:
                inventario=leggiInventario(inventario,&nInventario);
                break;
            case 3:
                printf("inserisci il nuovo personaggio\n");
                scanf("%s %s %s %d %d %d %d %d %d",personaggio.codice,personaggio.nome,personaggio.classe,&personaggio.statistiche.hp,&personaggio.statistiche.mp,&personaggio.statistiche.atk,&personaggio.statistiche.def,&personaggio.statistiche.mag,&personaggio.statistiche.spr);
                h=inserimento_in_coda(h,personaggio);
                break;
            case 4:
                printf("inserisci il codice del personaggio da eliminare\n");
                scanf("%s",personaggio.codice);
                h=cancellazione_per_codice(h,personaggio.codice);
                break;
            case 5:
                aggiungi_oggetto(inventario,nInventario,h);

                break;
            case 6:
                eliminaOggetto(h,inventario,nInventario);

                break;

            case 7:
                cntstat(h);
                break;

                case 8:
                Stampapg(h);
                break;
            case 9:
                return 1;
        }
    }
}
