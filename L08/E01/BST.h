#ifndef LISTAPROVA_BST_H
#define LISTAPROVA_BST_H
#endif //LISTAPROVA_BST_H
#define PREORDER  -1
#define INORDER    0
#define POSTORDER  1
#include "Item.h"
typedef struct  binarysearchtree *BST;

BST  BSTinit(void);//inizializza albero
void BSTfree(BST bst);//dealloca l'albero
int  BSTcount(BST bst);//conta i nodi dell'albero
int  BSTempty(BST bst);//controlla se l'albero e' vuoto
Item BSTsearch(BST bst, info_data k);//ricerca di un nodo con chiave data
void BSTinsert_leafI(BST bst, Item x, float num,float den);//inserire una foglia nell'albero
void RicercaTraDate(BST bst,info_data d1, info_data d2);
void RicercaMaxMin(BST bst);
int BSTvisitMaxMinDistance(BST bst);
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);
void BSTvisit(BST bst, int way);//visita l'albero e lo stampa
void BSTbalance(BST bst);//bilancia l'albero
