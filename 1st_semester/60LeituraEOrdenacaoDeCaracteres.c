#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printInt(int *inteiro, int counter){
    int i;                              //imprimindo os numeros;
    for(i = 0 ; i < counter/4 ; i++){
        printf("%d\n",inteiro[i]);
    }
}

void sortSTR(char *string, int counter) {
    int i, j, m, aux;                               //Realizando a ordenação do vetor
        for (i = 0; i < (counter-1); i++) {         //pelo 'selection_Sort';
            m = i;
            for (j = (i+1); j < counter; j++) {
                if(string[j] < string[m])
                m = j;
            }
            if (i != m) {
                aux = string[i];
                string[i] = string[m];
                string[m] = aux;
            }
        }

    return;
}

char *readLineUntilx(int *counter){
    char c;                     //funcao responsavel por ler uma linha na
    char *string = NULL;        //entrada padrao de texto até o 'x';
    do{
        c = fgetc(stdin);
        if(c != 10){
        string = (char *)realloc(string, sizeof(char)*((*counter)+1));
        string[(*counter)++] = c;
        }
    }while(c != 'x');
    string = (char *)realloc(string, sizeof(char)*(*counter+1));
    string[*counter++] = '\0';

    return string;
}

int main (int argc, char **argv){
//1) Lendo a string de caracteres e retornando o tamanho
//da string (atribuida a 'counter');
    int counter = 0;
    char *string = readLineUntilx(&counter);

//2) Ordenando a String;
    sortSTR(string,counter);

//3) Imprimindo os componentes da string como 'inteiro' - 4bytes;
    printInt((int *)string,counter);

//4) Liberando a memoria usada;
    free(string);

    return 0;
}
