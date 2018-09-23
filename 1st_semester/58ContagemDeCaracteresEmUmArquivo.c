#include <stdlib.h>
#include <stdio.h>

char *readLine(){
    char c;
    char *string = NULL;
    int counter = 0;
    do{
        c = fgetc(stdin);
        string = (char *)realloc(string, sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10);
    string[counter - 1] = '\0';

    return string;
}

int main (int argc, char **argv){

    char *file_name = readLine();

    FILE *fp = fopen(file_name,"r");
    if ( fp == NULL){
        printf("There is no file to read.");
        exit(1);
    }

    fseek(fp, 0 , SEEK_END);
    printf("%ld",ftell(fp));

    free(file_name);
    fclose(fp);

    return;
}
