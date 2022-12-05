#include <stdio.h>

int gcd(int a, int b){
    int temp;

    if(b>a){
        temp=a;
        a=b;
        b=temp;
    }

    if(a==b){
        return a;
    }

    if(a%2!=0 && b%2!=0){
        return gcd((a-b)/2,b);
    }
    else if(a%2==0 && b%2!=0){
        return gcd(a/2,b);
    }

    else if(a%2!=0 && b%2==0){
        return gcd(a,b/2);
    }
    else{
        return 2*gcd(a/2,b/2);
    }

}

int main() {
    int a=10;
    int b=20;
    int mcd;
    mcd=gcd(a,b);
    printf("Il MCD tra %d e %d e' %d",a,b,mcd);
}
