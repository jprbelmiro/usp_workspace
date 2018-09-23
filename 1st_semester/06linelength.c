/*
*	06 - Line Length
*	This program calculate Euclidean Distance of N points.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void freematrix(void **matrix, int nrow){
	int i;
	for(i = 0 ; i < nrow ; i++)
		free(matrix[i]);
	free(matrix);
	return;
}

int main(int argc, char **argv){
	
	//0. Variables
    	int i, N;
	float distx, disty, result;
	float **P = NULL;
	
	//1. Reading the number of points
    	scanf("%d",&N);
	
	//2. Reading the N points
	P = (float **)malloc(sizeof(float *)*N);
	for(i = 0 ; i < N ; i++){
		P[i] = (float *)malloc(sizeof(float)*2);
		scanf("%f %f",&P[i][0],&P[i][1]);
	}

	//3. Calculating the point-point distance and summing to final result
    	result = 0;
    	for(i = N-1; i > 0 ; i--){
        	distx = P[i][0]-P[i-1][0];
        	disty = P[i][1]-P[i-1][1];
        	result += sqrt(pow(distx,2)+pow(disty,2));
    	}

	//4. Freeing the used memory and printing the result
	printf("%.4f\n",result);
	freematrix((void **)P,N);
	
	//5. That's all folks
	return 0;
}
