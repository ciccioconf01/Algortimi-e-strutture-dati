#include "pgList.h"
#include "pg.h"

typedef struct pgList_s *link;
struct pgList_s{
    pg_t val;
    link successivo;
};

pgList_t pgList_init(){
    link x = malloc(sizeof *x);
    return x;
}

void pgList_free(pgList_t pgList){
    link x;
    for (x=pgList;x!=NULL;x=x->successivo){
        pg_clean(x);
        free(x);
    }

}

pgList_t pgList_read(FILE *fp, pgList_t pgList){
    pg_t personaggio;
    while (!feof(fp)){
        pg_read(fp,&personaggio);
        pgList = inserimento_in_coda(pgList,personaggio);
    }
    return pgList;
}

void pgList_insert(pgList_t pgList, pg_t pg){
    inserimento_in_coda(pgList,pg);
}

pgList_t pgList_remove(pgList_t pgList, char* cod){
    link x, p;
    for (x=pgList, p=NULL; x!=NULL; p=x, x=x->successivo) {
        if (strcmp(x->val.cod, cod) == 0){
            if (pgList==x){
                p=pgList;
                pgList=pgList->successivo;
                pg_clean(p);
                free(p);

                return pgList;
            }
            else{
                p->successivo= x->successivo;
                pg_clean(x);
                free(x);
                return pgList;
            }

        }
    }
    return pgList;

}

pg_t *pgList_searchByCode(pgList_t pgList, char *cod){
    if(pgList != NULL){
        while(pgList != NULL){
            if(strcmp(cod,pgList->val.cod)==0) {
                return pgList;
            }
            pgList = pgList -> successivo;
        }
        printf("Elemento non trovato\n");
    }
    else {
        printf("LISTA VUOTA \n");
    }
}

link newNode(pg_t val, link successivo ) {
    link x;
    x=pgList_init();
    x->val.equip=equipArray_init();
    if (x==NULL)
        return NULL;
    else {
        strcpy(x->val.cod,val.cod);
        strcpy(x->val.nome,val.nome);
        strcpy(x->val.classe,val.classe);
        x->val.b_stat.hp=val.b_stat.hp;
        x->val.b_stat.mp=val.b_stat.mp;
        x->val.b_stat.atk=val.b_stat.atk;
        x->val.b_stat.def=val.b_stat.def;
        x->val.b_stat.mag=val.b_stat.mag;
        x->val.b_stat.spr=val.b_stat.spr;
        x->val.eq_stat.hp=val.eq_stat.hp;
        x->val.eq_stat.mp=val.eq_stat.mp;
        x->val.eq_stat.atk=val.eq_stat.atk;
        x->val.eq_stat.def=val.eq_stat.def;
        x->val.eq_stat.mag=val.eq_stat.mag;
        x->val.eq_stat.spr=val.eq_stat.spr;
        x->successivo = successivo;
    }
    return x;
}

link inserimento_in_coda(link h,pg_t val) {
    link x;
    if (h==NULL) {
        return newNode(val,NULL);
    }
    for(x=h; x->successivo!=NULL; x=x->successivo);
    x->successivo=newNode(val,NULL);
    return h;
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    while (pgList!=NULL){
        pg_print(fp,pgList,invArray);
        pgList=pgList->successivo;
    }
}

