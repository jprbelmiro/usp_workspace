#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

void free_(void *pointer){
    if(pointer)
        free(pointer);
    return;
}

void printString(string str){
    int i = 0;
    for(i = 0; i < strlen(str) ; i++)
        printf("%c",str[i]);
    printf("\n");
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