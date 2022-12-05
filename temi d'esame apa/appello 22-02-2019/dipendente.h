#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int operaio;
    int amministrativo;
    int tecnico;
    int informatico;
}comp;

typedef struct {
    int matricola;
    char nome[20];
    char cognome[20];
    comp competenze
}dipendente;

dipendente *LoadDipendenti(FILE *fin,dipendente *dip, int *Ndip);
dipendente DipSearch(int matricola, int Ndip, dipendente *dip);
