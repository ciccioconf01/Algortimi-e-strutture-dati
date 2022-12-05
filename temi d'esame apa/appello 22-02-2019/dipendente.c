#include "dipendente.h"

dipendente *LoadDipendenti(FILE *fin,dipendente *dip,int *Ndip){

    int n;
    fscanf(fin,"%d",&n);
    dip = malloc(n * sizeof(dipendente));
    for(int i=0;i<n;i++){
        fscanf(fin,"%d %s %s %d %d %d %d",&dip[i].matricola,dip[i].nome,dip[i].cognome,&dip[i].competenze.operaio,&dip[i].competenze.amministrativo,&dip[i].competenze.tecnico,&dip[i].competenze.informatico);
    }
    *Ndip=n;
    return dip;
}

dipendente DipSearch(int matricola, int Ndip, dipendente *dip){
    for(int i=0;i<Ndip;i++){
        if(dip[i].matricola == matricola){
            return dip[i];
        }
    }
}
