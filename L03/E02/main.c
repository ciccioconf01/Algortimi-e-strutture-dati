#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char **scelte;
    int num_scelte;
}livello;

int playlist(int pos, livello *val, char **sol, int n, int cnt){

    if(pos>=n){
        for(int i=0;i<n;i++){
            printf("%s ",sol[i]);
        }
        printf("\n");
        return cnt+1;
    }

    for(int i=0;i<val[pos].num_scelte;i++){
        strcpy(sol[pos],val[pos].scelte[i]);
        cnt=playlist(pos+1,val,sol,n,cnt);
    }
    return cnt;

}
int main() {
    FILE *fp_read;
    int n,i,j;
    char  **sol;
    livello *val;
    if((fp_read=fopen("brani.txt", "r"))==NULL)
        return -1;
    fscanf(fp_read,"%d",&n);
    val=malloc(n*sizeof(livello));
    if(val==NULL)
        return -1;
    for(i=0;i<n;i++) {
        fscanf(fp_read,"%d", &val[i].num_scelte);
        val[i].scelte = malloc(val[i].num_scelte * sizeof(char *));
        if(val[i].scelte==NULL)
            exit(1);
        for(j=0;j<val[i].num_scelte;j++){
            val[i].scelte[j]=malloc(255*sizeof(char));
            if(val[i].scelte[j]==NULL)
                exit(1);
            fscanf(fp_read,"%s", val[i].scelte[j]);
        }
    }

    int pos=0,cnt=0;

    sol=malloc(n*(sizeof(char*)));
    for(i=0;i<n;i++){
        sol[i]=malloc(255* sizeof(char));
    }

    cnt=playlist(pos,val,sol,n,cnt);

    printf("il numero di combinazioni e' %d",cnt);

    free(sol);
    for(i=0;i<n;i++){
        free(val[i].scelte);
    }
    free(val);

}



