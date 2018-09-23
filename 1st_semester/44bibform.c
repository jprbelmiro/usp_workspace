/*
*	44 - Bib form
* This program prints a name in bibliography form.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void freematrix(void **matrix, int nrow){
	int i;
	for(i = 0 ; i < nrow ; i++)
		free(matrix[i]);
	free(matrix);
	return;
}

char *read_uSpace(char *nome_completo, int j) {
    char c, *string = NULL;
    int counter = 0;

	do{ 
		c = nome_completo[j++];
        string=(char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++]=c;
    }while(c != 32 && c != '\0');
    
	string[counter-1]='\0';

return string;
}

void printbibliographyform(char *name){
    int i = 0, j = 0;
    char c, **token = NULL;
	
	//a. tokenizing
    do{ 
        token = (char **)realloc(token,sizeof(char *)*(i+1));
        token[i++] = read_uSpace(name, j);
        j += strlen(token[i-1])+1;
    }while(j < strlen(name));

	//b. printing
    for(j = 0; j < strlen(token[i-1]) ; j++){
        c = token[i-1][j];
        printf("%c",toupper(c));
    }printf(", ");
    for(j = 0; j < i-1; j++)
		printf("%s ",token[j]);
    
	//c. freeing
    freematrix((void **)token,i);

    return;
}

char *readline(FILE *inputfile, char delim){
	char c, *string = NULL;
	int counter = 0;

	do{
		c = fgetc(inputfile);
		string = (char *)realloc(string, sizeof(char)*(counter+1));
		string[counter++] = c;
	}while (c != 10 && c != 11 && c != 12 && c != 13 && c != EOF && c != delim);
	string[counter-1] = '\0';

	return string;
}

int main (int argc, char **argv){
	//0. Variables
    char *name = NULL;

	//1. Reading the name
	name = readline(stdin,'\n');
	
	//2. Printing name in bibliography form
    printbibliographyform(name);

	//3. That's all folks... :)
    free(name);

    return 0;
}
