#ifndef _T5_BASIC_H_
#define _T5_BASIC_H_

//Funcao responsavel por liberar uma matriz da memoria...
void free_matrix(void **, int );

//Funcao responsavel por criar uma matriz de float na memoria...
float **create_fmatrix(int , int );

//Funcao responsavel por criar uma matriz de inteiros na memoria...
int **create_imatrix(int , int );

//Funao responsavel por imprimir uma matriz de floats na tela...
void print_fmatrix(float **, int , int );

//Funcao responsavel por preencher uma matriz de floats linha por linha...
void fill_fmatrix(float **, int , int );

#endif
