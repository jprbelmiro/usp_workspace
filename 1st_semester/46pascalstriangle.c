/*
*	46 - Pascal's Triangle
* This program prints N lines of the Pascal's Triangle
*/
#include <stdio.h>
#include <math.h>

int newtonbinomial(int i, int j){
    if( i == 0 || j == 0 || i == j)
        return 1; 
    return newtonbinomial(i-1, j-1) + newtonbinomial(i-1, j);
}

void printf_TP(int N){
    int i, j;
    for(i = 0; i < N ; i++){
		for(j = 0; j <= i; j++){
            printf("%d ",newtonbinomial(i,j));
        } printf("\n");
    }

    return;
}

int main (int argc, char **argv){
	//0. Variables
	int N = 0;
	
	//1. Reading the number N of lines
    scanf("%d",&N);

	//2. Printing the Pascal's triangle
    printf_TP(N+1);

    return 0;
}
