/*
*	36 - Sine
* This program calculates the sine of a radian value by a Taylor Series
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

long double fatorial(double e){
	int i =0;
    long double fat = 1;
    for(i = e; i > 1 ; i--)
		fat *= i;
    return fat;
}

float sinTaylorSerie(float x){
	int i;
    float sen = x;
    for(i = 1; i < 300 ; i++){
        double e = (i*2) + 1;
        double potencia_x = pow(x,e);
        long double fatorial_x = fatorial(e);
        if(i % 2 == 0)
			sen += potencia_x / fatorial_x;
        else 
			sen -= potencia_x / fatorial_x;
    }

    return sen;
}

int main (int argc, char **argv){
	//0. Variables
	float rad = 0, seno = 0;
	
	//1. Reading the radian value to calculate the sine
    scanf("%f",&rad);

	//2. Calculating sin(rad) by a Taylor Series and printing the result
    seno = sinTaylorSerie(rad);
    printf("%.6f",seno);

    return 0;
}
