#include <stdio.h>
#include<stdlib.h>

typedef struct {
    int inizio;
    int fine;
} Attivita;



void LISprint(Attivita *val, int *P, int i) {
    if (P[i]==-1) {
        printf("%d %d\n", val[i].inizio,val[i].fine);
        return;
    }
    LISprint(val, P, P[i]);
    printf("%d %d\n", val[i].inizio,val[i].fine);
}

void LISDP(Attivita *val,int N, int lunghezzaOrdinato) {
    int i, j, ricorda, ris = val[0].fine-val[0].inizio, L[N], P[N], last = 1,flag=0;
    L[0] = val[0].fine-val[0].inizio;
    P[0] = -1;
    for (i = 1; i < N; i++) {
        L[i] = val[i].fine-val[i].inizio;
        P[i] = i-1;
        for (j = 0; j < i; j++){

            if(val[i].inizio==val[j].inizio) {
                if (val[j].fine < val[i].fine) {
                    flag = 1;
                    if (L[i] > L[j] && j<lunghezzaOrdinato && (val[i].inizio>=val[j-1].fine)) {

                        ris = ris + L[i] - L[j];
                        P[i] = P[j];
                        if(j!=lunghezzaOrdinato-1){
                            P[j+1] = i;}
                        ricorda=j;

                    }
                }
            }


            else if(val[i].fine==val[j].fine) {
                if (val[j].inizio > val[i].inizio) {
                    flag = 1;
                    if (L[i] > L[j] && j<lunghezzaOrdinato && (val[i].inizio>=val[j-1].fine)) {
                        ris = ris + L[i] - L[j];
                        P[i] = P[j];
                        if(j!=lunghezzaOrdinato-1){
                            P[j+1] = i;}
                        ricorda=j;

                    }
                }
            }

            else if (val[j].inizio<val[i].inizio && val[j].fine>val[i].inizio || val[j].inizio<val[i].fine && val[j].fine>val[i].fine) {
                flag=1;
                if(L[i]>L[j] && j<lunghezzaOrdinato && (val[i].inizio>=val[j-1].fine)){
                ris=ris+L[i]-L[j];
                P[i]=P[j];
                if(j!=lunghezzaOrdinato-1){
                    P[j+1] = i;}


                ricorda=j;


            }
            }
        }

if (flag==0) {
            ris = ris + L[i];
            last = i;
        }
if(flag==1 && ricorda==lunghezzaOrdinato-1){
    last=i;
}

        flag=0;
        ricorda=-1;
    }
    printf("One of the Longest Increasing Sequences is \n");
    LISprint(val, P, last);
    printf("and its length is %d\n", ris);
}

int LISR(Attivita *val, int N, int flag, int lunghezzaOrdinato) {
    int ricorda,ris,x;
    if(flag==0){
        ris=val[0].fine-val[0].inizio;
    }
    if(flag!=0){
        if(val[flag].fine-val[flag].inizio < val[N].fine-val[N].inizio){

            x= (val[N].fine-val[N].inizio) - (val[flag].fine-val[flag].inizio);
            val[flag].fine=val[N].fine;
            val[flag].inizio=val[N].inizio;
            return x;}
        return 0;
    }
    for (int i = 1; i <= N; i++) {

        for (int j = 0; j < i; j++) {

            if(val[i].inizio==val[j].inizio) {
                if (val[j].fine < val[i].fine) {
                    flag=1;
                    if ( j<lunghezzaOrdinato && (val[i].inizio>=val[j-1].fine)){
                    ricorda=N;
                    ris = ris +LISR(val,i,j,lunghezzaOrdinato);
                    N=ricorda;
                    }
                }
            }


            else if(val[i].fine==val[j].fine) {
                if (val[j].inizio > val[i].inizio) {
                    flag=1;
                    if ( j<lunghezzaOrdinato && (val[i].inizio>=val[j-1].fine)){
                        ricorda=N;
                        ris = ris +LISR(val,i,j,lunghezzaOrdinato);
                        N=ricorda;
                    }
                }
            }

            else if (val[j].inizio < val[i].inizio && val[j].fine > val[i].inizio || val[j].inizio < val[i].fine && val[j].fine > val[i].fine){
                flag=1;
                if ( j<lunghezzaOrdinato && (val[i].inizio>=val[j-1].fine)){
                    ricorda=N;
                    ris = ris +LISR(val,i,j,lunghezzaOrdinato);
                    N=ricorda;
                }
            }

        }
        if(flag==0){
            ris=ris+val[i].fine-val[i].inizio;
        }

    }
    return ris;
}


