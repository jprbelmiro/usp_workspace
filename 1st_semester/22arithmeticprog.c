/*
*	22 - Arithmetic Progression
* This program prints on the screen the an and sn values of
* an arithmetic progression.
*/
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
	//0. Variables
    long long int a1,r,n,an;
	
	//1. Reading the parameters
    scanf("%lld",&a1);
    scanf("%lld",&r);
    scanf("%lld",&n);

	//2. Printing the element an and the sum sn of
	//the arithmetic progression
	an = a1+((n-1)*r);
    printf("%lld\n",an);
    printf("%lld",((a1+an)*n)/2);

	//3. That's all folks... :)
    return 0;
}
