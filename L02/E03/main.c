#include <stdio.h>
#include<string.h>
#include <stdlib.h>
typedef struct {
    char codice[30];
    char partenza[30];
    char arrivo[30];
    char data[30];
    char ora_partenza[30];
    char ora_arrivo[30];
    int ritardo;
}dizionario;

typedef enum {
    r_stampa, r_ordinamento_data, r_ordinamento_codice, r_stazionepartenza, r_stazionearrivo, r_ricercalineare, r_ricercadicotomica, r_lettura_nuovofile, r_fine,
}comando_e;


comando_e leggiComando(){
    comando_e x;
    char stringa[500];
    char tabella[r_fine][500]={
            "stampa","ordinaperdata","ordinapercodice","ordinaperpartenza","ordinaperarrivo","ricercalineare","ricercadicotomica","letturanuovofile"
    };
    printf("stampa, ordinaperdata, ordinapercodice, ordinaperpartenza, ordinaperarrivo, ricercalineare, ricercadicotomica, letturanuovofile\n");
    scanf("%s",stringa);
    x=r_stampa;
    while (x<r_fine && strcmp(stringa,tabella[x])){
        x++;
    }
    return x;
}

void stampa(dizionario **diz1,dizionario **diz2, dizionario **diz3, dizionario **diz4,  int n){
    char stringa[10];
    printf("Quale ordinamento vuoi stampare? (data,codice,partenza,arrivo)\n");
    scanf("%s",stringa);
    if (strcmp(stringa,"data")==0){
        for(int i=0;i<n;i++){
            printf("%s %s %s %s %s %s %d\n",diz1[i]->codice,diz1[i]->partenza,diz1[i]->arrivo,diz1[i]->data,diz1[i]->ora_partenza,diz1[i]->ora_arrivo, diz1[i]->ritardo);
        }
    }

    if (strcmp(stringa,"codice")==0){
        for(int i=0;i<n;i++){
            printf("%s %s %s %s %s %s %d\n",diz2[i]->codice,diz2[i]->partenza,diz2[i]->arrivo,diz2[i]->data,diz2[i]->ora_partenza,diz2[i]->ora_arrivo, diz2[i]->ritardo);
        }
    }

    if (strcmp(stringa,"partenza")==0){
        for(int i=0;i<n;i++){
            printf("%s %s %s %s %s %s %d\n",diz3[i]->codice,diz3[i]->partenza,diz3[i]->arrivo,diz3[i]->data,diz3[i]->ora_partenza,diz3[i]->ora_arrivo, diz3[i]->ritardo);
        }
    }

    if (strcmp(stringa,"arrivo")==0){
        for(int i=0;i<n;i++){
            printf("%s %s %s %s %s %s %d\n",diz4[i]->codice,diz4[i]->partenza,diz4[i]->arrivo,diz4[i]->data,diz4[i]->ora_partenza,diz4[i]->ora_arrivo, diz4[i]->ritardo);
        }
    }

}

