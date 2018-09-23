#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "t1b_regex.h"
#include "t1b_basic.h"

enum{
    ERROR = -1,
    CREATE_TABLE,
    CREATE_INDEX,
    SELECT,
    INSERT,
    SORT,
    SHOW_ALL_TABLES,
    SHOW_ALL_INDEXES,
    STATISTICS
};

int index_table(TABLE *table, char *table_name, int ntables){
    int index;

    for( index = 0 ; index < ntables ; index++){
        if(strcmp(table_name,table[index].table_name)==0)
            return index;
    }

    return -1;
}

int elem_order(TABLE table, char *elem){
    int order;

        for( order = 0 ; order < table.nfields ; order++){

            if(strcmp(elem,table.field[order].name)==0)
                return order;
        }

    return -1;
}

int file_binary_search( FILE *idx_file, char *elem, int order, char *table_name, int index, TABLE *table, STAT *ninfo, int *check){
    int i = 0;
    char **all_strings = NULL;

    //1 - Lendo todas as linhas do arquivo de indice...
    while(!feof(idx_file)){
        all_strings = (char **)realloc(all_strings,sizeof(char *)*(i+1));
        all_strings[i] = readLine(idx_file,10);
        
        if(match(all_strings[i],"^\\s*$") && all_strings[i] != NULL)
            free(all_strings[i]);
        else
            i++;
    }

    //2 - Realizando uma busca binaria com base no "vetor" de todas as linhas...
    int nrow = i;
        binary_search_idx(all_strings,elem,0,nrow-1,table_name,table,index,ninfo,check);

    //3 - Liberando a memoria alocada...
    freeMatrix((void **)all_strings,nrow);

    return 0;
}

int file_sequential_search(FILE *tmp_file, char *elem, int order, int table_index, int nfields, TABLE *table,STAT *ninfo, int *check){
    int i = 0;
    char **aux = NULL;

    while(!feof(tmp_file)){
        //1 - "Tokanizando" um elemento de mesma "ordem" que o elemento procurado...       
        for(i = 0 ; i < order ; i++){
            aux = (char **)realloc(aux,sizeof(char *)*(i+1));
            aux[i] = tokenize_elem(tmp_file,',','\n');
        }
            aux = (char **)realloc(aux,sizeof(char *)*(i+1));
            aux[i] = tokenize_elem(tmp_file,',','\n');
            if(aux[i] == NULL){
                break;
            }
          
        //2 - Comparando o elemento "tokanizado" no passo anterior com o procurado...
        //2.0 - caso seja igual...
        if(strcmp(aux[i],elem)== 0){
            ninfo->recordsInLastSelectSequential += 1;
            i++;

                //2.1 - Recolhendo todos os argumentos...
                while(i < nfields){
                    aux = (char **)realloc(aux,sizeof(char *)*(i+1));
                    aux[i++] = tokenize_elem(tmp_file,',','\n');
                }
    
                //2.2 - Imprimindo na tela os argumentos recolhidos...
                for(i = 0 ; i < nfields ; i++){
                    if(i == nfields-1){
                        if(match(table[table_index].field[i].type,"[Cc][Hh][Aa][Rr]"))
                            printf("'%s'\n",aux[i]);
                        if(match(table[table_index].field[i].type,"[Ii][Nn][Tt]"))
                            printf("%d\n",atoi(aux[i]));
                        if(match(table[table_index].field[i].type,"[Ff][Ll][Oo][Aa][Tt]"))
                            printf("%f\n",atof(aux[i]));
                        if(match(table[table_index].field[i].type,"[Dd][Oo][Uu][Bb][Ll][Ee]"))
                            printf("%lf\n",atof(aux[i]));  
                    }
                    else{
                        if(match(table[table_index].field[i].type,"[Cc][Hh][Aa][Rr]"))
                            printf("'%s', ",aux[i]);
                        if(match(table[table_index].field[i].type,"[Ii][Nn][Tt]"))
                            printf("%d, ",atoi(aux[i]));
                        if(match(table[table_index].field[i].type,"[Ff][Ll][Oo][Aa][Tt]"))
                            printf("%f, ",atof(aux[i]));
                        if(match(table[table_index].field[i].type,"[Dd][Oo][Uu][Bb][Ll][Ee]"))
                            printf("%lf, ",atof(aux[i]));  
                    }
                }
    
                //2.3 - Liberando a matriz com os argumentos...
                freeMatrix((void **)aux,nfields);
                aux = NULL;
                i = 0;
                *check += 1;
        }
        
        //3 - caso nao seja igual e tambem nao seja o final do arquivo...
        else if(!feof(tmp_file)){
            i++;
            //3.1 - Sao lidos todos os argumentos da linha
            while(i < nfields){
               aux = (char **)realloc(aux,sizeof(char *)*(i+1));
               aux[i++] = tokenize_elem(tmp_file,',','\n');
            }
            //3.2 - e liberados logo em seguida...
            if(aux != NULL)
                freeMatrix((void **)aux,nfields);

            aux = NULL;
            i = 0;
        }
    }//O processo e repetido ate o fim do arquivo...
    
    if(aux != NULL)
        freeMatrix((void **)aux,i);
    
    return 0;
}

