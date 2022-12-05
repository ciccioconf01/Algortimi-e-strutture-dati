#include <stdio.h>
#include <stdlib.h>
// il file proposta è composto da 0 per caselle libere, 1 per caselle piene in partenza e da numeri da 2 a 20 per le varie regioni
int GiaControllato(int val,int *vetDeiControllati){
    int i=0;
    while (vetDeiControllati[i]!=-1){
        if (val==vetDeiControllati[i]){
            return 1;
        }
        i++;
    }
    return 0;
}
int LunghezzaVet(int *vetDeiControllati){
    int i=0; int conta=0;
    while (vetDeiControllati[i]!=-1){
        conta++;
        i++;
    }
    return conta;
}
int ControllaValidita(FILE *fin){
    int nr,nc;
    int **matrice;
    fscanf(fin,"%d %d",&nr,&nc);

    matrice = malloc(nr* sizeof(int*));
    for(int i=0;i<nr;i++){
        matrice[i]=malloc(nc * sizeof(int));
    }

    for(int i=0;i<nr;i++){
        for (int j=0;j<nc;j++){
            fscanf(fin,"%d",&matrice[i][j]);
        }
    }

    int *vetDeiControllati;
    vetDeiControllati = malloc(nr*nc*sizeof(int));
    for(int i=0;i<nr*nc;i++){
        vetDeiControllati[i]=-1;
    }

    // inizia il controllo
    int index=0;

    for(int i=0;i<nr;i++){
        for (int j=0;j<nc;j++){
            if(matrice[i][j]==0){
                return -1;
            }
            if (GiaControllato(matrice[i][j],vetDeiControllati)==0){
                if(matrice[i][j]!=1){
                    int k=j+1, conta=1;
                    while (matrice[i][k]==matrice[i][j] && k>=0 && k<12){
                        conta++;
                        k++;
                    }
                    k--;
                    int z=i+1; int conta2=1;
                    while (z>=0 && z<12 && k>=0 && k<12 && matrice[i][j]==matrice[z][k]){
                        conta2++;
                        z++;
                    }
                    z--;
                    if(conta==conta2){
                        conta2=0;
                        while (z>=0 && z<12 && k>=0 && k<12 && matrice[i][j]==matrice[z][k]){
                            conta2++;
                            k--;
                        }
                        k++;
                        if(conta==conta2){
                            conta2=0;
                            while (z>=0 && z<12 && k>=0 && k<12 && matrice[i][j]==matrice[z][k] ){
                                conta2++;
                                z--;
                            }
                            if(conta==conta2){
                                vetDeiControllati[index]= matrice[i][j];
                                index++;
                            }
                            else{
                                return -1;
                            }
                        }
                        else{
                            return -1;
                        }
                    }
                    else{
                        return -1;
                    }
                }
            }

        }
    }

    for(int i=0;i<nr;i++){
        free(matrice[i]);
    }
    free(matrice);
    int a=LunghezzaVet(vetDeiControllati);
    free(vetDeiControllati);
    return a;
}

int ControllaValidita2(int **matrice, int nr, int nc){


    int vetDeiControllati[nr*nc];

    for(int i=0;i<nr*nc;i++){
        vetDeiControllati[i]=-1;
    }

    // inizia il controllo
    int index=0;

    for(int i=0;i<nr;i++){
        for (int j=0;j<nc;j++){
            if(matrice[i][j]==0){
                return -1;
            }
            if (GiaControllato(matrice[i][j],vetDeiControllati)==0){
                if(matrice[i][j]!=1){
                    int k=j+1, conta=1;
                    while (matrice[i][k]==matrice[i][j] && k>=0 && k<12){
                        conta++;
                        k++;
                    }
                    k--;
                    int z=i+1; int conta2=1;
                    while (z>=0 && z<12 && k>=0 && k<12 && matrice[i][j]==matrice[z][k]){
                        conta2++;
                        z++;
                    }
                    z--;
                    if(conta==conta2){
                        conta2=0;
                        while (z>=0 && z<12 && k>=0 && k<12 && matrice[i][j]==matrice[z][k]){
                            conta2++;
                            k--;
                        }
                        k++;
                        if(conta==conta2){
                            conta2=0;
                            while (z>=0 && z<12 && k>=0 && k<12 && matrice[i][j]==matrice[z][k] ){
                                conta2++;
                                z--;
                            }
                            if(conta==conta2){
                                vetDeiControllati[index]= matrice[i][j];
                                index++;
                            }
                            else{
                                return -1;
                            }
                        }
                        else{
                            return -1;
                        }
                    }
                    else{
                        return -1;
                    }
                }
            }

        }
    }
    int a=LunghezzaVet(vetDeiControllati);

    return a ;
}

