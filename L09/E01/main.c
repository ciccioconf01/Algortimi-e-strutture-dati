#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int check(int *sol, Graph grafo,Arco *archi,int i){
    Graph ricorda = grafo;
    int j,z=0,cont = 0,flag = 0;
    for(j=0;j<i;j++){
        archi[j].v='1';
        archi[j].w='1';
    }
    grafo=GRAPHload2(grafo,i,archi);
    printf("\n\n");
    GRAPHstore(grafo,stdout);
    printf("\n\n");
    for(int k=0;k< verticiGrafo(grafo);k++){
        if((cont = GRAPHdfs(grafo,k,cont))!=0){
            flag=1;
        }

    }
    if(flag==1){return 2;}
    return 1;

}

int powerset_r(int* val, int n, int* sol, int i,
               int pos, int start,Arco *archi,Graph grafo,int flagDAG){
    int count = 0, j,x;
    if (pos == i){
        x=check(sol,grafo,archi,i);
        if(x==1){
            printf("Dag trovato \n");
            flagDAG=1;
        }

        return 1;
    }
    if(flagDAG==1){
        return 1;
    }
    for (j = start; j < n; j++){
        sol[pos] = val[j];
        count += powerset_r(val, n, sol, i, pos+1, j+1,archi,grafo,flagDAG);
    }
    return count;
}

int powerset_comb_semp(int pos,int *val,int *sol,int n,int cnt,Graph *grafo, Arco *archi){
    int count = 0, i,flagDAG=0;
    count++;
    for(i = 1; i <= n; i++){
        count += powerset_r(val, n, sol, i, 0, 0,archi, grafo,flagDAG);
    }
    return count;
}

int main() {
    FILE *fin;
    int *val, *sol;
    Arco *archi;
    Graph G;
    int cont = 0;
    char nome[20] = "grafo2.txt";
    fin = fopen(nome, "r");
    if(fin == NULL){
        printf("Errore apertura file\n");
        return 1;
    }
    G = GRAPHload(fin);
    fclose(fin);
    if((cont = GRAPHdfs(G,0,cont))==0){
        printf("Il grafo e' gia' un DAG\n");
        return 2;
    }
    else {
        printf("Gli archi sopra elencati non rendono il grafo un DAG\n");
    }
    archi = malloc((archiGrafo(G))*sizeof (Arco));
    int n = archiGrafo(G);
    int z = verticiGrafo(G);
    val = malloc(n* sizeof(int));
    for(int i=0;i<n;i++){
        val[i]=i;
    }
    sol = malloc(n* sizeof(int));
    int pos=0,cnt=0;
    free(val);
    free(sol);
    GRAPHfree(G);
}