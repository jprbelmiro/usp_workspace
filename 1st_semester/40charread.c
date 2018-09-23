/*
*	40 - Char read
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    char  *string = NULL;
	int i = 0, len = 0;
	
	//1. Reading the input
    string = readline(stdin,'\n');

	//2. Printing
	len = strlen(string);
    while( i < len ) 
		printf("%c\n",string[i++]);

	//3. Freeing the used memory
    free(string);

	//4. That's all folks... :)
    return 0;
}
