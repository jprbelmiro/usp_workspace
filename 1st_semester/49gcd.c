/*
*	49 - GCD
* This program calculates the GCD of two numbers by a recursive function.
*/
#include <stdlib.h>
#include <stdio.h>

int recursivegcd(int a, int b, int d){
	if(a % d == 0 && b % d == 0)
		return d;
	return recursivegcd(a,b,d-1);
}

double gcd(double a, double b){
	return recursivegcd((int)a,(int)b,(int)((a < b)?(a):(b)));
}

int main(int argc, char **argv){
	//0. Variables
	double a, b;
	
	//1. Reading the value A and B
    scanf("%lf %lf",&a,&b);

	//2. Calculating and printing the LCM
    printf("%.0lf",gcd(a,b));

    //3. That's all folks... :)
    return 0;
}

