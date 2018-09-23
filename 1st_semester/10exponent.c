/*
*	10 - Exponent
*	This program read two numbers to make the exponent
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main () {
	//0. Variables
    	float a,b;
	
	//1. Reading the values
    	scanf("%f %f",&a,&b);
	
	//2. Realizing the exponent;
    	printf("%.4f",pow(a,b));

	//3. That's all folks... :)
	return 0;
}
