#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "azioni.h"
typedef struct node *Link;
struct titolo{char *nome;int num_transazioni;BST albero;};
struct node{InfoPnt Titolo;Link next;};
struct list{Link head;int N;Link tail;};
//ADT I tipo lista di titoli
LIST ListInit(void){
    LIST L=malloc(sizeof(*L));
    L->head=NULL;
    L->N=0;
    return L;
}
Link newNode(InfoPnt z, Link next,Item T, float num,float den) {
    Link x = malloc(sizeof (*x));
    if (x==NULL)
        return NULL;
    x->Titolo=malloc(sizeof(InfoPnt));
    x->Titolo->nome=calloc(10,sizeof(char));
    strcpy(x->Titolo->nome,z->nome);
    x->Titolo->num_transazioni=z->num_transazioni;
    x->Titolo->albero=BSTinit();
    BSTinsert_leafI(x->Titolo->albero,T,num,den);
    x->next=next;
    return x;
}
void SortListIns(LIST L, InfoPnt z,Item T, float num,float den){
    Link x,p;
    if(L->head!=NULL){//controllo se si sta inserendo una data gia' dentro all'albero
        for(x=L->head;x!=NULL;x=x->next){
            if(strcmp(x->Titolo->nome,z->nome)==0){
                BSTinsert_leafI(x->Titolo->albero,T,num,den);
                return;
            }
        }
    }
    if(L->head==NULL || strcmp(L->head->Titolo->nome,z->nome)>0){
        L->head=newNode(z,L->head,T,num,den);
    }else{
        for(x=L->head->next, p=L->head;x!=NULL && strcmp(x->Titolo->nome,z->nome)<0;p=x, x=x->next);
        p->next=newNode(z, x,T,num,den);
    }
}
LIST ListLoad(LIST L,FILE *fin){
    int i,j;
    float valore,numero,num,den,Q;
    fscanf(fin,"%d",&L->N);
    InfoPnt z=TITOLOinit();
    Item T;
    for(i=0;i<L->N;i++){
        num=0;
        den=0;
        fscanf(fin, "%s", z->nome);
        fscanf(fin,"%d",&z->num_transazioni);
        for(j=0; j < z->num_transazioni; j++){
            fscanf(fin,"%d/%d/%d %d:%d %f %f",&T.data.anno,&T.data.mese,&T.data.giorno,&T.data.ora,&T.data.minuto,&valore,&numero);
            num+=(valore*numero);
            den+=numero;
        }
        SortListIns(L, z,T,num,den);
    }
    return L;
}
void PrintList(LIST L){
    Link x;
    printf("\nLISTA:");
    for(x=L->head;x!=NULL;x=x->next)
        StampaTitolo(x->Titolo);
}
InfoPnt RicercaTitolo(LIST L,char *nome){
    Link x;
    if(L->head==NULL){
        printf("lista vuota!");
        return NULL;
    }else{
        for(x=L->head;x!=NULL;x=x->next){
            if(strcmp(x->Titolo->nome,nome)==0){
                return(x->Titolo);
            }
        }
        printf("non e'stato possibile trovare il titolo richiesto!");
        return NULL;
    }
}
void RicercaQuotazione(LIST L,char *nome){
    Item item;
    InfoPnt val;
    info_data k;
    val=RicercaTitolo(L,nome);
    if(val!=NULL){
        printf("\nInserire la data in cui si vuole cercare: (AAAA/M/G): ");
        scanf("%d/%d/%d",&k.anno,&k.mese,&k.giorno);
        item=BSTsearch(val->albero,k);
        if(ITEMcheckNull(item)==0){
            printf("\nQuotazione di %s il %d/%d/%d: %f",val->nome,item.data.anno,item.data.mese,item.data.giorno,item.num/item.den);
        }else
            printf("non e' stato possibile trovare la quotazione a questa data!");
    }
}
void CercaDate(LIST L,char *nome,info_data d1, info_data d2){
    InfoPnt val;
    val=RicercaTitolo(L,nome);
    if(val!=NULL){
        RicercaTraDate(val->albero,d1,d2);
    }
}
void CercaMaxMin(LIST L,char *nome){
    InfoPnt val;
    val=RicercaTitolo(L,nome);
    if(val!=NULL){
        RicercaMaxMin(val->albero);
    }
}
void Bilanciamento(LIST L){
    int x,soglia;
    InfoPnt val;
    char nome[7];
    printf("inserire nome del titolo da cercare: ");
    scanf("%s",nome);
    printf("inserire Soglia da non superare: ");
    scanf("%d",&soglia);
    val=RicercaTitolo(L,nome);
    if(val!=NULL){
        x=BSTvisitMaxMinDistance(val->albero);
        if(x!=-1){
            if(x>soglia){
                BSTbalance(val->albero);
                printf("\nalbero bilanciato!");
            }
        }else
            printf("albero vuoto!");
    }

}
//ADT I tipo Titolo
InfoPnt TITOLOinit(void){
    InfoPnt x=malloc(sizeof(*x));
    x->nome=calloc(10,sizeof(char));
    return x;
}

void StampaTitolo(InfoPnt x){
    printf("\n%s",x->nome);
    printf("\nElenco quotazioni per questo titolo: \n");
    BSTvisit(x->albero,0);
}