/*
*	48 - LCM
* This program calculates the LCM of two numbers by a recursive function.
*/
#include <stdlib.h>
#include <stdio.h>

double recursivelcm(double a, double b, double i, double j){
	if(a*i == b*j)
		return a*i;
	else if(a < b)
		return recursivelcm(a,b,i+1,j);
	else
		return recursivelcm(a,b,i,j+1)
}

double lcm(double a, double b){
	return recursivelcm(a,b,1,1);
}

int main(int argc, char **argv){
	//0. Variables
	double a, b;
	
	//1. Reading the value A and B
    scanf("%lf %lf",&a,&b);

	//2. Calculating and printing the LCM
    printf("%.0lf",lcm(a,b));

    //3. That's all folks... :)
    return 0;
}

