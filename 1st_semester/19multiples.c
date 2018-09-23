/*
*	19 - Multiples
* This program prints on screen the n first numbers that 
* are multiples of one or both two input numbers.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
	//0. Variables
    int n,i,j;
	
	//1. Reading the numbers
    scanf("%d",&n);
    scanf("%d",&i);
    scanf("%d",&j);

	//2. Printing on screen the multiples of number
    int c = 0;
    while(n > 0){
        if(c % i == 0 || c % j == 0){
            printf("%d\n",c);
            n--;
        }
        c++;
    }
	
	//3. That's all folks... :)
	return 0;
}
