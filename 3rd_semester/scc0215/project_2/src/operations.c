#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "regexCustom.h"
#include "file.h"
#include "operations.h"

// Busca binaria, retornando byte offset do registro conforme indicado no indice
int binarySearch(t_index *index, int start, int end, int key, int *indexPos) {
	if (start > end) return -1;
	int middle = (start + end) / 2;
	if (key == index[middle].key){
	    *indexPos = middle;
	    return index[middle].offset;  
	} 
	if(key < index[middle].key){ 
	    return binarySearch(index, start, middle-1, key, indexPos);
	} else {
		return binarySearch(index, middle+1, end, key, indexPos);
	}
}

// REMOCAO LOGICA

// Para first-fit
void rearangeFF(FILE *datafile, int byteoffset, int top){
    fseek(datafile, 0, SEEK_SET);
    fwrite(&byteoffset, sizeof(int), 1, datafile);
}

// Para best-fit
int rearangeBF(FILE *datafile, int byteoffset, int size, int initTop){
    int currSize, currOffset, prevOffset;
    char c;
    
    if(initTop == -1){ // Primeira inserçao na lista
        fseek(datafile, 0, SEEK_SET);
        fwrite(&byteoffset, sizeof(int), 1, datafile);
        return initTop;
    }
    
    currOffset = initTop;
    prevOffset = initTop;
    
    while(currOffset != -1){
        fseek(datafile, currOffset, SEEK_SET);
        fread(&c, sizeof(char), 1, datafile); // Pega o *
        fread(&currSize, sizeof(int), 1, datafile);
        
        if(currSize > size){ // Ordem crescente
            if(currOffset == initTop){ // Inserindo no topo
                fseek(datafile, 0, SEEK_SET);
                fwrite(&byteoffset, sizeof(int), 1, datafile);
                return currOffset;
            }
            break;
        }
        prevOffset = currOffset;
        fread(&currOffset, sizeof(int), 1, datafile); // Pega endereco do proximo espaco vazio
    }
    // Inserindo no meio ou no final
    fseek(datafile, prevOffset + sizeof(char) + sizeof(int), SEEK_SET);
    fwrite(&byteoffset, sizeof(int), 1, datafile);
    return currOffset;
}

// Para worst-fit
int rearangeWF(FILE *datafile, int byteoffset, int size, int initTop){
    int currSize, currOffset, prevOffset;
    char c;
    
    if(initTop == -1){ // Primeira inserçao na lista
        fseek(datafile, 0, SEEK_SET);
        fwrite(&byteoffset, sizeof(int), 1, datafile);
        return initTop;
    }
    currOffset = initTop;
    prevOffset = initTop;
    
    while(currOffset != -1){
        fseek(datafile, currOffset, SEEK_SET);
        fread(&c, sizeof(char), 1, datafile); // Pega o *
        fread(&currSize, sizeof(int), 1, datafile);
        
        if(currSize <= size){ // Ordem decrescente
            if(currOffset == initTop){ // Inserindo no topo
                fseek(datafile, 0, SEEK_SET);
                fwrite(&byteoffset, sizeof(int), 1, datafile);
                return currOffset;
            }
            break;
        }

        prevOffset = currOffset;
        fread(&currOffset, sizeof(int), 1, datafile); // Pega endereco do proximo espaco vazio
    }
    
    // Inserindo no meio ou no final
    fseek(datafile, prevOffset + sizeof(char) + sizeof(int), SEEK_SET);
    fwrite(&byteoffset, sizeof(int), 1, datafile);
    return currOffset;
}

void dataRemove(int byteoffset, FILE *datafile, int mode){
    int size = F_SIZE; // Tem pelo menos o tamanho dos campos fixos
    char c;
    int top, next = -1;
    
    // Pegando topo da lista invertida
    fseek(datafile, 0, SEEK_SET);
    fread(&top, sizeof(int), 1, datafile);
    
    // Descobrindo quantos bytes podem ser reaproveitados
    fseek(datafile, byteoffset + F_SIZE, SEEK_SET);
    do{
        c = fgetc(datafile);
        size++;
    }while (c != '#' && c != '*');
    
    // Ajustando lista invertida
    if(mode == 1){
        rearangeFF(datafile, byteoffset, top);
        next = top;
    }
    if(mode == 2){
        next = rearangeBF(datafile, byteoffset, size, top);
    }
    if(mode == 3){
        next = rearangeWF(datafile, byteoffset, size, top);
    }
        
    //Retorna ao inicio do registro
    fseek(datafile, byteoffset, SEEK_SET);
    // Marcando como removido
    c = '*';
    fwrite(&c, sizeof(char), 1, datafile);
    // Marcando espaço disponivel
    fwrite(&size, sizeof(int), 1, datafile);
    // Marcando proximo na lista invertida
    fwrite(&next, sizeof(int), 1, datafile);
}

