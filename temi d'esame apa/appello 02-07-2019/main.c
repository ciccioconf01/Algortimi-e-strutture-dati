#include <stdio.h>
#include <stdlib.h>
#define DistMax 8

int VerificaProp1(int *proposta,int n,int Dist,int **mat){

    int *vetDiUni;
    vetDiUni=malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        vetDiUni[i]=1;
    }

    for(int i=0;i<n;i++){
        if(proposta[i]==1){
            for(int j=0;j<n;j++){
                if(mat[i][j]<=Dist){
                    vetDiUni[j]=0;
                }
            }
        }
    }

    for(int i=0;i<n;i++){
        if(vetDiUni[i]==1){
            return -1;
        }
    }

    free(vetDiUni);
    return 0;

}

int Cardinalita(int *proposta,int n){
    int conta=0;

    for(int i=0;i<n;i++){
        if(proposta[i]==1){
            conta++;
        }
    }
    return conta;
}

int solOttima(int **mat,int pos,int n, int min, int *sol, int *Bsol){

    if(pos==n){
        if(VerificaProp1(sol,n,DistMax,mat)==0){
            min = Cardinalita(sol,n);
            for(int i=0;i<n;i++){
                Bsol[i]=sol[i];
            }
        }
        return min;
    }

    if(Cardinalita(sol,n)<min){
        sol[pos]=1;
        min = solOttima(mat,pos+1,n,min,sol,Bsol);
        sol[pos]=0;
        min = solOttima(mat,pos+1,n,min,sol,Bsol);
    }

    return min;

}

int calcolaVal(int *sol,int n, int **mat, int *pop){
    int val=0; int d_min=10000; int conta=0;
    for(int i=0;i<n;i++){
        if(sol[i]==0){

            for(int j=0;j<n;j++){
                if(sol[j]!=0){
                    if(mat[i][j]<d_min){
                        d_min=mat[i][j];
                        conta=1;
                    }
                    else if(d_min==mat[i][j]){
                        conta++;
                    }
                }
            }
            val = val + pop[i] * d_min / conta;
        }
        conta=0;
        d_min=10000;
    }
    return val;
}

int solOttima2(int **mat, int n, int pos, int *pop, int *stazMass, int numStaz, int *sol, int *Bsol, int min){
    int val;

    if(pos==numStaz){
        val = calcolaVal(sol,n,mat,pop);
        if(val<min){
            min=val;
            for(int i=0;i<n;i++){
                Bsol[i]=sol[i];
            }
        }
        return min;

    }

    for(int i=0;i<n;i++){

        if(stazMass[i]>0){
            sol[i]++;
            stazMass[i]--;
            min = solOttima2(mat,n,pos+1,pop,stazMass,numStaz,sol,Bsol,min);
            sol[i]--;
            stazMass[i]++;
        }
    }
    return min;
}

int main() {
    FILE *fin;
    int n;
    fin = fopen("dati.txt","r");
    fscanf(fin,"%d",&n);
    int *pop;
    pop=malloc(n* sizeof(int));
    for(int i=0;i<n;i++){
        fscanf(fin,"%d",&pop[i]);
    }

    int **mat;
    mat=malloc(n* sizeof(int*));
    for(int i=0;i<n;i++){
        mat[i]=malloc(n* sizeof(int));
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fscanf(fin,"%d",&mat[i][j]);
        }
    }


    int *proposta;
    proposta=malloc(n* sizeof(int));
    for(int i=0;i<n;i++){
        if(i==1 || i==3){
            proposta[i]=1;
        }
        else{
            proposta[i]=0;
        }
    }


    int a = VerificaProp1(proposta,n,DistMax,mat);
    if(a==-1){
        printf("proposta NON valida\n");
    }
    else{
        printf("proposta valida\n");
    }

    free(proposta);

    int pos=0;int min=10000;
    int *sol;int *Bsol;
    sol=malloc(n* sizeof(int));
    Bsol=malloc(n* sizeof(int));

    min=solOttima(mat,pos,n,min,sol,Bsol);
    printf("soluzione ottima 1:\n");
    for(int i=0;i<n;i++){
        if(Bsol[i]==1){
            printf("%d ",i);
        }
    }
    printf("\n");

    for(int i=0;i<n;i++){
        sol[i]=0;Bsol[i]=0;
    }
    int stazMass[5]={1,1,4,3,2};
    int numStaz=2;
    min=10000;
    min=solOttima2(mat,n,pos,pop,stazMass,numStaz,sol,Bsol,min);

    printf("soluzione ottima 2, con risultato funzione obiettivo 2 = %d \n",min);
    for(int i =0;i<n;i++){
        if(Bsol[i]!=0){
            for(int j=0;j<Bsol[i];j++){
                printf("%d ",i);
            }
        }
    }

    free(sol); free(Bsol); free(pop);
    for(int i=0;i<n;i++){
        free(mat[i]);
    }
    free(mat);


}
