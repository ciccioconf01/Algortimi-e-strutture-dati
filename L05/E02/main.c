#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char colore1;
    int valore1;
    char colore2;
    int valore2;

} tessera;

typedef struct {
    tessera val;
    char orientamentoT1;
    char orientamentoT2;

}Scacchiera;

void stampa_scacchiera(Scacchiera **scacchiera, int nr) {


    for (int i = 0; i < nr; i++) {


        if (scacchiera[i][0].val.valore1 != -1) {
            if (scacchiera[i][0].orientamentoT1 == 'o') {
                printf(" %c  ", scacchiera[i][0].val.colore2);
            } else { printf(" %c  ", scacchiera[i][0].val.colore1); }
        } else { printf("    "); }

        if (scacchiera[i][1].val.valore1 != -1) {
            if (scacchiera[i][1].orientamentoT1 == 'o') {
                printf(" %c  ", scacchiera[i][1].val.colore2);
            } else { printf(" %c  ", scacchiera[i][1].val.colore1); }
        } else { printf("     "); }

        if (scacchiera[i][2].val.valore1 != -1) {
            if (scacchiera[i][2].orientamentoT1 == 'o') {
                printf(" %c  ", scacchiera[i][2].val.colore2);
            } else { printf(" %c  ", scacchiera[i][2].val.colore1); }
        } else { printf("     "); }

        printf("\n");

        if (scacchiera[i][0].val.valore1 != -1) {
            if (scacchiera[i][0].orientamentoT1 == 'o') {
                printf("%c %d ", scacchiera[i][0].val.colore1, scacchiera[i][0].val.valore1);
            } else { printf("%c %d ", scacchiera[i][0].val.colore2, scacchiera[i][0].val.valore2); }
        } else { printf("     "); }

        if (scacchiera[i][1].val.valore1 != -1) {
            if (scacchiera[i][1].orientamentoT1 == 'o') {
                printf("%c %d ", scacchiera[i][1].val.colore1, scacchiera[i][1].val.valore1);
            } else { printf("%c %d ", scacchiera[i][1].val.colore2, scacchiera[i][1].val.valore2); }
        } else { printf("     "); }

        if (scacchiera[i][2].val.valore1 != -1) {
            if (scacchiera[i][2].orientamentoT1 == 'o') {
                printf("%c %d ", scacchiera[i][2].val.colore1, scacchiera[i][2].val.valore1);
            } else { printf("%c %d ", scacchiera[i][2].val.colore2, scacchiera[i][2].val.valore2); }
        } else { printf("     "); }

        printf("\n");

        if (scacchiera[i][0].val.valore1 != -1) {
            if (scacchiera[i][0].orientamentoT1 == 'o') {
                printf(" %d  ", scacchiera[i][0].val.valore2);
            }
            else { printf(" %d  ", scacchiera[i][0].val.valore1); }
        }
        else { printf("     "); }

        if (scacchiera[i][1].val.valore1 != -1) {
            if (scacchiera[i][1].orientamentoT1 == 'o') {
                printf(" %d  ", scacchiera[i][1].val.valore2);
            } else { printf(" %d  ", scacchiera[i][1].val.valore1); }
        } else { printf("     "); }

        if (scacchiera[i][2].val.valore1 != -1) {
            if (scacchiera[i][2].orientamentoT1 == 'o') {
                printf(" %d  ", scacchiera[i][2].val.valore2);
            } else { printf(" %d  ", scacchiera[i][2].val.valore1); }
        } else { printf("     "); }

        printf("\n\n");


    }

}

