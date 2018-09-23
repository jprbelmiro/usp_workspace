/*
*	38 - Division by subtraction
* This program divide two integer numbers by consecutive subtractions
*/
#include <stdio.h>

void divisionbysubtraction(int a, int b){
    int result = 0;
    if(a >= b){
        do{
            a -= b;
            result++;
        } while (b <= a);
    }

    printf("%d\n",result); 	// result
    printf("%d",a);			// rest
    return;
}

int main (int argc, char **argv){
	//0. Variables
	int a, b;
	
	//1. Reading two integer numbers
    scanf("%d%d",&a,&b);

	//2. Operating and printing
    divisionbysubtraction(a,b);
	
	//3. That's all folks... :)
    return 0;
}
