#include <stdio.h>
#include <string.h>

char *cercaRegexp(char *src, char *regexp){
    char *p;
    char vet[30], vet2[30], flag='f',prosegui='f';
    int dimensione=strlen(src);
    int j=0,k=0;
    char letterainiziale1,letterainiziale2;
    char vettore_ausiliario[10];

    while(*regexp!='\0'){

        if(*regexp=='.'){



            do{
                regexp++;
                vet[j]=*regexp;
                j++;


            } while (*regexp>=65 && *regexp<=90 || *regexp>=97 && *regexp<=122);

            src=src+dimensione-j+1;
            j=0;
            while (*src!='\0'){
                vet2[j]=*src;
                j++;
                src++;
            }

            if(strcmp(vet,vet2)==0){
                flag='t';
                printf("trovato");

            }



    }

        else if (*regexp=='['){
            regexp++;
            if (*regexp=='^'){
                regexp++;
                letterainiziale1=*regexp;
                regexp++;
                do{
                    regexp++;
                    vet[j]=*regexp;
                    j++;

                } while (*regexp>=65 && *regexp<=90 || *regexp>=97 && *regexp<=122);

                letterainiziale2=*src;
                src=src+dimensione-j+1;
                j=0;
                while (*src!='\0'){
                    vet2[j]=*src;
                    j++;
                    src++;
                }

                if(strcmp(vet,vet2)==0 && letterainiziale1!=letterainiziale2){
                    flag='t';
                    printf("trovato");

                }
            }

            else{
                do{

                    vettore_ausiliario[k]=*regexp;
                    regexp++;
                    k++;
                } while (*regexp!=']');

                regexp++;
                do{

                    vet[j]=*regexp;
                    j++;
                    regexp++;
                } while (*regexp>=65 && *regexp<=90 || *regexp>=97 && *regexp<=122);

                letterainiziale2=*src;
                src=src+dimensione-j;
                j=0;
                while (*src!='\0'){
                    vet2[j]=*src;
                    j++;
                    src++;
                }
                for(int s=0;s<k;s++){
                    if(vettore_ausiliario[s]==letterainiziale2){
                        prosegui='t';
                    }
                }

                if(strcmp(vet,vet2)==0 && prosegui=='t'){
                    flag='t';
                    printf("trovato");

                }
            }
        }

        else if(*regexp=='/'){
            regexp++;
            if(*regexp==65){
                regexp++;
                do{

                    vet[j]=*regexp;
                    j++;
                    regexp++;
                } while (*regexp>=65 && *regexp<=90 || *regexp>=97 && *regexp<=122);

                letterainiziale2=*src;
                src=src+dimensione-j;
                j=0;
                while (*src!='\0'){
                    vet2[j]=*src;
                    j++;
                    src++;
                }

                if(strcmp(vet,vet2)==0 && letterainiziale2>=65 && letterainiziale2<=90){
                    flag='t';
                    printf("trovato");

                }
            }

            if (*regexp==97){
                regexp++;
                do{

                    vet[j]=*regexp;
                    j++;
                    regexp++;

                } while (*regexp>=65 && *regexp<=90 || *regexp>=97 && *regexp<=122);

                letterainiziale2=*src;
                src=src+dimensione-j;
                j=0;
                while (*src!='\0'){
                    vet2[j]=*src;
                    j++;
                    src++;
                }

                if(strcmp(vet,vet2)==0 && letterainiziale2>=97 && letterainiziale2<=122){
                    flag='t';
                    printf("trovato");

                }

            }
        }
        else{
            regexp++;
        }



}

    if(flag=='t'){
        return p;
    }
    else{
        printf("non trovato");
        return NULL;
    }

}

int main() {
    char src[100]={"voto"};
    char regexp[100]={"[mv]oto"};
    cercaRegexp(&src, &regexp);
}