TABLE create_table(FILE *fp, STAT *ninfo){
    TABLE table;
    //1 - Recolhendo o nome da tabela do arquivo de entrada...
    table.table_name = tokenize(fp);

    table.nfields = 0;
    //2 - Lendo uma string de argumentos ate o final do comando...
    char **arg_str = tokenize_arg_FILE(fp,&table.nfields);
        if(table.nfields == 0){
            free(table.table_name);
            return table;
        }
     //3 - Atribuindo nome, tipo e tamanho para cada campo da tabela...      
    int i;
    table.field = (TABLE_FIELD *)malloc(sizeof(TABLE_FIELD)*table.nfields);
    for( i = 0 ; i < table.nfields ; i++){
        table.field[i].name = tokenize_arg_STR(arg_str[i],' ','\t',0);
        table.field[i].type = tokenize_arg_STR(arg_str[i],' ','\t',1);

        if(match(table.field[i].type,"[Ii][Nn][Tt]"))
            table.field[i].SIZE = 4;

        if(match(table.field[i].type,"[Ff][Ll][Oo][Aa][Tt]"))
            table.field[i].SIZE = 4;

        if(match(table.field[i].type,"[Dd][Oo][Uu][Bb][Ll][Ee]"))
            table.field[i].SIZE = 8;

        if(match(table.field[i].type,"[Cc][Hh][Aa][Rr]")){
            if(match(table.field[i].type,"[Cc][Hh][Aa][Rr]\\[[[:digit:]]+\\]")){
                char *digit = NULL;
                digit = vec_digit(table.field[i].type);
                    table.field[i].SIZE = atoi(digit);
                        free(digit);

                free(table.field[i].type);
                    table.field[i].type = (char *)malloc(sizeof(char)*5);
                    table.field[i].type[0] = 'c';
                    table.field[i].type[1] = 'h';
                    table.field[i].type[2] = 'a';
                    table.field[i].type[3] = 'r';
                    table.field[i].type[4] = '\0';
            }
            else
                table.field[i].SIZE = 1;
        }
    }
    //4 - Liberando a memoria auxiliar utilizada para criacao da tabela e conta_
    //bilizando mais uma tabela criada...
    freeMatrix((void **)arg_str,table.nfields);
    ninfo->ntables += 1;
    
    return table;
};

