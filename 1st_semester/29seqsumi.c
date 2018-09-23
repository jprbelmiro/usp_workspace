/*
*	29 - SeqSum I
*/
#include <stdio.h>

int main(int argc, char **argv){
	//0. Variables
    int N = 0;
	float s = 0;
	
	//1. Realizing the operation
    scanf("%d",&N);
    while( N > 0 ){
		if( N % 2 == 0)
			s -= (float)1/N;
		else 
			s += (float)1/N;
		N--;
    }

	//2. Printing the result
    printf("%.4f",s);
	
	//3. That's all folks... :)
	return 0;
}
