#include <stdlib.h>
#include <stdio.h>

int *ScanNumeros (int qtdd){
    int *numeros = (int *)malloc(sizeof(int)*(qtdd+1));
    int *novo;

// lendo -------------------------------------------------------------------
    int i, n, c = 0;
    for(i = 1 ; i <= qtdd ; i++){
    scanf("%d",&n);
    numeros[i]=n;
    c++;
    } numeros[0]= c; // este endereco sera responsavel por retornar o valor
                    // que representa o tamanho do ponteiro;

    return numeros;
}

int main (int arc, char *argv[]){

// entrando com a chave e a quantidade de numeros------------------------------------------------------------------------
    int k,qtdd;
    scanf("%d%d",&k,&qtdd);

// entrando com os numeros-----------------------------------------------------------------------------------------------
    int *num =(int *)malloc(sizeof(int)*(qtdd+1));
    num = ScanNumeros(qtdd);    //esta funcao sera responsavel realizar a
                                //leitura dos 'n' numeros. (n == qtdd);

// criando vp e vd para a impressão;
    int **vd = (int **)malloc(sizeof(int*)*k);
    int *vp = NULL;

    int i, c, j;
    for(i = 0; i < k ; i++){    // este laço sera responsavel por
        printf("%d: ",i);       //imprimir na tela a tabela com os
                                //valores organizados;
        c = 0;

        for(j = 1 ; j <= num[0] ; j++){                 // aqui, tem-se a atribuicao dos numeros do
            if((num[j] % k) == i){                      //ponteiro 'num' para o ponteiro 'vp' de modo que
            vp = (int *)realloc(vp,sizeof(int)*(c+1));  //numeros que, quando divididos pela chave 'k', tenham
            vp[c++] = num[j];                           //o mesmo resto, fiquem em um mesmo 'vetor', ou seja, destro
            }                                           //de vp;
        } vd[i] = vp;           // atribui-se o ponteiro vp ao endereço de vd cujo 'indice' representa o
        vp = NULL;              //resto comum aos numeros dividido pela chave 'k';

        for(j = 0; j < c ; j++){        //impressao dos numeros contidos em vd;
            printf("%d ", *(vd[i]+j));
        }

        printf("\n");
    }

// liberacao dos espacos de memorias allocados pelos ponteiros ---------------------------------------------------------
    free(num);
    free(vp);
    free(vd);


    return 0;
}
