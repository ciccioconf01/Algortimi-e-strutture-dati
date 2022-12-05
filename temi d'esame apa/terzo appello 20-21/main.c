#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int i;
    int j;
}coppia;



int** leggiMappa(FILE *fn, int R, int C) {

    int **mat;

    mat = malloc ( R*sizeof(int*));
    for(int i=0;i<R;i++){
        mat[i] = malloc (C*sizeof(int));
    }

    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            fscanf(fn,"%d",&mat[i][j]);
        }
    }

    return mat;


}

int verifica(FILE *fn, int **mat) {

    int nr, nc;
    fscanf(fn, "%d %d", &nr, &nc);
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(fn, "%d", &mat[i][j]);
        }
    }

    int **matVisitati;
    matVisitati = malloc(nr * sizeof(int *));
    for (int i = 0; i < nr; i++) {
        matVisitati[i] = malloc(nc * sizeof(int));
    }

    coppia *vet;
    int z = 1;
    vet = malloc(9 * sizeof(coppia));
    for (int i = 0; i < 9; i++) {
        vet[i].i = -1;
        vet[i].j = -1;
    }


    int i = 0;
    int j = 0; int pos=0;
    int x, y;
    int valoreAtteso;
    int conta;
    while (pos<nr*nc) {
        if (mat[i][j] != 1 && matVisitati[i][j] != -1) {
            valoreAtteso = mat[i][j]; z=1;
            conta = 1;
            x = i;
            y = j;
            matVisitati[i][j] = -1;
            do {
                z--;
                if (y - 1 >= 0 && mat[x][y - 1] == valoreAtteso && matVisitati[x][y-1] != -1) {
                    conta++;
                    matVisitati[x][y - 1] = -1;
                    vet[z].i = x;
                    vet[z].j = y - 1;
                    z++;
                }
                if (x - 1 >= 0 && mat[x - 1][y] == valoreAtteso && matVisitati[x-1][y] != -1) {
                    conta++;
                    matVisitati[x - 1][y] = -1;
                    vet[z].i = x - 1;
                    vet[z].j = y ;
                    z++;
                }
                if (x + 1 < nr && mat[x + 1][y] == valoreAtteso && matVisitati[x+1][y] != -1) {
                    conta++;
                    matVisitati[x + 1][y] = -1;
                    vet[z].i = x + 1;
                    vet[z].j = y ;
                    z++;
                }
                if (y + 1 < nc && mat[x][y + 1] == valoreAtteso && matVisitati[x][y+1] != -1) {
                    conta++;
                    matVisitati[x][y + 1] = -1;
                    vet[z].i = x;
                    vet[z].j = y + 1;
                    z++;
                }
                x = vet[z - 1].i;
                y = vet[z - 1].j;
                vet[z - 1].i = -1;
                vet[z - 1].j = -1;

            } while (z != 0);
            if (conta != valoreAtteso) { return -1; }


        }
        if (j == nc - 1) {
            j = 0;
            i++;
        }
        else { j++; }

        pos++;

    }
    return 0;
}