int massimo(Scacchiera **scacchiera,int nr,int nc){
    char colore_riga,flag='t';
    int accumula_riga[nr];
    for (int i = 0; i < nr; i++) {
        accumula_riga[i]=0;
    }

    int accumula_colonna[nc];
    for (int i = 0; i < nc; i++) {
        accumula_colonna[i]=0;
    }

    int accumulaTOT=0;

    for (int i = 0; i < nr; i++) {
        if(scacchiera[i][0].orientamentoT1=='o')
        colore_riga=scacchiera[i][0].val.colore1;
        else colore_riga=scacchiera[i][0].val.colore2;
        for (int j = 0; j < nc && flag!='f'; j++) {
            if(scacchiera[i][j].orientamentoT1=='o'){
                if(colore_riga==scacchiera[i][j].val.colore1){
                    accumula_riga[i]=accumula_riga[i]+scacchiera[i][j].val.valore1;
                }
                else{flag='f'; accumula_riga[i]=0;}
            }
            else{
                if(colore_riga==scacchiera[i][j].val.colore2){
                    accumula_riga[i]=accumula_riga[i]+scacchiera[i][j].val.valore2;
                }
                else{flag='f'; accumula_riga[i]=0;}
            }


        }
        flag='t';

    }

    flag='t';

    for (int j = 0; j < nc; j++) {
        if (scacchiera[0][j].orientamentoT1=='o')
        colore_riga=scacchiera[0][j].val.colore2;
        else colore_riga=scacchiera[0][j].val.colore2;
        for (int i = 0; i < nr && flag!='f'; i++) {
            if(scacchiera[i][j].orientamentoT1=='o'){
            if(colore_riga==scacchiera[i][j].val.colore2){
                accumula_colonna[j]=accumula_colonna[j]+scacchiera[i][j].val.valore2;
            }
            else{flag='f'; accumula_colonna[j]=0;}
            }
            else{
                if(colore_riga==scacchiera[i][j].val.colore1){
                    accumula_colonna[j]=accumula_colonna[j]+scacchiera[i][j].val.valore1;
                }
                else{flag='f'; accumula_colonna[j]=0;}
            }
        }
        flag='t';

    }

    for (int i = 0; i < nr ; i++) {
        accumulaTOT=accumulaTOT+accumula_riga[i];

    }

    for (int i = 0; i < nc; i++) {
        accumulaTOT=accumulaTOT+accumula_colonna[i];

    }

    return accumulaTOT;


}

int inserimento(int pos,Scacchiera **scacchiera,Scacchiera **sol,int nr, int nc,tessera *vettore,int dim_vett,int mass){
int New_mass;
    if(pos==dim_vett) {
        New_mass=massimo(scacchiera,nr,nc);
        if(New_mass>mass){
            mass=New_mass;
            for (int i = 0; i < nr; i++) {
                for (int j = 0; j < nc; j++) {

                    sol[i][j].val.valore1=scacchiera[i][j].val.valore1;
                    sol[i][j].val.valore2=scacchiera[i][j].val.valore2;
                    sol[i][j].val.colore1=scacchiera[i][j].val.colore1;
                    sol[i][j].val.colore2=scacchiera[i][j].val.colore2;
                    sol[i][j].orientamentoT1=scacchiera[i][j].orientamentoT1;
                    sol[i][j].orientamentoT2=scacchiera[i][j].orientamentoT2;
                }

            }
        }
        return mass ;

    }
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                if(scacchiera[i][j].val.valore2==-1){
                    scacchiera[i][j].val.colore1=vettore[pos].colore1;
                    scacchiera[i][j].val.colore2=vettore[pos].colore2;
                    scacchiera[i][j].val.valore1=vettore[pos].valore1;
                    scacchiera[i][j].val.valore2=vettore[pos].valore2;
                    scacchiera[i][j].orientamentoT1='o';
                    scacchiera[i][j].orientamentoT2='v';

                    mass=inserimento(pos+1,scacchiera,sol,nr,nc,vettore,dim_vett,mass);



                    scacchiera[i][j].val.colore1=vettore[pos].colore1;
                    scacchiera[i][j].val.colore2=vettore[pos].colore2;
                    scacchiera[i][j].val.valore1=vettore[pos].valore1;
                    scacchiera[i][j].val.valore2=vettore[pos].valore2;
                    scacchiera[i][j].orientamentoT1='v';
                    scacchiera[i][j].orientamentoT2='o';

                    mass=inserimento(pos+1,scacchiera,sol,nr,nc,vettore,dim_vett,mass);

                    scacchiera[i][j].val.colore1='x';
                    scacchiera[i][j].val.colore2='x';
                    scacchiera[i][j].val.valore1=-1;
                    scacchiera[i][j].val.valore2=-1;
                    scacchiera[i][j].orientamentoT1='x';
                    scacchiera[i][j].orientamentoT2='x';

                }

            }

        }
    return mass;
    }


