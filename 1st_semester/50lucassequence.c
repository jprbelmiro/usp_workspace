/*
*	50 - Lucas Sequence
* This program prints the nth element of the Lucas Sequence.
*/
#include <stdio.h>

double lucasseq(double n, double Lf,double L){
    if(n > 1) 
		return Lucas_Seq(n-1,Lf+L,Lf);
    else return Lf;
}

int main (int argc, char **argv){
	//0. Variables
	double n, L[2];
	
	//1. Reading the number n of elements of the Lucas Sequence
    scanf("%lf",&n);

	//2. Printing the nth element of Lucas Sequence
    L[0] = 2; L[1] = 1;
    if(n < 2)
        printf("%lf",L[n]);
    else 
		printf("%lf",lucaseq(n,L[1],L[0]));

	//3. That's all folks... :)
    return 0;
}
