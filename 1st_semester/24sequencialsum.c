/*
*	24 - Sequential Sum
* This program prints on the screen the result of a sequential sum
*/
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
	//0. Variable
    int i = 0, N;
	float E = 0;
	
	//1. Reading the number N
    scanf("%d",&N);

	//2. Summing and printing the result
    for(i = 1 ; i <= N ; i++)
       E+=(float)i/(N-i+1);
    
    printf("%.4f\n",E);

	//3. That's all folks... :)
    return 0;
}
