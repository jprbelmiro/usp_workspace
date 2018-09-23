#ifndef _MATCH_H_
#define _MATCH_H_

/*
*    int match(char *string, char *regex)
* Funcao responsavel por verificar se uma linha combina com uma expressao regular
* passada para a funcao. Caso a linha combine com a expressao, retorna-se um
* inteiro que representa sucesso. Caso contrario, retorna-se o inteiro oposto.
* @return inteiro que representa sucesso (1) ou falha (0)
* @args linha a ser verificada e a expressao regular
*/
int match(char *, char *);

#endif