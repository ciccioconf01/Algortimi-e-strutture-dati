#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int v1;
    int v2;
} archi;

int check(int *sol, int *val, archi *grafo, int k){
    int *occ;
    int flag=1;
    occ = malloc(k*sizeof (int ));
    for(int i=0;i<k;i++){
        occ[i]=0;
    }
    for(int i=0;i<k;i++){
        for (int j = 0; j < k; j++) {
            if(sol[i]!=0){
                if(grafo[j].v1==val[i] || grafo[j].v2==val[i]){
                    occ[j]++;
                }
            }
        }
    }
    for (int i = 0; i < k; ++i) {
        if(occ[i]==0){
            flag=0;
        }
    }

    free(occ);
    if(flag==0){
        return -1;
    }
    else{
        return 1;
    }
}

int powerset(int pos,int *val,int *sol,int k,int cnt,archi *grafo){
    int j;
    if (pos >= k) {
        if(check(sol,val,grafo,k)==1){

            printf("{ \t");
        for (j=0; j<k; j++)
            if (sol[j]!=0)
                printf("%d \t", val[j]);
        printf("} \n");
        return cnt+1;
        }
        else{
            return cnt;
        }
    }

    sol[pos] = 0;
    cnt = powerset(pos+1, val, sol, k, cnt, grafo);
    sol[pos] = 1;
    cnt = powerset(pos+1, val, sol, k, cnt, grafo);
    return cnt;
}

int main() {
    int N,E;
    FILE *fin;
    if((fin = fopen("grafo.txt", "r"))==NULL){
        printf("Errore apertura file\n");
        return -1;
    }
    fscanf(fin, "%d %d\n", &N, &E);
    archi *grafo;
    grafo = malloc(N*sizeof(archi));
    for(int i=0;i<E;i++){
        fscanf(fin, "%d %d\n", &grafo[i].v1, &grafo[i].v2);

    }
    int pos=0,cnt=0,*val,*sol;
    val=malloc(N* sizeof(int));
    sol=malloc(N* sizeof(int));
    for(int i=0;i<N;i++){
        val[i]=i;
    }
    powerset(pos,val,sol,N,cnt,grafo);
    free(val);
    free(sol);
    free(grafo);
}