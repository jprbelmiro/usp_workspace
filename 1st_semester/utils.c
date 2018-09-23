#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

void freematrix(void **matrix, int nrow){
	int i;
	for(i = 0 ; i < nrow ; i++)
		free(matrix[i]);
	free(matrix);
	return;
}

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

boolean inrange(int a, int low, int hi){
	return (a < low || a > hi)?(FALSE):(TRUE);
}

double harmonicmean(double *vector, int n, boolean aflag){
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

int newtonbinomial(int i, int j){
    if( i == 0 || j == 0 || i == j)
        return 1; 
    return newtonbinomial(i-1, j-1) + newtonbinomial(i-1, j);
}

int *eratosthenes(int threshold, int *nprimes){
	int i = 0, j = 0, *primes = NULL;
	
	primes = (int *)realloc(primes,sizeof(int)*(threshold-1));
	for(i = 2 ; i <= threshold ; i++)
		primes[i-2] = i;
	
	for(i = 2 ; i <= floor(sqrt(threshold)) ; i++)
		if(primes[i-2] != 0)
			for(j = 2 ; i*j <= threshold ; j++)
				primes[(i*j)-2] = 0;
	
	
	*nprimes = 0;
	for(i = 2 ; i <= threshold ; i++){
		if(primes[i-2] == 0){
			for(j = i+1 ; j <= threshold ; j++)
				if(primes[j-2] != 0){
					primes[i-2] = primes[j-2];
					primes[j-2] = 0;
					*nprimes += 1;
					break;
				}
		}
		else
		    *nprimes += 1;
	}
	
	primes = (int *)realloc(primes,sizeof(int)*(*nprimes));
	
	return primes;
}

void printintmatrix(int **matrix, int nrow, int ncol){
	int i, j;
    for(i = 0 ; i < 3  ; i++){
        for(j = 0 ; j < 3 ; j++){
            printf("%d ",matrix[i][j]);
        }printf("\n");
    }
    return;
}

void initializeintmatrix(int **matrix, int nrow, int ncol, int init){
    int i, j;
    for(i = 0 ; i < nrow  ; i++)
        for(j = 0 ; j < ncol ; j++)
            matrix[i][j] = init;
}

void setintmatrix(int **matrix, int row, int col, int set){
     matrix[row][col] = set;
     return;
}

void createintmatrix(int ***matrix, int nrow, int ncol){
	int i;
	*matrix = (int **)malloc(sizeof(int *)*nrow);
	for(i = 0 ; i < nrow ; i++)
		(*matrix)[i] = malloc(sizeof(int)*ncol);
	return;
}

void printintvec(int *vec, int size){
    int i = 0;
    for( i = 0 ; i < size ; i++ )
        printf("%d ",vec[i]);
    printf("\n");
    return;
}

int occurrences(void *string, size_t size, size_t nelem, void *elem){
    int i = 0, counter = 0;
    for(i = 0 ; i < nelem ; i++){
        switch(size){
            case sizeof(char):
                for(i = 0 ; i < nelem ; i++)
                    if(((char *)string)[i] == *((char*)elem))
                        counter++;
            break;
            case sizeof(int):
                for(i = 0 ; i < nelem ; i++)
                    if(((int *)string)[i] == *((int *)elem))
                        counter++;
            break;
            case sizeof(double):
                for(i = 0 ; i < nelem ; i++)
                    if(((double *)string)[i] == *((double)elem))
                        counter++;
            break;
        }
    }
    return counter;
}

int countlower(char *string){
    int i = 0, low = 0, len = strlen(string);
    for(i = 0; i < len ; i++)
		if(islower(string[i]))
			low++;
    return low;
}

int countupper(char *string){
    int i = 0, up = 0, len = strlen(string);
    for(i = 0; i < len ; i++)
		if(isupper(string[i]))
			up++;
    return up;
}

void tolower_(char **string){
	int i = 0, len = strlen(*string);
	for(i = 0; i < len ; i++){
		if(inrange((*string)[i],'A','Z'))
			(*string)[i] -= 'A'-'a';
	}
	return;
}

char *readline(FILE *inputfile, char delim){
	char c, *string = NULL;
	int counter = 0;

	do{
		c = fgetc(inputfile);
		string = (char *)realloc(string, sizeof(char)*(counter+1));
		string[counter++] = c;
	}while (c != 10 && c != 11 && c != 12 && c != 13 && c != EOF && c != delim);
	string[counter-1] = '\0';

	return string;
}
