#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int giorno;
    int mese;
    int anno;
}data;

typedef struct {
    char codice[6];
    char nome[50];
    char cognome[50];
    data data_di_nascita;
    char via[50];
    char citta[50];
    int cap;
} item;

typedef struct node *link;
struct node{
    item val;
    link next;
};


void StampaLista(struct node *h) {
    struct node *s;
    s=h;

    while(s!=NULL) {
        printf("%s %s %s %d/%d/%d %s %s %d\n", s->val.codice, s->val.nome, s->val.cognome, s->val.data_di_nascita.giorno,s->val.data_di_nascita.mese,s->val.data_di_nascita.anno, s->val.via, s->val.citta, s->val.cap);
        s=s->next;
    }

    printf("\n");
}


link newnode(item val, link next) {
    link x = malloc(sizeof *x);

    if (x==NULL)
        return NULL;
    else {
        strcpy(x->val.codice,val.codice);
        strcpy(x->val.nome,val.nome);
        strcpy(x->val.cognome,val.cognome);
        x->val.data_di_nascita.giorno=val.data_di_nascita.giorno;
        x->val.data_di_nascita.mese=val.data_di_nascita.mese;
        x->val.data_di_nascita.anno=val.data_di_nascita.anno;
        strcpy(x->val.via,val.via);
        strcpy(x->val.citta,val.citta);
        x->val.cap=val.cap;
        x->next = next;
    }
    return x;
}


link inserimento_ordinato(link h, item elemento) {
    link x,p;
    if (h==NULL ||(h->val.data_di_nascita.anno < elemento.data_di_nascita.anno || (h->val.data_di_nascita.anno == elemento.data_di_nascita.anno && h->val.data_di_nascita.mese < elemento.data_di_nascita.mese)||(h->val.data_di_nascita.anno == elemento.data_di_nascita.anno && h->val.data_di_nascita.mese == elemento.data_di_nascita.mese && h->val.data_di_nascita.giorno < elemento.data_di_nascita.giorno)))
        return newnode(elemento, h);
    for (x=h->next, p=h;
         x!=NULL && (x->val.data_di_nascita.anno > elemento.data_di_nascita.anno || (x->val.data_di_nascita.anno == elemento.data_di_nascita.anno && x->val.data_di_nascita.mese > elemento.data_di_nascita.mese)||(x->val.data_di_nascita.anno == elemento.data_di_nascita.anno && x->val.data_di_nascita.mese == elemento.data_di_nascita.mese && x->val.data_di_nascita.giorno > elemento.data_di_nascita.giorno));
         p=x, x=x->next);
    p->next = newnode(elemento, x);
    return h;
}

item ricerca(link h, char *chiave) {
    link x;
    x=h;

        while (x!=NULL){
            if(strcmp(chiave, x->val.codice)==0){
                return x->val;

            }
            x=x->next;
        }
        printf("L'elemento non e' stato trovato");


}


item cancellazione_per_codice(link *hp,char *codice) {
    link h;
    link x, p;
    h=*hp;

    for (x=h, p=NULL; x!=NULL; p=x, x=x->next) {
        if (strcmp(x->val.codice, codice) == 0){
            if (h==x){
                *hp=h->next;
                return x->val;
            }
            else{
                p->next = x->next;
                return x->val;
            }

        }
    }

}

item cancellazione_per_date(link *hp, data d1, data d2){
    link x,h,p;
    h=*hp;

    for (x=h, p=NULL; x!=NULL; p=x, x=x->next) {
        if (d1.anno < x->val.data_di_nascita.anno &&  x->val.data_di_nascita.anno< d2.anno){
            if (h==x){
                *hp=h->next;
                return x->val;
            }
            else{
                p->next = x->next;
                return x->val;
            }

        }
        if(d1.anno == x->val.data_di_nascita.anno){

            if(d1.mese < x->val.data_di_nascita.mese){
                if (h==x){
                    *hp=h->next;
                    return x->val;
                }
                else{
                    p->next = x->next;
                    return x->val;
                }
            }
        }

        if(d2.anno == x->val.data_di_nascita.anno){

            if(d2.mese > x->val.data_di_nascita.mese){
                if (h==x){
                    *hp=h->next;
                    return x->val;
                }
                else{
                    p->next = x->next;
                    return x->val;
                }
            }
        }

        if(d1.mese == x->val.data_di_nascita.mese){

            if(d1.giorno < x->val.data_di_nascita.giorno){
                if (h==x){
                    *hp=h->next;
                    return x->val;
                }
                else{
                    p->next = x->next;
                    return x->val;
                }
            }
        }

        if(d2.mese == x->val.data_di_nascita.mese){

            if(d2.giorno > x->val.data_di_nascita.giorno){
                if (h==x){
                    *hp=h->next;
                    return x->val;
                }
                else{
                    p->next = x->next;
                    return x->val;
                }
            }
        }

    }

    item el;
    el.cap=-1;
    return el;



}

