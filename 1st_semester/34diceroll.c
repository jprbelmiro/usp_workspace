/*
*	34 - Dice Roll
* This program analysis a dice roll result and print the result 
* (dice face) with the major occurrence.
*/
#include <stdlib.h>
#include <stdio.h>

void Print_Mais_Jogados(int *qtdd_rept){
    int i, j, counter = 1;
    int *maior = (int *)realloc(maior,sizeof(int));
    int M = qtdd_rept[1];

    for(i = 1; i <= 6 ; i++){
        if(M < qtdd_rept[i] ) M = qtdd_rept[i];
    }

    for(i = 1; i <= 6 ; i++){
        if(M == qtdd_rept[i])printf("%d\n",i);
    } printf("%d",M);
	
    return;
}

int main(int argc, char **argv){
	//0. Variables
    int n,i = 0, j, counter = 0;
    int *dado = NULL;
    int *qtdd_rept = (int *)calloc(7,sizeof(int));

	//1. Reading all dice rolls
    while(scanf("%d",&n) != EOF){                               //lendo os lançamentos até o "EOF";
        dado = (int *)realloc(dado,sizeof(int)*(i+1));
        dado[i++] = n;
    } int vezes_lan = i - 1;

	//2. Counting the results occurrences
    for(i = 1; i <= 6 ; i++){                                   //contando quantas vezes cada numero foi
        for(j = 0; j <= vezes_lan ; j++){                       // jogado e armazenando em um vetor;
            if(i == dado[j])counter++;
        }
        qtdd_rept[i]=counter;
        counter = 0;
    }

	//3. Printing the major occurrence result in this dice roll
    Print_Mais_Jogados(qtdd_rept);                         //retornando os numeros com maiores lances e
                                                            //o valor do lance;
	//4. Freeing the used memory
    free(qtdd_rept);
    free(dado);

	//5. That's all folks... :)
    return 0;
}
