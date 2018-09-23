/*
*	17 - To lower
*	This program is an implementation of the function tolower
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int inrange(int a, int low, int hi){
	return (a < low || a > hi)?(0):(1);
}

void tolower_(char **string){
	int i = 0, len = strlen(*string);
	for(i = 0; i < len ; i++){
		if(inrange((*string)[i],'A','Z'))
			(*string)[i] -= 'A'-'a';
	}
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

int main(int argc, char *argv[]) {
	//0. Variables
	char *string = NULL;

	//1. Reading the input string
	string = readline(stdin,'\n');
	
	//2. Applying the function tolower
	tolower_(&string);

	//3. Printing the result
	printf("%s", string);
	
	//4. Freeing the used memory
	free(string);
	
	//5. That's all folks... :)
	return 0;
}
