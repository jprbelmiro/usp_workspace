#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"
#include "file.h"
#include "regexCustom.h"

//Funcoes de Liberação de Memória
void free_(void *pointer){
    if(pointer != NULL){
        free(pointer);
    }
}

//Funcoes de Ordenação
static void merge(int *vec, int start, int mid, int end) {
    int left = start, right = mid+1, aux = 0;
    int auxvec[end-start+1];

    while(left <= mid && right <= end){
        if(vec[left] >= vec[right]){
            auxvec[aux] = vec[left];
            left++;
        }else{
            auxvec[aux] = vec[right];
            right++;
        }
        aux++;
    }

    while(left<=mid){  //Caso ainda haja elementos na primeira metade
        auxvec[aux] = vec[left];
        aux++;left++;
    }

    while(right <= end){   //Caso ainda haja elementos na segunda metade
        auxvec[aux] = vec[right];
        aux++;right++;
    }

    for(aux = start; aux <= end ;aux++){    //Move os elementos de volta para o vec original
        vec[aux] = auxvec[aux-start];
    }
}

void mergesort(int *vec, int start, int end){
    if (start < end) {
        int mid = (start+end)/2;

        mergesort(vec, start, mid);
        mergesort(vec, mid+1, end);
        merge(vec, start, mid, end);
    }
    return;
}

//compara os inteiros A e B, retornando um numero 
//menor, igual ou maior que 0, caso A seja menor, 
//igual ou maior que B, respectivamente.
int fieldCompare(const void *A, const void *B){
    int *X = (int *) A;
    int *Y = (int *) B;
    
    return (*X) - (*Y);
}

//compara os indices A e B, retornando um numero 
//menor, igual ou maior que 0, caso a chave de A 
//seja menor, igual ou maior que a chave  B, 
//respectivamente.
int indexesCompare(const void *A, const void *B){
    t_index *X = (t_index *) A;
    t_index *Y = (t_index *) B;
    
    return (X->key) - (Y->key);
}

//Funcoes para Manipulacao de Matrizes
void freeMatrix(void **matrix, int n){
    int i = 0;
    for(i = 0 ; i < n ; i++)
        free(matrix[i]);
    free(matrix);
    return;
}

//Funcoes para Manipulacao de Vetores
boolean contains(int *vec, int start, int end,int elem){
    int i, j;
    for(i = start ; i < end ; i++)
        for(j = i+1 ; j < end ; j++ )
            if(vec[i] == elem)
                return TRUE;
    return FALSE;
}

//Funcoes para Manipulacao de Strings
boolean sisdigit(char *string){
    int i;
    for(i = 0 ; i < strlen(string) ; i++)
        if(!isdigit(string[i]))
            return FALSE;
    return TRUE;
}

char *readLine(FILE *inputfile, char delim){
    int counter = 0;
    char c = 0, *string = NULL;
    
    do{
        c = fgetc(inputfile);
        string = (char *)realloc(string, sizeof(char)*(counter+1));
        string[counter++] = c;
    } while(c != 10 && c != 11 && c != 12 && c != 13 && c != EOF && c != delim);

    string[counter-1] = '\0';

    return string;
}

char *readString(char *inputstring, int start, int end, char delim){
    int i = 0, counter = 0;
    char c = 0, *string = NULL;
    
    for( i = start ; i < strlen(inputstring) && i < end && inputstring[i] != delim; i++){
        c = inputstring[i];
        string = (char *)realloc(string, sizeof(char)*(counter+1));
        string[counter++] = c;
    }
    string = (char *)realloc(string, sizeof(char)*(counter+1));
    string[counter] = '\0';

    return string;
}