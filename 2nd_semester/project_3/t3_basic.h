#ifndef _T3_BASIC_H_
#define _T3_BASIC_H_

#include <stdlib.h>
#include <stdio.h>
#include "t3_regex.h"

#include "t3_basic.c"

//Funcao responsavel por realizar uma leitura em cima de uma string de caracte_
//res e retornar somente os digitos existentes nesta string...
int *digit_readString(char *, int *);

//Funcao responsavel por ler uma "linha" de caracteres a partir de um arquivo de
//entrada e retorna-la ao usuario...
char *readLine(FILE *);

//Funcao responsavel por abrir um arquivo para a compactacao ou descompactacao 
//de Huffman. Desta forma, ele so realiza a abertura de um arquivo, retornando o
//ao usuario se o arquivo aberto/escolhido for .txt ou .huff, retornando junto a
//abertura uma "flag" que indica qual a extensao do arquivo aberto (0 = .txt e
// 1 = .huff)...
FILE *huff_fopen(int *);

#endif