// REMOCAO FISICA
void indexRemove(int pos, int *indexSize, t_index **index){
    int i;
    for(i = pos; i < ((*indexSize) - 1); i++){
        (*index)[i] = (*index)[i+1];
    }
    (*indexSize)--;
    (*index) = (t_index *) realloc(*index, sizeof(t_index)*(*indexSize));
}

//Remove registro de um par arquivo de dados - indice  
void removeFromFile(int ticket, FILE *datafile, t_index **index, int *indexSize, int mode){
    int byteoffset, indexPos;
    
    // (i) buscar o registro desejado usando-se o índice primário correspondente; 
    byteoffset = binarySearch(*index, 0, *indexSize, ticket, &indexPos);
    if(byteoffset == -1){
         printf("Registro nao encontrado. Remocao falhou.\n");
         return;
    }
    
    // (ii) realizar a remoção lógica do registro desejado no arquivo de dados; 
    dataRemove(byteoffset, datafile, mode);
    // (iii) realizar a remoção física da entrada correspondente no arquivo de índice; e 
    indexRemove(indexPos, indexSize, index);
    
    printf("|Registro de chave %d removido com sucesso do arquivo %d.\n",ticket,mode);
    return;
}

// Remove um determinado registro em cada par arquivo de dados - indice
void removeFromAll(FILE *datafile1, FILE *datafile2, FILE *datafile3, 
        t_index **index1, t_index **index2, t_index **index3, 
        int *indexSize1, int *indexSize2, int *indexSize3){
    char *string;
    int ticket;
    // Primeiramente, o usuário deve indicar um valor para o campo ticket 
    printf("|Digite o ticket do dominio que deseja remover: ");
    string = readLine(stdin, 10);
    if(sisdigit(string) == FALSE){
        printf("Registro invalido.\n\n");
        free(string);
        return;
    }
    ticket = atoi(string);
    removeFromFile(ticket, datafile1, index1, indexSize1, 1);
    removeFromFile(ticket, datafile2, index2, indexSize2, 2);
    removeFromFile(ticket, datafile3, index3, indexSize3, 3);
    printf("\n");
    free(string);
    return;
}

t_insert *readRegister(){
    t_insert *reg = (t_insert *) malloc(sizeof(t_insert));
    reg->fixedFields = (char **) malloc(3 * sizeof(char *)); 
    reg->variableFields = (char **) malloc(4 * sizeof(char *));
    char *string = NULL;
    int i;
    
    // Usuário indicará os dados que deverão ser armazenados
    printf("|Digite os campos a serem inseridos no arquivo de dados: \n");
    
    printf("|  Dominio: ");
    reg->variableFields[0] = readLine(stdin, '\n');
    printf("|  Documento: ");
    reg->fixedFields[0] = readLine(stdin, '\n');
    printf("|  Nome: ");
    reg->variableFields[1] = readLine(stdin, '\n');
    printf("|  UF: ");
    reg->variableFields[2] = readLine(stdin, '\n');
    printf("|  Cidade: ");
    reg->variableFields[3] = readLine(stdin, '\n');
    printf("|  DataHoraCadastro: ");
    reg->fixedFields[1] = readLine(stdin, '\n');
    printf("|  DataHoraAtualiza: ");
    reg->fixedFields[2] = readLine(stdin, '\n');
    printf("|  Ticket: ");
    string = readLine(stdin, '\n');
    reg->ticket = atoi(string);
    free_(string);
    
    for(i = 0; i < 3; i++){
        reg->fixedFields[i] = (char *) realloc(reg->fixedFields[i], 19 * sizeof(char));
        reg->fixedFields[i][18] = '\0';
    }
    
    return reg;
}

