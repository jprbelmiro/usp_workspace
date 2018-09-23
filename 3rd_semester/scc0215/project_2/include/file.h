#ifndef _FILE_H_
#define _FILE_H_

typedef struct{
    int key;
    long int offset;
}t_index;

/*
*    FILE *fopen_(char *filename, char *mode);
* Funcao responsavel por abrir um arquivo passado como parametro para a funcao
* no modo escolhido (read-only,write-only,binaryread,etc).
* @return caso a abertura seja bem sucessida, retorna-se o arquivo aberto, caso
* a acao e abortada e o programa encerrado (exit(1)).
* @args char *filename, char *mode
*/
FILE *fopen_(char *, char *);

/*
*    void create_datafile(char *filename, FILE *sourcefile, char *format_order, boolean hflag, char delim){
* Funcao responsavel por criar um arquivo de dados baseando-se em um arquivo
* fonte. Os parametros da funcao sao o nome do arquivo a se criar, o arquivo
* fonte, uma expressao que mostra por mascaras a ordem dos campos que estao no
* arquivo fonte, um booleano indicando se o arquivo fonte possui cabeçalho ou
* nao e o delimitador entre os campos.
* As mascaras para o arg. fileorder sao:
*       %F{inteiro} = indica um campo de tamanho fixo que obrigatoriamente e seguido do
*   seu tamanho. Ex.: %F4 <= usado para representar inteiros por exemplo;
*        %V  = indica um campo de tamanho variavel que obrigatoriamente e seguido do
*   seu tamanho. Ex.: %V;
* @return vazio
* @args char *filename, FILE *sourcefile, char *file_order, boolean hflag, char delim
*/
void create_datafile(char *, FILE *, char *, boolean , char);

/*
* Funcao que recebe um vetor de indices como argumento e imprime-os no arquivo de indice
* atualizando-o
*/
void writeprimaryidxfile(FILE *pifile, t_index *idx, int nregs);

/*
*    t_index *create_primaryidxfile(char *filename, FILE *sourcefile, char *format_order, int *size);
* Funcao responsavel por criar um arquivo de indice primario baseando-se em um 
* arquivo de dados fonte. Os parametros da funcao sao o nome do arquivo a se criar,
* o arquivo fonte, uma expressao que mostra por mascaras a ordem dos campos que estao no
* arquivo fornte e a referencia a uma variavel para se carregar o tamanho de uma
* estrutura em RAM que representa o arquivo de indice criado.
* As mascaras para o arg. file_order sao:
*       %F{inteiro} = indica um campo de tamanho fixo que obrigatoriamente e seguido do
*   seu tamanho. Ex.: %F4 <= usado para representar inteiros por exemplo;
*        %V  = indica um campo de tamanho variavel que obrigatoriamente e seguido do
*   seu tamanho. Ex.: %V;
* @return t_index* idx, arquivo de indice primario em RAM
* @args char *filename, FILE *sourcefile, char *format_order, int *size
*/
t_index *create_primaryidxfile(char *filename, FILE *sourcefile, char *format_order, int *size);

#endif
