#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "t6_basic.h"
#include "t6_hash.h"

void free_hash(HASH *hash_table){
    int i, j;
    for(i = 0 ; i < hash_table->nindex ; i++){
        for(j = 0 ; j < hash_table->ha_struct[i].nwords ; j++)
            free(hash_table->ha_struct[i].words[j]);
        if(hash_table->ha_struct[i].nwords != 0) 
            free(hash_table->ha_struct[i].words);
    }
    free(hash_table->ha_struct);
    free(hash_table);
    return;
}

//Funcao responsavel por ordenar os elementos de um indice da tabela hash...
static void heapsort_hastructs(HA_AUX *aux_struct, HASH *hash_table, int n){
   int i = n/2, father, son;
   int aux;
   
   while(1){
      if(i > 0){
          i--;
          aux = aux_struct->indexes[i];
      } 
      else{
          n--;
          if(n == 0) return;
          aux = aux_struct->indexes[n];
          aux_struct->indexes[n] = aux_struct->indexes[0];
      }

      father = i;
      son = (i * 2)+1;

      while(son < n){
          if((son + 1 < n)  &&  (strcmp(hash_table->ha_struct[aux_struct->indexes[son + 1]].words[0],
                                    hash_table->ha_struct[aux_struct->indexes[son]].words[0]) >0)) son++;
               
          if(strcmp(hash_table->ha_struct[aux_struct->indexes[son]].words[0],
                    hash_table->ha_struct[aux].words[0])>0){

             aux_struct->indexes[father] = aux_struct->indexes[son];
             father = son;
             son = father * 2 + 1;
          } else break;
      }
      aux_struct->indexes[father] = aux;
   }
   
   return;
}

//Funcao responsavel por imprimir na tela o resultado da aplicao no formato 
//desejado...
static void print_hash_result(HASH *hash_table, HA_AUX *aux_struct){
    int i, j;
    
    //Ordenando segundo a lexografia, cada indice resultado...
    for(i = 0 ; i < aux_struct->nindexes ; i++)
        heapsort_strings(hash_table->ha_struct[aux_struct->indexes[i]].words,
                        hash_table->ha_struct[aux_struct->indexes[i]].nwords);
                        
    //Ordenando a impressao dos indices em ordem lexografica
    heapsort_hastructs(aux_struct, hash_table,aux_struct->nindexes);

    //Imprimindo o resultado...
    printf("%d\n",aux_struct->nindexes);
    for(i = 0 ; i < aux_struct->nindexes ; i++){
        for(j = 0 ; j < aux_struct->nanagrams ; j++){
            if(j == aux_struct->nanagrams-1) 
                printf("%s\n",hash_table->ha_struct[aux_struct->indexes[i]].words[j]);
            else printf("%s, ",hash_table->ha_struct[aux_struct->indexes[i]].words[j]);
        }
    }
    return;
}

//Funcao responsavel por realizar a indexacao de cada elemento da Hash...
static double hash_index(char *string, int *primes, int m){
    int i;
    double index = 1;
    for(i = 0 ; i < strlen(string) ; i++){
        if(string[i] == '-') index *= primes[26];
        else index *= primes[string[i]-97];
        index = (int)index % m;
    }
    return index;
}

//Funcao responsavel por inserir um elemento na hash table...
static void hash_put(HASH *hash_table, char *string, int key, HA_AUX *aux_struct){
    //Inserindo um elemento na hash table...
    if(hash_table->ha_struct[key].nwords == 0)
        hash_table->ha_struct[key].words = NULL;
    
    if(hash_table->ha_struct[key].nwords != 0 
        && strlen(hash_table->ha_struct[key].words[0]) != strlen(string))
            return hash_put(hash_table,string, key+1,aux_struct);
            
    hash_table->ha_struct[key].words = (char **)realloc
                            (hash_table->ha_struct[key].words,
                            sizeof(char *)*(hash_table->ha_struct[key].nwords+1));
    
    hash_table->ha_struct[key].words[hash_table->ha_struct[key].nwords] = string;
    hash_table->ha_struct[key].nwords +=1;
    
    //Modificando a estrutura auxiliar auxiliar...
    if(hash_table->ha_struct[key].nwords > aux_struct->nanagrams){
        if(aux_struct->indexes != NULL || aux_struct->nanagrams == 0){
            free(aux_struct->indexes);
            aux_struct->indexes = NULL;
        }
        aux_struct->nindexes = 0;
        aux_struct->nanagrams = hash_table->ha_struct[key].nwords;
        
        aux_struct->indexes = (int *)realloc(aux_struct->indexes,sizeof(int)*(aux_struct->nindexes+1));
        aux_struct->indexes[aux_struct->nindexes] = key;
        aux_struct->nindexes += 1;
    }
    else if(hash_table->ha_struct[key].nwords == aux_struct->nanagrams){
        aux_struct->indexes = (int *)realloc(aux_struct->indexes,sizeof(int)*(aux_struct->nindexes+1));
        aux_struct->indexes[aux_struct->nindexes] = key;
        aux_struct->nindexes += 1;
    }
        
    
    return;
}

HASH *create_hash(int m){
    HASH *hash_table = (HASH *)malloc(sizeof(HASH));
    
    hash_table->nindex = m;
    hash_table->total_words = 0;
    hash_table->ha_struct = (HA_STRUCT *)calloc(m,sizeof(HA_STRUCT));
    
    return hash_table;
}

void hash_dispersing(int *primes, HASH *hash_table, FILE *fwords){
    double key;
    char *aux_string = NULL;
    HA_AUX *aux_struct = (HA_AUX *)calloc(1,sizeof(HA_AUX)); 

    //Realizando uma unica leitura do arquivo e inserindo as palavras na hash 
    //de forma que os anagramas se concentrem em um indice especifico...
    while(!feof(fwords)){
        fscanf(fwords,"%ms",&aux_string);
        if(aux_string != NULL || !feof(fwords)){
            key = hash_index(aux_string,primes,hash_table->nindex);
            hash_put(hash_table,aux_string,key,aux_struct);
            hash_table->total_words += 1;
        }
    }
    
    //Organizando os indices com maior conjuto de anagramas para impressao e 
    //imprimindo o resultado final...
    print_hash_result(hash_table,aux_struct);
    
    //Liberando a estrutura auxiliar...
    free(aux_struct->indexes);
    free(aux_struct);
    
    return;
}