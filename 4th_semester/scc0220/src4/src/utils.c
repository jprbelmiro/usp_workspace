#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void free_(void *pointer){
    if(pointer)
        free(pointer);
    return;
}

short digittoshort(char c){
    if(!isdigit(c)){
        printf(":: Invalid digit %c::\n",c);
        exit(1);
    }
    return c - '0';
}

boolean isanumber(char *string){
    int i = 0;
    
    if(!string || strcmp(string,"")== 0)
        return FALSE;

    if(string[0] == '-') i+=1;
    for(i = i ; i < strlen(string) ; i++)
        if(!isdigit(string[i]))
            return FALSE;
    return TRUE;
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