int SoluzioneOttima(int **matrice,int nr,int nc,int i,int j,int val ,int LunghSol, int **Bmat){
    int x;
    if(i==nr-1 && j==nc-1){
        x=ControllaValidita2(matrice,nr,nc);
        if(x!=-1){
            if(x<LunghSol){
                LunghSol=x;
                for(int a =0;a<nr;a++){
                    for(int b=0;b<nc;b++){
                        Bmat[a][b]=matrice[a][b];
                    }
                }
            }

        }
        return LunghSol;
    }

    if(matrice[i][j]==0){
        if(j==nc){
            while (val<nr*nc - 25){
                matrice[i][j]=val;
                LunghSol = SoluzioneOttima(matrice,nr,nc,i+1,0,val,LunghSol,Bmat);
                matrice[i][j]=0;
                val = val +1;
                LunghSol = SoluzioneOttima(matrice,nr,nc,i+1,0,val,LunghSol,Bmat);

            }

        }
        else{
            while (val<nr*nc -25 ){
                matrice[i][j]=val;
                LunghSol = SoluzioneOttima(matrice,nr,nc,i,j+1,val,LunghSol,Bmat);
                matrice[i][j]=0;
                val = val +1;
                LunghSol = SoluzioneOttima(matrice,nr,nc,i,j+1,val,LunghSol,Bmat);

            }
        }

    }
    else{
        if(j==nc){
            LunghSol = SoluzioneOttima(matrice,nr,nc,i+1,0,val,LunghSol,Bmat);
        }
        else{
            LunghSol = SoluzioneOttima(matrice,nr,nc,i,j+1,val,LunghSol,Bmat);
        }
    }
    return LunghSol;


}

int main() {
    FILE *fin;
    int nr, nc;
    int ** matrice;
    fin = fopen("griglia.txt","r");
    fscanf(fin, "%d %d",&nr, &nc);

    matrice = malloc(nr * sizeof(int *));
    for (int i=0;i<nr;i++){
        matrice[i]=malloc(nc* sizeof(int));
    }

    for(int i=0;i<nr;i++){
        for (int j=0;j<nc;j++){
            fscanf(fin,"%d",&matrice[i][j]);
        }
    }

    fclose(fin);

    fin = fopen("proposta.txt","r");

    int a;
    a = ControllaValidita(fin);
    if(a!=-1){
        printf("la proposta e' valida\n");
        printf("Il numero di regioni e':%d\n\n",a);
    }
    else{
        printf("la proposta NON e' valida");
    }

    int i=0,j=0;

    int lunghSol=1000;

    int *vetDeiControllati;
    vetDeiControllati = malloc(nr*nc*sizeof(int));
    for(int i=0;i<nr*nc;i++){
        vetDeiControllati[i]=-1;
    }
    int val=2;

    int **Bmat;
    Bmat = malloc(nr * sizeof(int *));
    for (int i=0;i<nr;i++){
        Bmat[i]=malloc(nc* sizeof(int));
    }

    lunghSol = SoluzioneOttima(matrice,nr,nc,i,j,val,lunghSol,Bmat);
    printf("La soluzione ottima e' composta da %d sottoregioni\n",lunghSol);
    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            printf("%d ",Bmat[i][j]);
        }
        printf("\n");
    }
}
