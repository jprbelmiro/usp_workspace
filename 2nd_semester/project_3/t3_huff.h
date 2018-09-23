#ifndef _T3_HUFF_H_
#define _T3_HUFF_H_

#include <math.h>
#include <ctype.h>
#include <string.h>

#include "t3_basic.h"
#include "t3_huff.c"

//Funcao responsavel por realizar a compactacao de Huffman a partir de um
//arquivo de texto...
void huff_compact(FILE *);

//Funcao responsavel por realizar a descompactacao de Huffman a partir de um
//arquivo ".huff"...
void huff_descompact(FILE *);

#endif