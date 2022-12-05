#ifndef E01_GRAPH_H
#define E01_GRAPH_H

#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;
typedef struct arco{ int v; int w; int wt; } Arco;
typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHedges(Graph G, Edge *a);
int GRAPHdfs(Graph G, int id, int conta);
int verticiGrafo(Graph G);
int archiGrafo(Graph G);
Graph GRAPHload2(Graph grafo,int cardinalita, Arco *archi);

#endif