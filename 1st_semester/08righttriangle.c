/*
*	08 - Right Triangle
*/
#include <stdio.h>
#include <math.h>

int main () {
	//0. Variables
    	int edge1,edge2,edge3;
    	int produto,divisao,comprv;

	//1. Reading the numbers
    	scanf("%d %d %d",&edge1,&edge2,&edge3);
	
	//2.Printing the result
	if((edge1*edge2*edge3)-((edge1*edge2*edge3)/60)*60 == 0)
		printf("SIM");
    	else 
		printf("NAO");
 
	//4. That's all folks
    	return 0;
}
