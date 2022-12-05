#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include "dipendente.h"
typedef struct {
    int div;
    int dip;
    int tip;
}soluzione;

typedef struct divisione *Divisione;
Divisione LoadDivisioni(FILE *fin,Divisione *div,int *Ndiv,int Ndip);
Divisione DivInit(FILE *fin,Divisione *div,int n);
Divisione Libera(Divisione *div,int n);
Divisione InserimentoDip(Divisione*div,int Ndiv, int matricola, char *nomeDiv, int tipologia ,dipendente *dip, int Ndip );
int Verifica(Divisione *div,int Ndiv,int Ndip);