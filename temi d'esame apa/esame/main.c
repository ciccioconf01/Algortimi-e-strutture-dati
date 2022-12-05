#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char **GRID;

typedef struct{
    char nome[15];
    int valore;
}parola;

typedef int **SOL;


// il file proposta è una matrice di interi, tale matrice è inizialmente inizializzata con tutti zeri,
// le lettere selezionate sono marcate con degli uni,
// nel caso ci sia una sovrapposizione si incrementa il valore val[i][j] all'intero successivo

// la funzione Verifica ritorna -1 per indicare che la proposta è errata
// la funzione controllaNome ritorna 0 se la parola non è stata trovata
int controllaNome(char *nome, int index, parola *vetparole, int Nparole){
    char key[15]={"//"};
    for(int i=0;i<index;i++){
        key[i]=nome[i];
    }

    for(int i=0;i<Nparole;i++){
        if(strcmp(key, vetparole[i].nome)==0){
            return 1;
        }
    }
    return 0;
}
int Verifica (char **griglia, int **proposta, int nr, int nc, parola *vetparole, int Nparole) {

    int **matVisit;
    matVisit = malloc(nr * sizeof(int *));
    for (int i = 0; i < nr; i++) {
        matVisit[i] = malloc(nc * sizeof(int));
    }
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            matVisit[i][j] = 0;
        }
    }
    int x, y; int contavero=0,contafalso=0; int dentro=0;
    int index = 0;
    char nome[15];
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if (proposta[i][j] > 2) { return -1; }
            if (proposta[i][j] != 0 && (matVisit[i][j] == 0 || matVisit[i][j]==1 && proposta[i][j]==2) ) {
                if (proposta[i][j] == 1 || proposta[i][j] == 2) {
                    matVisit[i][j] ++;
                    nome[0] = griglia[i][j];
                    index++;
                    if (j + 1 < nc && proposta[i][j + 1] != 0) {
                        x = i;
                        y = j + 1; dentro=1;
                        while (y<nc && proposta[x][y] != 0) {
                            nome[index] = griglia[x][y];
                            matVisit[x][y] ++;
                            y++;
                            index++;
                        }
                        if (controllaNome(nome, index, vetparole, Nparole) == 0)
                        { contafalso++;
                            while (x!=i || y!=j+1){
                                y--;
                                matVisit[x][y]--;

                            }
                        }
                        else{contavero++;}
                    }
                    index = 1;

                    if (i + 1 < nr && proposta[i + 1][j] != 0) {
                        x = i + 1;
                        y = j; dentro=1;
                        while (x<nr && proposta[x][y] != 0) {
                            nome[index] = griglia[x][y];
                            matVisit[x][y]++;
                            x++;
                            index++;
                        }
                        if (controllaNome(nome, index, vetparole, Nparole) == 0)
                        { contafalso++;
                            while (x!=i+1 || y!=j){
                                x--;
                                matVisit[x][y]--;

                            }
                        }
                        else{contavero++;}
                    }
                    index = 1;
                    if (i + 1 < nr && j + 1 < nc && proposta[i + 1][j + 1] != 0) {
                        x = i + 1;
                        y = j + 1; dentro=1;
                        while (x<nr && y<nc && proposta[x][y] != 0) {
                            nome[index] = griglia[x][y];
                            matVisit[x][y] ++;
                            x++;
                            y++;
                            index++;
                        }
                        if (controllaNome(nome, index, vetparole, Nparole) == 0)
                        { contafalso++;
                            while (x!=i+1 || y!=j+1){
                                x--;y--;
                                matVisit[x][y]--;

                            }
                        }
                        else{contavero++;}
                    }
                    if(proposta[i][j]==1){
                        if (contavero==0){
                            return -1;
                        }
                    }
                    if(dentro==0){return -1;}
                    dentro=0;


                }
                index = 0; contavero=0; contafalso=0;
            }
        }

    }
     for (int i = 0; i < nr; i++) {
            free(matVisit[i]);
        }
       free(matVisit);
       return 1;
}

// la funzione RitornaValore è molto simile alla controllaNome definita nel punto precedente solamente che, in caso di strcmp()==0, al posto di ritornare 1 ritornavetparole[i].valore

int RitornaValore(char *nome, int index, parola *vetparole, int Nparole){
    char key[15]={"//"};
    for(int i=0;i<index;i++){
        key[i]=nome[i];
    }

    for(int i=0;i<Nparole;i++){
        if(strcmp(key, vetparole[i].nome)==0){
            return vetparole[i].valore;
        }
    }
    return 0;
}

