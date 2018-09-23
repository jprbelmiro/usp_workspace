/*
*	16 - Inverse order
*	This program prints the inverse of N user inputs on screen
*/
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv){
	//0. Variables
    int N, i = 0, *v = NULL;
  
	//1. Reading the N number of inputs
    scanf("%d",&N);
	
	//2. Reading the N inputs
    v = (int *)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++){
        scanf("%d",&(v[i]));
    }
    
	//3. Printing the inverse user input
    while(--i >= 0)
		printf("%d\n",v[i]);

	//4. That's all folks... :)
	return 0;
}
