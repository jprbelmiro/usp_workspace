#ifndef _UTILS_H_
#define _UTILS_H_

typedef enum{
  FALSE,
  TRUE
}boolean;

//Funcoes de Liberação de Memória
/*
*    void free_(void *pointer)
* Funcao responsavel por liberar um ponteiro alocado na memoria. Diferentemente
* da função free(), realiza uma verificação se realmente há algo para se liberar
* na memoria, ou seja, se o vetor foi alocado.
* @return void
* @args void *pointer
*/
void free_(void *);

//Funcoes para Ordenacao de Vetores
/*
*    void mergesort(int *vec, int start, int end)
* Funcao responsavel por ordenar um vetor de inteiros de um ponto inicial ate um
* ponto final.
* @return void
* @args int *vec, int start, int end
*/
void mergesort(int *, int , int );

//Funcoes para Manipulacao de Matrizes
/*
*    boolean sisdigit(char *string);
* Funcao responsavel por verificar se uma string so contem numeros inteiros, ou
* seja, verifica se a string é um numero inteiro.
* @return boolean TRUE, caso a string represente um número inteiro, ou boolean 
* FALSE caso a string não represente um número inteiro.
* @args FILE *string
*/
void freeMatrix(void **, int );

//Funcoes para Minipulacao de Strings
/*
*    boolean sisdigit(char *string);
* Funcao responsavel por verificar se uma string so contem numeros inteiros, ou
* seja, verifica se a string é um numero inteiro.
* @return boolean TRUE, caso a string represente um número inteiro, ou boolean 
* FALSE caso a string não represente um número inteiro.
* @args FILE *string
*/
boolean sisdigit(char *string);

/*
*    char *readLine(FILE *inputfile,  char delim) 
* Funcao responsavel por ler uma linha de um arquivo de entrada ate que se en_
* contre um delimitador valido. Ao final o tamanho e retornado por referencia.
* @return char *string
* @args FILE *inputfile,  char delim
*/
char *readLine(FILE *, char );

/*
*    char *readString(char *inputstring, int start, int end,char delim);
* Funcao responsavel por ler uma string passada como argumento do ponto inicial
* passado até no maximo um ponto final determinado ou um delimitador, retornando
* uma substring da string de entrada.
* @return char *string
* @args char *inputstring, int start, int end,char delim
*/
char *readString(char *, int , int ,char );

int fieldCompare(const void *, const void *);

int indexesCompare(const void *, const void *);

#endif