int CalcolaVal( char **griglia, int**proposta,int nr, int nc, parola *vetparole, int Nparole){
    int **matriceVisit;
    int acc=0;
    int x,y,index=0;
    char nome[15];
    matriceVisit=malloc(nr*sizeof(int*));
    for(int i=0;i<nr;i++){
        matriceVisit[i] = malloc(nc*sizeof(int));
    }
    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            if(proposta[i][j]==1 || proposta[i][j]==2 && (matriceVisit[i][j] == 0 || matriceVisit[i][j]==1 && proposta[i][j]==2)){
                nome[0]=griglia[i][j]; index++; matriceVisit[i][j]=1;

                if(j+1<nc && proposta[i][j+1]!=0){
                    x=i;y=j+1;
                    while(y<nc && proposta[x][y]!=0){
                        nome[index]=griglia[x][y];
                        matriceVisit[x][y]++;
                        y++; index++;
                    }
                    acc=acc+RitornaValore(nome,index,vetparole,Nparole);
                }


                index=1;
                if(i+1<nr && proposta[i+1][j]!=0){
                    x=i+1; y=j;
                    while(x<nr && proposta[x][y]!=0){
                        nome[index]=griglia[x][y];
                        matriceVisit[x][y]++;
                        x++; index++;
                    }
                    acc=acc+RitornaValore(nome,index,vetparole,Nparole);
                }
                index=1;
                if(i+1<nr && j+1<nc && proposta[i+1][j+1]!=0){
                    x=i+1;y=j+1;
                    while(x<nr && y<nc && proposta[x][y]!=0){
                        nome[index]=griglia[x][y];
                        matriceVisit[x][y]++; x++; y++; index++;
                    }
                    acc=acc+RitornaValore(nome,index,vetparole,Nparole);
                }
                index=0;

            }
        }
    }
    for(int i=0;i<nr;i++){
            free(matriceVisit[i]);
        }
        free(matriceVisit);
    return acc;
}

int solOttimaR(char ** griglia, SOL sol, int nr, int nc, int pos, int i, int j, int **Bsol,
               int max, parola *vetparole,int Nparole){
    if(pos==nr*nc){
        if(Verifica( griglia, sol,nr,nc,vetparole,Nparole)==1){
            int x=CalcolaVal(griglia,sol,nr,nc,vetparole,Nparole);
            if(x>max){
                max=x;
                for(int i=0;i<nr;i++){
                    for(int j=0;j<nc;j++){
                        Bsol[i][j]=sol[i][j];
                    }
                }
            }
        }
        return max;

    }
    for(int x=0;x<3;x++){
        sol[i][j] = x;
        if(j==nc-1){
            max = solOttimaR(griglia,sol,nr,nc,pos+1,i+1,0,Bsol,max,vetparole,Nparole);
        }
        else{
            max = solOttimaR(griglia,sol,nr,nc,pos+1,i,j+1,Bsol,max,vetparole,Nparole);
        }

    }
    return max;
}

void solOttima(SOL sol, int nr, int nc, char ** griglia, parola *vetparole, int Nparole){
    int i=0,j=0,pos=0;
    int **Bsol; int max=0;
    Bsol = malloc(nr*sizeof(int*));
    for(int i=0;i<nr;i++){
        Bsol[i]=malloc(nc*sizeof(int));
    }

    max = solOttimaR(griglia,sol,nr,nc,pos,i,j,Bsol,max,vetparole,Nparole);

    printf("Il valore massimo e':%d",max);

}
  

    int main() {
        GRID griglia;
        int nr, nc;
        FILE *fin = fopen("griglia3.txt", "r");
        fscanf(fin, "%d %d", &nr, &nc);
        griglia = malloc(nr * sizeof(char *));
        for (int i = 0; i < nr; i++) {
            griglia[i] = malloc(nc * sizeof(char));
        }
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                fscanf(fin, " %c", &griglia[i][j]);
            }
        }

        FILE *fn = fopen("parole.txt", "r");
        int conta = 0;

        char tmp[15];
        int val;
        while (!feof(fn)) {
            fscanf(fn, "%s %d", tmp, &val);
            conta++;
        }
        fclose(fin);
        parola *par;
        par = malloc(conta * sizeof(parola));
        FILE *fp = fopen("parole.txt", "r");
        int i = 0;
        while (!feof(fp)) {
            fscanf(fp, "%s %d", par[i].nome, &par[i].valore);
            i++;
        }

        FILE *f = fopen("proposta3.txt", "r");
        int **proposta;
        proposta = malloc(nr * sizeof(int *));
        for (int i = 0; i < nr; i++) {
            proposta[i] = malloc(nc * sizeof(int));
        }

        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                fscanf(f, "%d", &proposta[i][j]);
            }
        }

        int a = Verifica(griglia, proposta, nr, nc, par, conta);
        if (a == -1) { printf("la proposta NON e' valida\n"); }
        else { printf("la proposta e' valida\n"); }

        int **sol;
        sol = malloc(nr * sizeof(int *));
        for (int i = 0; i < nr; i++) {
            sol[i] = malloc(nc * sizeof(int));
        }
        solOttima(sol,nr,nc,griglia,par,conta);
        for (int i = 0; i < nr; i++) {
            free(sol[i]);
            free(proposta[i]);
            free(griglia[i]);
        }
        free(sol);
        free(proposta);
        free(griglia);
        free(par);

    }







