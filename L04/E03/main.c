#include <stdio.h>
#include <stdlib.h>

int controlla(int *sol, int pos){
    int flag=1;



        if(pos!=0){

                if(sol[pos-1]==0){
                    if(sol[pos]!=0 && sol[pos]!=1){
                        flag=0;
                    }
                }

                else if(sol[pos-1]==3){
                    if(sol[pos]!=2 && sol[pos]!=3){
                        flag=0;
                    }
                }

                else if(sol[pos-1]==2){
                    if(sol[pos]!=0 && sol[pos]!=1){
                        flag=0;
                    }
                }
                else if(sol[pos-1]==1) {
                    if(sol[pos]!=2 && sol[pos]!=3){
                        flag=0;
                    }
                }
            }


    return flag;
}






int perm(int pos, int *mat, int *sol, int cnt, int lmax){

    if(cnt>0){
        return cnt;
    }

    if(pos>=lmax){


        for(int i=0;i<lmax;i++){
            printf("%d ",sol[i]);
        }
        printf("\n");
        return cnt+1;


    }



    for(int i=0;i<4;i++){
        if(mat[i]>0){

            sol[pos] = i;
            mat[i]--;
            if(controlla(sol, pos)==1) {

                cnt = perm(pos + 1, mat, sol, cnt, lmax);
                if (cnt > 0) {
                    return cnt;
                }
            }
            sol[pos]=-1;
            mat[i]++;

        }
    }


    return cnt;
}







int main() {
    FILE *fin;
    if((fin=fopen("easy_test_set.txt","r"))==NULL){
        return 1;
    }
    int n;
    fscanf(fin,"%d", &n);
    int lmax;
    int **mat;
    int matStatic[n][4];
    int flag=1;

    mat=malloc(n* sizeof(int*));
    for(int i=0;i<n;i++){
        mat[i]=malloc(4* sizeof(int ));
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<4;j++){
            fscanf(fin,"%d",&mat[i][j]);
            matStatic[i][j]=mat[i][j];

        }
    }
    fclose(fin);

    int *sol,pos=0,cnt=0;


    for(int j=0;j<n;j++) {
        printf("TEST # %d\n", j + 1);
        lmax = mat[j][0] + mat[j][1] + mat[j][2] + mat[j][3];


        sol = malloc((lmax) * sizeof(int));

        for (int z = 0; z < lmax; z++) {
            sol[z] = -1;
        }


        for (int z = 0; z < 4; z++) {


            mat[j][z] = matStatic[j][z];


        }

        int i = 0;
        cnt = perm(pos, mat[j], sol, cnt, lmax);
        free(sol);
        if (cnt == 0){

            flag=0;
            for (i = 1; i < lmax && cnt==0 ; i++) {




                sol = malloc((lmax - i) * sizeof(int));

                for (int z = 0; z < lmax - i; z++) {
                    sol[z] = -1;
                }

                for (int z = 0; z < 4; z++) {


                    mat[j][z] = matStatic[j][z];


                }


                cnt = perm(pos, mat[j], sol, cnt, lmax - i);

                free(sol);

            }
        }



        if(flag==1){
            printf("collana di lunghezza massima = %d\n\n",lmax-i);
        } else{
            printf("collana di lunghezza massima = %d\n\n",lmax-i+1);
        }
        flag=1;

        cnt=0;


    }



    for(int i=0;i<n;i++){
        free(mat[i]);
    }
    free(mat);

}