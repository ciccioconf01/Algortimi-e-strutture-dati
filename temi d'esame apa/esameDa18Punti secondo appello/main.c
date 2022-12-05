#include <stdio.h>
#include <stdlib.h>

int Controlla_e_Calcola(int **proposta, int **mat,int nr,int nc, int terminazione){
    int i=0;int j=0; int val=3; char direzione; int contaCambi=0;
    if(proposta[i+1][j]==val){
        direzione='s';
        i = i+1;
    }
    if(proposta[i][j+1]==val){
        direzione='e';
        j = j+1;
    }
    val++;
    while (val!=terminazione+1){
        if(i+1>=0 && i+1<=nr-1 && proposta[i+1][j]==val){
            if(direzione != 's'){
                contaCambi++;
                direzione='s';
            }
            i++;
            val++;
        }
        else if(j+1>=0 && j+1<=nc-1 && proposta[i][j+1]==val){
            if(direzione != 'e'){
                contaCambi++;
                direzione='e';
            }
            j++;
            val++;
        }
        else if(i-1>=0 && i-1<=nr-1 && proposta[i-1][j]==val){
            if(direzione != 'n'){
                contaCambi++;
                direzione='n';
            }
            i--;
            val++;
        }
        else if(j-1>=0 && j-1<=nc-1 && proposta[i][j-1]==val){
            if(direzione != 'o'){
                contaCambi++;
                direzione='o';
            }
            j--;
            val++;
        }
        else{
            return -1; // spostamento in diagonale
        }

        if(mat[i][j]==1){
            return -1; // si è oltrepassato un confine nero
        }
    }
    return contaCambi;



}

int Controlla_e_Calcola2(int **proposta, int nr,int nc, int terminazione){
    int i=0;int j=0; int val=3; char direzione; int contaCambi=0;
    if(proposta[i+1][j]==val){
        direzione='s';
        i = i+1;
    }
    if(proposta[i][j+1]==val){
        direzione='e';
        j = j+1;
    }
    val++;
    while (val!=terminazione+1){
        if(i+1>=0 && i+1<=nr-1 && proposta[i+1][j]==val){
            if(direzione != 's'){
                contaCambi++;
                direzione='s';
            }
            i++;
            val++;
        }
        else if(j+1>=0 && j+1<=nc-1 && proposta[i][j+1]==val){
            if(direzione != 'e'){
                contaCambi++;
                direzione='e';
            }
            j++;
            val++;
        }
        else if(i-1>=0 && i-1<=nr-1 && proposta[i-1][j]==val){
            if(direzione != 'n'){
                contaCambi++;
                direzione='n';
            }
            i--;
            val++;
        }
        else if(j-1>=0 && j-1<=nc-1 && proposta[i][j-1]==val){
            if(direzione != 'o'){
                contaCambi++;
                direzione='o';
            }
            j--;
            val++;
        }
        else{
            return -1; // spostamento in diagonale
        }

    }
    return contaCambi;



}

int CalcoloSolOttima(int **mat,int nr,int nc,int i,int j,int val,int **Bsol,int minCambi,int terminazione){
    int n;

    mat[i][j]=val;

    if(val==terminazione){
        n = Controlla_e_Calcola2(mat,nr,nc,terminazione);
        if(n<minCambi){
            minCambi=n;
            for(int i=0;i<nr;i++){
                for(int j=0;j<nc;j++){
                    Bsol[i][j]=mat[i][j];
                }
            }
        }
        return minCambi;
    }


    if(i+1>=0 && i+1<=nr-1 && mat[i+1][j]==0){
        minCambi = CalcoloSolOttima(mat,nr,nc,i+1,j,val+1,Bsol,minCambi,terminazione);
        mat[i+1][j]=0;

    }

    if(j+1>=0 && j+1<=nc-1 && mat[i][j+1]==0){
        minCambi = CalcoloSolOttima(mat,nr,nc,i,j+1,val+1,Bsol,minCambi,terminazione);
        mat[i][j+1]=0;
    }

    if(i-1>=0 && i-1<=nr-1 && mat[i-1][j]==0){
        minCambi = CalcoloSolOttima(mat,nr,nc,i-1,j,val+1,Bsol,minCambi,terminazione);
        mat[i-1][j]=0;
    }

    if(j-1>=0 && j-1<=nc-1 && mat[i][j-1]==0){
        minCambi = CalcoloSolOttima(mat,nr,nc,i,j-1,val+1,Bsol,minCambi,terminazione);
        mat[i][j-1]=0;
    }

    return minCambi;
}
int main() {
    FILE *fin;
    int nr,nc;
    int **mat;
    fin=fopen("griglia.txt","r");
    fscanf(fin,"%d %d",&nr,&nc);
    mat = malloc(nr * sizeof(int*));
    for(int i=0;i<nr;i++){
        mat[i]=malloc(nc * sizeof(int));
    }

    int conta1=0;
    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            fscanf(fin,"%d",&mat[i][j]);
            if(mat[i][j]==1){
                conta1++;
            }

        }
    }

    int Terminazione = nr * nc - conta1 + 1;

    fin=fopen("proposta.txt","r");

    int **proposta;
    proposta=malloc(nr* sizeof(int*));
    for(int i=0;i<nr;i++){
        proposta[i]=malloc(nc* sizeof(int));
    }

    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            fscanf(fin,"%d",&proposta[i][j]);
        }
    }

    int a=Controlla_e_Calcola(proposta, mat,nr,nc,Terminazione);

    if (a==-1){
        printf("proposta NON valida");
    }
    else{
        printf("proposta valida\n");
        printf("il numero di cambi e':%d\n",a);
    }

    int val = 2;
    int minCambi=10000;
    int **Bsol;
    Bsol = malloc(nr* sizeof(int *));
    for(int i=0;i<nr;i++){
        Bsol[i]=malloc(nc* sizeof(int));
    }
    int i=0;int j=0;
    int x=CalcoloSolOttima(mat,nr,nc,i,j,val,Bsol,minCambi,Terminazione);
    printf("la soluzione ottima e' composta da %d cambi\n\n",x);

    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            printf("%d ",Bsol[i][j]);
        }
        printf("\n");
    }

    for(int i=0;i<nr;i++){
        free(mat[i]);
        free(Bsol[i]);
        free(proposta[i]);
    }

    free(mat);
    free(Bsol);
    free(proposta);
}
