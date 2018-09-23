/*
*	13 - Odd sequence
*	This program prints a sequence of N odd numbers on screen
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
	//0. Variables
    int N = 0, i = 0;
	
	//1. Reading the N number of odd number
    scanf("%d",&N);

	//2. Printing the N first odd numbers
    for( i = 1 ; N > i-1 ; i++)
        printf("%d\n",(i*2)-1);

	//3. That's all folks... :)
	return 0;
}
