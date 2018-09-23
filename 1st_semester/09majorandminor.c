/*
*	09 - Major and Minor
*	This program read N integer numbers and print the major 
*    and minor on screen.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INT_MAX 2147483647
#define INT_MIN -2147483648

int main () {
    	//0. Variables
	int input, N, *number = NULL;
	int minor = INT_MAX, major = INT_MIN;
	
	//1. Reading the N number of inputs
    	scanf("%d",&N);
	
	//2. Reading the N inputs and searching for
	//minor and major input
	number = (int *)malloc(sizeof(int)*N);
    	while(N-- > 0){
        	scanf("%d",&input);
        	number[N] = input;
		
		major = (input>major)?(input):(major);
		minor = (input<minor)?(input):(minor);
    	}

	//3. Printing the result and Freeing the used memory
   	 printf("max: %d\n",major);
    	printf("min: %d\n",minor);
    	free(number);

	//4. That's all folks... :)
	return 0;
}
