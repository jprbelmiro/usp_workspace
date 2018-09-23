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

void printCharMatrix(char **matrix, int nrow, int ncol){
    int i, j;
    for(i = 0 ; i < nrow ; i++){
        for(j = 0 ; j < ncol ; j++){
            printf("%c",matrix[i][j]);
        }printf("\n");
    }
    return;
}

char *tokenize (char *string, int n, char delim){
    char c = string[0], *token = NULL;
    int counter = 0, i = 0;
    
    if(string[i] == ';' || string[i] == ',' || string[i] == delim)
        while((string[i] == ';' || string[i] == ',' || string[i] == delim) && (i < strlen(string))) i++;
        
    while(counter < n && (i < strlen(string))){
        while(string[i] != ';' && string[i] != ',' && string[i] != delim) i++;
        if(string[i] == ';' || string[i] == ',' || string[i] == delim) i++;
        counter++;
    }
    
    if(i >= strlen(string)) return NULL;
    
    counter = 0;
    do{
        c = string[i++];
        if(c != ';' && c != ',' && c != delim){
            token = (char *)realloc(token,sizeof(char)*counter+1);
            token[counter++] = c;
        }
    }while(c != ';' && c != ',' && c != delim && c != '\0' && c != EOF);
                
    token = (char *)realloc(token,sizeof(char)*counter+1);
    token[counter++] = '\0';
    
    return token;
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

char **createCharMatrix(int nrow, int ncol){
    int i = 0;
    char **matrix = (char **)malloc(sizeof(char *)*nrow);
    for(i = 0 ; i < ncol ; i++)
        matrix[i] = (char *)malloc(sizeof(char)*ncol);
    return matrix;
}