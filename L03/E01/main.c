#include <stdio.h>

int maggioritario(int *a, int l, int r, int n){
    int m=(l+r)/2;
    int u,v;
    int conta=0;
    int conta2=0;

    if(l==r){
        return a[l];
    }
    u=maggioritario(a,l,m,n/2);
    v=maggioritario(a,m+1,r,n/2);

    if(u==v){
        return u;
    }
    if(u!=-1 && v==-1){
        for(int i=l;i<=r;i++){
            if(a[i]==u){
                conta++;
            }
        }
        if(conta>n/2){
            return u;
        }
        else{
            return -1;
        }

    }

    if(u==-1 && v!=-1){
        for(int i=l;i<=r;i++){
            if(a[i]==v){
                conta++;
            }
        }
        if(conta>n/2){
            return v;
        }
        else{
            return -1;
        }
    }
    if(u!=-1 && v!=-1){
        for(int i=l;i<=r;i++){
            if(a[i]==u){
                conta++;
            }
            if(a[i]==v){
                conta2++;
            }
        }
        if(conta>n/2){
            return u;
        }
        else if(conta2>n/2){
            return v;
        }
        else{
            return -1;
        }
    }




}

int majority( int *a, int N){
    int l=0,r=N-1,mag;
    mag=maggioritario(a,l,r,N);
    return mag;

}

int main() {
    int vet[11]={3,8,3,4,3,3,9,3,5,3,4};
    int n=11;
    int numero;

    numero=majority(vet,n);
    printf("Il maggioritario e': %d",numero);


}
