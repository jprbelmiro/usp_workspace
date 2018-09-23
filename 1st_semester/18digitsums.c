/*
*	18 - Digit sums
*	This program is an implementation of the function tolower
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int inrange(int a, int low, int hi){
	return (a < low || a > hi)?(0):(1);
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


int main(int argc, char **argv){
	//0. Variables
	int i = 0, len = 0, sum = 0;
    char *string = NULL;
    
	//1. Reading the string
	string = readline(stdin,'\n');
	
	//2. Getting the string length 
    len = strlen(string);
	
	//3. Summing the digits and printing the result
    for(i = 0 ; i < len ; i++)
		if(!inrange(string[i],'0','9')){
			printf("It isn't a number. Use only numbers.\n");
			exit(1);
		}
		else
			sum += string[i] - '0';
	
    printf("%d",(int) sum);

	//4. Freeing the used memory
    free(string);

	//5. That's all folks... :)
	return 0;
}
