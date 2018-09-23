#ifndef _T4_BASIC_H_
#define _T4_BASIC_H_

//Funcao responsavel por liberar um "cubo" da memoria...
void free_cube(void ***, int, int);

//Funcao responsavel por liberar uma "matrix" da memoria...
void free_matrix(void **, int);

//Funcao responsavel por imprimir uma matriz de doubles na tela...
void print_dmatrix(double **, int , int );

//Funcao responsavel por criar um "cubo de doubles" na memoria...
double ***create_dcube(int , int , int);

//Funcao responsavel por criar um "matrix de doubles" na memoria...
double **create_dmatrix(int , int);

//Funcao responsavel por preencher um "cubo de doubles" com valores...
void fill_dcube(double ***, int , int , int );

//Funcao responsavel por retornar qual o elemento de maior frequencia em um vetor de doubles...
int who_repeat_more(double *, int );

//Funcao responsavel por tokenizar um string de um arquivo...
char *tokenize(FILE *);

//Funcao responsavel por ler uma "linha" de caracteres a partir de um arquivo de
//entrada e retorna-la ao usuario...
char *readLine(FILE *);

//Funcao responsavel por abrir um arquivo para leitura...
FILE *fopen_r();

#endif