void insertRegister(FILE *datafile, t_insert *reg, int r_size, int size, int byteoffset, int top, int mode){
    int i, len, next;
    char delim = '#';
    
    fseek(datafile, byteoffset, SEEK_SET);
    fwrite(&(reg->ticket), sizeof(int), 1, datafile);
    
    for(i = 0; i < 3; i++){
       fwrite(reg->fixedFields[i], sizeof(char), 19, datafile);
    }
        
    for(i = 0; i < 4; i++){
        len = strlen(reg->variableFields[i]);
        fwrite(&len, sizeof(int), 1, datafile);
        fwrite(reg->variableFields[i], sizeof(char), len, datafile);
    }
    
    fwrite(&delim, sizeof(char), 1, datafile);
    len = size - r_size;
  
    if(len > 2*sizeof(int) + 2*sizeof(char)) {
        byteoffset = ftell(datafile);
        if(mode == 1){
            rearangeFF(datafile, byteoffset, top);
            next = top;
        }
        if(mode == 2){
            next = rearangeBF(datafile, byteoffset, len, top);
        }
        if(mode == 3){
            next = rearangeWF(datafile, byteoffset, len, top);
        }
        fseek(datafile, byteoffset, SEEK_SET);
        delim = '*';
        //Retorna ao inicio do registro
        fwrite(&delim, sizeof(char), 1, datafile);
        fwrite(&len, sizeof(int), 1, datafile);
        fwrite(&next, sizeof(int), 1, datafile);
    } else {
        delim = '$';
        for(i = 0; i < len; i++){
            fwrite(&delim, sizeof(char), 1, datafile);
        }
    }
    printf("|Novo registro de ticket %d inserido no arquivo %d\n", reg->ticket, mode);
}

int reglen(t_insert *reg){
    int i, size;
    
    size = 3 * 19 * sizeof(char) + sizeof(int);
    
    for(i = 0; i < 4; i++)
        size += strlen(reg->variableFields[i]) + 1 + sizeof(int);
    
    return size;
}

void freeRegister(t_insert *reg){
    int i;
    
    for(i = 0; i < 3; i++){
        free(reg->fixedFields[i]); 
        free(reg->variableFields[i]);   
    }
    
    free(reg->variableFields[3]);  
    free(reg->fixedFields);
    free(reg->variableFields);
    free(reg);
}

void insertInFile(FILE *datafile, t_index **index, int *indexSize, t_insert *reg, int mode){
    int size, r_size = reglen(reg);
    int cur, indexPos, i, byteoffset, top, prev, next;
    char r;
    
    byteoffset = binarySearch(*index, 0, *indexSize, reg->ticket, &indexPos);
    
    if(byteoffset != -1){
        printf("|Inserção falhou: chave primaria inválida\n");
        return;
    }
    
    fseek(datafile, 0, SEEK_SET);
    fread(&(cur),sizeof(int),1,datafile);
    prev = 0;
    top = cur;
    
    // Ver se tem registros removidos
    // Se sim, fazer FF, BF ou WF
    while(cur != -1){
        fseek(datafile, cur, SEEK_SET);
        fread(&r,sizeof(char),1,datafile);
        fread(&size,sizeof(int),1,datafile);
        fread(&next,sizeof(int),1,datafile);
        
        if(size >= r_size) {
            // Insere no local apropriado no arquivo de dados
            //e atualiza a lista
            fseek(datafile, prev, SEEK_SET);
            fwrite(&next, sizeof(int), 1, datafile);
            if(prev == 0) top = next;
            insertRegister(datafile, reg, r_size, size, cur, top, mode);
            
            break;
        }
        prev = cur + sizeof(char) + sizeof(int);
        cur = next;
    }
    
    // Se não ou se não houver espaço reaproveitável, insere no final do arquivo de dados
    if(cur == -1) {
        fseek(datafile, 0, SEEK_END);
        cur = ftell(datafile);
        insertRegister(datafile, reg, r_size, r_size, cur, top, mode);
    }
   
    // Insere no índice primario
    (*indexSize)++;
    *index = (t_index *) realloc(*index, (*indexSize) * sizeof(t_index));
    
    // e reordena-o
    for(i = 0; i < *indexSize; i++){
        if((*index)[i].key > reg->ticket){
            indexPos = i;
            break;
        }
    }
    
    for(i = *indexSize - 1; i > indexPos; i--){
        (*index)[i] = (*index)[i - 1];
    }
    
    (*index)[indexPos - 1].key = reg->ticket;
    (*index)[indexPos - 1].offset = cur;
}

// Insere um determinado registro em cada par arquivos de dados - indice
void insertInAll(FILE *datafile1, FILE *datafile2, FILE *datafile3, 
        t_index **index1, t_index **index2, t_index **index3, 
        int *indexSize1, int *indexSize2, int *indexSize3){
            
    t_insert *reg = readRegister();
    
    insertInFile(datafile1, index1, indexSize1, reg, 1);
    insertInFile(datafile2, index2, indexSize2, reg, 2);
    insertInFile(datafile3, index3, indexSize3, reg, 3);
    
    freeRegister(reg);
}

