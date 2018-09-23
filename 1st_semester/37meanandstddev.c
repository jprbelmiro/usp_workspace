/*
*   37 - Mean and Stddev
* This program calculates the arithmetic mean and std deviation from a number vector
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double stddeviation(double *vec, int n, double m){
    int i = 0;
    double msum = 0;
    while(i < n)
        msum += pow((vec[i++] - m),2)/n;
    return sqrt(msum);
}

double mean(double *vec, int n){
    int i = 0;
    double sum = 0;
    while(i < n) 
		sum += vec[i++];
    return sum / n;
}

double *read(size_t size, int nelem, FILE *inputfile){
	int i;
    void *vec = (void *)malloc(size*nelem);
    for(i = 0 ; i < nelem ; i++){
        switch(size){
			case sizeof(char):
				scanf("%c%*c",&(((char *)vec)[i]));
			break;
			case sizeof(int):
				scanf("%d%*c",&(((int *)vec)[i]));
			break;
			case sizeof(double):
				scanf("%lf%*c",&(((double *)vec)[i]));
			break;
        }
    }
    return vec;
}

int main (int argc, char **argv){
	//0. Variables
	int N = 0;
	double m = 0, sdev = 0, *vec = NULL;
	
	//1. Reading the number N of inputs
    scanf("%d",&N);

	//2. Reading N real numbers
    vec = read(sizeof(double),N,stdin);

	//3. Calculating the mean
    m = mean(vec,N);
	printf("%.4lf\n",m);

	//4. Calculating the std deviation
    sdev = stddeviation(vec,N,m);
	printf("%.4lf",sdev);

	//5. Freeing the used memory
    free(vec);

	//6. That's all folks... :)
    return 0;
}
