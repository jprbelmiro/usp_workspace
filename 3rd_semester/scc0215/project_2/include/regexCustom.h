#ifndef _REGEX_CUSTOM_H_
#define _REGEX_CUSTOM_H_

/*
*    int match(char *linha, char *regex)
* Funcao responsavel por verificar se uma linha combina com uma expressao regular
* passada para a funcao. Caso a linha combine com a expressao, retorna-se um
* inteiro que representa sucesso. Caso contrario, retorna-se o inteiro oposto.
* @return inteiro que representa sucesso (1) ou falha (0)
* @args linha a ser verificada e a expressao regular
*/
int match(char *, char *);

/*
*    int countMatch(char *string1, char *string2)
* Funcao responsavel por verificar quantas vezes uma string se repete dentro de
* outra, isto é, dado uma string1 a função, a partir de uma string2 ela verifica
* quantas vezes a string1 contem a string2 dentro de si.
* @return inteiro que representa o numero de repeticoes de string2 em string1
* @args char *string1, char *string2
*/
int countMatch(char *, char *);

/*
*    char *tokenize (char *linha, int n, char delimitador)
* Funcao responsavel por 'tokenizar', ie, colher de uma linha de caracteres uma
* palavra circundada por delimitadores comuns e que ocupa a posicao n. Exemplo:
* tome "isso,eh,um,exemplo" como a linha, n = 2 e o delimitador = ','. O retorno
* da funcao neste caso seria "um".
* @return token escolhido
* @args linha a ser percorrida, a posicao do token desejado e o delimitador
* existente entre os tokens
*/
char *tokenize (char *, int n, char );

/*
*    char **tokenizeAll (char *string, char delim, int ntokens)
* Funcao responsavel por 'tokenizar' todas as palavras em uma string. Exemplo:
* tome "isso,eh,um,exemplo" como a string passada como parametro a função e o 
* delimitador = ','. O retorno da funcao é uma matriz de string que, no caso,
* seria uma matriz composta por "isso","eh","um" e "exemplo" (matriz[4][x]).
* @return char **tokens, todos os tokens existentes na string
* @args char *string, char delim, int ntokens
*/
char **tokenizeAll(char *, char , int );

#endif