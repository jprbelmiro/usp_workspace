#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

void free_(void *pointer){
    if(pointer)
        free(pointer);
    return;
}

void freeMatrix(void **pointer, int n){
    int i;
    for( i = 0 ; i < n ; i++)
        if(pointer[i])
            free_(pointer[i]);
    free_(pointer);
    return;
}

int *copyIntVec(int *source, int N){
    int i = 0, *vector = (int *)malloc(sizeof(int)*N);
    for(i = 0 ; i < N ; i++){
        int num = source[i];
        vector[i] = num;
    }
    return vector;
}

int *readIntVector(int N){
    int i = 0, *vector = (int *)malloc(sizeof(int)*N);
    for(i = 0 ; i < N ; i++)
        scanf("%d%*c",&(vector[i]));
    return vector;
}

char *readLine(FILE *inputfile, char delim){
    int counter = 0;
    char c = 'c', *string = NULL;
    
    do{
        c = fgetc(inputfile);
        string = (char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10 && c != 11 && c != 12 && c != 13 && c != EOF && c != delim);
    string[counter-1] = '\0';
    
    return string;
}

char **readWords(int O, FILE *inputfile, char delim){
    int i;
    char **words = (char **)malloc(sizeof(char *)*O);
    for(i = 0 ; i < O ; i++)
        words[i] = readLine(inputfile,delim);
    return words;
}