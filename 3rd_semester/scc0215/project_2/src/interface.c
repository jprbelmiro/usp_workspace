#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "regexCustom.h"
#include "interface.h"

//Funcoes de impressao de interface
void printOperations(){
    printf("|\t(1) Inserir novo registro [insert]                            |\n");
    printf("|\t(2) Remover registro existente [remove/rm]                    |\n");
    printf("|\t(3) Exibir estatisticas dos arquivos de indice [index stat]   |\n");
    printf("|\t(4) Exibir estatisticas dos arquivos de dados [data stat]     |\n");
    printf("|\t(0) Sair do programa [exit/quit/q]                            |\n");
    return;
}

void printInvalidOp(){
    printf("\n|Operacao Invalida. As operacoes disponiveis sao:                     |\n");
    printOperations();
    return;
}

void printSelectOp(){
    printf("|Qual operacao voce deseja realizar?                                  |\n");
    printf("|Digite o codigo ou a chave e pressione ENTER para inicia-la.         |\n> ");
    return;
}

void printBye(){
    printf(" _____________________________________________________________________\n");
    printf("| Obrigado por usar nosso programa! Ate a proxima!                    |\n");
    printf("|---                                                                  |\n");
    printf("| SCC0215 . Organização de Arquivos . Turma A                         |\n");
    printf("| Gabriel Cyrillo dos Santos Cerqueira - nº 9763022                   |\n");
    printf("| Joao Pedro Ramos Belmiro             - nº 9791198                   |\n");
    printf("| Juliana de Mello Crivelli            - nº 8909303                   |\n");
    printf("| Matheus Aparecido do Carmo Alves     - nº 9791114                   |\n");
    printf("|---                                                                  |\n");
    printf("| Professora Ciferri - 1o Semestre 2017                               |\n");
    printf("|_____________________________________________________________________|\n");
    return;
}

void printWelcome(){
    printf(" _____________________________________________________________________\n");
    printf("|\tTRABALHO 2 - ORGANIZACAO DE ARQUIVOS                          |\n");
    printf("|\t                                                              |\n");
    printf("|\tBem vindo ao programa criado para o segundo trabalho da disci_|\n");
    printf("| plina Organizacao de Arquivos.                                      |\n");
    printf("|\tEste programa consiste, basicamente, na aplicacao e  manipula_|\n");
    printf("| cao de arquivos indexados por indices primarios. A partir de  um ar_|\n");
    printf("| quivo de dados governamental, serao criados tres arquivos  de  saida|\n");
    printf("| formatados corretamente para manipulacao, i.e.,hibridizados com cam_|\n");
    printf("| pos de tamanho variavel ao final, tradados por indicadores de  tama_|\n");
    printf("| nho, e com os campos fixos no  inicio  do  registro ( cada  registro|\n");
    printf("| eh de tamanho variavel e tratado por delimitadores).                |\n");
    printf("|\tCada um dos arquivos criados sera manipulado por  uma politica|\n");
    printf("| diferente (Best,Worst e First-Fit),ordenacao tambem distinta,mas to_|\n");
    printf("| dos terao tratamento de fragmentacao interna e nao ocorrera a juncao|\n");
    printf("| de espacos vazios adjacentes.                                       |\n");
    printf("|\tAssim, torna-se possivel realizar uma comparacao do resultado |\n");
    printf("| da manipulacao de cada tipo de arquivo.Estatisticas serao geradas em|\n");
    printf("| cima de sua manipulacao e podem ser apresentadas a qualquer momento.|\n");
    printf("|Voce por realizar as seguintes operacoes:                            |\n");
    printOperations();
    printf("|OBS.:PARA A OPERACAO DE REMOCAO DEVE-SE ENTRAR O NUMERO DO TICKET DE_|\n");
    printf("| SEJADO, UMA VEZ QUE O ARQUIVO DE INDICE PRIMARIO  FOI CONSTRUIDO COM|\n");
    printf("| BASE NOS NUMEROS DO TICKET DE CADA REGISTRO.                        |\n");
    printf("|_____________________________________________________________________|\n");
    printf("APERTE 'ENTER' PARA CONTINUAR PARA O SISTEMA...");
    getchar();
    printf("\n");
    return;
}

//Funcoes de operacao
int readOperation(){
    int op = INVALID;
    char *string = readLine(stdin, 10);
    if(string){
        if(match(string,"^\\s*[Ii]+[Nn]+[Ss]+[Ee]+[Rr]+[Tt]+\\s*$") ||
            match(string,"^\\s*[1]\\s*$"))
            op = INSERT;
        else if(match(string,"^\\s*[Rr]+[Ee]+[Mm]+[Oo]+[Vv]+[Ee]+\\s*$") ||
            match(string,"^\\s*[Rr]+[Mm]+\\s*$") || match(string,"^\\s*[2]\\s*$"))
            op = REMOVE;
        else if(match(string,"^\\s*[Ii]+[Nn]+[Dd]+[Ee]+[Xx]+\\s+[Ss]+[Tt]+[Aa]+[Tt]+\\s*$") ||
            match(string,"^\\s*[3]\\s*$"))
            op = INDEX_STAT;
        else if(match(string,"^\\s*[Dd]+[Aa]+[Tt]+[Aa]+\\s+[Ss]+[Tt]+[Aa]+[Tt]+\\s*$") ||
            match(string,"^\\s*[4]\\s*$"))
            op = DATA_STAT;
        else if(match(string,"^\\s*[Ee]+[Xx]+[Ii]+[Tt]+\\s*$") ||
            match(string,"^\\s*[Qq][Uu][Ii][Tt]\\s*$")|| match(string,"^\\s*[Qq]\\s*$")|| 
            match(string,"^\\s*[0]\\s*$"))
            op = EXIT;
        else
            op = INVALID;
        free(string);
    }
    return op;
}