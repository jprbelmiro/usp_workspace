#ifndef T1_DB_H_
#define T1_DB_H_

#include "t1b_db.c"

//Funcao responsavel por retornar o numero da tabela cujo o nome
//e igual ao informado pelo usuario e passado como argumento...
//- caso ele nao exista, e retornado -1;
int index_table(TABLE *, char *, int );

//Funcao responsavel por retornar o numero da ordem de um elemento
//igual ao informado pelo usuario e passada como argumento...
//- caso ele nao exista, e retornado -1;
int elem_order(TABLE , char *);

//Funcao responsavel por realizar uma busca binaria por um elemento
//em um arquivo de indice ordenado de maneira estavel, imprimindo todos
//aqueles que tiverem mesma caracteristica de busca...
int file_binary_search( FILE *, char *, int , char *, int , TABLE *, STAT *, int *);

//Funcao responsavel por realizar uma busca sequencial por um elemento
//em um arquivo temporario, imprimindo todos aqueles que tiverem mesma
//caracteristica de busca...
int file_sequential_search(FILE *, char *, int , int , int , TABLE *,STAT *, int *);

//Funcao responsavel por criar uma tabela com caracteristicas informadas
//pelo usuario atraves de um arquivo de texto...
TABLE create_table(FILE *, STAT *);

//Funcao responsavel por criar um arquivo de indice com base em um parametro
//informado pelo usuario atraves de um arquivo de texto...
void create_index(FILE *, TABLE *, int , STAT *);

//Funcao responsavel por inserir um elemento em uma tabela. Este elemento
//inserido fica inicialmente salvo em um arquivo temporario.
void insert_into(FILE *, TABLE *);

//Funcao responsavel por buscar um elemento no "Banco de Dados". Esta busca
//e feita atraves de uma busca sequencial em um arquivo temporario (gerado
//pela insercao de elementos em uma tabela) e de uma busca binaria em um 
//arquivo ordenado (gerado pela funcao 'create index')...
void select_(FILE *, TABLE *, int , STAT *);

//Funcao responsavel por regerar um arquivo de indice...
void sort_(FILE *, TABLE *, STAT *);

//Funcao responsavel por imprimir na tela todas as tabelas criadas, respeitando
//a ordem de criacao...
void showalltables( TABLE *, int );

//Funcao responsavel por imprimir na tela todos os arquivos de indice ja
//criados pelo usuario, respeitando a ordem de criacao...
void showallindexes( STAT *);

//Funcao responsavel por imprimir na tela as estatisticas do "SGBD".
void statitics( STAT *);

//Funcao responsavel por retornar qual operacao deve ser realizada a partir da 
//leitura de um arquivo de comandos do usuario...
int select_operation(FILE *);

//Funcao responsavel por simular um "Sistema de Gerenciamento de Banco de Dados",
//garantindo a correta leitura de arquivos de comando, assim como a correta
//destinacao de cada funcao...
void Database_problem( FILE *);

#endif
