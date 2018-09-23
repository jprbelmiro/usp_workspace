/*
*	52 - Online mean and var
* This program prints the online mean and variance of an number set.
*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

double *onlinemean(double *num, int nnum){
    int i;
    double mean = num[0];
    double *mvec = (double *)malloc(sizeof(double)*(nnum - 1));
    for( i = 1 ; i < nnum ; i++){
        mean += num[i];
        mvec[i-1] = mean/(i+1);
    }
    return mvec;
}

void onlinevar(double *num, int nnum){
    int i, j;
    double mean;
    double *mo = onlinemean(num,nnum);
    for( i = 1 ; i < nnum ; i++){
            mean = 0;
            for( j = 0 ; j <= i ; j++){
                mean += pow(num[j] - mo[i-1],2);
            }
            printf("%.2lf ",mean/i);
    }
    free(mo);
    return;
}

void onlinemeanprint(double *num, int nnum){
    int i;
    double mean = num[0];
    for( i = 1 ; i < nnum ; i++){
        mean += num[i];
        printf("%.2lf ",mean/(i+1));
    }printf("\n");
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

double *readnnumbers(int *nnum){
	int i = 0, j = 0;
	char *string = NULL, *aux = NULL;	
	double *seq = NULL;
    
	string = readline(stdin,'\n');
	while(i < strlen(string)){
		j = 0;
		aux = NULL;
		
        if(isdigit(string[i])){
            (*nnum) += 1;
			seq = (double *)realloc(seq,sizeof(double)*(*nnum));
	
			while(i < strlen(string) && isdigit(string[i])){
				aux = (char *)realloc(aux,sizeof(char)*(j+1));
				aux[j++] = string[i++];
			}
			aux = (char *)realloc(aux,sizeof(char)*(j+1));
			aux[j++] = '\0';
			
			seq[(*nnum)-1] = atof(aux);
			free(aux);
		}
		else
			i++;
	}
	
	free(string);
    return seq;
}

int main (int argc, char **argv){
	//0. Variables...
	int nnumbers = 0;
	double *numbers = NULL;
	
	//1. Reading n real numbers...
    numbers = readnnumbers(&nnumbers);

	//2. Printing the Mean and the Var of numbers...
    onlinemeanprint(numbers,nnumbers);
    onlinevar(numbers,nnumbers);

	//3. Freeing the used memory...
    free(numbers);

	//4. That's all folks... :)
    return 0;
}