/*
* PROGRAM 03 - Real Number
* This program print on screen a real number.
*/
#include <stdio.h>
#include <math.h>

int main(){
    //0. Variable
    float a;
	
    //1. Reading the number and printing
    printf("Enter a number: ");
    scanf("%f", &a);

    printf("integer: %d\n", (int)a);
    printf("float point: %.4f\n", a-(int)a);
    printf("rounded: %d\n", (int)round(a));

    //2. That's all folks... :)
    return 0;
}
