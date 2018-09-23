#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void free_(void *pointer){
    if(pointer)
        free(pointer);
    return;
}

void freeMatrix(void **pointer, int n){
    int i;
    for( i = 0 ; i < n ; i++)
        free_(pointer[i]);
    free_(pointer);
    return;
}

void formatString(char **string){
    int i = 0, counter = 0;
    char *aux = strdup(*string);
    
    free_(*string);
    *string = NULL;
    
    for(i = 0 ; i < strlen(aux) ; i++){
        if(isalpha(aux[i]) || aux[i] == '-'){
            *string = (char *)realloc(*string,sizeof(char)*(counter+1));
            (*string)[counter++] = tolower(aux[i]);
        }
    }
    *string = (char *)realloc(*string,sizeof(char)*(counter+1));
    (*string)[counter++] = '\0';
    
    free_(aux);
    return;
}

void mergeString(char ***strings, int start, int mid, int end) {
    int left = start, right = mid+1, counter = 0;
    char **aux = (char **)malloc(sizeof(char *)*(end-start+1));
    
    while(left<=mid && right<=end){
        if(strcmp((*strings)[left],(*strings)[right])<=0){
            aux[counter] = (*strings)[left];
            left++;
        }else{
            aux[counter] = (*strings)[right];
            right++;
        }
        counter++;
    }

    while(left<=mid){  //Caso ainda haja elementos na primeira metade
        aux[counter] = (*strings)[left];
        counter++;left++;
    }

    while(right<=end){   //Caso ainda haja elementos na segunda metade
        aux[counter] = (*strings)[right];
        counter++;right++;
    }

    for(counter=start;counter<=end;counter++){
        (*strings)[counter] = aux[counter-start];
    }
    
    free(aux);
    return;
}

void sortStrings(char ***strings, int start, int end){
    if (start < end) {
        int mid = (end+start)/2;

        sortStrings(strings, start, mid);
        sortStrings(strings, mid+1, end);
        mergeString(strings, start, mid, end);
    }
    return;
}

char *readLine(FILE *inputfile, char delim){
    int counter = 0;
    char c, *string = NULL;
    
    do{
        c = fgetc(inputfile);
        string = (char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != '\n' && c != EOF && c != delim);
    
    string[counter-1] = '\0';
    return string;
}

FILE *fopen_(char *filename, char *mode){
    FILE *fp = fopen(filename,mode);
    if(!fp){
        printf("Invalid file - filename = %s / mode = %s .\n",filename,mode);
        exit(1);
    }
    return fp;
}
