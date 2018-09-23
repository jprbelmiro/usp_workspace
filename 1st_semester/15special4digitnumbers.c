/*
*	15 - Special 4 digit numbers
*	This program verifies if a 4-digit number have your sqrt
* equal to the sum of your halves.
* Exemple: sqrt(9801) = 98+01
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main (){
	//0. Variables
    int n = 1000, p, s, x;

	//1. Verifying if the number is special for printing it
    while(n <= 9999){
        p = n/100;
        s = n % 100;
        x = p+s;

        if(x == sqrt(n++))
			printf("%d\n",n-1);
    }

	//2. That's all folks... :)
	return 0;
}
