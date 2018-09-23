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