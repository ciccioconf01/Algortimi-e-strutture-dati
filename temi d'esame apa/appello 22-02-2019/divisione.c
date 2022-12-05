#include "divisione.h"

struct divisione{
    char nome[10];
    int minAddetti1; int CompMinTot1; int CompOttTot1; dipendente *dip1;
    int minAddetti2; int CompMinTot2; int CompOttTot2; dipendente *dip2;
    int minAddetti3; int CompMinTot3; int CompOttTot3; dipendente *dip3;
    int minAddetti4; int CompMinTot4; int CompOttTot4; dipendente *dip4;
};

Divisione DivInit(FILE *fin,Divisione *div,int n){
    div = malloc(n* sizeof(Divisione));
    return div;
}
Divisione LoadDivisioni(FILE *fin,Divisione *div,int *Ndiv,int Ndip){
    int n;
    fscanf(fin,"%d",&n);
    div = DivInit(fin,div,n);
    for(int i=0;i<n;i++){
        fscanf(fin,"%s",div[i]->nome);
        fscanf(fin,"%d %d %d\n%d %d %d\n%d %d %d\n%d %d %d",&div[i]->minAddetti1,&div[i]->CompMinTot1,&div[i]->CompOttTot1,&div[i]->minAddetti2,&div[i]->CompMinTot2,&div[i]->CompOttTot2,&div[i]->minAddetti3,&div[i]->CompMinTot3,&div[i]->CompOttTot3,&div[i]->minAddetti4,&div[i]->CompMinTot4,&div[i]->CompOttTot4);
        div[i]->dip1 = div[i]->dip2 = div[i]->dip3 = div[i]->dip4 = malloc(Ndip * sizeof(dipendente));
        div[i]->dip1[i].matricola = div[i]->dip2[i].matricola = div[i]->dip3[i].matricola = div[i]->dip4[i].matricola = -1;
    }

    *Ndiv=n;

    return div;

}

Divisione Libera(Divisione *div,int n){

    for(int i=0;i<n;i++){
        free(div[i]->dip1);
        free(div[i]->dip2);
        free(div[i]->dip3);
        free(div[i]->dip4);
    }
    free(div);

}

Divisione InserimentoDip(Divisione*div,int Ndiv, int matricola, char *nomeDiv, int tipologia, dipendente *dip, int Ndip  ){//1 op 2 amm, 3 tecn, 4 inf

    for(int i=0;i<Ndiv;i++){
        if(strcmp(div[i]->nome,nomeDiv)==0){
            if(tipologia==1){
                for(int j=0;j<Ndip;j++){
                    if(div[i]->dip1 !=NULL){
                        div[i]->dip1[j] = DipSearch(matricola, Ndip, dip);
                    }
                }

            }

            if(tipologia==2){
                for(int j=0;j<Ndip;j++){
                    if(div[i]->dip2 !=NULL){
                        div[i]->dip2[j] = DipSearch(matricola, Ndip, dip);
                    }
                }

            }

            if(tipologia==3){
                for(int j=0;j<Ndip;j++){
                    if(div[i]->dip3 !=NULL){
                        div[i]->dip3[j] = DipSearch(matricola, Ndip, dip);
                    }
                }

            }

            if(tipologia==4){
                for(int j=0;j<Ndip;j++){
                    if(div[i]->dip4 !=NULL){
                        div[i]->dip4[j] = DipSearch(matricola, Ndip, dip);
                    }
                }

            }

        }
    }
    return div;
}

void Stampa(Divisione *div, int Ndiv, int Ndip){

    for(int i=0;i<Ndiv;i++){
        printf("DIV: %d, Nome: \n",i,div[i]->nome);
        printf("Sezione Operai: ",div[i]->minAddetti1,div[i]->CompMinTot1,div[i]->CompOttTot1);
        if(div[i]->dip1!=NULL){
            PrintaOp(div[i]->dip1);
        }
        printf("Sezione Amministrativa: ",div[i]->minAddetti2,div[i]->CompMinTot2,div[i]->CompOttTot2);
        if(div[i]->dip2!=NULL){
            PrintaOp(div[i]->dip2);
        }
        printf("Sezione Tecnici: ",div[i]->minAddetti3,div[i]->CompMinTot3,div[i]->CompOttTot3);
        if(div[i]->dip3!=NULL){
            PrintaOp(div[i]->dip3);
        }
        printf("Sezione Informatici: ",div[i]->minAddetti4,div[i]->CompMinTot4,div[i]->CompOttTot4);
        if(div[i]->dip4!=NULL){
            PrintaOp(div[i]->dip4);
        }
    }

};

int Verifica(Divisione *div,int Ndiv,int Ndip){
    int conta=0; int acc=0;
    for(int i=0;i<Ndiv;i++){
        for(int j=0;j<Ndip;j++){
            if(div[i]->dip1[j].matricola!=-1){
                conta++;
                acc=acc+div[i]->dip1[j].competenze.operaio;
            }
            if(conta<div[i]->minAddetti1 || acc<div[i]->CompMinTot1){
                return -1;
            }
            conta=0;acc=0;
        }

        for(int j=0;j<Ndip;j++){
            if(div[i]->dip2[j].matricola!=-1){
                conta++;
                acc=acc+div[i]->dip2[j].competenze.operaio;
            }
            if(conta<div[i]->minAddetti1 || acc<div[i]->CompMinTot1){
                return -1;
            }
            conta=0;acc=0;
        }

        for(int j=0;j<Ndip;j++){
            if(div[i]->dip3[j].matricola!=-1){
                conta++;
                acc=acc+div[i]->dip3[j].competenze.operaio;
            }
            if(conta<div[i]->minAddetti1 || acc<div[i]->CompMinTot1){
                return -1;
            }
            conta=0;acc=0;
        }

        for(int j=0;j<Ndip;j++){
            if(div[i]->dip4[j].matricola!=-1){
                conta++;
                acc=acc+div[i]->dip4[j].competenze.operaio;
            }
            if(conta<div[i]->minAddetti1 || acc<div[i]->CompMinTot1){
                return -1;
            }
            conta=0;acc=0;
        }
    }

    return 0;

}

int solOttima(dipendente *dip,Divisione *div,int pos,int pos2, int *mark, int Ndip,int Ndiv,soluzione *sol,soluzione *Bsol){

    if(pos==Ndip){
        div = FunzTraduzione(sol);
        if(Verifica(div,Ndiv,Ndip)!=-1){
            if(verificaOttimita(sol)>max){
                max = verificaOttimita(sol);
                for(int i=0;i<Ndip;i++){
                    Bsol[i].div=sol[i].div;
                    Bsol[i].tip=Bsol[i].tip;
                }
            }
        }
    }

    for(int i=0;i<Ndip;i++){
        sol[pos2].div=i;
        for(int j=0;j<Ndip;j++){
            if(mark[j]==0){
                mark[j]=1;
                sol[pos].dip=j;
                sol[pos].tip=1;
                solOttima(dip,div,pos+1,pos2,mark,Ndip,Ndiv,sol,Bsol);
                sol[pos].tip=2;
                solOttima(dip,div,pos+1,pos2,mark,Ndip,Ndiv,sol,Bsol);
                sol[pos].tip=3;
                solOttima(dip,div,pos+1,pos2,mark,Ndip,Ndiv,sol,Bsol);
                sol[pos].tip=4;
                solOttima(dip,div,pos+1,pos2,mark,Ndip,Ndiv,sol,Bsol);
                mark[j]=0;
                sol[pos].dip=-1;

            }

            solOttima(dip,div,pos,pos2+1,mark,Ndip,Ndiv,sol,Bsol);
        }
    }
}