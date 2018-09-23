#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

#define F_SIZE 61

typedef struct t_insert{
  char **fixedFields;
  char **variableFields;
  int ticket;
}t_insert;

typedef struct{
    int offset;
    int size;
}t_removed;

/*
* Funcao responsavel por identificar e remover um registro específico contido
* nos arquivos de dados e nos seus índices primários correspondentes.
* @param FILE *datafile - arquivo de dados
* @param t_index **index - estrutura em RAM do índice primário
* @param int indexSize - número de registros contidos no índice 
*/
void removeFromAll(FILE *datafile1, FILE *datafile2, FILE *datafile3, 
        t_index **index1, t_index **index2, t_index **index3, 
        int *indexSize1, int *indexSize2, int *indexSize3);
        
/*
* Funcao responsavel por ler e incluir um registro do usuários
* nos arquivos de dados e seus respectivos índices primários
* @param FILE *datafile - arquivo de dados
* @param t_index **index - estrutura em RAM do índice primário
* @param int indexSize - número de registros contidos no índice 
*/
void insertInAll(FILE *datafile1, FILE *datafile2, FILE *datafile3, 
        t_index **index1, t_index **index2, t_index **index3, 
        int *indexSize1, int *indexSize2, int *indexSize3);

/*
* Função para visualização da estatísticas sobre os arquivos de 
* índice, com a quantidade de entradas que ele possui.
* Exibição dos registros dos três índices simultaneamente, um por vez.
* @param t_index **index - estrutura em RAM do índice primário
* @param int indexSize - número de registros contidos no índice
*/

void indexStats(t_index *index1, t_index*index2, t_index *index3, int indexSize1, int indexSize2, int indexSize3);

/*
* Função para descrever a lista ligada criada em cada um dos
* arquivos de dados de acordo com a política de reaproveitamento
* de espaço de fragmentação interna (first, best ou worst fit).
* @param FILE *datafile - arquivo de dados
*/
void fileStats(FILE *datafile1, FILE *datafile2, FILE *datafile3);

int indexesCompare(const void * a, const void * b);

#endif
