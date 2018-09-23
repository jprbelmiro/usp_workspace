/*
* PROGRAM 02 - Bitwise Operators
* This program print on screen the result of each bitwise operation.
*/
#include <stdio.h>

int main () {
    //0. Variables
    int a,b;
	
    //1. Reading two numbers
    printf("Enter a value to A: ");
    scanf("%d",&a);
    
    printf("Enter a value to B: ");
    scanf("%d",&b);

    //2. Printing the result
    printf("AND: %d\n",a & b);
    printf("OR: %d\n",a | b);
    printf("XOR: %d\n",a ^ b);
    printf("NOT A:%d\n",~a);
    printf("NOT B: %d\n",~b);
    printf("RIGHT SHIFT A: %d\n",a>>1);
    printf("LEFT SHIFT B: %d\n",b<<1);

    return 0;
}
