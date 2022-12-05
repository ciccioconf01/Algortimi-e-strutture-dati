#ifndef LISTAPROVA_LISTATITOLI_H
#define LISTAPROVA_LISTATITOLI_H
#include "BST.h"
typedef struct titolo *InfoPnt;
typedef struct list *LIST;
LIST ListInit(void);
LIST ListLoad(LIST L,FILE *fin);
void PrintList(LIST L);
InfoPnt RicercaTitolo(LIST L,char *nome);
void RicercaQuotazione(LIST L,char *nome);
void CercaDate(LIST L,char *nome,info_data d1, info_data d2);
void CercaMaxMin(LIST L,char *nome);
void Bilanciamento(LIST L);

InfoPnt TITOLOinit(void);
void StampaTitolo(InfoPnt x);

#endif
