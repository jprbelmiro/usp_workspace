#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "file.h"
#include "regexCustom.h"

FILE *fopen_(char *filename, char *mode){
    FILE *fp = fopen(filename,mode);
    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo %s\n",filename);
        exit(1);
    }
    if(ftell(fp) != 0)
        fseek(fp,0,SEEK_SET);
    return fp;
}

static int *scanorder(char *order, int *nfields){
    int i, fieldlen = 0, *fieldstype = NULL;
    char delim = '%', *string = NULL;
    
    (*nfields) = 0;
    for(i = 0 ; i < strlen(order) ; i++){
        if(order[i] == '%'){
            i++;
            fieldstype = (int *)realloc(fieldstype,sizeof(int)*((*nfields)+1));
            
            if(order[i] == 'V')
                fieldstype[(*nfields)] = -1;

            else if(order[i] == 'F'){
                i++;
                string = readString(order,i,strlen(order),delim);
                fieldlen = atoi(string);
                fieldstype[(*nfields)] = fieldlen;
                if(string) 
                    free(string);
            }
            
            (*nfields)++;
        }
    }
    return fieldstype;
}

static void hybridsort(int *insertorder,int nfields, int *fieldstype){
    //0. Variaveis
    int i = 0, j = 0;
    
    //1. Ordenando os tipos de campo
    //mergesort(insertorder,0,nfields);
    qsort(insertorder, nfields, sizeof(int), fieldCompare);
    
    //PRIMEIRO o campo ticket (chave primaria)
    for(j = 0; j < nfields ; j++){
        if(fieldstype[j] == 4){
            insertorder[i++] = j;
        }
    }
    //SEGUNDO os campos de tamanho fixo
    for(j = 0 ; j < nfields ; j++){
        if(fieldstype[j] > 4)
            insertorder[i++] = j;
    }
    
    //DEPOIS os campos variaveis
    for(j = 0 ; j < nfields ; j++){
        if(fieldstype[j] < 0)
            insertorder[i++] = j;
    }
    
    return;
}

void create_datafile(char *filename, FILE *sourcefile, char *format_order, boolean hflag, char delim){
    //0. Variaveis...
    char c, *header = NULL, *string = NULL, **tokens = NULL;
    int i, num, nfields = 0, *fieldstype = NULL, *insertorder = NULL;
    FILE *dfp = fopen_(filename,"wb+");
    
    //1. Verificando se o arquivo provedouro possui cabecalho...
    fseek(sourcefile,0,SEEK_SET);
    if(hflag == TRUE) 
        header = readLine(sourcefile,10);
    
    //2. Criando um vec que caracteriza o tipo dos campos salvos no registro e a
    //sua ordem de insercao no arquivo de maneira hibrida...
    fieldstype = scanorder(format_order,&nfields);
    insertorder = scanorder(format_order,&nfields);
    hybridsort(insertorder,nfields,fieldstype);

    //3. Iniciando a construcao do arquivo de dados...
    //a. colocando no arquivo o numero que indica (no cabeçalho) o ultimo reg.
    //removido...
    num = -1;
    fwrite(&(num),sizeof(int),1,dfp);
    
    while(!feof(sourcefile)){
        string = readLine(sourcefile,'\n');
        if(!match(string,"^\\s*$")){
            //b. tokenizando todos os campos
            tokens = tokenizeAll(string,delim,nfields);

            //c.escrevendo no arquivo...
            for(i = 0 ; i < nfields ; i++){
                if(match(tokens[insertorder[i]],"^\\s*null\\s*$")){
                    if(fieldstype[insertorder[i]] < 0){
                        num = 0;
                        fwrite(&num,sizeof(int),1,dfp);
                    }
                    else{
                        free_(tokens[insertorder[i]]);
                        tokens[insertorder[i]] = (char *)calloc(fieldstype[insertorder[i]],sizeof(char));
                        fwrite(tokens[insertorder[i]],sizeof(char),fieldstype[insertorder[i]],dfp);
                    }
                }
                else{
                    if(fieldstype[insertorder[i]] < 0){
                        num = strlen(tokens[insertorder[i]]);
                        fwrite(&num,sizeof(int),1,dfp);
                        fwrite(tokens[insertorder[i]],sizeof(char),strlen(tokens[insertorder[i]]),dfp);
                    }
                    else{
                        if(sisdigit(tokens[insertorder[i]])){
                            num = atoi(tokens[insertorder[i]]);
                            fwrite(&num,sizeof(int),1,dfp);
                        }
                        else
                            fwrite(tokens[insertorder[i]],fieldstype[insertorder[i]],1,dfp);
                    }
                }
            }
            c = '#';
            fwrite(&c,sizeof(char),1,dfp);
            freeMatrix((void **)tokens,nfields);
        }
        free(string);
    }

    //4. Encerrando a funcao...
    fseek(sourcefile,0,SEEK_SET);
    free(fieldstype);
    free(insertorder);
    free(header);
    fclose(dfp);
    return;
}

