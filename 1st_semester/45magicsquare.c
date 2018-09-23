/*
*	45 - Magic Square
* This program verifies if a matrix is a magic square.
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

void magicsquare(int **matrix, int n){
    int *row_sum = (int *)calloc(n,sizeof(int));
    int *col_sum = (int *)calloc(n,sizeof(int));
    int *diag_sum = (int *)calloc(2,sizeof(int));

    int i = 0, j = 0;
    for(i = 0; i < n ; i++){
        for(j = 0; j < n ; j++){
            row_sum[i] += matrix[i][j];
            col_sum[i] += matrix[i][j];
            if(i == j)
				diag_sum[0] += matrix[i][j];
            if(i + j == n - 1)
				diag_sum[1] += matrix[i][j];
        }
    }

	//a. row and col sum
    for(i = 0; i < n ; i++){
        for(j = 0 ; j < n ; j++){
            if(row_sum[i] != col_sum[j]){
                free(row_sum);
				free(col_sum);
				free(diag_sum);
                printf("NAO");
                return;
            }
        }
    }

	//b. row and diag sum
    for(i = 0; i < n ; i++){
        if(row_sum[i] != diag_sum[0]){
               free(row_sum);
				free(col_sum);
				free(diag_sum);
                printf("NAO");
                return;
        }
        if(row_sum[i] != diag_sum[1]){
                free(row_sum);
				free(col_sum);
				free(diag_sum);
                printf("NAO");
                return;
        }
    }

	//c. col and diag sum
    for(i = 0; i < n ; i++){
        if(col_sum[i] != diag_sum[0]){
                free(row_sum);
				free(col_sum);
				free(diag_sum);
                printf("NAO");
                return;
        }
        if(col_sum[i] != diag_sum[1]){
			    free(row_sum);
				free(col_sum);
				free(diag_sum);
                printf("NAO");
                return;
        }
    }

    printf("SIM");
    free(row_sum);
    free(col_sum);
    free(diag_sum);
    return;
}

void createintmatrix(int ***matrix, int nrow, int ncol){
	int i;
	*matrix = (int **)malloc(sizeof(int *)*nrow);
	for(i = 0 ; i < nrow ; i++)
		(*matrix)[i] = malloc(sizeof(int)*ncol);
	return;
}

int main (int argc, char **argv){
	//0. Variables
	int i, j, n, **matrix = NULL;
	
	//1. Reading the square matrix dimension
    scanf("%d", &n);

	//2. Creating the matrix
    createintmatrix(&matrix,n,n);
    for(i = 0 ; i < n ; i++)
        for(j = 0; j < n ; j++)
            scanf("%d",&matrix[i][j]);

	//3. Checking if this matrix is a magic square
    magicsquare(matrix,n);

	//4. Freeing the used memory
	freematrix((void **)matrix,n);
	
	//5. That's all folks... :)
    return 0;
}
