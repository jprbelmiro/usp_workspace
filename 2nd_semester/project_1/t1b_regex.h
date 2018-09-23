#ifndef T1_REGEX_H_
#define T1_REGEX_H_

#include "t1b_regex.c"

//Funcao responsavel por comparar uma string de caracteres com uma expressao regular, 
//retornando 1 caso sejam semelhantes e 0 caso sejam diferentes...
int match(char *, char *);

//Funcao responsavel por retornar um vetor que possui as informacoes do tamanho de
//um parametro de uma tabela...
char *vec_digit(char *);

//Funcao responsavel por "tokenizar" um elemento de um arquivo. Diferentemente das
//outras funcoes, a funcao 'tokenize' possui uma baixa abrangencia a caracteres 
//especiais e tokaniza somente uma palavra...
char *tokenize( FILE *);

//Funcao responsavel por "tokenizar" um elemento de um arquivo. Diferentemente das
//outras funcoes, a funcao 'tokenize_arg_FILE' possui uma maior abrangencia a caracteres 
//especiais e tokaniza toda uma linha de argumentos...
char **tokenize_arg_FILE(FILE *, int *);

//Funcao responsavel por "tokenizar" um elemento de uma string. Diferentemente das
//outras funcoes, a funcao 'tokenize_arg_STR' possui uma maior abrangencia a caracteres 
//especiais, o usuario escolhe quais os delimitadores para criar-se um token e ela
//tokaniza toda uma linha que respeite os limites dado pelo usuario - nao reconhece
//"whitespaces" na leitura...
char *tokenize_arg_STR(char *, char , char , int );

//Funcao responsavel por "tokenizar" um elemento de uma string. Diferentemente das
//outras funcoes, a funcao 'tokenize_elem_STR' possui uma maior abrangencia a caracteres 
//especiais, o usuario escolhe quais os delimitadores para criar-se um token e ela
//tokaniza toda uma linha que respeite os limites dado pelo usuario - reconhece
//'whitespaces' na leitura...
char *tokenize_elem_STR(char *, char , char , int );

//Funcao responsavel por "tokenizar" um elemento de um arquivo. Diferentemente das
//outras funcoes, a funcao 'tokenize_elem' possui uma baixa abrangencia a caracteres 
//especiais, o usuario escolhe quais os delimitadores para criar-se um token e ela
//tokaniza toda uma linha que respeite os limites dado pelo usuario...
char *tokenize_elem( FILE *, char , char );

//Funcao responsavel por imprimir na tela os elementos encontrados na busca binaria...
void print_find(int , int , char **, char *, TABLE *, int );

//Funcao responsavel por buscar por todos os elemento em um arquivo ordenado que
//respeitem uma caracteristica de busca...
void binary_search_idx( char **, char *, int , int , char *, TABLE *, int , STAT *, int *);

//Funcao responsavel por escrever informacoes em um arquivo .idx...
void write_idx(FILE *, FILE *, char **, int , int );

//Funcao responsavel por criar um "vetor" ordenado...
char **create_sorted_vec( FILE *, char *, int , int *, char *);

#endif // T1_REGEX_H_INCLUDED
