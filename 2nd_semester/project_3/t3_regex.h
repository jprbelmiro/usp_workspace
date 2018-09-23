#ifndef _T3_REGEX_H_
#define _T3_REGEX_H_

#include <regex.h>

#include "t3_regex.c"

//Funcao responsavel por analizar se existe correspondencia entre uma string de
//caracteres e uma expressao regular...
int match(char *, char *);

#endif