void create_index(FILE *fp, TABLE *table, int ntables, STAT *ninfo){
    //1 - Recolhendo o nome da tabela e o parametro utilizado para a criacao do
    //arquivo de indice...
    char *table_name = tokenize(fp);
    
    int nargs = 0;
    char **param = tokenize_arg_FILE(fp,&nargs);

        if(nargs != 1){
            free(table_name);
            if(param  != NULL)
                freeMatrix((void **)param,nargs);
            return;
        }
        
    //2 - Copiando (caso exista) o arquivo temporario para o arquivo permanente...
    FILE *temp_file = open2read_tmp(table_name);
    FILE *dat_file = open2write_dat(table_name);
    if(temp_file != NULL && dat_file != NULL){
        copy_file(temp_file,dat_file);
            fclose(temp_file);
            fclose(dat_file);
    }
    else{
        if(temp_file != NULL)
            fclose(temp_file);
        if(dat_file != NULL)
            fclose(dat_file);
    }
    
    //3 - Removendo o arquivo temporario da memoria...
    char *temp_file_name = file_name_temp(table_name);
        remove(temp_file_name);
            free(temp_file_name);

    //4 - Abrindo o arquivo permanente para consulta e escrita no arquivo de in_
    //dice...
    dat_file = open2read_dat(table_name);
    FILE *idx_file = open2write_idx(table_name,param[0]);
    //-caso exista...
    if(dat_file != NULL && idx_file != NULL){
        int table_idx = index_table(table,table_name,ntables);
        int order = elem_order(table[table_idx],param[0]);
        int nelem = 0;
        
        //a1 - Criando um "vetor" ordenado de acordo com o parametro escolhido
        //pelo usuario...
        char **sorted_vec = create_sorted_vec(dat_file,param[0],order,&nelem,table[table_idx].field[order].type);
        fseek(dat_file,0,SEEK_SET);
        
        //b1 - Escrevendo as informacoes no arquivo de indice
        write_idx(idx_file,dat_file,sorted_vec,nelem,order);
        
        //c1 - Guardando as informacoes necessarias para conhecer e acessar os
        //arquivos de indices criados...
        ninfo->nindexes += 1;
        ninfo->idx_info = (INDEX_INFO *)realloc(ninfo->idx_info,sizeof(INDEX_INFO)*ninfo->nindexes);
        ninfo->idx_info[ninfo->nindexes-1].table_name = (char *)malloc(sizeof(char *)*(strlen(table_name)));
            strcpy(ninfo->idx_info[ninfo->nindexes-1].table_name,table_name);
        ninfo->idx_info[ninfo->nindexes-1].field_name = (char *)malloc(sizeof(char *)*(strlen(param[0])));
            strcpy(ninfo->idx_info[ninfo->nindexes-1].field_name,param[0]);
            freeMatrix((void **)sorted_vec,nelem);
    }
    else{
        //- caso nao exista
        //a2 - Liberando a memoria utilizada...
        free(table_name);
        freeMatrix((void **)param,nargs);
        
        //b2 - Fechando os arquivos usados...
        if(dat_file != NULL)
            fclose(dat_file);
        if(idx_file != NULL)
            fclose(idx_file); 
            
        return;

    }

    //5 - Fechando os arquivos abertos e liberando a memoria utilizada...
    if(dat_file != NULL)
           fclose(dat_file);
    if(idx_file != NULL)
        fclose(idx_file); 

    free(table_name);
    freeMatrix((void **)param,nargs);

    return;
};

void insert_into(FILE *fp, TABLE *table){
    //1 - Recolhendo o nome da tabela e os argumentos da funcao...
    char *table_name = tokenize(fp);

    int nargs1 = 0;
    char **arg_str = tokenize_arg_FILE(fp,&nargs1);
    
    //2 - Recolhendo os valores a serem inseridos pela funcao...
    int nargs2 = 0;    
    char **value_str = (char **)malloc(sizeof(char *)*1);
    value_str[0] = tokenize(fp);
        freeMatrix((void **)value_str,1);
    value_str = tokenize_arg_FILE(fp,&nargs2);

    //3 - Abrindo o arquivo temporario para armazenar as informacoes a serem
    //inseridas...
    FILE *temp_file = open2write_tmp(table_name);
    int i;
    for(i = 0 ; i < nargs2   ; i++){
        if(i != nargs2-1)
            fprintf(temp_file,"%s, ",value_str[i]);
        else
            fprintf(temp_file,"%s\n",value_str[i]);
    }

    //4 - Liberando a memoria utilizada para criar o arquivo temporario com as
    //insercoes e fechando os arquivos abertos...
    fclose(temp_file);
    free(table_name);
    freeMatrix((void **)arg_str,nargs1);
    freeMatrix((void **)value_str,nargs2);

    return;
};

