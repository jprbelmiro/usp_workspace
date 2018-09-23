#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Contagem_de_Ocorrencias(char *string, int tam_arquivo, char *s){
    int i, j,counter = 0;                                               // Nesta funcao ocorre a contagem de repeticoes de uma "string"
                                                                        //na outra. No caso, a contagem de repeticoes de uma string
    for(i = 0; i < strlen(string)-strlen(s); i++){                      //definida pelo usuario na mensagem do arquivo selecionado.
        for(j = 0; j < strlen(s) && s[j] == string[i+j] ; j++);
            if(j == strlen(s)) counter++;
    }
    printf("%d",counter);
}

int Verificar_Shift(unsigned int *v){
    char *c = (char *) v;                               // Esta funcao eh complementar a Descriptografia, sendo ela responsavel por
    int i;                                              //verificar quais bytes fazem, realmente, parte da mensagem. Ela faz isso
    for(i = 0 ; i < 4 ; i++){                           //buscando por simbolos especificos que podem constituir a mensagem.
        if(!((*(c+i) >= 48 && *(c+i) <= 57) || (*(c+i) >= 65 && *(c+i) <= 90) || (*(c+i) <= 122 && *(c+i) >= 97)
             || (*(c+i) == 58) || (*(c+i) == 46) || (*(c+i) == 32) || (*(c+i) == '\0') || (*(c+i) == 44) || (*(c+i) == 40)
             || (*(c+i) == 41) || (*(c+i) == 63) || (*(c+i) == 33))){
                    return 0;
             }
    }
     return 1;
}

void Descriptografia(unsigned int *v, int tam_arquivo, int escolha){
    int i;
    for (i = 0 ; i < tam_arquivo ; i++){                                       //Aqui ocorre todo o processo de descriptografia do
        int valid = Verificar_Shift(&v[i]);                                    //arquivo por um processo pre-definido, ou seja, ocorre
            if(valid == 0){                                                    //o processo inverso da criptografia.
                v[i] = v[i]>>1;
            }
    }
    if(escolha ==2)printf("%s",(char *)v);

}

unsigned int obtendo_o_digito(unsigned int *v, int k, int i ){
    int j;                                                                     //Esta funcao eh responsavel por resgatar o digito
    unsigned int digito = v[i];                                                //desejado em cada unsigned int contido no vetor v;

    if( k > 0){for(j = 0 ; j < k ; j++){
                digito /= 10;
                }
    }

    digito %= 10;

    return digito;
}

void Mapeamento_de_Digitos(char *arquivo, unsigned int *v, int tam_arquivo){
    int i, k = arquivo[0] - 48, digito;                                        //Aqui ocorre o proceso de Mapeamento de
    for(i = 0 ; i < tam_arquivo ; i++){                                        //Digitos e a impressao do resultado;
        digito = obtendo_o_digito(v,k,i);
        printf("%u", digito);
        k = digito;
    }

}

void Desinverter(unsigned int **v, int tam_arquivo){
    int i;
    unsigned int aux = 0;
    for(i = 0 ; i < tam_arquivo ; i++){                 //Nesta funcao, ocorre a troca da posicoes dos termos
       aux = *(*(v)+i);                                 // de um vetor. No caso, inverte-se o inicio com o fim.
       *(*(v)+i) = *(*(v)+(tam_arquivo-1));         //O 1o termo vira o ultimo, o 2o o penultimo e assim em diante...
        *(*(v)+(tam_arquivo-1)) = aux;
        tam_arquivo--;
    }

    return;
}

char *readLine(){ //Esta funcao eh responsavel por criar strings.

    char s;
    char *string = NULL;
    int counter = 0;
    do{ s=fgetc(stdin);
        string=(char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++]=s;
        }while(s != 10);
            string[counter-1]='\0';

    return string;
}

//(0)==============================================================================================================================
int main(int argc, char *argv[]) {
//Selecionando o arquivo pelo nome;--------------------------------------------
    char *arquivo;                                                      //(0.a)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    arquivo=readLine();                                                         //Esta eh a primeira parte do trabalho.
                                                                                //Aqui, faz-se a leitura do nome do arquivo
    FILE *read_file;                                                            //para abri-lo como leitura;
    read_file = fopen(arquivo,"rb");

    // conferindo se e possivel a leitura do arquivo selecionado;
        if (read_file == NULL) {                                                //Este 'if' foi usado para garantir que o ar_
            printf("Nao ha nada para a leitura.\n");                            //quivo foi aberto com sucesso.
            exit(1);
        }

//Atribuindo o tamanho do arquivo para uma variavel----------------------------
    int tam_arquivo = 0;                                                 //(0.b)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    fseek(read_file, 0, SEEK_END);                                              //Nesta segunda parte, percorre-se o arquivo
    tam_arquivo = ftell(read_file) / 4;                                         //contando quantos bytes ele contem.
                                                                                //Uma vez que tratam-se de inteiros, divide-se
                                                                                //o tamanho por 4 para saber o no. de elementos;
//Atribuindo a mensagem do arquivo para um vetor-------------------------------
    fseek(read_file, 0, SEEK_SET);                                       //(0.c)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    unsigned int *v = (unsigned int *)calloc(tam_arquivo,sizeof(unsigned int)); //No ponto 'c', ha a atribicao dos caracteres lidos
                                                                                // a um ponteiro.
    fread(v,sizeof(unsigned int),tam_arquivo,read_file);

//Desinvertendo o vetor--------------------------------------------------------
    Desinverter(&v,tam_arquivo);                                         //(1.d)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int i;                                                                      //Nesta parte, 'desiverte-se' o vetor criado;

//Selecionando a função que será utilizada-------------------------------------
    int escolha;                                                         //(1.e)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    scanf("%d",&escolha);                                                       //Aqui, havera a escolha entre o Mapeamento de Digitos,
                                                                                //a Descriptografia e a Contagem de ocorrencias com a
                                                                                //entrada de um numero inteiro;
//(1)Mapeamento de Digitos==============================================================================================================================
    if(escolha == 1) Mapeamento_de_Digitos(arquivo,v,tam_arquivo);      //Iniciando a funcao escolhida.
//(2)Descriptografia====================================================================================================================================
    else if(escolha == 2) Descriptografia(v,tam_arquivo,escolha);       //Iniciando a funcao escolhida.
//(3)Contagem de ocorrencia=============================================================================================================================
    else if(escolha == 3){
            fgetc(stdin);                                               //Aqui limpamos o buffer para poder entrar com a string 's'.
        char *s = readLine();
        Descriptografia(v,tam_arquivo,escolha);
        Contagem_de_Ocorrencias((char *)v,tam_arquivo,s);                  //Inciando a funcao escolhida.
    }

    else printf("Operando invalido.");  //Informando uma entrada nao valida.

	fclose(read_file); //fechando o arquivo aberto anteriormente.
	free(v);            //liberando a memorio utilizada.

	return 0;
}
