#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Funcao responsavel por realizar as remoldelagens do vetor base de eratostenes
//ate se alcancar um vetor que possui somente primos...
static int *eratostenes_remolding(int *L, int tam, int kl, int j){
    int *aux = NULL;
    int counter = 0, c = j+1, i = 0;

    if(L[j] <= kl){
        while(i <= j){
            aux = (int *)realloc(aux,sizeof(int)*(counter+1));
            aux[counter++] = L[i++];
        }
        while(c < tam){
            if(L[c] % L[j] != 0){
                aux = (int *)realloc(aux,sizeof(int)*(counter+1));
                aux[counter++] = L[c];
            }
            c++;
        }
        free(L);
        return eratostenes_remolding(aux,counter,kl,j+1);
    }
    
    return L;
}

//Funcao responsavel por criar o vetor base para a aplicao do teorema de eratos_
//tenes...
static int *eratostenes_vec(int k){
    int counter;
    int *vec = (int *)malloc(sizeof(int)*k-1);
    for(counter = 2 ; counter <= k ; counter++)
        vec[counter-2] = counter;
    return vec;
}

int *eratostenes_sieve(double k){
    int *L = NULL;
    double kl = floor(sqrt(k));
    
    L = eratostenes_vec(k);
    L = eratostenes_remolding(L,k-1,kl,0);

    return L;
}