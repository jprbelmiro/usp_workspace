#ifndef T1_BASIC_H_
#define T1_BASIC_H_

#include "t1b_basic.c"

//Funcao responsavel por liberar uma "matriz" alocada na memoria...
void freeMatrix(void **, int );

//Funcao responsavel ordenar de maneira estavel um "vetor"...
void bubble_sort_by_param(char **, int , int );

//Funcao responsavel por ler de um arquivo de entrada...
char *readLine(FILE *, char );

//Funcao responsavel por copiar um "arquivo de entrada" em um "arquivo de saida"...
void copy_file(FILE *, FILE *);

//Funcao responsavel por retornar uma string no formato do nome de um arquivo .idx...
char *file_name_idx(char *, char *);

//Funcao responsavel por retornar uma string no formato do nome de um arquivo .tmp...
char *file_name_temp(char *);

//Funcao responsavel por retornar uma string no formato do nome de um arquivo .dat...
char *file_name_dat(char *);

//Funcao responsavel por abrir um arquivo .idx para escrita...
FILE *open2write_idx(char *, char *);

//Funcao responsavel por abrir um arquivo .tmp para escrita...
FILE *open2write_tmp(char *);

//Funcao responsavel por abrir um arquivo .dat para escrita...
FILE *open2write_dat(char *);

//Funcao responsavel por abrir um arquivo .idx para leitura...
FILE *open2read_idx(char *, char *);

//Funcao responsavel por abrir um arquivo .tmp para leitura...
FILE *open2read_tmp(char *);

//Funcao responsavel por abrir um arquivo .dat para leitura...
FILE *open2read_dat(char *);

//Funcao responsavel por abrir um arquivo para leitura - o arquivo e dado pela
//entrada do seu nome pelo usuario...
FILE *open_file2read();

#endif // T1_BASIC_H_