int Verifica2 (int **mat,int nr,int nc ){

    int **matVisitati;
    matVisitati = malloc(nr * sizeof(int *));
    for (int i = 0; i < nr; i++) {
        matVisitati[i] = malloc(nc * sizeof(int));
    }

    coppia *vet;
    int z = 1;
    vet = malloc(9 * sizeof(coppia));
    for (int i = 0; i < 9; i++) {
        vet[i].i = -1;
        vet[i].j = -1;
    }


    int i = 0;
    int j = 0; int pos=0;
    int x, y;
    int valoreAtteso;
    int conta;
    while (pos<nr*nc) {
        if (mat[i][j] != 1 && matVisitati[i][j] != -1) {
            valoreAtteso = mat[i][j]; z=1;
            conta = 1;
            x = i;
            y = j;
            matVisitati[i][j] = -1;
            do {
                z--;
                if (y - 1 >= 0 && mat[x][y - 1] == valoreAtteso && matVisitati[x][y-1] != -1) {
                    conta++;
                    matVisitati[x][y - 1] = -1;
                    vet[z].i = x;
                    vet[z].j = y - 1;
                    z++;
                }
                if (x - 1 >= 0 && mat[x - 1][y] == valoreAtteso && matVisitati[x-1][y] != -1) {
                    conta++;
                    matVisitati[x - 1][y] = -1;
                    vet[z].i = x - 1;
                    vet[z].j = y ;
                    z++;
                }
                if (x + 1 < nr && mat[x + 1][y] == valoreAtteso && matVisitati[x+1][y] != -1) {
                    conta++;
                    matVisitati[x + 1][y] = -1;
                    vet[z].i = x + 1;
                    vet[z].j = y ;
                    z++;
                }
                if (y + 1 < nc && mat[x][y + 1] == valoreAtteso && matVisitati[x][y+1] != -1) {
                    conta++;
                    matVisitati[x][y + 1] = -1;
                    vet[z].i = x;
                    vet[z].j = y + 1;
                    z++;
                }
                x = vet[z - 1].i;
                y = vet[z - 1].j;
                vet[z - 1].i = -1;
                vet[z - 1].j = -1;

            } while (z != 0);
            if (conta != valoreAtteso) { return -1; }


        }
        if (j == nc - 1) {
            j = 0;
            i++;
        }
        else { j++; }

        pos++;

    }
    return 0;

}



int CalcolaUni(int **sol, int nr, int nc){
    int conta=0;
    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            if(sol[i][j]==1){conta++;}
        }
    }
    return conta;
}

void SpostaInBsol(int **sol, int **Bsol, int nr, int nc){

    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            Bsol[i][j] = sol[i][j];
        }
    }
}

//la funzione Verifica2 sottostante è simile a verifica solamente che riceve non il file contenete la matrice, ma direttamente la matrice e le sue dimensioni

int solveR(int **sol, int nr, int nc, int i, int j, int **Bsol, int min,int pos){

    if(pos==nr*nc){
        if(Verifica2 ( sol, nr, nc ) !=-1){
            int x=CalcolaUni(sol,nr,nc);
            if( x < min){
                min = x;
                SpostaInBsol(sol,Bsol,nr,nc);
            }
        }
        return min;
    }
int flag;
    for(int x=1;x<10;x++){
        flag=0;
        if(sol[i][j]==0){
            sol[i][j] = x;
            flag=1;
        }

        if(j==nc-1){
            min = solveR(sol,nr,nc,i+1,0,Bsol,min,pos+1);
            if(flag==1){
                sol[i][j]=0;
            }

        }

        else{
            min = solveR(sol,nr,nc,i,j+1,Bsol,min,pos+1);
            if(flag==1){
                sol[i][j]=0;
            }
        }

    }
    return min;

}

int **solve(int **m, int R, int C) {
    int i=0, j=0; int min=10000;
    int **Bsol;
    Bsol = malloc(R *sizeof(int*));
    for(int i=0;i<R;i++){
        Bsol[i] = malloc(C * sizeof(int));
    }
    int pos=0;
    solveR(m,R,C,i,j,Bsol,min,pos);
    return Bsol;

}

int main() {
    FILE *fin; int nr;int nc;
    fin=fopen("mappa.txt","r");
    fscanf(fin,"%d %d",&nr,&nc);
    int **mat;
    mat = leggiMappa(fin,nr,nc);

    fin=fopen("proposta.txt","r");
    int **mat2;
    mat2 = malloc(nr * sizeof(int*));
    for(int i=0;i<nr;i++){
        mat2[i]=malloc(nc* sizeof(int));
    }

    int a=verifica(fin,mat2);
    if(a==-1){
        printf("la proposta NON e' valida\n");
    }
    else{
        printf("la proposta e' valida\n");
    }

    mat2 = solve(mat,nr,nc);

    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            printf("%d ",mat2[i][j]);
        }
        printf("\n");
    }



}
