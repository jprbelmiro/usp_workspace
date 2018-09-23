#ifndef _PROJETO1_BASIC_H_
#define _PROJETO1_BASIC_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "projeto1_regex.h"

#include "projeto1_basic.c"

//Funcao responsavel por retornar a copia de uma string passada como parametro...
char *stringcopy(char *);

//Funcao responsavel por tokanizar uma string e retornar a token obtido em na po_
//sicao passada como parametro...
char *tokenize(int,char *);

//Funcao responsavel por ler uma linha de um arquivo ate o pulo de linha ou o 
//final do arquivo...
char *readLine(FILE *);

//Funcao responsavel por retornar um numero lido de um arquivo de entrada passado
//para a funcao...
int inNumber(FILE *);

#endif