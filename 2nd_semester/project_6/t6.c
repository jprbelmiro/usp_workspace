#include <stdlib.h>
#include <stdio.h>
#include "t6_basic.h"
#include "t6_hash.h"
#include "t6_prime.h"

//T6 - Hash Table / Anagrama do Felipe Gigante
int main (int argc, char **argv){
    FILE *fwords = NULL;
    int m, *primes = NULL;
    HASH *hash_table = NULL;
    
    //1- Abrindo o arquivo que contem as palavras do dicionario...
    fwords = fopen_r();
    
    //2- Criando a Hash Table para o problema proposto...
    //- Usa-se m = 300.007 (ou seja, cria-se uma hash indexada de 0 a 300.006)
    //pois sabe-se que ha no maximo uma entrada de 300.000 verbetes para se des_
    //cobrir quais sao anagramas. Logo, no pior dos casos tem-se a entrada de um
    //arquivo que nao possui anagramas, sendo desejavel ocupar toda a hash sem 
    //colisoes (colidindo apenas palavras que sejam anagramas), explicando assim
    //a escolha do tamanho e o fato do numero ser primo.
    m = 300007;
    hash_table = create_hash(m);
    
    //3- Criando um vetor que auxiliara na indexacao das palavras...
    //- Este vetor sera responsavel por indexar cada letra do alfabeto por um
    //numero primo. Desta forma, e possivel indexar cada palavra tomando como 
    //parametro a multiplicacao do valor de suas letras. 
    //- Sendo a multiplicacao de numeros primos responsavel por gerar multiplos 
    //divisiveis apenas por seus proprios primos entao pode-se garantir uma boa 
    //dispersao na tabela.
    primes =  eratostenes_sieve(103);
    
    //4- Lendo o arquivo, dispersando os dados na tabela hash e imprimindo o
    //conteudo dos indices da tabela que possuem maior numero de palavras anagramas...
    hash_dispersing(primes,hash_table,fwords);
    
    //5- Liberando a memoria utilizada e fechando os arquivos abertos...
    free(primes);
    free_hash(hash_table);
    fclose(fwords);
    
    return 0;
}