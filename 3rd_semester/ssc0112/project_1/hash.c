#include <stdlib.h>
#include <stdio.h>
#include <hash.h>


#define TAM 16

//recebe uma hash por referencia
//e aloca espaco para a ela
void createHash(t_hash *H){
    //allocando o vetor de listas
    //e inicializando todas
    *H = calloc(TAM, sizeof(t_list));
}

//Funcao que insere um item na hash tratando colisões
void insertHash(t_hash *H, t_item item){
    int key = item % TAM;
    insertList(&(*H)[key], item);
}

//Funcao que procura um item na hash e remove ele
void removeHash(t_hash *H, t_item item){
    int key = item % TAM;
    removeItemList(&(*H)[key], item);
}

//funcao que imprime a Hash completa
void printHash(t_hash *H){
    int i;
    for(i = 0; i < TAM; i++) {
        printf("%d: ", i);
        printList((*H)[i]);
    }
}

//funcao que procura um item na hash e caso ele existir
//retorna o numero dele, caso contrario, retorna -1
int searchItemHash(t_hash *H, t_item item){
    int key = item % TAM;
    if(FindItemInList((*H)[key], item)) return key;
    return -1;
}

void destroyHash(t_hash *H){
    int i;
    for(i = 0; i < TAM; i++){
        destroyList(&(*H)[i]);
    }
    free(*H);
}