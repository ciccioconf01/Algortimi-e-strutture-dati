#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
#define DBG 0

typedef struct BSTnode* link;
struct BSTnode { Item item; link p; link l; link  r; int N; };

struct binarysearchtree { link root;  link z; };

static link NEW(Item item, link p, link l, link r, int N,float den, float num);
static void treeFree(link h, link z);
static int  countR(link h, link z);
static void treePrintR(link h, link z, int strategy);
static Item searchR(link h, info_data k, link z);
static link rotR(link h);
static link rotL(link h);
static link partR(link h, int r);

static link NEW(Item item, link p, link l, link r, int N,float num, float den) {//INIZIALIZZAZIONE ALBERO
    link x = malloc(sizeof *x);
    x->item = item; x->p = p; x->l = l; x->r = r; x->N = N;
    x->item.den+=den;
    x->item.num+=num;
    return x;
}

BST BSTinit( ) {//INIZIALIZZAZIONE ALBERO
    BST bst = malloc(sizeof *bst) ;
    bst->root = ( bst->z = NEW(ITEMsetNull(), NULL, NULL, NULL, 0,0,0));
    return bst;
}

void BSTfree(BST bst) {//DEALLOCAZIONE ALBERO
    if (bst == NULL)
        return;
    treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}

static void treeFree(link h, link z) {//DEALLOCAZIONE ALBERO
    if (h == z)
        return;
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}
static int countR(link h, link z) {//CONTO DELLE FOGLIE
    if (h == z)
        return 0;
    return countR(h->l, z) + countR(h->r, z) +1;
}
int BSTcount(BST bst) {//CONTO DELLE FOGLIE
    return countR(bst->root, bst->z);
}

int BSTempty(BST bst) {//CHECK ALBERO VUOTO
    if (BSTcount(bst) == 0)
        return 1;
    return 0;
}

void BSTinsert_leafI(BST bst, Item x, float num,float den) {//INSERIMENTO FOGLIA
    link p = bst->root, h = p;
    if (bst->root == bst->z) {
        bst->root = NEW(x, bst->z, bst->z, bst->z, 1,num,den);
        return;
    }
    while (h != bst->z) {
        p = h;
        h->N++;
        if(KEYcmp(KEYget(x), KEYget(h->item))==0){
            h->item.den+=den;
            h->item.num+=num;
            return;
        }else
            h = (KEYcmp(KEYget(x), KEYget(h->item))==-1) ? h->l : h->r;
    }
    h = NEW(x, p, bst->z, bst->z, 1,num,den);
    if (KEYcmp(KEYget(x), KEYget(p->item))==-1)
        p->l = h;
    else
        p->r = h;
}
void BSTvisit(BST bst, int strategy) {//VISITA ALBERO
    if (BSTempty(bst))
        return;
    treePrintR(bst->root, bst->z, strategy);
}
void treePrintR(link h, link z, int strategy) {//STAMPA ALBERO
    if (h == z)
        return;

    if (strategy == PREORDER)
        ITEMstore(h->item);
    treePrintR(h->l, z, strategy);
    if (strategy == INORDER)
        ITEMstore(h->item);
    treePrintR(h->r, z, strategy);
    if (strategy == POSTORDER)
        ITEMstore(h->item);
}
Item searchR(link h, info_data k, link z) {//RICERCA DI UN NODO, CHIAVE:DATA
    int cmp;
    if (h == z)
        return ITEMsetNull();
    cmp = KEYcmp(k, KEYget(h->item));
    if (cmp==0)
        return h->item;
    if (cmp==-1)
        return searchR(h->l, k, z);
    else
        return searchR(h->r, k, z);
}
Item BSTsearch(BST bst, info_data k) {//RICERCA
    return searchR(bst->root, k, bst->z);
}
void SearchBetweenDates(link h, link z,info_data d1, info_data d2,float *max,float *min) {//STAMPA ALBERO
    if (h == z)
        return;
    if(KEYcmp(h->item.data,d1)==1 && KEYcmp(h->item.data,d2)==-1){
        if((h->item.num/h->item.den)>*max)
            *max=h->item.num/h->item.den;
        if((h->item.num/h->item.den)<*min)
            *min=h->item.num/h->item.den;
    }
    SearchBetweenDates(h->l, z,d1,d2,max,min);
    SearchBetweenDates(h->r, z,d1,d2,max,min);
}
void RicercaTraDate(BST bst,info_data d1, info_data d2){//Ricerca massimo e minimo tra due date
    if (BSTempty(bst)){
        printf("\nalbero vuoto!");
        return;
    }
    float max=0;
    float min=(bst->root->item.num/bst->root->item.den);
    SearchBetweenDates(bst->root, bst->z,d1,d2,&max,&min);
    if(max!=0){
        printf("\nMassimo: %f",max);
        printf("\nMinimo: %f",min);
    }
    else
        printf("\nnon e' stato possibile trovare una quotazione tra questo intervallo di date!");
}
void SearchMaxMin(link h, link z,float *max,float *min) {//ricerca mmassimo e minimo ALBERO
    if (h == z)
        return;
    if((h->item.num/h->item.den)>*max)
        *max=h->item.num/h->item.den;
    if((h->item.num/h->item.den)<*min)
        *min=h->item.num/h->item.den;
    SearchMaxMin(h->l, z,max,min);
    SearchMaxMin(h->r, z,max,min);
}
void RicercaMaxMin(BST bst){//Ricerca massimo e minimo dell'intero albero
    if (BSTempty(bst)){
        printf("\nalbero vuoto!");
        return;
    }
    Item z;
    float max=0;
    float min=(bst->root->item.num/bst->root->item.den);
    SearchMaxMin(bst->root, bst->z,&max,&min);
    if(max!=0){
        printf("\nMassimo: %f",max);
        printf("\nMinimo: %f",min);
    }
    else
        printf("\nnon e' stato possibile trovare una quotazione tra questo intervallo di date!");
}
void VisitDistance(link h, link z,int *min,int *max,int *cnt){
    if (h == z){
        if(*max<*cnt)
            *max=*cnt;
        if(*min>*cnt)
            *min=*cnt;
        *cnt-=1;
        return;
    }
    *cnt++;
    VisitDistance(h->l, z,min,max,cnt);
    *cnt++;
    VisitDistance(h->r, z,min,max,cnt);
}
int BSTvisitMaxMinDistance(BST bst){
    if (BSTempty(bst))
        return -1;
    int min=1000,max=0,cnt=0;
    VisitDistance(bst->root, bst->z,&min,&max,&cnt);
    return max/min;
}
link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r->p = h;
    x->r = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += h->l->N;
    h->N += h->r->N;
    return x;
}
link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l->p = h;
    x->l = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += h->l->N;
    h->N += h->r->N;
    return x;
}

link partR(link h, int r) {
    int t  = h->l->N;
    if ( t > r) {
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if ( t < r) {
        h->r = partR(h->r, r-t-1);
        h = rotL(h);
    }
    return h;
}
link balanceR(link h, link z) {
    int r;
    if (h == z)
        return z;
    r = (h->N+1)/2-1;
    h = partR(h, r);
    h->l = balanceR(h->l, z);
    h->r = balanceR(h->r, z);
    return h;
}

void BSTbalance(BST bst) {
    bst->root = balanceR(bst->root, bst->z);
}
