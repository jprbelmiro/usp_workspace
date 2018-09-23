/*
*	51 - Sieve of Eratosthenes
* This program finds all prime numbers up to any given limit.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void printintvec(int *vec, int size){
    int i = 0;
    for( i = 0 ; i < size ; i++ )
        printf("%d ",vec[i]);
    printf("\n");
    return;
}

int *eratosthenes(int threshold, int *nprimes){
	int i = 0, j = 0, *primes = NULL;
	
	primes = (int *)realloc(primes,sizeof(int)*(threshold-1));
	for(i = 2 ; i <= threshold ; i++)
		primes[i-2] = i;
	
	for(i = 2 ; i <= floor(sqrt(threshold)) ; i++)
		if(primes[i-2] != 0)
			for(j = 2 ; i*j <= threshold ; j++)
				primes[(i*j)-2] = 0;
	
	
	*nprimes = 0;
	for(i = 2 ; i <= threshold ; i++){
		if(primes[i-2] == 0){
			for(j = i+1 ; j <= threshold ; j++)
				if(primes[j-2] != 0){
					primes[i-2] = primes[j-2];
					primes[j-2] = 0;
					*nprimes += 1;
					break;
				}
		}
		else
		    *nprimes += 1;
	}
	
	primes = (int *)realloc(primes,sizeof(int)*(*nprimes));
	
	return primes;
}
	
int main (int argc, char **argv){
	//0. Variables
	int threshold, nprimes;
	int *primes = NULL;
	
	//1. Reading a threshold to the Eratosthenes Sieve
    scanf("%d",&threshold);

	//2. Finding all primes between 2 and threshold
	primes = eratosthenes(threshold,&nprimes);

	//3. Printing the result
    printintvec(primes,nprimes);
	
	//4. Freeing the used memory
	free(primes);

	//5. That's all folks... :)
    return 0;
}