int main() {

    FILE *fin;
    if((fin=fopen("tiles.txt","r"))==NULL){
        return 1;
    }
    int n;
    fscanf(fin,"%d\n",&n);
    tessera *vettore;
    vettore=malloc(n* sizeof(*vettore));

    for(int i=0;i<n;i++){
        fscanf(fin,"%c %d %c %d\n",&vettore[i].colore1,&vettore[i].valore1,&vettore[i].colore2,&vettore[i].valore2);
    }

    fclose(fin);

    if((fin=fopen("board.txt","r"))==NULL){
        return 2;
    }

    int nr,nc,val1,val2;

    fscanf(fin,"%d %d",&nr,&nc);

    Scacchiera **scacchiera;
    scacchiera=malloc(nr* sizeof(Scacchiera *));
    for(int i=0;i<nr;i++){
        scacchiera[i]=malloc(nc* sizeof(Scacchiera));
    }

    int z=0;
    int *tessere_utilizzate;

    tessere_utilizzate=malloc(n* sizeof(int ));


    for (int i = 0; i < nr; i++) {

        for (int j = 0; j < nc; j++) {

            fscanf(fin,"%d/%d",&val1,&val2);
            if(val1>=0 && val1<=9 && val2>=0 && val2<=9){
                if(val2==0){
                scacchiera[i][j].val.colore1=vettore[val1].colore1;
                scacchiera[i][j].val.valore1=vettore[val1].valore1;
                scacchiera[i][j].val.colore2=vettore[val1].colore2;
                scacchiera[i][j].val.valore2=vettore[val1].valore2;
                scacchiera[i][j].orientamentoT1='o';
                scacchiera[i][j].orientamentoT2='v';

                }
                else
                {
                    scacchiera[i][j].val.colore1=vettore[val1].colore1;
                    scacchiera[i][j].val.valore1=vettore[val1].valore1;
                    scacchiera[i][j].val.colore2=vettore[val1].colore2;
                    scacchiera[i][j].val.valore2=vettore[val1].valore2;
                    scacchiera[i][j].orientamentoT1='v';
                    scacchiera[i][j].orientamentoT2='o';
                }
                tessere_utilizzate[z]=val1;
                z++;
            }
            else{
                scacchiera[i][j].val.colore1='x';
                scacchiera[i][j].val.valore1=-1;
                scacchiera[i][j].val.colore2='x';
                scacchiera[i][j].val.valore2=-1;
                scacchiera[i][j].orientamentoT1='x';
                scacchiera[i][j].orientamentoT2='x';
            }

        }

    }

    tessera *vettore_da_inserire;
    vettore_da_inserire=malloc((n-z)* sizeof(tessera));
    int j=0;
    z=0;
    for (int i = 0; i < n; i++) {
        if(i!=tessere_utilizzate[j]){

        vettore_da_inserire[z].colore1=vettore[i].colore1;
        vettore_da_inserire[z].colore2=vettore[i].colore2;
        vettore_da_inserire[z].valore1=vettore[i].valore1;
        vettore_da_inserire[z].valore2=vettore[i].valore2;
        z++;
        }
        else{
            j++;

        }
    }

    free(vettore);
    free(tessere_utilizzate);

    int pos=0,massimo_valore=0;

    Scacchiera **sol;
    sol=malloc(nr* sizeof(Scacchiera *));
    for(int i=0;i<nr;i++){
        sol[i]=malloc(nc* sizeof(Scacchiera));
    }


    massimo_valore=inserimento(pos,scacchiera,sol,nr,nc,vettore_da_inserire,z,massimo_valore);
    printf("La scacchiera di valore massimo e':\n");
    stampa_scacchiera(sol,nr);
    printf("\n il valore della scacchiera e' %d",massimo_valore);

    free(vettore_da_inserire);
    for (int i = 0; i < nr ; i++) {
        free(sol[i]);
    }
    free(sol);

    for (int i = 0; i < nr ; i++) {
        free(scacchiera[i]);
    }
    free(scacchiera);

}