void select_(FILE *fp, TABLE *table, int ntables, STAT *ninfo){
    //1 - Recolhendo o nome da tabela e os argumentos da funcao assim como
    //o elemento procurado...
    char *table_name = tokenize(fp);
    char *arg = tokenize(fp);

    char *elem = tokenize_elem(fp,';',';');

    //2 - Descobrindo qual o indice da tabela a qual deseja-se acessar para 
    //busca...
    int table_index = index_table(table,table_name,ntables);
        if(table_index == -1){
            free(elem);
            free(arg);
            free(table_name);
            return;
        }

    //3 - Descobrindo a "ordem" do argumento que se procura...
    int order = elem_order(table[table_index],arg);
        if(order == -1){
            free(elem);
            free(arg);
            free(table_name);
            return;
        }


    //4 - Abrindo os arquivos nos quais serao realizados as buscas...
    FILE *file_idx = open2read_idx(table_name,arg);
    FILE *file_tmp = open2read_tmp(table_name);

    ninfo->recordsInLastSelectBinary = 0;
    ninfo->recordsInLastSelectSequential = 0;
    int check = 0;
    
    //a - Realizando uma busca binaria no arquivo de indice (ordenado)...
    if(file_idx != NULL)
        file_binary_search(file_idx,elem,order,table_name,table_index,table,ninfo,&check);

    //b - Realizando uma busca sequencial no arquivo temporario...
    if(file_tmp != NULL)
        file_sequential_search(file_tmp,elem,order,table_index,table[table_index].nfields,table,ninfo,&check);
    
    //c - Caso nenhum elemento seja encontrado, e impresso "null" na tela...
    if(check == 0){
        printf("null\n");
    }

    //5 - Liberando a memoria auxiliar para a realizacao da funcao e fechando
    //os arquivos utilizados...
    if(elem != NULL)
        free(elem);
    if(arg != NULL)
        free(arg);
    if(table_name != NULL)
        free(table_name);

    if(file_tmp != NULL)
        fclose(file_tmp);
    if(file_idx != NULL)
        fclose(file_idx);

    return;
};

void sort_(FILE *fp, TABLE *table, STAT *ninfo){
    //1 - Recolhendo o nome da tabela e o parametro utilizado para regerar o
    //arquivo de indice...
    char *table_name = tokenize(fp);
    
    int nargs = 0;
    char **param = tokenize_arg_FILE(fp,&nargs);
        if(nargs != 1){
            free(table_name);
            if(param  != NULL)
                freeMatrix((void **)param,nargs);
            return;
        }

    //2 - Removendo o arquivo de indice da memoria, caso ele exista...
    FILE *idx_file = open2read_idx(table_name,param[0]);
    if(idx_file != NULL){
        fclose(idx_file);
        char *idx_file_name = file_name_idx(table_name,param[0]);
            remove(idx_file_name);
                free(idx_file_name);

    //3 - Copiando (caso exista) o arquivo temporario para o arquivo permanente...
    FILE *temp_file = open2read_tmp(table_name);
    FILE *dat_file = open2write_dat(table_name);
        if(temp_file != NULL){
            copy_file(temp_file,dat_file);
            fclose(temp_file);
            fclose(dat_file);
        }
        else{
            if(dat_file != NULL);
            fclose(dat_file);
        }

        //- Removendo o arquivo temporario da memoria...
        char *temp_file_name = file_name_temp(table_name);
            remove(temp_file_name);
                free(temp_file_name);

            //4 - Abrindo o arquivo permanente para consulta e escrita no arquivo de in_
            //dice...
            FILE *idx_file = open2write_idx(table_name,param[0]);
            dat_file = open2read_dat(table_name);

            int table_idx = index_table(table,table_name,ninfo->ntables);
            int order = elem_order(table[table_idx],param[0]);
                int nelem = 0;
            
            //a - Criando um "vetor" ordenado de acordo com o parametro escolhido
            //pelo usuario...
            char **sorted_vec = create_sorted_vec(dat_file,param[0],order,&nelem,table[table_idx].field[order].type);

            //b - Escrevendo as informacoes no arquivo de indice            
                fseek(dat_file,0,SEEK_SET);
            write_idx(idx_file,dat_file,sorted_vec,nelem,order);

             //5 - Fechando os arquivos abertos e liberando a memoria utilizada...
                freeMatrix((void **)sorted_vec,nelem);
                if(dat_file != NULL)
                    fclose(dat_file);
                if(idx_file != NULL)
                    fclose(idx_file);
    }
    
    //6 - Liberando a memoria pioneira alocada...
    free(table_name);
    freeMatrix((void **)param,nargs);
    
    return;
};

void showalltables( TABLE *table, int ntables){
    int i, j;
    for( i = 0 ; i < ntables ; i++){
        printf("\nTablename: %s\n",table[i].table_name);
        for (j = 0; j < table[i].nfields; j++){
            printf("\tField: %s Type: %s Size %d\n",
                   table[i].field[j].name,
                   table[i].field[j].type,
                   table[i].field[j].SIZE);
        }
        printf("\n");
    }

    return;
};

void showallindexes( STAT *ninfo ){
    int i;
    for(i = 0 ; i < ninfo->nindexes ; i++){
        printf("\nIndex information\n");

        printf("\tTablename: %s\n", ninfo->idx_info[i].table_name);

        printf("\tFieldname: %s\n\n", ninfo->idx_info[i].field_name);
    }

    return;
};