int main() {

    int n;

    FILE *fin;
    if((fin=fopen("att2.txt","r"))==NULL){
        return 1;
    }
    fscanf(fin,"%d",&n);
    Attivita *attivita;
    attivita=malloc(n* sizeof(Attivita));
    for (int i = 0; i < n; i++) {
        fscanf(fin,"%d %d",&attivita[i].inizio, &attivita[i].fine);

    }

    // Ordinamento// // //
    Attivita *vettOrdinato,*vettNonOrdinato;
    vettOrdinato=malloc(n* sizeof(Attivita));
    vettNonOrdinato=malloc(n* sizeof(Attivita));
    int k=0,x=1;

    vettOrdinato[0].inizio=attivita[0].inizio;
    vettOrdinato[0].fine=attivita[0].fine;
    int ricorda=0;

    for (int i = 1; i < n ; i++) {

        if(attivita[i].inizio < attivita[ricorda].fine){
            vettNonOrdinato[k].inizio=attivita[i].inizio;
            vettNonOrdinato[k].fine=attivita[i].fine;
            k++;
        }
        else{
            vettOrdinato[x].inizio=attivita[i].inizio;
            vettOrdinato[x].fine=attivita[i].fine;
            x++;
            ricorda=i;
        }

    }

    int lunghezzaOrdinato=x;



    int y=0;
    for (int i = 0; i < n; i++) {

        if(y<lunghezzaOrdinato){
            attivita[i].inizio=vettOrdinato[i].inizio;
            attivita[i].fine=vettOrdinato[i].fine;
            y++;
        }
        else{
            attivita[i].inizio=vettNonOrdinato[i-y].inizio;
            attivita[i].fine=vettNonOrdinato[i-y].fine;
        }

    }

    for (int i = 0; i < n; i++) {
        printf("%d %d\n",attivita[i].inizio,attivita[i].fine);
    }
    printf("\n");



    int scelta,risultato,flag=0;
    while (scelta!=-1){
    printf("\n1 calcolo del valore ottimo ricorsivo\n2 calcolo della soluzione ottima bottom-up\n");
    scanf("%d",&scelta);
    switch (scelta) {
        case 1:
            risultato=LISR(attivita,n-1,flag,lunghezzaOrdinato);
            printf("il valore ottimo della soluzione e' %d\n",risultato);
            break;

        case 2:
            LISDP(attivita,n,lunghezzaOrdinato);
            break;

        default:
            return 2;

    }

         y=0;
        for (int i = 0; i < n; i++) {

            if(y<lunghezzaOrdinato){
                attivita[i].inizio=vettOrdinato[i].inizio;
                attivita[i].fine=vettOrdinato[i].fine;
                y++;
            }
            else{
                attivita[i].inizio=vettNonOrdinato[i-y].inizio;
                attivita[i].fine=vettNonOrdinato[i-y].fine;
            }

        }

}
    free(vettNonOrdinato);
    free(vettOrdinato);
    free(attivita);




}


// DIMOSTRAZIONE SOTTOSTRUTTURA OTTIMA //

// Un intervallo senza intersezione con altri intervalli nel vettore, è una sottostruttura ottima, perchè se così
// non fosse ci sarebbe un'altra sottostruttura migliore (assurdo perchè non ci sono intersezioni con altri intervalli).