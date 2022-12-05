#include "pg.h"

stat_t pg_equipInit(stat_t equipin){
    equipin.hp=0;
    equipin.mp=0;
    equipin.atk=0;
    equipin.def=0;
    equipin.mag=0;
    equipin.spr=0;
    return equipin;
}

int pg_read(FILE *fp, pg_t *pgp){
    fscanf(fp,"%s %s %s",pgp->cod,pgp->nome,pgp->classe);
    pgp->b_stat = stat_read(fp,pgp->b_stat);
    pgp->eq_stat = pg_equipInit(pgp->eq_stat);
    return 1;
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp, "%s %s %s ",pgp->cod,pgp->nome,pgp->classe);
    stat_print(fp,&pgp->b_stat);
    equipArray_print(fp,pgp->equip,invArray);
    if(pgp->eq_stat.hp!=0 || pgp->eq_stat.mp!=0 || pgp->eq_stat.atk!=0 || pgp->eq_stat.def!=0 || pgp->eq_stat.mag!=0 || pgp->eq_stat.spr!=0){
        pg_contastat(pgp->eq_stat,pgp->b_stat);
    }
}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip,invArray);
    pgp->eq_stat = equipArray_updateStat(pgp->equip,pgp->eq_stat);

}

void pg_contastat(stat_t b_stat, stat_t eq_stat){
    int cnthp=0,cntmp=0,cntatk=0,cntdef=0,cntmag=0,cntspr=0;
    printf("|->Statistiche complessive\n");
    cnthp = b_stat.hp + eq_stat.hp;
    cntmp = b_stat.mp + eq_stat.mp;
    cntatk = b_stat.atk + eq_stat.atk;
    cntdef = b_stat.def + eq_stat.def;
    cntmag= b_stat.mag + eq_stat.mag;
    cntspr = b_stat.spr + eq_stat.spr;
    if(cnthp < 0) printf("1 ");
    else printf("|-> %d ", cnthp);
    if(cntmp < 0) printf("1 ");
    else printf("%d ", cntmp);
    if(cntatk < 0) printf("1 ");
    else printf("%d ", cntatk);
    if(cntdef < 0) printf("1 ");
    else printf("%d ", cntdef);
    if(cntmag < 0) printf("1 ");
    else printf("%d ", cntmag);
    if(cntspr < 0) printf("1\n");
    else printf("%d\n", cntspr);




}