void statitics( STAT *ninfo){

    printf("#Tables: %d\n", ninfo->ntables);
    printf("#Indexes: %d\n", ninfo->nindexes);
    printf("#Inserts: %d\n", ninfo->ninserts);
    printf("#Selects: %d\n", ninfo->nselects);
    printf("#Sorts: %d\n", ninfo->nsorts);

    printf("#ShowAllTables: %d\n", ninfo->nshowalltables);

    printf("#ShowAllIndexes: %d\n", ninfo->nshowallindexes);

    printf("#Records in last select (binary search): %d\n",
    ninfo->recordsInLastSelectBinary);


    printf("#Records in last select (sequential search): %d\n",
    ninfo->recordsInLastSelectSequential);

    return;
};

int select_operation(FILE *fp){
    char *token = tokenize(fp);
    
    if(token == NULL){
        return ERROR;
    }

    if(match(token,"[Cc][Rr][Ee][Aa][Tt][Ee]")){
        free(token);
        token = tokenize(fp);
        if(match(token,"[Tt][Aa][Bb][Ll][Ee]")){
            free(token);
            return CREATE_TABLE;
        }
        else if(match(token,"[Ii][Nn][Dd][Ee][Xx]")){
            free(token);
            return CREATE_INDEX;
        }
    }

    if(match(token,"[Ss][Ee][Ll][Ee][Cc][Tt]")){
        free(token);
        return SELECT;
    }

    if(match(token,"[Ii][Nn][Ss][Ee][Rr][Tt]")){
        free(token);
        token = tokenize(fp);
        if(match(token,"[Ii][Nn][Tt][Oo]")){
            free(token);
            return INSERT;
        }
    }

    if(match(token,"[Ss][Oo][Rr][Tt]")){
        free(token);
        return SORT;
    }

    if(match(token,"[Ss][Hh][Oo][Ww][Aa][Ll][Ll][Tt][Aa][Bb][Ll][Ee]")){
        free(token);
        return SHOW_ALL_TABLES;
    }

    if(match(token,"[Ss][Hh][Oo][Ww][Aa][Ll][Ll][Ii][Nn][Dd][Ee][Xx][Ee][Ss]")){
        free(token);
        return SHOW_ALL_INDEXES;
    }

    if(match(token,"[Ss][Tt][Aa][Tt][Ii][Ss][Tt][Ii][Cc][Ss]")){
        free(token);
        return STATISTICS;
    }

        free(token);
        return ERROR;
};

void Database_problem( FILE *input_file ){
    TABLE *table = NULL;
    STAT *ninfo = NULL;
    ninfo = (STAT *)calloc(1,sizeof(STAT));

    while(!feof(input_file)){
        switch(select_operation(input_file)){
            case CREATE_TABLE:
                table = (TABLE *)realloc(table,sizeof(TABLE)*(ninfo->ntables+1));
                table[ninfo->ntables] = create_table(input_file,ninfo);
                break;

            case CREATE_INDEX:
                create_index(input_file,table,ninfo->ntables,ninfo);
                break;

            case SELECT:
                select_(input_file,table,ninfo->ntables,ninfo);
                ninfo->nselects++;
                break;

            case INSERT:
                insert_into(input_file,table);
                ninfo->ninserts++;
                break;

            case SORT:
                sort_(input_file,table,ninfo);
                ninfo->nsorts++;
                break;

            case SHOW_ALL_TABLES:
                showalltables(table,ninfo->ntables);
                ninfo->nshowalltables++;
                break;

            case SHOW_ALL_INDEXES:
                showallindexes(ninfo);
                ninfo->nshowallindexes++;
                break;

            case STATISTICS:
                statitics(ninfo);
                break;

            case ERROR:
                break;
        }
    }
    
    //Liberando a tabela...
    int i, j;
    for(i = 0 ; i < ninfo->ntables ; i++){
        for(j = 0 ; j < table[i].nfields ; j++){
            free(table[i].field[j].name);
            free(table[i].field[j].type);
        }
        free(table[i].table_name);
        free(table[i].field);
    }
    free(table);

    //Liberando as informacoes...
    for(i = 0 ; i < ninfo->nindexes ; i++){
        free(ninfo->idx_info[i].table_name);
        free(ninfo->idx_info[i].field_name);
    }
    free(ninfo->idx_info);
    free(ninfo);

    return;
};