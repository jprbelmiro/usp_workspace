/*
*	07 - Leap Year
*	----
*/
#include <stdio.h>
#include <math.h>

int main () {
    	//0. Variables
    	int x;
	int r,resto;
	
	//1. Reading the year
    	scanf("%d",&x);
    
	//2. Verifying if the year is a leap year
    	r = x/4;
    	resto = x-(r*4);

    	if(resto==0)
        	printf("SIM");
    	else
        	printf("NAO");

	//3. That's all folks... :)
    	return 0;
}
