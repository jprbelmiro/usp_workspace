/*
*	21 - Mean without minimum
* This program prints on the screen of the group without the 
* minimum value
*/
#include <stdio.h>

int main(int argc, char **argv){
	//0. Variables
    double a,b,c,d,min;
	
	//1. Reading the numbers
    scanf ("%lf %lf %lf %lf",&a,&b,&c,&d);

	//2. Searching for the minimum
    min = a;
    min = (min<b)?(min):(b);
	min = (min<c)?(min):(c);
	min = (min<d)?(min):(d);
	
	//3. Calculating and printing
    printf("%.4lf",(a+b+c+d-min)/3);

	//4. That's all folks... :)
    return 0;
}
