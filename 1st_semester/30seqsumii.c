/*
*	30 - SeqSum II
*/
#include <stdio.h>

int main(int argc, char **argv){
	//0. Variables
    int i = 0, x = 0, N = 0;
	float s = 0;
	
	//1. Realizing the operation
    scanf("%d",&N);
    while(N-i!=0){
        x = ((i+1)*2)-1;
        s += (float)x/(N-i);
        i++;
    }
	
	//2. Printing the result
    printf("%.4f",s);

	//3. That's all folks... :)
    return 0;
}
