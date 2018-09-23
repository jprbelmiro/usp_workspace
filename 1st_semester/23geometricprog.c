/*
*	23 - Geometric Progression
* This program prints on the screen the an and sn values of
* an geometric progression.
*/
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
	//0. Variables
    float a1,q,n,an;
	
	//1. Reading the parameters
    scanf("%f",&a1);
    scanf("%f",&q);
    scanf("%f",&n);

	//2. Printing the element an and the sum sn of
	//the geometric progression
    an = a1*pow(q,(n-1));
    printf("%.2f\n",an);
    printf("%.2f",a1*((pow(q,n)-1)/(q-1)));

	//3. That's all folks... :)
    return 0;
}
