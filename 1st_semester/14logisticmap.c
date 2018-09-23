/*
*	14 - Logistic map
*	This program prints a logistic map on screen
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
	//0. Variables
    float x,r;
    int K = 0, t = 0;

	//1. Reading the parameters
    scanf("%f %f %d",&x,&r,&K);

	//2. Building the logistic map and printing it
    while(K-->0){
        x = r*x*(1-x);
        printf("%d %f\n",++t,x);
    }

	//3. That's all folks... :)
	return 0;
}
