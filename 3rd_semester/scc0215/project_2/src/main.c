/* 
|    SCC0215 . Organização de Arquivos . Turma A
|    Matheus Aparecido do Carmo Alves       - nº 9791114
|    Juliana de Mello Crivelli              - nº 8909303
|    Joao Pedro Ramos Belmiro               - nº 9791198
|    Gabriel Cyrillo dos Santos Cerqueira   - nº 9763022
*/

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "file.h"
#include "interface.h"
#include "operations.h"

int main (int argc, char **argv){
    //0. Variaveis...
    int op = INVALID, indexSize1, indexSize2, indexSize3;
    FILE *sourcefile = fopen_("turmaA-dadosDominios.csv","r");
    FILE *datafile1 = NULL, *datafile2 = NULL, *datafile3 = NULL;
    FILE *indexfile1 = NULL, *indexfile2 = NULL, *indexfile3 = NULL;
    t_index *index1 = NULL, *index2 = NULL, *index3 = NULL;

    //1. Imprimindo as saudacoes ao usuario...
    printWelcome();

    //2. Manipulando o arquivo de entrada e gerando os três arquivos de saida...
    create_datafile("Data(1)",sourcefile,"%V%F19%V%V%V%F19%F19%F4",FALSE,';');
    create_datafile("Data(2)",sourcefile,"%V%F19%V%V%V%F19%F19%F4",FALSE,';');
    create_datafile("Data(3)",sourcefile,"%V%F19%V%V%V%F19%F19%F4",FALSE,';');

    datafile1 = fopen_("Data(1)","rwb+");
    datafile2 = fopen_("Data(2)","rwb+");
    datafile3 = fopen_("Data(3)","rwb+");
    
    //3. Criando os arquivos de indice primario para cada arquivo de saida...
    indexSize1 = 0;
    index1 = create_primaryidxfile("PrimaryIdx(1)",datafile1,"%F4%F19%F19%F19%V%V%V%V",&indexSize1);
    indexSize2 = 0;
    index2 = create_primaryidxfile("PrimaryIdx(2)",datafile2,"%F4%F19%F19%F19%V%V%V%V",&indexSize2);
    indexSize3 = 0;
    index3 = create_primaryidxfile("PrimaryIdx(3)",datafile3,"%F4%F19%F19%F19%V%V%V%V",&indexSize3);
    
    //4. Lendo a operacao que o usuario deseja realizar e iniciando-a...
    while(op != EXIT){
        printSelectOp();
        op = readOperation();
        switch(op){
            case INSERT:
                insertInAll(datafile1, datafile2, datafile3, &index1, &index2, &index3, &indexSize1, &indexSize2, &indexSize3);
            break;
            case REMOVE:
                removeFromAll(datafile1, datafile2, datafile3, &index1, &index2, &index3, &indexSize1, &indexSize2, &indexSize3);
            break;
            case INDEX_STAT:
                indexStats(index1,index2,index3,indexSize1,indexSize2,indexSize3);
            break;
            case DATA_STAT:
                fileStats(datafile1, datafile2, datafile3);
            break;
            case EXIT:
                printBye();
            break;
            default:
                printInvalidOp();
            break;
        }
    }
    
    //5. Passando os indices da RAM para o arquivo de indices no final do trabalho
    indexfile1 = fopen_("PrimaryIdx(1)","rwb+");
    indexfile2 = fopen_("PrimaryIdx(2)","rwb+");
    indexfile3 = fopen_("PrimaryIdx(3)","rwb+");
    
    writeprimaryidxfile(indexfile1, index1, indexSize1);
    writeprimaryidxfile(indexfile2, index2, indexSize2);
    writeprimaryidxfile(indexfile3, index3, indexSize3);
    
    
    //6. Encerrando o programa e liberando a memoria usada...
    fclose(sourcefile);
    fclose(datafile1);fclose(datafile2);fclose(datafile3);
    fclose(indexfile1);fclose(indexfile2);fclose(indexfile3);
    free(index1);free(index2);free(index3);
    return 0;
}
