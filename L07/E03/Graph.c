#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"

#define MAXC 10
#define maxWT INT_MAX

typedef struct node *link;

typedef struct{
    int wt;
    int node;
}value;

struct graph {
    int V;
    int E;
    int **madj;
    ST tab;
    link *ladj;
};
struct node{value x;link next;};
static Edge  EDGEcreate(int v, int w, int wt);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static void  sort(Edge *a, int l, int r );

void GRAPHinsertEdge(Graph g,char *id_elab1,char *id_elab2,int flux){
    int id1,id2;
    id1=STsearch(g->tab,id_elab1);
    id2=STsearch(g->tab,id_elab2);
    g->E++;
    g->madj[id1][id2]=flux;
    g->madj[id2][id1]=flux;
}


int findV(FILE* fin){
    int flag1=1,flag2=1,conta=0,numero,fpm1=1;
    char V1[30],V2[30],nonserve[30];
    char vertici[30][30];
    while(!feof(fin)){
        fscanf(fin,"%s %s %s %s %d",V1,nonserve,V2,nonserve,&numero);
        if(conta==0){
            strcpy(vertici[conta],V1);
            conta++;
            strcpy(vertici[conta], V2);
            conta++;
        }
        else{
            for(int i=0;i<conta;i++){
                if(strcmp(V1,vertici[i])==0 ){
                    flag1=0;
                }
                if(strcmp(V2,vertici[i])==0 ){
                    flag2=0;
                }
            }
        }
        if(flag1==1 && fpm1!=1){
            strcpy(vertici[conta],V1);
            conta++;
        }
        if(flag2==1 && fpm1!=1){
            strcpy(vertici[conta], V2);
            conta++;
        }
        flag1=1;flag2=1,fpm1=0;
    }
    return conta;
}

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

int **MATRIXint(int r, int c, int val) {
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
            t[i][j] = 0;
    return t;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, maxWT);
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

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    Item x,y;
    int flusso;
    Graph G;
    fin = fopen("grafo.txt", "r");
    V = findV(fin);
    G = GRAPHinit(V);
    fclose(fin);
    fin = fopen("grafo.txt", "r");
    while(!feof(fin)){
        fscanf(fin, "%s %s %s %s %d", x.id_elab,x.id_rete,y.id_elab,y.id_rete,&flusso);
        if(STsearch(G->tab,x.id_elab)==-1){
            STinsert(G->tab,x.id_elab,x.id_rete);
        }
        if(STsearch(G->tab,y.id_elab)==-1){
            STinsert(G->tab,y.id_elab,y.id_rete);
        }
        GRAPHinsertEdge(G,x.id_elab,y.id_elab,flusso);
    }
    fclose(fin);
    return G;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (G->madj[v][w] == maxWT)
        G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}

void  GRAPHedges(Graph G, Edge *a) {
    int v, w, E = 0;
    for (v=0; v < G->V; v++)
        for (w=v+1; w < G->V; w++)
            if (G->madj[v][w] != maxWT)
                a[E++] = EDGEcreate(v, w, G->madj[v][w]);
}

void GRAPHstore(Graph G, FILE *fout) {
    int i;
    Edge *a;
    a = malloc(G->E * sizeof(Edge));
    if (a == NULL)
        return;
    GRAPHedges(G, a);
    fprintf(fout, "%d\n", G->V);
    for (i = 0; i < G->V; i++)
        fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));
    for (i = 0; i < G->E; i++)
        fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
}


static void sort(Edge *a, int l, int r ) {
    int i, j, min, temp;
    for(i = l; i < r; i++) {
        min = i;
        for (j = i+1; j <= r; j++)
            if (a[j].wt < a[min].wt)
                min = j;

        temp = a[i].v;
        a[i].v = a[min].v;
        a[min].v = temp;

        temp = a[i].w;
        a[i].w = a[min].w;
        a[min].w = temp;

        temp = a[i].wt;
        a[i].wt = a[min].wt;
        a[min].wt = temp;
    }
    return;
}

