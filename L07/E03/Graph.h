#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHstore(Graph G, FILE *fout);
void  GRAPHedges(Graph G, Edge *a);
int findV(FILE *);
void GraphPrint(Graph g);
void Stampamatrice(Graph g);
void CreaLista(Graph g);
void PrintLista(Graph g);
void ControllaVertice(Graph g);

#endif