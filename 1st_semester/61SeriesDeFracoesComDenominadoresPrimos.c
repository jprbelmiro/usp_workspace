#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int *remolding_vector(int *L, int tam, int kl, int j, int *counter){
// - Função : remolding_vector()
// Responsável manipular um vetor de inteiros a fim de remolda-lo retirando os numeros
//não primos existentes nele...
    int *aux = NULL;
    int c = j+1, i = 0;

    //Conferindo se i é menor ou igual a k' - se for, continuar o processo;
    if(L[j] <= kl){                                                 //1) i <= k':
        *counter = 0;
        while(i<=j){                                                //o primeiro passo é garantir que os numeros que sao
        aux = (int *)realloc(aux,sizeof(int)*((*counter)+1));          //menores que k' obtidos nos processos passados e neste
        aux[(*counter)++] = L[i++];                                    //continuem fazendo parte do vetor, entao...
        }
            while(c < tam){                                             //2) Conferir os multiplos de "i" e nao
                if(L[c] % L[j] != 0){                                   //atribuir ao novo vetor L;
                    aux = (int *)realloc(aux,sizeof(int)*((*counter)+1));
                    aux[(*counter)++] = L[c];
                }
                c++;
            }
        free(L);                                              //Liberando o vetor antigo;
        return remolding_vector(aux,(*counter),kl,j+1,counter);          //refazendo o mesmo processo com o novo vetor;
    }
    else{
        *counter = *counter == 0 ? L[tam-1]-c : *counter;
		return L;
    }
}

int *sieve_vector_Create( int k ){
// - Função : sieve_vector_Create()
// Responsável por criar um vetor de numeros inteiros de 2 a um numero 'k', entrado pelo usuario...
    int i;
    int *vector = NULL;
    for(i = 2 ; i <= k ; i++){
        vector = (int *)realloc(vector,sizeof(int)*(i-1));
        vector[i-2] = i;
    }

    return vector;
}

void Apply_Serie( int n ){
// - Função : Apply_Serie()
// Responsável por encontrar os numeros primos e realizar a soma da sequencia...
    int i, j = 0, counter = 0, *primes = NULL;
    double sum = 0;

    //OBS.: Os primos são encontrados através do Crivo de Eratostenes...
    primes = sieve_vector_Create(n);
    primes = remolding_vector(primes, n-1, floor(sqrt(n)), j, &counter);

    //- Realizando a soma da sequencia...
    for( i = 0 ; i < counter ; i ++){
            sum += (pow(-1,j++)/primes[i]);
    }
    free(primes);

    // O resultado é impresso na tela ao final...
    printf("%lf",sum);

    return;
}

int main ( int argc , char **argv){
//      Series de Fracoes com Denominadores Primos
// - Inicialmente pede-se ao usuario que entre com o valor de um numero inteiro
// 'n'. Este numero será utilizado para realizar a soma de uma sequencia de sinal
// alternado do inverso dos numeros primos de 2 até este valor entrado...
    int n;
    scanf("%d%*c",&n);
        Apply_Serie(n);

    return 0;
}