// Estatísticas sobre os arquivos de índice: quantidade de entradas que ele possui.
// Exibição dos registros dos três índices simultaneamente, um por vez.
void indexStats(t_index *index1, t_index*index2, t_index *index3, int indexSize1, int indexSize2, int indexSize3){
    int count = 0;
    char *string = NULL;
    
    printf("Tamanho dos indices:\n");
    printf("\tFirst-fit: %d\n", indexSize1);
    printf("\tBest-fit: %d\n", indexSize2);
    printf("\tWorst-fit: %d\n\n", indexSize3);
    
    printf("*Registros de indice sao mostrados no formato [ticket] - [byte offset]\n");
    do{
        printf("Visualizar registro %d? [S/N]\n", count);
        if(string != NULL) free(string);
        string = readLine(stdin, 10);
        if(string){
            if(match(string,"^\\s*[Ss]\\s*$")){
                printf("\tFirst-fit: %d - %ld\n", index1[count].key, index1[count].offset);
                printf("\tBest-fit: %d - %ld\n", index2[count].key, index2[count].offset);
                printf("\tWorst-fit: %d - %ld\n", index3[count].key, index3[count].offset);
                count++;
            }
        }
    } while (!(match(string,"^\\s*[Nn]\\s*$")));
    free(string);
}

// Retorna informações sobre registros removidos de um arquivo
t_removed *getRemoved(FILE *datafile, int *qtd){
    int top = -1;
    int aux;
    char c;
    t_removed *rmd = NULL;
    *qtd = 0;
    
    fseek(datafile, 0, SEEK_SET);
    fread(&top, sizeof(int), 1, datafile);
    
    while(top != -1){
        rmd = (t_removed *) realloc(rmd, sizeof(t_removed) * ((*qtd) + 1));
        fseek(datafile, top, SEEK_SET);
        fread(&c, sizeof(char), 1, datafile);
        if(c != '*'){
            break;
        }
        fread(&aux, sizeof(int), 1, datafile);
        rmd[*qtd].size = aux;
        rmd[*qtd].offset = top;
        (*qtd)++;
        fread(&aux, sizeof(int), 1, datafile);
        top = aux;
    }
    
    return rmd;
}

// Estatísticas sobre as listas de registros removidos: quantidade de registros removidos.
// Lista de registros removidos de cada arquivo de dados: byte offset e o tamanho do registro removido, 
// bem como o byte offset do próximo registro.
void fileStats(FILE *datafile1, FILE *datafile2, FILE *datafile3){
    t_removed *rmd1, *rmd2, *rmd3;
    int qtd1, qtd2, qtd3, i;
    char *string = NULL;

    rmd1 = getRemoved(datafile1, &qtd1);
    rmd2 = getRemoved(datafile2, &qtd2);
    rmd3 = getRemoved(datafile3, &qtd3);
    
    printf("Quantidade de registros removidos em:\n");
    printf("\tFirst-fit: %d\n", qtd1);
    printf("\tBest-fit: %d\n", qtd2);
    printf("\tWorst-fit: %d\n\n", qtd3);
    
    if(qtd1 == 0 && qtd2 == 0 && qtd3 == 0){
        printf("Não ha removidos registros para visualizar.\n");
    }else{
        printf("*Registros removidos sao mostrados no formato [byte offset]/[espaco livre]\n");
        do {    
            printf("Visualizar registros removidos? [S/N]\n");
            free_(string);
            string = readLine(stdin, 10);
            if(string){
                if(match(string,"^\\s*[Ss]\\s*$")){
                    printf("First-fit [offset/espaco livre]:\n\t");
                    for(i = 0; i < qtd1; i++){
                        printf("[%d/%d] -> ", rmd1[i].offset, rmd1[i].size);
                    }printf("-1.");
                    
                    printf("\nBest-fit [offset/espaco livre]:\n\t");
                    for(i = 0; i < qtd2; i++){
                        printf("[%d/%d] -> ", rmd2[i].offset, rmd2[i].size);
                    }printf("-1.");
                    
                    printf("\nWorst-fit [offset/espaco livre]:\n\t");
                    for(i = 0; i < qtd3; i++){
                        printf("[%d/%d] -> ", rmd3[i].offset, rmd3[i].size);
                    }printf("-1.");
                    printf("\n\n");
                    break;
                }
            }
        } while (!(match(string,"^\\s*[Nn]\\s*$")));
    }
    
    free_(string);
    free_(rmd1);
    free_(rmd2);
    free_(rmd3);
}