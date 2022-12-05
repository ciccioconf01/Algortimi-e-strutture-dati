#include <stdio.h>
#include <stdlib.h>

int allocazione(int ***matr, int nr, int nc, FILE *fin){

        int **m;
        m=(int**)malloc(nr* sizeof(int *));
        if (m==NULL){
            return 2;
        }
        for(int i=0;i<nr;i++){
            m[i]=(int*)malloc(nc*sizeof (int));
            if(m[i]==NULL){
                return 3;
            }
            for(int j=0;j<nc;j++){
                fscanf(fin,"%d",&m[i][j]);

            }

        }

    *matr=m;

}

int  separa(int **mat,int **vnero, int **vbianco, int nr, int nc){

    int indicebianco=0,indicenero=0;
    int *vbianco2,*vnero2;

    vbianco2=malloc((nr*nc/2+1) * sizeof(*vbianco ));
    vnero2=malloc((nr*nc/2+1) * sizeof(*vnero));
    for (int i = 0; i < nr; i++) {

        for(int j=0;j<nc;j++){
            if((i+j)%2==0 || i+j==0){
                vbianco2[indicebianco]=mat[i][j];
                indicebianco++;
            }
            else{
                vnero2[indicenero]=mat[i][j];
                indicenero++;
            }
        }


    }
    *vbianco=vbianco2;
    *vnero=vnero2;



}

int stampa_e_dealloca(int *vnero,int *vbianco, int nr, int nc){

    printf("Nelle caselle bianche sono contenuti i valori:\n");
    for (int i = 0; i < (nr*nc/2+1) ; i++) {
        printf("%d\n",vbianco[i]);
    }

    printf("Nelle caselle nere sono contenuti i valori:\n");
    for (int i = 0; i < (nr*nc/2) ; i++) {
        printf("%d\n",vnero[i]);
    }

    free(vnero);
    free(vbianco);

}

int main() {
    FILE *fin;
    int nr, nc, **matr,*vnero,*vbianco;
    fin=fopen("mat.txt","r");
    if(fin==NULL){
        return 1;
    }

    fscanf(fin,"%d %d",&nr,&nc );

    allocazione(&matr,nr,nc,fin);
    separa(matr,&vnero,&vbianco,nr,nc);
    stampa_e_dealloca(vnero,vbianco,nr,nc);


}
