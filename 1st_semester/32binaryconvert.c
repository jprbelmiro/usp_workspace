/*
*	32 - Binary Convert
* This program converts a integer number to binary.
*/
#include <stdlib.h>
#include <stdio.h>

void Binary_Convert(int N){
    int *Binario = (int *)calloc(32,sizeof(int));
    int i = 1;

    do{
       Binario[32-i] = N % 2;
       N = N / 2;
       i++;
    }while( N != 0);

    for(i = 0; i < 32 ; i++) 
		printf("%d",Binario[i]);

    return;
}

int main(int argc, char **argv){
	//0. Variables
    int N;
	
	//1. Reading a number
    scanf("%d",&N);

	//2. Converting to binary and printing the result
    Binary_Convert(N);

	//3. That's all folks... :)
    return 0;
}
