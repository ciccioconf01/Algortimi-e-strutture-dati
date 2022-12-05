#include "inv.h"

stat_t stat_read(FILE *fp, stat_t statp){
    fscanf(fp,"%d %d %d %d %d %d",&statp.hp,&statp.mp,&statp.atk,&statp.def,&statp.mag,&statp.spr);
    return statp;
}

void stat_print(FILE *fp, stat_t *statp){
    fprintf(fp," %d %d %d %d %d %d\n",statp->hp,statp->mp,statp->atk,statp->def,statp->mag,statp->spr);
}

inv_t inv_read(FILE *fp, inv_t invp){
    fscanf(fp,"%s %s",invp.nome,invp.tipo);
    invp.stat=stat_read(fp,invp.stat);
    return invp;
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"%s %s", invp->nome, invp->tipo);
    stat_print(fp,&invp->stat);
}

stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}