#include <stdio.h>
#include <stdlib.h>

typedef struct edge { int v; int w; } Edge;

typedef struct graph *Graph;
Graph GraphLoad(Graph G, FILE *fin);
int ControllaProposta(FILE *fin,Graph G);
Graph GRAPHinit(int V);
void  GRAPHinsertE(Graph G, int id1, int id2);
int ritornaNumVerticiGraph(Graph G);
int SoluzioneOttima(Graph G,int V,int *vettorePartizioni,int pos, int cardinalita, int *Bsol);
int controllaCardinalita(int *vettorePartizioni,int V);
char * GraphSearch(Graph G, int i);