void InsertionSort(Item *A, int n) {
    int i, j, l=0, r=n-1;
    Item x;
    for (i = l+1; i <= r; i++) {
        x = A[i];
        j = i - 1;
        while (j >= l && strcmp(x.id_elab,A[j].id_elab)<0){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = x;
    }
}

void OrderedEdges(char *str,Graph g){
    int i,j,cnt=0;
    Item *VettNomi;
    VettNomi=calloc(STsize(g->tab),sizeof(Item));
    if(VettNomi==NULL)
        printf("Allocation Error!");
    i=STsearch(g->tab,str);
    for(j=0;j<STsize(g->tab);j++){
        if(g->madj[i][j]!=0){
            strcpy(VettNomi[cnt].id_elab,STsearchByIndex(g->tab,j));
            cnt++;
        }
    }
    printf("collegato con: ");
    InsertionSort(VettNomi,cnt);
    for(i=0;i<cnt;i++)
        printf("%s ",VettNomi[i].id_elab);
}

void GraphPrint(Graph g){
    Item *x;
    int i;
    x=calloc(STsize(g->tab),sizeof(Item));
    if(x==NULL)
        printf("Allocation error!");
    for(i=0;i<STsize(g->tab);i++){
        x[i]=GetItem(g->tab,i);
    }
    InsertionSort(x,STsize(g->tab));
    for(i=0;i<STsize(g->tab);i++){
        printf("\n-%s,",x[i].id_elab);
        OrderedEdges(x[i].id_elab,g);
    }
}

void Stampamatrice(Graph g){
    int i,j;
    for(i=0;i<g->V;i++){
        for(j=0;j<g->V;j++){
            printf("%d\t",g->madj[i][j]);
        }
        printf("\n");
    }
}

link newnode(int flux,int NodeIndex,link next){
    link z = malloc(sizeof *z);
    if (z == NULL)
        return NULL;
    z->x.node=NodeIndex;
    z->x.wt=flux;
    z->next=next;
    return z;
}

void CreaLista(Graph g){
    int dim=g->V,j,i;
    g->ladj=calloc(dim,sizeof(link));
    for(i=0;i<dim;i++)
        g->ladj[i]=NULL;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            if(g->madj[i][j]!=0){
                g->ladj[i]=newnode(g->madj[i][j],j,g->ladj[i]);
            }
        }
    }
}

void PrintLista(Graph g){
    int i;
    link x;
    for(i=0;i<g->V;i++){
        printf("\n %s ",STsearchByIndex(g->tab,i));
        for(x=g->ladj[i];x!=NULL;x=x->next)
            printf("\n |-> %s peso: %d",STsearchByIndex(g->tab,x->x.node),x->x.wt);
        printf("\n");
    }
}

int CheckMat(int v1,int v2,int v3,Graph g){
    if(g->madj[v1][v2]!=0 && g->madj[v1][v3]!=0)
        return 1;
    else
        return -1;
}

int CheckList(int v1,int v2,int v3,Graph g){
    link x;
    int flag1=0,flag2=0;
    for(x=g->ladj[v1];x!=NULL;x=x->next){
        if(x->x.node==v2)
            flag1=1;
        if(x->x.node==v3)
            flag2=1;
    }
    if(flag1==1 && flag2==1)
        return 1;
    else
        return -1;
}

void ControllaVertice(Graph g){
    char V1[30],V2[30],V3[30];
    int id1,id2,id3,scelta;
    printf("\ninserire il nome di un vertice: ");
    scanf("%s",V1);
    printf("\ninserire il nome di un vertice: ");
    scanf("%s",V2);
    printf("\ninserire il nome di un vertice: ");
    scanf("%s",V3);
    id1=STsearch(g->tab,V1);
    id2=STsearch(g->tab,V2);
    id3=STsearch(g->tab,V3);
    if(id1>=0 && id2>=0 && id3>=0){
        printf("\nsi desidera usare la matrice delle adiacenze [0] o la lista delle adiacenze [1]?");
        scanf("%d",&scelta);
        switch(scelta){
            case 0:
                if(CheckMat(id1,id2,id3,g)==1 && CheckMat(id2,id1,id3,g)==1 && CheckMat(id3,id1,id2,g)==1)
                    printf("\ni vertici %s,%s e %s formano un sottografo completo",V1,V2,V3);
                else
                    printf("\ni vertici %s,%s e %s non formano un sottografo completo",V1,V2,V3);
                break;
            case 1:
                if(CheckList(id1,id2,id3,g)==1 && CheckList(id2,id1,id3,g)==1 && CheckList(id3,id1,id2,g)==1)
                    printf("\ni vertici %s,%s e %s formano un sottografo completo",V1,V2,V3);
                else
                    printf("\ni vertici %s,%s e %s non formano un sottografo completo",V1,V2,V3);
                break;
            default:printf("inserire valore accettabile!"); break;

        }
    }else
        printf("\ni nomi inseriti non sono validi!");
}