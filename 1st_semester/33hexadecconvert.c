/*
*	32 - Hexadec Convert
* This program converts a integer number to Hexadec.
*/
#include <stdlib.h>
#include <stdio.h>

void Hexadec_Convert(long long int N){
    long long int *Hexadec = NULL;
    int i = 0;

    do{
        Hexadec = (long long int *)realloc(Hexadec, sizeof(long long int)*(i+1));
        Hexadec[i] = N % 16;
        N = N / 16;
        i++;
    }while( N != 0);

    int n;
    for(i= i-1; i >= 0 ; i--){
        if(Hexadec[i] > 9){
			n = Hexadec[i] + 55;
			printf("%c",n);
        } else printf("%lld",Hexadec[i]);
    }

    return;
}

int main (int argc, char **argv){
	//0. Variables
    long long int N = 0;
	
	//1. Reading a number
    scanf("%lld",&N);

	//2. Converting to hexadec and printing the result
    Hexadec_Convert(N);

	//3. That's all folks... :)
    return 0;
}
