/*
*	28 - Case Counter
* This program prints on the screen the number of upper  
* and lower characters in a string.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countlower(char *string){
    int i = 0, low = 0, len = strlen(string);
    for(i = 0; i < len ; i++)
		if(islower(string[i]))
			low++;
    return low;
}

int countupper(char *string){
    int i = 0, up = 0, len = strlen(string);
    for(i = 0; i < len ; i++)
		if(isupper(string[i]))
			up++;
    return up;
}

int main(int argc, char **argv){
	//0. Variables
    int l = 0, u = 0, i = 0, N = 0;
	char *string = NULL;
	
	//1. Reading the number N of input
    scanf("%d%*C",&N);
	
	//2. Reading N characters as input
    string = (char *)malloc(sizeof(char)*N+1);
    for(i = 0 ; i < N ; i++)
        scanf("%c%*c",&string[i]);
	string[i] = '\0';

	//3. Counting the number of upper and lower case characters
    u = countupper(string);
    l = countlower(string);
	
	//4. Freeing the used memory and printing the result
    printf("%d %d",u,l);
	free(string);
	
	//5.That's all folks... :)
    return 0;
}
