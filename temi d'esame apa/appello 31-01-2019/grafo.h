#include <stdio.h>
#include <stdlib.h>
typedef struct graph *Graph;

typedef struct edge { int v; int w; } Edge;

void  GRAPHfree(Graph G);
void GRAPHinsertE(Graph G, int id1, int id2);
int ritornaV(Graph G);
int Acquisisci(Graph G, char V);
int Lvet(int *proposta, int v);
int VerificaProposta(Graph G, int *proposta);
int calcolo(int *val, int v);
int *traduzione(int *val, int v);
int kernelMinimo(Graph G, int pos, int *sol, int *Bsol, int min, int *solTrad);
char GraphSearch(Graph G, int val);
Graph GraphInsertEdge(int **madj, char v1, char v2);
Graph GraphInit(int v);
Graph GraphLoad(Graph G, FILE *fin);
int MigliorCammino(Graph G, int *vetKernel, int lunghezza, int *max,int pos, int *vetPassati,int min);
