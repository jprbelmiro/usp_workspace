/*
*	35 - Char Occurrences
* This program counts the occurrence of a char in a string.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int occurences(void *string, size_t size, size_t nelem, void *elem){
    int i = 0, counter = 0;
    for(i = 0 ; i < nelem ; i++){
        switch(size){
            case sizeof(char):
                for(i = 0 ; i < nelem ; i++)
                    if(((char *)string)[i] == *((char*)elem))
                        counter++;
            break;
            case sizeof(int):
                for(i = 0 ; i < nelem ; i++)
                    if(((int *)string)[i] == *((int *)elem))
                        counter++;
            break;
            case sizeof(double):
                for(i = 0 ; i < nelem ; i++)
                    if(((double *)string)[i] == *((double *)elem))
                        counter++;
            break;
        }
    }
    return counter;
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
	int result = 0;
	char c, *string = NULL;
	
	//1. Reading a string
    string = readline(stdin,'\n');

	//2. Reading a character
    scanf("%c%*c",&c);

	//3. Counting the char occurrence and printing the result
    result = occurences((void *)string,sizeof(char),strlen(string),&c);
    printf("%d",result);

	//4. Freeing the used memory
    free(string);

	//5. That's all folks... :)
    return 0;
}
