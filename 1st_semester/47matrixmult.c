/*
*	47 - Matrix Multiplication
* This program realizes the multiplication of two matrices.
*/
#include <stdlib.h>
#include <stdio.h>

void freematrix(void **matrix, int nrow){
	int i;
	for(i = 0 ; i < nrow ; i++)
		free(matrix[i]);
	free(matrix);
	return;
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

void createintmatrix(int ***matrix, int nrow, int ncol){
	int i;
	*matrix = (int **)malloc(sizeof(int *)*nrow);
	for(i = 0 ; i < nrow ; i++)
		(*matrix)[i] = malloc(sizeof(int)*ncol);
	return;
}

int **matrixmultply(int **matrixa, int rowa, int cola, int **matrixb, int rowb, int colb){
	int i = 0, j = 0, k = 0, sum = 0;
    int **matrixr = NULL;
	
	createintmatrix(&matrixr,rowa,colb);
	
    for(i = 0; i < rowa ; i++){
        for(j = 0; j < colb; j++){
            for(k = 0; k < cola ; k++){
                sum += (matrixa[i][k] * matrixb[k][j]);
            }
            matrixr[i][j] = sum;
            sum = 0;
        }
    }

    return matrixr;
}

int main (int argc, char **argv){
	//0. Variables
	int i = 0, j = 0;
	int rowa = 0, rowb = 0, cola = 0, colb = 0;
	int **matrixa = NULL, **matrixb = NULL, **matrixr = NULL;
	
	//1. Reading the params and creating the matrix A
    scanf("%d %d",&rowa,&cola);
    createintmatrix(&matrixa,rowa,cola);
    for(i = 0 ; i < rowa ; i++)
		for(j = 0 ; j < cola ; j++)
			scanf("%d%*c",&(matrixa[i][j]));

	//2. Reading the params and creating the matrix B
    scanf("%d %d",&rowb,&colb);
    createintmatrix(&matrixb,rowb,colb);
    for(i = 0 ; i < rowb ; i++)
		for(j = 0 ; j < colb ; j++)
			scanf("%d%*c",&(matrixb[i][j]));

	//3. Multiplying the matrices
    matrixr = matrixmultply(matrixa,rowa,cola,matrixb,rowb,colb);
	printintmatrix(matrixr,rowa,colb);

	//4. Freeing the used memory
	freematrix((void **)matrixa,rowa);
	freematrix((void **)matrixb,rowb);
	freematrix((void **)matrixr,rowa);
	
	//5. That's all folks... :)
    return 0;
}
