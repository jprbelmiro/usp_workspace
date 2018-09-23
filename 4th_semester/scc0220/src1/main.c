/*
****** EXERCICIO 1 - A RAPOSA E O COELHO *****************************
* Resolução por: Matheus Aparecido do Carmo Alves - No.USP: 9791114
* Aula 1 - 04.08.2017 - SCC0220 - Laboratorio de ICC I
**********************************************************************
*   Em um grande campo viviam coelhos e uma raposa. A raposa quer de_
*vorar um coelho, enquanto o coelho quer fugir da raposa por  um  dos
*muitos buracos que possui no campo. Tanto a raposa quanto  o  coelho
*nao sao especialistas em matematica, mas tambem  nao  sao  completa_
*mente estupidos. O coelho escolhe um buraco  e  segue  em  direcao a 
*ele em linha reta e a uma velocidade constante. A raposa, que e mui_
*to boa em leitura de linguagem corporal, segue no mesmo instante  em
*direcao ao mesmo buraco escolhido pelo coelho, em linha reta e a uma
*velocidade igual ao dobro da velocidade do coelho. Se a raposa atinge
*o buraco primeiro ela devora o coelho, caso contr´ario o  coelho es_
*capa. Seu objetivo e escolher um buraco pelo qual o coelho possa es_
*capar, se tal buraco existir.
*   A entrada consiste de varios  casos de teste. A primeira  linha  de 
*cada caso contem um inteiro e quatro numeros  em  ponto  flutuante.  O 
*inteiro n denota o numero de  buracos  presentes  no  campo para  esse 
*caso de teste e os quatro n´umeros em ponto flutuante denotam as coor_
*denadas (x, y) do coelho seguidas das coordenadas (x, y) da raposa. Na
*sequˆencia, sao dadas n linhas com dois n´umeros em ponto flutuante:as 
*coordenadas  (x, y) de cada um dos buracos. Todas as distˆancias estao
*em metros.
*   Para cada caso, se o coelho puder fugir, a saıda deve conter  a  frase 
*”O coelho pode escapar pelo buraco (x,y).”. Caso contrario, a  saıda  de_
*ve conter a frase ”O coelho nao pode escapar.”. Se o coelho puder escapar
*por mais de um buraco, mostre na sa´ıda o buraco que aparece em  primeiro
*lugar na entrada. Nao ha mais que 1000 buracos em cada caso de teste e to_
*das as coordenadas variam entre −10000 e +10000. A saıda e sempre exibida 
*com 3 casas decimais
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Funcao responsavel por liberar uma matriz de tamanho n armazenada na memoria
void freeMatrix(void **matrix, int n){
    int i = 0;
    
    for(i = 0 ; i < n ; i++)
        if(matrix[i])
            free(matrix[i]);
            
    if(matrix)
        free(matrix);
    return;
}

// Funcao responsavel por liberar um vetor armazenado na memoria
void free_(void *pointer){
    if(pointer)
        free(pointer);
    return;
}

// Funcao responsavel por realizar o calculo da distancia euclidiana entre dois
//pontos, isto e, calcular a distancia ponto a ponto para dois pontos...
double euclideanDistance(double *pointA, double *pointB){
    double distance = 0;
        distance = sqrt(pow(pointA[0] - pointB[0],2) + pow(pointA[1] - pointB[1],2));
    return distance;
}

int main(int argc, char **argv){
    //0. Variaveis
    int n = 0, counter = 0, holeNumber = 0, *results = NULL;
    double rabbitDist = 0, foxDist = 0; 
    double *rabbit = NULL, *fox = NULL, **hole = NULL;
    
    //1. Realizando as leituras das entradas...
    //a. Lendo o numero de buracos...
    scanf("%d%*c",&n);
    
    //b. Lendo as posicoes iniciais do coelho e da raposa nesta sequencia...
    rabbit = (double *)malloc(sizeof(double)*2);
    scanf("%lf%*c%lf%*c",&(rabbit[0]),&(rabbit[1]));
    
    fox = (double *)malloc(sizeof(double)*2);
    scanf("%lf%*c%lf%*c",&(fox[0]),&(fox[1]));
    
    //2. Lendo as coordenadas dos n buracos e verificando de imediato se o coe_
    //lho possui alguma chance de escapar da raposa por esse buraco...
    //- as coordenadas deste buraco eh armazenado em uma matriz...
    hole = (double **)malloc(sizeof(double *)*n);
    while(holeNumber < n){
        hole[holeNumber] = (double *)malloc(sizeof(double)*2); 
        scanf("%lf%*c%lf%*c",&(hole[holeNumber][0]),&(hole[holeNumber][1]));
        
        rabbitDist = euclideanDistance(rabbit,hole[holeNumber]);
        foxDist = euclideanDistance(fox,hole[holeNumber]);
        if(rabbitDist < foxDist/2){
            results = (int *)realloc(results,sizeof(int)*(counter+1));
            results[counter++] = holeNumber;
        }
        holeNumber++;
    }
    
    //3. Imprimindo na tela o primeiro resultado encontrado...
    if(counter != 0)
        printf("O coelho pode escapar pelo buraco (%.3lf,%.3lf).\n",hole[results[0]][0],hole[results[0]][1]);
    else
        printf("O coelho nao pode escapar.\n");
        
        
    //4. Liberando a memoria utilizada...
    free_((void *)results);
    free_((void *)rabbit);
    free_((void *)fox);
    freeMatrix((void **)hole,n);
        
    return 0;
}