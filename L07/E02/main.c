#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[100];             //nome
    int tipologia;              //2 avanti, 1 indietro, 0 transizione
    int direzione_ingresso;     //1 frontalmente, 0 spalle
    int direzione_uscita;       //1 frontalmente, 0 spalle
    int precedenza;             //0 può essere primo in sequenza, 1 non può essere primo in sequenza
    int finale;                 //1 è l'ultimo elemento per forza, 0 può non essere l'ultimo per forza
    float valore;                 //punteggio corretta esecuzione
    int difficolta;             //difficolta esercizio
}diagonale;


void Merge(diagonale *A, diagonale *B, int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q+1;
    for(k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if(A[i].valore>A[j].valore)
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
    return;
}

void MergeSortR(diagonale *A, diagonale *B, int l, int r) {
    int q;
    if (r <= l)
        return;
    q = (l + r)/2;
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q+1, r);
    Merge(A, B, l, q, r);
}

void MergeSort(diagonale *A, int N) {
    int l=0, r=N-1;
    diagonale *B = (diagonale *)malloc(N*sizeof(diagonale));
    if (B == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    MergeSortR(A, B, l, r);
}

int obb1(diagonale *dizionario, int n, diagonale *soluzione, int DDtmp, int DPtmp){
    int is = 0;
    for (int i = n-1; i >= 0; i--) {
        if (dizionario[i].difficolta <= DDtmp && dizionario[i].difficolta <= DPtmp) {
            if (is == 0) {
                if (dizionario[i].precedenza == 0 && dizionario[i].direzione_ingresso == 1 && dizionario[i].tipologia==2) {
                    soluzione[is] = dizionario[i];
                    DDtmp = DDtmp - dizionario[i].difficolta;
                    DPtmp = DPtmp - dizionario[i].difficolta;
                    is++;
                    i=n-1;
                }
            } else if(is==1){
                if (dizionario[i].direzione_ingresso == soluzione[is-1].direzione_uscita && dizionario[i].tipologia==2) {
                    soluzione[is] = dizionario[i];
                    DDtmp = DDtmp - dizionario[i].difficolta;
                    DPtmp = DPtmp - dizionario[i].difficolta;
                    is++;
                    if(dizionario[i].finale==1){
                        i=0;
                    }
                    else{i = n-1;}
                }
            }
        }
    }
    for(int i = 0;i<n;i++){
            if (dizionario[i].direzione_ingresso == soluzione[is-1].direzione_uscita && dizionario[i].difficolta <= DDtmp && dizionario[i].difficolta <= DPtmp) {
                soluzione[is] = dizionario[i];
                DDtmp = DDtmp - dizionario[i].difficolta;
                DPtmp = DPtmp - dizionario[i].difficolta;
                is++;
                if(dizionario[i].finale==1){
                    i=n-1;
                }
                else{i =-1;}
            }

    }
    return is;
};

int obb2(diagonale *dizionario, int n, diagonale *soluzione, int DDtmp, int DPtmp){
    int is = 0;
    for (int i = n-1; i>=0; i--) {
        if (dizionario[i].difficolta <= DDtmp && dizionario[i].difficolta <= DPtmp) {
            if (is == 0) {
                if (dizionario[i].precedenza == 0 && dizionario[i].direzione_ingresso == 1) {
                    soluzione[is] = dizionario[i];
                    DDtmp = DDtmp - dizionario[i].difficolta;
                    DPtmp = DPtmp - dizionario[i].difficolta;
                    is++;
                    i=n-1;
                }
            } else if(is==1) {
                if (dizionario[i].direzione_ingresso == soluzione[is - 1].direzione_uscita &&
                    dizionario[i].tipologia == 1) {
                    soluzione[is] = dizionario[i];
                    DDtmp = DDtmp - dizionario[i].difficolta;
                    DPtmp = DPtmp - dizionario[i].difficolta;
                    is++;
                    if (dizionario[i].finale == 1) {
                        i = 0;
                    } else { i = n - 1; }
                }
            }
        }
    }
    for(int i = 0; i< n ; i++) {

            if (dizionario[i].direzione_ingresso == soluzione[is-1].direzione_uscita && dizionario[i].difficolta <= DDtmp && dizionario[i].difficolta <= DPtmp) {
                soluzione[is] = dizionario[i];
                DDtmp = DDtmp - dizionario[i].difficolta;
                DPtmp = DPtmp - dizionario[i].difficolta;
                is++;
                if(dizionario[i].finale==1){
                    i=n+1;
                }
                else{i = -1;}
            }
    }
    return is;
};

int obb3(diagonale *dizionario, int n, diagonale *soluzione, int DDtmp, int DPtmp){
    int is = 0;
    for (int i = n-1; i >= 0; i--) {
        if (dizionario[i].difficolta <= DDtmp && dizionario[i].difficolta <= DPtmp) {
            if (is == 0) {
                if (dizionario[i].precedenza == 0 && dizionario[i].direzione_ingresso == 1) {
                    soluzione[is] = dizionario[i];
                    DDtmp = DDtmp - dizionario[i].difficolta;
                    DPtmp = DPtmp - dizionario[i].difficolta;
                    is++;
                    i=n-1;
                }
            }
        }
    }
    for(int i = 0;i<n;i++){
        if (dizionario[i].direzione_ingresso == soluzione[is-1].direzione_uscita && dizionario[i].difficolta <= DDtmp && dizionario[i].difficolta <= DPtmp) {
            soluzione[is] = dizionario[i];
            DDtmp = DDtmp - dizionario[i].difficolta;
            DPtmp = DPtmp - dizionario[i].difficolta;
            is++;
            if(dizionario[i].finale==1){
                i=n-1;
            }
            else{i =-1;}
        }

    }
    return is;
};

int main() {
    diagonale *dizionario;
    int n, DD = 10, DP = 20;
    FILE *fin;
    fin = fopen("elementi.txt", "r");
    if (fin == NULL) {
        printf("Errore apertura file\n");
        return 1;
    }
    fscanf(fin, "%d", &n);
    dizionario = malloc(n * sizeof(diagonale));
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%s %d %d %d %d %d %f %d", dizionario[i].nome, &dizionario[i].tipologia,
               &dizionario[i].direzione_ingresso, &dizionario[i].direzione_uscita, &dizionario[i].precedenza,
               &dizionario[i].finale, &dizionario[i].valore, &dizionario[i].difficolta);
    }
    //printf("Inserire DD e DP\n");
    //scanf("%d %d",&DD,&DP);
    MergeSort(dizionario, n);
    diagonale *soluzione;
    soluzione = malloc(5 * sizeof(diagonale));
    int is = 0;
    int flag = 0;
    int DDtmp = DD, DPtmp = DP;
    for (int j = 0; j < 3; j++) {
        if (j == 0){
            DDtmp = (DP - DD)/2;
            if(DDtmp<6 && DD>6){
                DDtmp=6;
                flag=1;
            }
            else if (DDtmp > DD){
                DDtmp = DD;
            }
            is = obb1(dizionario,n,soluzione,DDtmp,DPtmp);
        }
        if(j == 1){
            DDtmp = (DP - DD)/2;
            if(flag == 1){
                DDtmp=DP-DD-6;
            }
            else if (DDtmp > DD){
                DDtmp = DD;
            }
            is = obb2(dizionario,n,soluzione,DDtmp,DPtmp);
        }
        if (j == 2) {
            DDtmp = DP - DD;
            if (DDtmp > DD) {
                DDtmp = DD;
            }
            is = obb3(dizionario,n,soluzione,DDtmp,DPtmp);
        }
        for (int i = 0; i < is; i++) {
            printf("%s %d %d %d %d %d %.2f %d\n", soluzione[i].nome, soluzione[i].tipologia,
                   soluzione[i].direzione_ingresso, soluzione[i].direzione_uscita, soluzione[i].precedenza,
                   soluzione[i].finale, soluzione[i].valore, soluzione[i].difficolta);
        }
        printf("\n");
        is = 0;
    }
}