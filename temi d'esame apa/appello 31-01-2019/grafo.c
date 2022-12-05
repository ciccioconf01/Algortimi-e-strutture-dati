
#include "grafo.h"
#include "ST.h"


struct graph{
    int V;
    int E;
    ST tab;
    int **madj;
};

static Edge  EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);
static int   pathR(Graph G, int v, int w, int *visited);
static void  bfs(Graph G, Edge e, int *time, int *pre, int *st);

static Edge EDGEcreate(int v, int w) {
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w;

    if (G->madj[v][w] == 0)
        G->E++;
    G->madj[v][w] = 1;
}

static int **MATRIXint(int r, int c, int val) {
    int i, j, **t;
    t = malloc(r * sizeof(int *));
    if (t==NULL)
        return NULL;

    for (i=0; i < r; i++) {
        t[i] = malloc(c * sizeof(int));
        if (t[i]==NULL)
            return NULL;
    }
    for (i=0; i < r; i++)
        for (j=0; j < c; j++)
            t[i][j] = val;
    return t;
}

Graph Graphinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);
    if (G->madj == NULL)
        return NULL;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int i;
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}

void GRAPHinsertE(Graph G, int id1, int id2) {
    insertE(G, EDGEcreate(id1, id2));
}

Graph GraphLoad(Graph G, FILE *fin){

    char v1,v2;
    int V=0;


    char *vet;
    vet = malloc(10 * sizeof(char));
    for(int i=0;i<10;i++){
        vet[i]='/';
    }

    int trovato1=0;int trovato2=0; int x=0;
    while (!feof(fin)){
        fscanf(fin,"%c %c\n",&v1,&v2);

        for(int i=0;i<10;i++){
            if(v1==vet[i]){
                trovato1=1;
            }
            if(v2==vet[i]){
                trovato2=1;
            }
        }
        if(trovato1==0){
            vet[x]=v1;
            x++;
        }
        if(trovato2==0){
            vet[x]=v2;
            x++;
        }
        trovato1=0;trovato2=0;
    }

    free(vet);

    G=Graphinit(x);

    fin=fopen("grafo.txt","r");

    while (!feof(fin)){
        fscanf(fin,"%c %c\n",&v1,&v2);
        if(STsearch(G->tab,v1)==-1){
            STinsert(G->tab,v1,v1-'a');
            V++;
        }
        if(STsearch(G->tab,v2)==-1){
            STinsert(G->tab,v2,v2 - 'a');
            V++;
        }
        GRAPHinsertE(G,STsearch(G->tab,v1),STsearch(G->tab,v2));
    }


    return G;
}
int ritornaV(Graph G){
    return G->V;
}
int Acquisisci(Graph G, char V){
    return STsearch(G->tab,V);
}

int Lvet(int *proposta,int v){

    int conta=0;
    for(int i=0;i<v;i++){
        if(proposta[i]!=-1){
            conta++;
        }
    }
    return conta;
}

int VerificaProposta(Graph G, int *proposta){
    int Lprop = Lvet(proposta,G->V);
    int trovato=0;

    // primo controllo
    for(int i=0;i<Lprop;i++){
        for(int j=i+1;j<Lprop;j++){
            if(proposta[i]!=-1 && proposta[j]!=-1){
                if(G->madj[proposta[i]][proposta[j]]!=0){
                    trovato=1;
                }
            }

        }
    }

    if(trovato==1){
        return -1;
    }

    //secondo controllo
    int *nodiNonSol; trovato=0; int z=0;
    nodiNonSol = malloc(G->V * sizeof(int));
    for(int i=0;i<G->V;i++){
        nodiNonSol[i]=-1;
    }

    for(int i=0;i<G->V;i++){
        for(int j=0;j<G->V;j++){
            if(STsearchByIndex(G->tab,i) == STsearchByIndex(G->tab,proposta[j])){
                trovato=1;
            }
        }

        if(trovato==0){
            nodiNonSol[z]=i;
            z++;
        }
        trovato=0;

    }

    int LnodiNonSol = Lvet(nodiNonSol,G->V);
    trovato=0;

    for(int i=0;i<LnodiNonSol;i++){
        for(int j=0;j<G->V;j++){
            if(nodiNonSol[i]!=-1 && proposta[j]!=-1){
                if(G->madj[nodiNonSol[i]][proposta[j]]!=0 || G->madj[proposta[j]][nodiNonSol[i]]!=0){
                    trovato=1;
                }
            }

        }
        if(trovato==0){
            return -1;
        }
        trovato=0;
    }

    return 0;

}

int calcolo(int *val, int v){
    int conta=0;
    for(int i=0;i<v;i++){
        if(val[i]==1){
            conta++;
        }
    }
    return conta;
}

int *traduzione(int *val, int v){
    int *val2;
    val2=malloc(v* sizeof(int));
    for(int i=0;i<v;i++){
        val2[i]=-1;
    }

    for(int i=0;i<v;i++){
        if(val[i]==1){
            val2[i]=i;
        }
    }
    return val2;
}

int kernelMinimo(Graph G,int pos,int *sol,int *Bsol,int min, int *solTrad){

    if(pos==G->V){
        solTrad = traduzione(sol,G->V);
        if(VerificaProposta(G,solTrad)!=-1){
            for(int i=0;i<G->V;i++){
                Bsol[i]=sol[i];
            }
            min=calcolo(Bsol,G->V);
        }
        return min;
    }

    sol[pos] = 1;
    min = kernelMinimo(G,pos+1,sol,Bsol,min,solTrad);
    sol[pos]=-1;
    min = kernelMinimo(G,pos+1,sol,Bsol,min,solTrad);

    return min;

}

char GraphSearch(Graph G, int val){
    return STsearchByIndex(G->tab,val);
}

int ContaKernel(int *vetKernel, int *vetPassati, int min, int v){
    int trovato=0; int conta=0;

    for(int i=0;i<v;i++){
        for(int j=0;j<min;j++){
            if(vetPassati[i]==vetKernel[j] && i!=j && vetPassati[i]!=-1 && vetKernel[j]!=-1){
                trovato=1;
            }
        }

        if(trovato==1){
            conta++;
        }
        trovato=0;
    }
    return conta;
}

int MigliorCammino(Graph G, int *vetKernel, int lunghezza, int *max,int pos, int *vetPassati,int min){


        for(int j=0;j<G->V;j++){
            if(G->madj[pos][j]!=0){
                vetPassati[j]=1;
                lunghezza = MigliorCammino(G,vetKernel,lunghezza,max,j,vetPassati,min);
                vetPassati[j]=-1;
                lunghezza = MigliorCammino(G,vetKernel,lunghezza,max,j,vetPassati,min);
            }
        }

        if(ContaKernel(vetKernel,vetPassati,min,G->V)>*max){
            *max=ContaKernel(vetKernel,vetPassati,min,G->V);
            lunghezza = Lvet(vetPassati,G->V);
        }

    return lunghezza;

}
