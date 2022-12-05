#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"

#define maxWT INT_MAX
#define MAXC 10

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

static Edge  EDGEcreate(int v, int w, int wt);
static link  NEW(int v, int wt, link next);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;

    G->V = V;
    G->E = 0;
    G->z = NEW(-1, 0, NULL);
    if (G->z == NULL)
        return NULL;
    G->ladj = malloc(G->V*sizeof(link));
    if (G->ladj == NULL)
        return NULL;
    for (v = 0; v < G->V; v++)
        G->ladj[v] = G->z;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int v;
    link t, next;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = next) {
            next = t->next;
            free(t);
        }
    STfree(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d\n", &V);
    G = GRAPHinit(V);
    if (G == NULL)
        return NULL;

    for (i=0; i<V; i++) {
        fscanf(fin, "%s\n", label1);
        STinsert(G->tab, label1, i);
    }

    while(fscanf(fin, "%s %s %d\n", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

void  GRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    link t;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = t->next)
            a[E++] = EDGEcreate(v, t->v, t->wt);
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

int GRAPHgetIndex(Graph G, char *label) {
    int id;
    id = STsearch(G->tab, label);
    if (id == -1) {
        id = STsize(G->tab);
        STinsert(G->tab, label, id);
    }
    return id;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}


static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->E++;
}

static void  removeE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    link x;
    if (G->ladj[v]->v == w) {
        G->ladj[v] = G->ladj[v]->next;
        G->E--;
    }
    else
        for (x = G->ladj[v]; x != G->z; x = x->next)
            if (x->next->v == w) {
                x->next = x->next->next;
                G->E--;
            }
}

void GRAPHspBF(Graph G, int id){
    int v, w, negcycfound;
    link t;
    int *st, *mindist;

    st = malloc(G->V*sizeof(int));
    mindist = malloc(G->V*sizeof(int));
    if ((st == NULL) || (mindist == NULL))
        return;

    for ( v = 0; v < G->V; v++) {
        st[v]= -1;
        mindist[v] = maxWT;
    }

    mindist[id] = 0;
    st[id] = id;

    for (w = 0; w < G->V - 1; w++)
        for (v = 0; v < G->V; v++)
            if (mindist[v] < maxWT)
                for (t = G->ladj[v]; t != G->z ; t = t->next)
                    if (mindist[t->v] > mindist[v] + t->wt) {
                        mindist[t->v] = mindist[v] + t->wt;
                        st[t->v] = v;
                    }
    negcycfound = 0;
    for (v = 0; v < G->V; v++)
        if (mindist[v] < maxWT)
            for (t = G->ladj[v]; t != G->z ; t = t->next)
                if (mindist[t->v] > mindist[v] + t->wt)
                    negcycfound = 1;
    if (negcycfound == 0) {
        printf("\n Shortest path tree\n");
        for (v = 0; v < G->V; v++)
            printf("Parent of %s is %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));

        printf("\n Minimum distances from node %s\n", STsearchByIndex(G->tab, id));
        for (v = 0; v < G->V; v++)
            printf("mindist[%s] = %d \n", STsearchByIndex(G->tab, v), mindist[v]);
    }
    else
        printf("\n Negative cycle found!\n");
}




int dfsR1(Graph G, Edge e, int *time, int *pre, int *post, int *st, int conta) {
    link t;
    int v, w = e.w;
    Edge x;
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next) {
        if (pre[t->v] == -1)
            conta = dfsR1(G, EDGEcreate(w, t->v, G->z->wt), time, pre, post, st, conta);
        else {
            v = t->v;
            x = EDGEcreate(w, v, G->z->wt);
            if (pre[w] < pre[v]) {
                printf("l'arco: (%s, %s) e' di tipo back\n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
                conta = conta + 1;

            }
            if (post[v] == -1) {
                printf("l'arco: (%s, %s) e' di tipo back\n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
                conta = conta + 1;
            }
        }
    }
    post[w] = (*time)++;
    return conta;
}

int GRAPHdfs(Graph G, int id, int conta) {
    int v, time=0, *pre, *post, *st;
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    for (v=0;v<G->V;v++) {
        pre[v]=-1; post[v]=-1; st[v]=-1;
    }
    conta=dfsR1(G, EDGEcreate(id,id,G->z->wt), &time, pre, post, st, conta);
    for (v=0; v < G->V; v++)
        if (pre[v]==-1)
            conta = dfsR1(G,EDGEcreate(v,v,G->z->wt),&time,pre,post,st,conta);
    return conta;
}


int verticiGrafo(Graph g){
    return g->V;
}

int archiGrafo(Graph g){
    return g->E;
}

Graph cancellaArco(Graph g,int i){
    return g;
}

Graph GRAPHload2(Graph grafo,int cardinalita, Arco *archi) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    V=verticiGrafo(grafo);
    Graph G;

    G = GRAPHinit(V);
    if (G == NULL)
        return NULL;

    for(int i=0;i<V;i++) {
        if(archi[i].w!='1'){
            id1 = STsearch(grafo->tab, archi[i].w);
            id2 = STsearch(grafo->tab,archi[i].v );
            if (id1 >= 0 && id2 >=0)
                GRAPHinsertE(G, id1, id2, wt);
        }
    }
    return G;
}