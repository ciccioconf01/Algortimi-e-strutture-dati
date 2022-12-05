#include <stdio.h>
#include "dipendente.h"
#include "divisione.h"

int main() {

    FILE *fin;
    dipendente *dip;
    int Ndip;
    fin=fopen("dipendenti.txt","r");
    dip = LoadDipendenti(fin,dip,&Ndip);

    Divisione *div;
    int Ndiv;
    fin=fopen("divisioni.txt","r");
    div = LoadDivisioni(fin,div,&Ndiv,Ndip);

    fin=fopen("associazioni.txt","r");
    int matricola, tipologia; char nomeDiv[10];
    while (!feof(fin)){
        fscanf(fin,"%d %d %s",&matricola,&tipologia,nomeDiv);
        div = InserimentoDip(div,Ndiv,matricola,nomeDiv,tipologia, dip,Ndip);
    }

    int a=Verifica(div,Ndiv,Ndip);
    if(a==-1){
        printf("condizioni NON verificate");
    }
    else{
        printf("condizioni verificate");
    }
    int pos;


    soluzione *sol;
    soluzione *Bsol;
    sol=malloc(Ndip * sizeof(soluzione));
    Bsol=malloc(Ndip * sizeof(soluzione));
    for(int i=0;i<Ndip;i++){
        sol[i].div=-1; sol[i].tip=-1;
        Bsol[i].tip=-1; Bsol[i].div=-1;
    }
    solOttima(dip,div,pos,Ndip,Ndiv,sol,Bsol);

    for(int i=0;i<Ndip;i++){
        if(Bsol[i].div!=-1){
            for(int j=0;j<Ndip;j++){
                if(Bsol[i].dip)
            }
        }
    }

}
