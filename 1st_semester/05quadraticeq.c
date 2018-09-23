/*
*	05 - Quadratic Equation	
*/
#include <stdio.h>
#include <math.h>

int main () {
	//0. Variables
    	float a,b,c,delta;
    
	//1. Reading the numbers
	printf("Enter a value to A:");
	scanf ("%f%*c", &a);
	printf("Enter a value to B:");
	scanf ("%f%*c", &b);
	printf("Enter a value to C:");
	scanf ("%f%*c", &c);

	//2. Printing the result
	printf("---\nEquation: (%.2f)x^2 + (%.2f)x + (%.2f) = 0\n",a,b,c);
	
	delta = pow(b,2)-(4*a*c);
	printf("Delta = %f\n",delta);
	
	printf("x1 = (-(%.2f)+sqrt(%.2f))/(2*(%.2f))\n",b,delta,a);
	printf("x2 = (-(%.2f)-sqrt(%.2f))/(2*(%.2f))\n",b,delta,a);
	
    	if(delta > 0)
        	printf ("--\nReal result\nR1 %f\nR2 %f\n", ((-b)+sqrt(delta))/(2*a),((-b)-sqrt(delta))/(2*a));
    	else if(delta == 0)
		printf ("--\nSingle result\nR %f\n", (-b)/(2*a));   
    	else
        	printf ("--\nComplex result\nR %f\nI %f\n",(-b)/(2*a),sqrt(-delta)/(2*a));

	return 0;
}
