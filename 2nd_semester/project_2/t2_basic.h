#ifndef _T2_BASIC_H_
#define _T2_BASIC_H_

#include <stdlib.h>
#include <stdio.h> 

#include "t2_basic.c"

typedef unsigned char t_raw;

//Funcao responsavel por abrir um arquivo para leitura binaria...
FILE *fopen_rb();

//Funcao responsavel por ler uma "linha" de caracteres a partir de um arquivo de
//entrada e retorna-la ao usuario...
char *readLine(FILE *);

//Funcao responsavel por imprimir na tela os dados de um audio ".raw" (composto
//por unsigned chars)...
void printf_raw(unsigned char *, int );

//Funcao responsavel por ler um arquivo de audio ".raw" (composto por unsigned 
//chars) do inicio ao fim alocando-o dinamicamente na memoria e retornando ao
//usuario um "vetor" com essas informacoes alocadas...
unsigned char *fread_raw(FILE *, int *);

#endif
