/*
*	27 - Type Counter
* This program prints on the screen the number of characters 
* and digits in a string.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    int len = 0, charcounter = 0, digitcounter = 0;
	char *string = NULL;
	
	//1. Reading the input string
    string = readline(stdin,'\n');
	
	//2. Counting the number of chars and digits
    len = strlen(string);
    while(len-- > 0){
		if(isalpha(string[len]))
			charcounter++;
		else if(isdigit(string[len]))
			digitcounter++;
    }

	//3. Printing result and freeing the used memory
    printf("%d\n%d",charcounter,digitcounter);
    free(string);

	//4. That's all folks... :)
	return 0;
}
