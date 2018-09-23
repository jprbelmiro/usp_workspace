#include <stdlib.h>
#include <stdio.h>

void free_matrix(void **matrix, int n){
    int i;
    for(i = 0; i < n ; i++)
        if(matrix[i] != NULL)free(matrix[i]);
    if(matrix != NULL)free(matrix);    
    return;
}

float **create_fmatrix(int row, int col){
    int i;
    float **matrix = (float **)calloc(row,sizeof(float *));
    for(i = 0 ; i < row ; i++)
        matrix[i] = (float *)calloc(col,sizeof(float));
    return matrix;
}

int **create_imatrix(int row, int col){
    int i;
    int **matrix = (int **)calloc(row,sizeof(int *));
    for(i = 0 ; i < row ; i++)
        matrix[i] = (int *)calloc(col,sizeof(int));
    return matrix;
}

void print_fmatrix(float **matrix, int row, int col){
    int i, j;
    for(i = 0 ; i < row ; i++){
        for(j = 0 ; j < col ; j++){
            printf("%.3f ",matrix[i][j]);
        }printf("\n");
    }
    return;
}

void fill_fmatrix(float **matrix, int row, int col){
    int i, j;
    for(i = 0 ; i < row ; i++)
        for(j = 0 ; j < col ; j++)
                scanf("%f%*c",&matrix[i][j]); 
    return;  
}
