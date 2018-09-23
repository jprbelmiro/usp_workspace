#ifndef _T6_HASH_H_
#define _T6_HASH_H_

//Estrutura responsavel por auxiliar e dinamizar o processo de obtencao de res_
//posta para a aplicacao implementada...
typedef struct hash_anagram_aux HA_AUX;
struct hash_anagram_aux{
    int nindexes;
    int nanagrams;
    int *indexes;
};

//Estrutura responsavel por representar um indice da hash...
typedef struct hash_anagram_struct HA_STRUCT;
struct hash_anagram_struct{
    int nwords;
    char **words;
};

//Estrutura responsavel por caracterizar a hash table da aplicacao...
typedef struct hash_table HASH;
struct hash_table{
    int nindex;
    int total_words;
    HA_STRUCT *ha_struct;
};

//Funcao responsavel por liberar a tabela hash da memoria...
void free_hash(HASH *hash_table);

//Funcao responsavel por criar uma tabela hash...
HASH *create_hash(int );

//Funcao responsavel por realizar a dispersao de um conjunto de dados vindos de
//um arquivo em uma tabela hash...
void hash_dispersing(int *, HASH *, FILE *);

#endif