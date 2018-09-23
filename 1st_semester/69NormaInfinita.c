#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct matrix{
    double **matrix;
    int size;
}mtz;

void freeStructM( mtz *f){
// Responsável por liberar uma matriz (que esta em uma struct) da memoria...
    int i;

    for( i = 0 ; i < f->size ; i++)
            free(f->matrix[i]);

    free(f->matrix);
    free(f);

    return;
}

void freeM( double **matrix , int n){
// Responsável por liberar uma matriz da memoria...
    int i;
    for( i = 0 ; i < n ; i++)
        free(matrix[i]);

    free(matrix);

    return;
}

void printMat(double **mat, int c, int r){
// Responsável por imprimir uma matriz na tela...
    int i, j;
    for(i = 0; i < r; ++i){
        for(j = 0; j < c; ++j){
            printf("%.4lf ", mat[i][j]);
        }
        printf("\n");
    }

    return;
}

void normainf( double **matrix , int c, int r){
// Responsável por calcular a norma infinita de uma matriz...
    int i, j;

    double *maxs = calloc(c,sizeof(double));
    for(i = 0 ; i < c ; i++)
        for(j = 0 ; j < r ; j ++)
            maxs[i] += matrix[i][j];

    double norma1 = maxs[0];
    for( i = 0 ; i < c ; i++)
        if( norma1 < maxs[i])
            norma1 = maxs[i];

    printf("%.4lf\n", norma1);
    free(maxs);

    return;
}

double ** matrixsum(double **m1, double **m2, int c, int r){
// Responsável por calcular a soma de duas matrizes de mesmas dimensões, retornando-a...
    int i, j;
    double **matrix = malloc(sizeof(double *)*r);

    for(i = 0 ; i < r ; i++){
        matrix[i] = malloc(sizeof(double)*c);
        for(j = 0 ; j < c ; j++){
            matrix[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return matrix;
}

void readamatrix( mtz *f , FILE *fp ){
// Responsável por ler uma matriz de um arquivo e alocala em uma struct...
    double *aux = NULL;
    int counter = 0, i, j;

    while(!feof(fp)){
        aux = (double *)realloc(aux,sizeof(double)*(counter+1));
        fscanf(fp,"%lf",&aux[counter++]);
    }

    f->size = sqrt(counter - 1);
    f->matrix = malloc(sizeof(double *)*f->size);
    for( i = 0 ; i < f->size ; i++ ){
        f->matrix[i] = malloc(sizeof(double)*f->size);
        for( j = 0 ; j < f->size ; j++ ){
            f->matrix[i][j] = aux[(i*(f->size))+j];
        }
    }

    free(aux);

    return;
}

char *readLine(){
// Responsável por ler uma "string" da entrada padrao até o "ENTER"...
    char c;
    char *string = NULL;
    int counter = 0;
    do{
        c = fgetc(stdin);
        string = (char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10);
        string[counter-1] = '\0';

    return string;
}

FILE *open2read(){
// Responsável por abrir um arquivo para leitura...
    FILE *fp = NULL;
    char *file_name = NULL;

    do{
        file_name = readLine();
        fp = fopen(file_name,"r");
        if(fp == NULL){
            printf("Cannot open file this file. Choose another.\n");
            free(file_name);
        }
    }while(fp == NULL);

    free(file_name);
    return fp;
}

int main ( int argc , char **argv ){
// Projeto : Norma Infinita
    //Abrindo os arquivos que possuem as matrizes que serão usadas...
    FILE *matrix1_file = open2read();
    FILE *matrix2_file = open2read();

    //Lendo as matrizes do arquivo e calculando sua norma infinita...
    mtz *file1 = malloc(sizeof(mtz));
        readamatrix(file1,matrix1_file);
            normainf(file1->matrix,file1->size,file1->size);
    mtz *file2 = malloc(sizeof(mtz));
        readamatrix(file2,matrix2_file);
            normainf(file2->matrix,file2->size,file2->size);

    //Calculando a soma das duas matrizes, imprimindo a matriz resultado e sua norma infinita na tela...
    double ** matrixresult = matrixsum(file1->matrix,file2->matrix,file1->size,file1->size);
    printMat(matrixresult,file1->size,file1->size);
        normainf(matrixresult,file1->size,file1->size);

    //Fechando os arquivos abertos e liberando a memoria usada...
    freeM(matrixresult,file1->size);
    freeStructM(file2);
    freeStructM(file1);
    fclose(matrix1_file);
    fclose(matrix2_file);

    return 0;
}
