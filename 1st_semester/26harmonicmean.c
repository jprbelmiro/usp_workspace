/*
*	26 - Harmonic Amortized Mean
* This program prints on the screen the result of an harmonic mean
*/
#include <stdlib.h>
#include <stdio.h>

double harmonicmean(double *vector, int n, int aflag){
	int i = 0;
	double result = 0;
	
	for(i = 0 ; i < n ; i++){
		if(vector[i] == 0 && !aflag)
			return 0;
		
		result += 1/(vector[i]+aflag);
	}
	
	result = n/result;
	return result-1;
}

int main(int argc, char **argv){
	//0 Variables
    int i = 0, N = 0;
	double mean = 0, *grade = NULL;
	
	//1. Reading the number N of grades
    scanf ("%d",&N);
    
    //2. Reading the grades
	grade = (double *)malloc(sizeof(double)*N);
    for(i = 0 ; i < N ; i++)
        scanf("%lf%*c",&grade[i]);
    
    //3. Calculating the Harmonic Mean
	mean = harmonicmean(grade,N,1);

	//4. Printing the result
    printf ("%.2f",mean);

	//5. Freeing the used memory
    free(grade);
	
	//6. That's all folks... :)
    return 0;
}
