#include "equipArray.h"

typedef struct equipArray_s{
    inv_t *vet;
};

equipArray_t equipArray_init(){
    equipArray_t *equip;
    equip = malloc(8 * sizeof (inv_t *));
    for(int i = 0 ;i<8;i++){
        equip[i]=NULL;
    }
    return equip;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    int cnt=0;
    for(int i = 0;i<8;i++){
        if(equipArray!=NULL){
            cnt++;
        }
    }
    return cnt;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    for(int i = 0;i<8;i++) {
        if (equipArray[i].vet != NULL){
                    printf("|->");
                    inv_print(fp,equipArray[i].vet);
                }
    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    char nome[50];
    int scelta=0;
    int in;
    printf("Inserire:\n1 per aggiungere\n2 per rimuovere\n");
    scanf("%d",&scelta);
    switch (scelta) {
        case 1:
            printf("digita nome equip:\n");
            scanf("%s", nome);
            in = invArray_searchByName(invArray, nome);
            for(int i = 0; i<8;i++){
                if(equipArray[i].vet==NULL){
                    equipArray[i].vet = invArray_getByIndex(invArray,in);
                    return;
                }
            }
            printf("Inventario già pieno\n");
            break;
        case 2:
            printf("digita nome equip:\n");
            scanf("%s", nome);
            for(int i = 0; i<8;i++){
                if(strcmp(equipArray[i].vet->nome,nome)==0){
                    equipArray[i].vet = NULL;
                    return;
                }
            }
            printf("Elemento non presente nell' inventario\n");
            break;
    }
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    invArray_getByIndex(equipArray, index);
}

stat_t equipArray_updateStat(equipArray_t equip, stat_t statistica){
    statistica.hp=0;
    statistica.mp=0;
    statistica.atk=0;
    statistica.def=0;
    statistica.mag=0;
    statistica.spr=0;
    for(int i = 0;i<8;i++){
        if(equip[i].vet!=NULL){
            statistica.hp = statistica.hp + equip[i].vet->stat.hp;
            statistica.mp = statistica.mp + equip[i].vet->stat.mp;
            statistica.atk = statistica.atk + equip[i].vet->stat.atk;
            statistica.def = statistica.def + equip[i].vet->stat.def;
            statistica.mag = statistica.mag + equip[i].vet->stat.mag;
            statistica.spr = statistica.spr+ equip[i].vet->stat.spr;
        }
    }
    return statistica;
}