void scrivi_file(link h){
    link x;
    x=h;
    FILE *fout;
    char nomefile[50];
    printf("Inserire il nome del file in cui salvare la lista\n");
    scanf("%s",nomefile);
    fout= fopen(nomefile, "w");
    while(x != NULL){
        fprintf(fout,"%s %s %s %d/%d/%d %s %s %d\n",x->val.codice, x->val.nome,x->val.cognome,x->val.data_di_nascita.giorno, x->val.data_di_nascita.mese, x->val.data_di_nascita.anno, x->val.via, x->val.citta, x->val.cap);
        x=x->next;
    }
    fclose(fout);
}


int main() {
    FILE *fin;
    item tabella;
    struct node *h;



    fin=fopen("anag1.txt", "r");
    if (fin==NULL) {
        printf("Errore in apertura del file");
        return 1;
    }

    h=NULL;

    while(!feof(fin)) {
        fscanf(fin,"%s",tabella.codice);
        fscanf(fin, "%s",tabella.nome);
        fscanf(fin,"%s",tabella.cognome);
        fscanf(fin,"%d/%d/%d",&tabella.data_di_nascita.giorno,&tabella.data_di_nascita.mese,&tabella.data_di_nascita.anno );
        fscanf(fin,"%s",tabella.via);
        fscanf(fin,"%s",tabella.citta);
        fscanf(fin, "%d",&tabella.cap);


        h=inserimento_ordinato(h,tabella);
    }

    fclose(fin);



    item elemento;
    int scelta=0;


    while (scelta!=-1){
        printf("inserisci un comando\n");
        printf("-1 per uscire\n");
        printf("1 inserimento ordinato di un elemento in lista da tastiera\n");
        printf("2 inserimento ordinato di elementi in lista da file\n");
        printf("3 ricerca per codice di un elemento\n");
        printf("4 cancellazione dato il codice\n");
        printf("5 cancellazione dato intervallo di date\n");
        printf("6 stampa della lista su file\n");
        printf("7 stampa della lista\n");
        scanf("%d",&scelta);

        switch (scelta) {
            case 1:
                printf("inserisci codice, nome, cognome, data di nascita, via, citta' e cap del nuovo elemento\n");
                scanf("%s %s %s %d/%d/%d %s %s %d",elemento.codice,elemento.nome,elemento.cognome,&elemento.data_di_nascita.giorno,&elemento.data_di_nascita.mese,&elemento.data_di_nascita.anno,elemento.via,elemento.citta,&elemento.cap);

                h=inserimento_ordinato(h,elemento);
                break;

            case 2:
                printf("Inserisci il nome del file\n");
                FILE *fin2;
                char nomefile[50];
                scanf("%s",nomefile);
                fin2=fopen(nomefile,"r");
                while (!feof(fin2)){

                    fscanf(fin2,"%s %s %s %d/%d/%d %s %s %d",elemento.codice,elemento.nome,elemento.cognome,&elemento.data_di_nascita.giorno,&elemento.data_di_nascita.mese,&elemento.data_di_nascita.anno,elemento.via,elemento.citta,&elemento.cap);
                    h=inserimento_ordinato(h,elemento);
                }
                break;

            case 3:
                printf("inserisci il codice da cercare\n");
                char *codice;
                codice=malloc(10*(sizeof(char)));
                scanf("%s",codice);
                elemento=ricerca(h,codice);
                printf("%s %s %s %d/%d/%d %s %s %d\n", elemento.codice, elemento.nome, elemento.cognome, elemento.data_di_nascita.giorno,elemento.data_di_nascita.mese,elemento.data_di_nascita.anno, elemento.via, elemento.citta, elemento.cap);
                free(codice);
                break;

            case 4:
                printf("inserisci il codice da cercare ed eliminare\n");
                char *codice1;
                codice1=malloc(10*(sizeof(char)));
                scanf("%s",codice1);
                elemento=cancellazione_per_codice(&h,codice1);
                printf("L'elemento cancellato e': %s %s %s %d/%d/%d %s %s %d\n", elemento.codice, elemento.nome, elemento.cognome, elemento.data_di_nascita.giorno,elemento.data_di_nascita.mese,elemento.data_di_nascita.anno, elemento.via, elemento.citta, elemento.cap);
                free(codice1);
                break;

            case 5:
                printf("inserisci la prima data\n");
                data d1;
                data d2;

                scanf("%d/%d/%d",&d1.giorno,&d1.mese,&d1.anno);
                printf("inserisci la seconda data\n");
                scanf("%d/%d/%d",&d2.giorno,&d2.mese,&d2.anno);
                while (elemento.cap!=-1){
                elemento=cancellazione_per_date(&h,d1,d2);
                if(elemento.cap!=-1){
                printf("L'elemento cancellato e': %s %s %s %d/%d/%d %s %s %d\n", elemento.codice, elemento.nome, elemento.cognome, elemento.data_di_nascita.giorno,elemento.data_di_nascita.mese,elemento.data_di_nascita.anno, elemento.via, elemento.citta, elemento.cap);
                }
                }
                break;



            case 6:
                scrivi_file(h);
                break;


            case 7:
                StampaLista(h);
                break;

            default:
                return 2;


        }

    }




}
