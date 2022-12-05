#include "grafo.h"
#include "ST.h"

struct graph{
    int V;
    int E;
    ST st;
    int **madj;
};

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
    G->madj[w][v] = 1;
}

int ritornaNumVerticiGraph(Graph G){
    return G->V;
}


static int **MATRIXint(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
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

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);
    if (G->madj == NULL)
        return NULL;
    G->st = STinit(V);
    if (G->st == NULL)
        return NULL;
    return G;
}

char * GraphSearch(Graph G, int i){
    return STsearchByIndex(G->st,i);
}

void GRAPHinsertE(Graph G, int id1, int id2) {
    insertE(G, EDGEcreate(id1, id2));
}

void GRAPHfree(Graph G) {
    int i;
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->st);
    free(G);
}

Graph GraphLoad(Graph G, FILE *fin){
    int n;
    char V1[3];char V2[3];
    int i;

    fscanf(fin,"%d",&n);

    G = GRAPHinit(n);
    while (!feof(fin)){
        fscanf(fin,"%s %s",V1,V2);
        i=STsearch(G->st,V1);
        if(i==-1){
            int d=V1[1]-'0';
            STinsert(G->st,V1,d);
        }
        i=STsearch(G->st,V2);
        if(i==-1){
            int d=V2[1]-'0';
            STinsert(G->st,V2,d);
        }
        int x1=STsearch(G->st,V1);
        int x2=STsearch(G->st,V2);

        GRAPHinsertE(G,x1,x2);
    }
    return G;

}

int ControllaProposta(FILE *fin,Graph G){
    int nr;
    int **mat;

    int nc = G->V;
    fscanf(fin,"%d",&nr);
    mat = malloc(nr* sizeof(int *));
    for(int i=0;i<nr;i++){
        mat[i]=malloc(nc * sizeof(int));
    }

    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            mat[i][j]=-1;
        }
    }

    char label[3];

    for(int i=0;i<nr;i++){
        fscanf(fin,"%d",&nc);
        for(int j=0;j<nc;j++){
            if(j!=nc-1){
                fscanf(fin,"%s ",label);
                mat[i][j]=STsearch(G->st,label);
            }
            else{
                fscanf(fin,"%s",label);
                mat[i][j]=STsearch(G->st,label);
            }
        }
    }


    // controllo corretto parzionamento

    int *vet;
    vet=malloc(G->V* sizeof(int ));
    for(int i=0;i<G->V;i++){
        vet[i]=-1;
    }

    for(int i=0;i<nr;i++){
        for(int j=0;j<G->V;j++){
            if(mat[i][j]!=-1){
                vet[mat[i][j]]++;
            }
        }
    }

    for(int i=0;i<G->V;i++){
        if(vet[i]!=0){
            return -1;
        }
    }

    // Controllo dominating set
    int z=0; int j=0;
    int vetDomin[G->V]; int indexD=0;
    int vetNONDomin[G->V]; int indexND=0;
    int trovato=0;

    for(int i=0;i<G->V;i++){
        vetDomin[i]=-1;
        vetNONDomin[i]=-1;
    }

    while (z<nr){
        j=0;
        while (mat[z][j]!=-1){
            vetDomin[indexD]=mat[z][j];
            j++;
            indexD++;
            if(j==G->V){
                return 0;
            }
        }

        for(int i=0;i<G->V;i++){
            for(int j=0;j<indexD;j++){
                if(i==vetDomin[j]){
                    trovato=1;
                }
            }
            if(trovato==0){
                vetNONDomin[indexND]=i;
                indexND++;
            }
            trovato=0;
        }

        int x,y;
        for(int i=0;i<indexND;i++){

            for(int j=0;j<indexD;j++){

                x=vetNONDomin[i];

                if(G->madj[x][vetDomin[j]]==1){
                    trovato=1;
                }
            }
            if(trovato==0){
                return -1;
            }
            trovato=0;
        }
        z++;
        indexD=0;indexND=0;
        for(int i=0;i<G->V;i++){
            vetDomin[i]=-1;
            vetNONDomin[i]=-1;
        }

    }
    return 0;
}



int controllaCardinalita(int *vettorePartizioni,int V){
    int conta1=0,conta2=0;

    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(vettorePartizioni[j]==i){
                conta1++;
            }
        }
        if(conta1!=0){
            conta2++;
        }
        conta1=0;
    }
    return conta2;
}

int ControllaNumerosita (int *vettorePartizioni, int V , int j){
    int conta=0;
    for(int i=0;i<V;i++){
        if(vettorePartizioni[i]==j){
            conta++;
        }
    }
    return conta;
}

int ControllaSeCiSonoInsiemiDi1(int *vettorePartizioni, int V){
    int C=controllaCardinalita(vettorePartizioni,V);
    int conta=0;
    for(int i=0;i<C;i++){
        for(int j=0;j<V;j++){
            if(vettorePartizioni[j]==i){
                conta++;
            }
        }
        if(conta==1){
            return -1;
        }
    }
    return 0;
}

FILE *FunzioneTraduzione(int *vettorePartizioni,int V,Graph G){

    int cardinalita = controllaCardinalita(vettorePartizioni,V);
    FILE *fout; int conta=0;
    fout=fopen("prova.txt","w");
    fprintf(fout,"%d\n",cardinalita);
    for(int i=0;i<cardinalita;i++){
        int x=ControllaNumerosita(vettorePartizioni,V,i);
        fprintf(fout,"%d\n",x);
        for(int j=0;j<V;j++){

            if(vettorePartizioni[j]==i && conta<x-1){
                fprintf(fout,"%s ",STsearchByIndex(G->st,j));
                conta++;
            }
            else if(vettorePartizioni[j]==i && conta==x-1){
                fprintf(fout,"%s\n",STsearchByIndex(G->st,j));
            }
        }
        conta=0;
    }
    fclose(fout);
    FILE *fin;
    fin=fopen("prova.txt","r");
    return fin;
}

int SoluzioneOttima(Graph G,int V,int *vettorePartizioni,int pos, int cardinalita, int *Bsol){

    if(pos==V){
        FILE *fin=FunzioneTraduzione(vettorePartizioni,V,G);
        if(ControllaProposta(fin,G)!=-1){
            int C=controllaCardinalita(vettorePartizioni,V);
            if(C>cardinalita){
                cardinalita=C;
                for(int i=0;i<G->V;i++){
                    Bsol[i]=vettorePartizioni[i];
                }

            }
        }
        return cardinalita;
    }

    for(int i=0;i<V;i++){

        vettorePartizioni[pos]=i;

        if(pos==6){
            if(ControllaSeCiSonoInsiemiDi1(vettorePartizioni,V)==0){
                cardinalita = SoluzioneOttima(G,V,vettorePartizioni,pos+1,cardinalita,Bsol);
            }
        }
        else{
            cardinalita = SoluzioneOttima(G,V,vettorePartizioni,pos+1,cardinalita,Bsol);
        }


    }
    return cardinalita;
}