void ordinamento_data(dizionario **p,int n){

    struct dizionario *temp;

    for (int i = 0;  i < n; i++) {
        for (int j = 0; j < n-1 ; j++) {

            if (strcmp(p[j]->data, p[j+1]->data)>0){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
            else if (strcmp(p[j]->data, p[j+1]->data)==0){
                if (strcmp(p[j]->ora_partenza, p[j+1]->ora_partenza)>0){
                    temp=p[j];
                    p[j]=p[j+1];
                    p[j+1]=temp;

                }
            }

        }

    }

}

void ordinamento_codice(dizionario **p, int n){

    struct dizionario *temp;

    for (int i = 0;  i < n; i++) {
        for (int j = 0; j < n-1 ; j++) {

            if (strcmp(p[j]->codice, p[j+1]->codice)>0){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }

        }

    }

}

void ordinamento_stazionepartenza(dizionario **p, int n){
    struct dizionario *temp;

    for (int i = 0;  i < n; i++) {
        for (int j = 0; j < n-1 ; j++) {

            if (strcmp(p[j]->partenza, p[j+1]->partenza)>0){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }

        }

    }

}

void ordinamento_stazionearrivo(dizionario **p, int n){

    struct dizionario *temp;

    for (int i = 0;  i < n; i++) {
        for (int j = 0; j < n-1 ; j++) {

            if (strcmp(p[j]->arrivo, p[j+1]->arrivo)>0){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }

        }

    }

}

void ricercalineare(dizionario **p, int n){
    char stringa[20];
    printf("inserisci la stazione di partenza da cercare\n");
    scanf("%s",stringa);
    for(int i=0;i<n;i++){
        if(strcmp(p[i]->partenza,stringa)==0){
            printf("%s %s %s %s %s %s %d\n",p[i]->codice,p[i]->partenza,p[i]->arrivo,p[i]->data,p[i]->ora_partenza,p[i]->ora_arrivo, p[i]->ritardo);
        }
    }
}

int ricercadicotomica(dizionario **p, int n, int l, int r, char stringa[],char flag){
    int m=0;
    if(l>r){
        if(flag!='t'){

            printf("l'elemento non e' stato trovato\n");
        }
        return -1;
    }
    m=(l+r)/2;
    if(strcmp(stringa,p[m]->partenza)==0){
        printf("%s %s %s %s %s %s %d\n",p[m]->codice,p[m]->partenza,p[m]->arrivo,p[m]->data,p[m]->ora_partenza,p[m]->ora_arrivo, p[m]->ritardo);
        flag='t';
    }
    if(strcmp(stringa,p[m]->partenza)<0){
        return ricercadicotomica(p,n,l,m-1,stringa,flag);
    }
    return ricercadicotomica(p,n,m+1,r,stringa,flag);

}

dizionario *letturanuovofile(dizionario *c, int n,FILE* fin){

    free(c);


    c=malloc(n*(sizeof(*c)));
    for(int i=0;i<n;i++){
        fscanf(fin,"%s",c[i].codice);
        fscanf(fin,"%s",c[i].partenza);
        fscanf(fin,"%s",c[i].arrivo);
        fscanf(fin,"%s",c[i].data);
        fscanf(fin,"%s",c[i].ora_partenza);
        fscanf(fin,"%s",c[i].ora_arrivo);
        fscanf(fin,"%d",&c[i].ritardo);
    }

    return c;

}

dizionario **alloca2(dizionario **diz,int n){
    diz=malloc(n* sizeof(*diz));
    for(int i=0;i<n;i++){
        diz[i]=malloc(n* sizeof(diz));
    }
    return diz;
}

void free2(dizionario **diz){
    free(diz);
}

int menuParola(dizionario *c,int n,comando_e comando){
    char flag;
    char stringa[20];
    int l=0, r=n-1;
    char nome[20];
    FILE *fin;
    struct dizionario **p[1000];
    struct dizionario **diz1[1000];
    struct dizionario **diz2[1000];
    struct dizionario **diz3[1000];
    struct dizionario **diz4[1000];
    *diz1=alloca2(diz1,n);
    *diz2=alloca2(diz2,n);
    *diz3=alloca2(diz3,n);
    *diz4=alloca2(diz4,n);
    for(int i=0;i<n;i++){
        p[i]=&c[i];
        diz1[i]=diz2[i]=diz3[i]=diz4[i]=&c[i];
    }

    int continua=1;
    while (continua){
        comando=leggiComando();

        switch (comando) {
            case r_stampa:
                stampa(diz1,diz2,diz3,diz4,n);
                break;
            case r_ordinamento_data:
                ordinamento_data(diz1,n);
                break;
            case r_ordinamento_codice:
                ordinamento_codice(diz2,n);
                break;
            case r_stazionepartenza:
                ordinamento_stazionepartenza(diz3,n);
                break;
            case r_stazionearrivo:
                ordinamento_stazionearrivo(diz4,n);
                break;
            case r_ricercalineare:
                ricercalineare(p,n);
                break;
            case r_ricercadicotomica:
                ordinamento_stazionepartenza(p,n);
                printf("inserisci la stazione di partenza da cercare\n");
                scanf("%s",stringa);
                ricercadicotomica(p,n,l,r,stringa,flag);
                break;
            case r_lettura_nuovofile:
                printf("Inserisci il nome del nuovo file\n");
                scanf("%s",nome);
                fin=fopen(nome,"r");
                if(fin==NULL){
                    return 1;
                }
                fscanf(fin,"%d",&n);

                c=letturanuovofile(c,n,fin);
                free2(p);
                free2(diz1);
                free2(diz2);
                free2(diz3);
                free2(diz4);

                alloca2(p,n);
                alloca2(diz1,n);
                alloca2(diz2,n);
                alloca2(diz3,n);
                alloca2(diz4,n);

                for(int i=0;i<n;i++){
                    p[i]=&c[i];
                    diz1[i]=diz2[i]=diz3[i]=diz4[i]=&c[i];
                }
                break;
            case r_fine:
                continua=0;
                break;

        }
    }
}



int main() {
    FILE *fin;
    comando_e comando;
    dizionario *c;
    int n,i;
    if((fin=fopen("log.txt","r"))==NULL){
        printf("errore di apertura");
        return 1;
    }
    fscanf(fin,"%d",&n);
    if(n>1000){
        printf("file non valido");
        return 2;
    }

    c=malloc(n*(sizeof(*c)));

    for(i=0;i<n;i++){
        fscanf(fin,"%s",c[i].codice);
        fscanf(fin,"%s",c[i].partenza);
        fscanf(fin,"%s",c[i].arrivo);
        fscanf(fin,"%s",c[i].data);
        fscanf(fin,"%s",c[i].ora_partenza);
        fscanf(fin,"%s",c[i].ora_arrivo);
        fscanf(fin,"%d",&c[i].ritardo);
    }

    menuParola(c,n,comando);
}