//Função que escreve todo o vetor de indices no 
//arquivo de indices, ambos passados como parametro
void writeprimaryidxfile(FILE *pifile, t_index *idx, int nregs){
    int i;
    for(i = 0 ; i < nregs ; i++){
        fwrite(&idx[i].key,sizeof(int), 1, pifile);
        fwrite(&idx[i].offset, sizeof(long int), 1, pifile);
    }//fprintf(pifile,"%d %ld",idx[i].key,idx[i].offset);
    return;
}

t_index *create_primaryidxfile(char *filename, FILE *sourcefile, char *format_order, int *idxSize){
    //0. Variaveis...
    char delim, *string = NULL;
    long int offset = 0, size = 0;
    int i, number, nregs = 0, headerIdx = -1, nfields = 0, *fieldstype = NULL;
    FILE *pifile = fopen_(filename,"wb+");
    t_index *idx = NULL;
    
    //1. Lendo o cabecalho do arquivo de dados...
    fread(&headerIdx, sizeof(int), 1, sourcefile);
    
    //2. Criando um vec que caracteriza o tipo dos campos salvos no registro e a
    //sua ordem...
    fieldstype = scanorder(format_order,&nfields);

    //3. Realizando a leitura do arquivo com base nas mascaras lidas e criando
    //o vetor de indices que sera usado para escrita
    while(!feof(sourcefile)){
        idx = (t_index *)realloc(idx,sizeof(t_index)*(nregs+1));
        offset = ftell(sourcefile);
        
        for(i = 0 ; i < nfields ; i++){
            if(fieldstype[i] < 0){
                fread(&size,sizeof(int),1,sourcefile);
                string = (char *)malloc(sizeof(char)*size);
                fread(string,sizeof(char),size,sourcefile);
                free_(string);
            }
            else{
                if(fieldstype[i] == sizeof(int)){
                    fread(&number,sizeof(int),1,sourcefile);
                    idx[nregs].key = number;
                    idx[nregs].offset = offset;
                }
                else{    
                    string = (char *)calloc(fieldstype[i],sizeof(char));
                    fread(string,fieldstype[i],1,sourcefile);
                    free_(string);
                }
            }
            
            if(feof(sourcefile)){
                nregs -= 1;
                idx = (t_index *)realloc(idx,sizeof(t_index)*(nregs+1));
                break;
            }
        }
        
        fread(&delim,sizeof(char),1,sourcefile);
        nregs++;
    }
    
    //4. Escrevendo o arquivo de indice primario a partir da estrutura criada...
    qsort(idx, nregs, sizeof(t_index), indexesCompare);
    writeprimaryidxfile(pifile,idx,nregs);
    *idxSize = nregs; 
    
    free(fieldstype);
    fclose(pifile);
    return idx;   
}
