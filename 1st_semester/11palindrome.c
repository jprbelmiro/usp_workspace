/*
*	11 - Palindrome
*	This program read a word and check if it is a palindrome
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

int main(int argc, char *argv[]) {
	//0. Variables
	char *nome = NULL;
	int p = 0, len = 0;
	
	//1. Reading the string
	nome = readline(stdin,'\n');

	//2. Getting string length
	len = strlen(nome) - 1;

	//3. Verifying the word and printing the result
	while(len >= 0 && nome[len]==nome[p]){
		len--;
		p++;
	}
	
	if(len<0)
		printf("SIM");
	else 
		printf("NAO");

	//4. Freeing used memory
	free(nome);

	//5. That's all folks... :)
	return 0;
}
