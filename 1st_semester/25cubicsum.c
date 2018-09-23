/*
*	25 - Cubic Sum
* This program prints on the screen the result of a cubic sum
*/
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
	//0. Variables
    int m, c = 1, j = 1, k;
	
	//1. Reading the range m
    scanf("%d",&m);

	//2. Cubic Sum
    while( c <= m && m > 0){
		k = c;
        while(k > 0){
			printf("%d ",(j*2)-1);
			j++;
			k--;
		}
        c++;
        printf("\n");
    }

	//3. That's all folks... :)
    return 0;
}
