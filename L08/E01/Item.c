#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Item.h"
typedef int key;

void ITEMstore(Item val) {
    printf("Data: %d/%d/%d quotazione giornaliera: %f\n", val.data.anno,val.data.mese,val.data.giorno, val.num/val.den);
}

int ITEMcheckNull(Item val) {
    if (val.den==0 & val.num==0)
        return 1;
    return 0;
}

Item ITEMsetNull() {
    Item val;
    val.den=0;
    val.num=0;
    return val;
}


info_data KEYget(Item val) {
    return val.data;
}

int KEYcmp(info_data k1, info_data k2){//0: uguali;1: k1>k2;-1:k2>k1
    if(k1.anno==k2.anno){
        if(k1.mese==k2.mese){
            if(k1.giorno==k2.giorno)
                return 0;
            else if(k1.giorno>k2.giorno)
                return 1;
            else
                return -1;
        }else if(k1.mese>k2.mese){
            return 1;
        }else
            return -1;
    }else if(k1.anno>k2.anno){
        return 1;
    }else
        return -1;
}


