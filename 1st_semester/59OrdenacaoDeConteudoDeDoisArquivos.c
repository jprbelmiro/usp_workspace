#include <stdlib.h>
#include <stdio.h>

typedef struct dd dados;

struct dd {
    char *cpf;
    char *nome;
    char *idade;
};

void freeInfo(dados *pessoais, int num_events){

    int i, j;                           //funcao responsavel por liberar a memoria alocada dentro
    for(i = 0; i < num_events; i++){    //da struct;
        free((pessoais+i)->cpf);
        free((pessoais+i)->nome);
        free((pessoais+i)->idade);
    }

    return;
}

void sortCPF(dados *pessoais, int N){

    int i , j;                      //funcao responsavel por ordenar as informacoes contindas na
    char *aux;                      //struct do menor numero de cpf para o maior, imprimindo-o
    for(i = 0; i < N ; i++){        //na sequencia;
        for(j = i+1 ; j < N ; j++){
            if(strcmp((pessoais+i)->cpf,(pessoais+j)->cpf) >0){
                aux = (pessoais+i)->cpf;
                (pessoais+i)->cpf = (pessoais+j)->cpf;
                (pessoais+j)->cpf = aux;

                aux = (pessoais+i)->nome;
                (pessoais+i)->nome = (pessoais+j)->nome;
                (pessoais+j)->nome = aux;

                aux = (pessoais+i)->idade;
                (pessoais+i)->idade = (pessoais+j)->idade;
                (pessoais+j)->idade = aux;
            }
        }
        printf("%s\n%s\n%s\n",(pessoais+i)->cpf,(pessoais+i)->nome,(pessoais+i)->idade);
    }


    return;
}

char *readLineOfFile(FILE *fp){
    char c;                     //funcao responsavel por ler uma linha
    char *string = NULL;        //a partir de um arquivo;
    int counter = 0;
    do{
        c = fgetc(fp);
        string = (char *)realloc(string, sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10 && c != EOF);
    string[counter - 1] = '\0';

    return string;
}

void readInfo(dados *pessoais, FILE *fp1, FILE *fp2, int num1, int num2){
    int i, j;

    fseek(fp1,0,SEEK_SET);                              //funcao responsavel por
    for(i = 0 ; i < num1 ; i++){                        //ler dados dos 2 arquivos
        (pessoais+i)->cpf = readLineOfFile(fp1);        //utilizando uma funcao
        (pessoais+i)->nome = readLineOfFile(fp1);       //parecida com a readLine
        (pessoais+i)->idade = readLineOfFile(fp1);      //e armazena-los em uma
    }                                                   //struct de dados unica
                                                        //para ambos;
    fseek(fp2,0,SEEK_SET);
    for(; i < num2+num1 ; i++){
        (pessoais+i)->cpf = readLineOfFile(fp2);
        (pessoais+i)->nome = readLineOfFile(fp2);
        (pessoais+i)->idade = readLineOfFile(fp2);
    }

    return;
}

int counterInfo(FILE *fp){
    int num = 0;            //funcao responsavel por retornar o numero
    char c;                 //de pessoas com dados no arquivo;

    while( c != EOF){
        c = fgetc(fp);
        if(c == 10) num++;
    }


    return (num+1)/3;
}

char *readLine(){
    char c;                 //funcao responsavel por ler uma 'linha'
    char *string = NULL;    //a partir do teclado;
    int counter = 0;
    do{
        c = fgetc(stdin);
        string = (char *)realloc(string, sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10);
    string[counter - 1] = '\0';

    return string;
}

int main (int argc, char **argv){
//1.1) Lendo o nome do primeiro arquivo;
    char *file_name1 = readLine();
    //abrindo o arquivo;
    FILE *fp1 = fopen(file_name1,"r");
    //conferindo a existencia de um arquivo com este nome;
    if ( fp1 == NULL){
        printf("There is no file to read.");
        exit(1);
    }
    //descobrindo o numero de pessoas com dados no arquivo;
    int num_dados1 = counterInfo(fp1);

//1.2) Lendo o nome do primeiro arquivo;
    char *file_name2 = readLine();
    //abrindo o arquivo;
    FILE *fp2 = fopen(file_name2,"r");

    //conferindo a existencia de um arquivo com este nome;
    if ( fp2 == NULL){
        printf("There is no file to read.");
        exit(1);
    }

    //descobrindo o numero de pessoas com dados no arquivo;
    int num_dados2 = counterInfo(fp2);

//2) Separando os dados de pessoa por pessoa;
    dados *pessoais = malloc(sizeof(dados)*(num_dados1+num_dados2));
    readInfo(pessoais,fp1,fp2,num_dados1,num_dados2);

//3) Ordenando e imprimindo os dados;
    sortCPF(pessoais,num_dados1+num_dados2);

//4) Liberando a memoria utilizada;
    freeInfo(pessoais,num_dados1+num_dados2);
    free(pessoais);
    free(file_name1);
    free(file_name2);
    fclose(fp1);
    fclose(fp2);

    return;
}
