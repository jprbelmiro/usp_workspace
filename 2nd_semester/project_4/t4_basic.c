#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void free_cube(void ***cube, int nmatrix, int dimens){
    int i, j;
    for(i = 0 ; i < nmatrix ; i++){
        for(j = 0 ; j < dimens ; j++){
            if(cube[i][j] != NULL)free(cube[i][j]);
        }if(cube[i] != NULL)free(cube[i]);
    }if(cube != NULL)free(cube);
    return;
}

void free_matrix(void **matrix, int n){
    int i;
    for(i = 0; i < n ; i++)
        if(matrix[i] != NULL)free(matrix[i]);
    if(matrix != NULL)free(matrix);    
    return;
}

void print_dmatrix(double **matrix, int row, int col){
    int i,j;
    printf("\n");
    for(i = 0 ; i < row ; i++){
        for(j = 0 ; j < col ; j++ ){
            printf("%.1lf ",matrix[i][j]);
        }printf("\n");
    }printf("\n");
    return;
}

double ***create_dcube(int height, int lenght, int width){
    int i, j;
    double ***cube = (double ***)malloc(sizeof(double **)*height);
    for(i = 0 ; i < height ; i++){
        cube[i] = (double **)malloc(sizeof(double *)*lenght);
        for(j = 0 ; j < lenght ; j++){
            cube[i][j] = (double *)malloc(sizeof(double)*width);
        }
    }
    return cube;
}

double **create_dmatrix(int row, int col){
    int i;
    double **matrix = (double **)calloc(row,sizeof(double *));
    for(i = 0 ; i < row ; i++)
        matrix[i] = (double *)calloc(col,sizeof(double));
    return matrix;
}

void fill_dcube(double ***cube, int h, int l, int w){
    int i, j, k;
    for(i = 0 ; i < h ; i++)
        for(j = 0 ; j < l ; j++)
            for(k = 0 ; k < w ; k++)
                scanf("%lf",&cube[i][j][k]); 
    return;  
}

int who_repeat_more(double *vec, int n){
    int i, j, counter, aux_counter = 0;
    double class, aux;
    for(i = 0 ; i < n ; i++){
	counter = 0;
	aux = vec[i];
	for( j = 0 ; j < n ; j++)
	   if(aux == vec[j]) counter++;

	if(aux_counter < counter){
	    class = aux;
	    aux_counter = counter;
	}
    }
    return class;
}

char *tokenize( FILE *fp ){
    int i = 0;
    char *token = NULL;

    while(!feof(fp)){
        char c = fgetc(fp);

        if( c != '\n' && c != '\t' && c != ' ' && c != ';' && c != EOF && c != ',' && c != '(' && c != ')' && c != 39 && c != 96){
            token = (char *)realloc(token,sizeof(char)*i+1);
            token[i++] = c;
        }

        if((c == '\n' || c == '\t' || c == ' ' || c == EOF || c == '(' || c == ')' || c == ';' || c == ',') && token != NULL){
            token = (char *)realloc(token,sizeof(char)*i+1);
            token[i] = '\0';

            return token;
        }
        else if( c == EOF  && token == NULL)
            return NULL;
    }
    
    if(token != NULL)
        free(token);
        
    return NULL;
}

char *readLine(FILE *finput){
    char *string = NULL;
    int counter = 0;
    char c = 0;
    
    do{
        c = fgetc(finput);
        string = (char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10 && c != 11 && c != 12 && c != 13 && c != EOF);
    
    string[counter-1] = '\0';
    return string;
}

FILE *fopen_r(){
    FILE *fp = NULL;
    char *name = NULL;
    
    do{
        scanf("%ms",&name);
        fp = fopen(name,"r");
        if(fp == NULL)
            printf("Invalid file (name: %s), try annother.\n",name);
        free(name);
    }while(fp == NULL);
    
    return fp;
}
