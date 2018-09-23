/*
*	20 - Congruent module
* This program prints on screen the n first congruent modules 
* of one or both of two input numbers.
*/
#include <stdio.h>

int main(int argc, char **argv){
	//0. Variables
    int i = 0, n,j,m;
	
	//1. Reading the inputs
    scanf("%d", &n);
    scanf("%d", &j);
    scanf("%d", &m);
	
	//2. Printing the congruent modules
    while (n>0){
        if(i % m == j % m){
			printf("%d\n",i); 
			n--;
		}
        i++;
    }
	
	//3. That's all folks... :)
    return 0;
}