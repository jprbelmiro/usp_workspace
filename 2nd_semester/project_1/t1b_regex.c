#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <regex.h>
#include "t1b_basic.h"

//Estrutura de dados que contem informacoes de cada campo de uma tabela...
typedef struct{
    char *name;
    char *type;
    int SIZE;
}TABLE_FIELD;

//Estrutura de dados que contem informacoes sobre uma tabela...
typedef struct {
    char *table_name;
    TABLE_FIELD *field;
    int nfields;
}TABLE;

//Estrutura de dados que contem informacoes sobre os arquivos de indice ja criados...
typedef struct{
    char *table_name;
    char *field_name;
}INDEX_INFO;

//Estrutura de dados que contem informacoes estastisticas sobre o SGBD...
typedef struct{
    int ntables;
    int nindexes;
    int ninserts;
    int nselects;
    int nsorts;
    int nshowalltables;
    int nshowallindexes;
    int recordsInLastSelectBinary;
    int recordsInLastSelectSequential;
    INDEX_INFO *idx_info;
}STAT;

int match(char *str, char *pattern){
    int status;
    regex_t re;

    if(regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0)
        return 0;

    status = regexec(&re, str, (size_t) 0, NULL, 0);
    regfree(&re);

    if(status != 0)
        return 0;

    return 1;
}

char *vec_digit(char *type_str){
    int i = 0, counter = 0;
    char *str = NULL;

    while(type_str[i] != '\0'){
        if(isdigit(type_str[i])){
            str = (char *)realloc(str,sizeof(char)*(counter+1));
            str[counter++] = type_str[i];
        }
        i++;
    }
            str = (char *)realloc(str,sizeof(char)*(counter+1));
            str[counter] = '\0';

    return str;
}

char *tokenize( FILE *fp ){
    int i = 0;
    char *token = NULL;

    while(!feof(fp)){
        char c = fgetc(fp);

        if( c != '\n' && c != '\t' && c != ' ' && c != ';' && c != EOF && c != ',' && c != '(' && c != ')' && c != 39 && c != 96){
            token = (char *)realloc(token,sizeof(char)*i+1);
            token[i++] = c;
        }

        if((c == '\n' || c == '\t' || c == ' ' || c == EOF || c == '(' || c == ')' || c == ';' || c == ',') && token != NULL){
            token = (char *)realloc(token,sizeof(char)*i+1);
            token[i] = '\0';

            return token;
        }
        else if( c == EOF  && token == NULL)
            return NULL;
    }
    
    if(token != NULL)
        free(token);
        
    return NULL;
}

char **tokenize_arg_FILE(FILE *fp, int *nargs){
    char **str = NULL;
    char c;
    int i = 0;

    str = (char **)realloc(str,sizeof(char *)*(*nargs+1));
    str[*nargs] = NULL;
    while( (c = fgetc(fp)) != ';'  && c != ')' ){
        if( c != 10 && c != ',' && c != ';' && c != '(' && c != ')' && c != 39 && c != 96 && c != EOF ){
            if((c == ' ' || c == '\t' ) && str[*nargs] != NULL){
                str[*nargs] = (char *)realloc(str[*nargs],sizeof(char)*(i+1));
                str[*nargs][i++] = c;
            }
            else if( c != ' ' && c != '\t' ){
                str[*nargs] = (char *)realloc(str[*nargs],sizeof(char)*(i+1));
                str[*nargs][i++] = c; 
            }
        }
        if( c == ',' ){
            while(str[*nargs][i-1] == ' ' || str[*nargs][i-1] == '\t') i--;
            str[*nargs] = (char *)realloc(str[*nargs],sizeof(char)*(i+1));
            str[*nargs][i] = '\0';
            *nargs += 1;
            i = 0;
            str = (char **)realloc(str,sizeof(char *)*(*nargs+1));
            str[*nargs] = NULL;
        }
    }
    while(str[*nargs][i-1] == ' ' || str[*nargs][i-1] == '\t') i--;
    str[*nargs] = (char *)realloc(str[*nargs],sizeof(char)*(i+1));
    str[*nargs][i] = '\0';
    
    *nargs += 1;

    return str;
};

char *tokenize_arg_STR(char *str, char delimin1, char delimin2, int position){
    char *token = NULL;
    int i = 0, counter = 0, current_position = 0;

    while(str[counter] != '\0'){
        if((str[counter] == delimin1 || str[counter] == delimin2 ) && token != NULL){
            if( current_position == position ){
                token = (char *)realloc(token,sizeof(char)*(i+1));
                token[i] = '\0';
                return token;
            }
            else{
                free(token);
                token = NULL;
                i = 0;
                current_position += 1;
            }
        }
        else{
            if(str[counter] != ' ' && str[counter] != '\t'){
                token = (char *)realloc(token,sizeof(char)*(i+1));
                token[i++] = str[counter];
            }
        }
        counter++;
    }

    if(token != NULL){
        token = (char *)realloc(token,sizeof(char)*(i+1));
        token[i] = '\0';
    }

    return token;
};

char *tokenize_elem_STR(char *str, char delimin1, char delimin2, int position){
    char *token = NULL;
    int i = 0, counter = 0, current_position = 0;

    while(str[counter] != '\0'){
        if((str[counter] == delimin1 || str[counter] == delimin2 ) && token != NULL){
            if( current_position == position ){
                token = (char *)realloc(token,sizeof(char)*(i+1));
                token[i] = '\0';
                return token;
            }
            else{
                free(token);
                token = NULL;
                i = 0;
                current_position += 1;
            }
        }
        else{
            if(str[counter] != '\t' && str[counter] != ' '){
                token = (char *)realloc(token,sizeof(char)*(i+1));
                token[i++] = str[counter];
            }
            else if(str[counter] == ' '){
                if(token != NULL){
                    token = (char *)realloc(token,sizeof(char)*(i+1));
                    token[i++] = str[counter];   
                }
            }
        }
        counter++;
    }

    if(token != NULL){
        token = (char *)realloc(token,sizeof(char)*(i+1));
        token[i] = '\0';
    }

    return token;
};

char *tokenize_elem( FILE *fp , char delimin1, char delimin2 ){
    int i = 0;
    char *token = NULL;

    while(!feof(fp)){
        char c = fgetc(fp);

        if( c != '\n' && c != '\t' && c != ';' && c != EOF && c != ',' && c != '(' && c != ')' && c != 39 && c != 96 && c != delimin1 && c != delimin2){
            if(c == ' ' && token != NULL){
                token = (char *)realloc(token,sizeof(char)*i+1);
                token[i++] = c;
            }
            else if( c != ' '){
                token = (char *)realloc(token,sizeof(char)*i+1);
                token[i++] = c;
            }
        }

        if(( c == EOF || c == delimin1 || c == delimin2) && token != NULL){
            token = (char *)realloc(token,sizeof(char)*i+1);
            token[i] = '\0';
            return token;
        }
        else if( c == EOF  && token == NULL)
            return NULL;
    }
    
    if(token != NULL)
        free(token);
        
    return NULL;
}

void print_find(int start, int end, char **vec, char *table_name, TABLE *table, int index){
    int i = 0, j = 0, counter = 0;
    char *str_find = NULL;
    char *indicator = NULL;
    //1
    FILE *dat_file = open2read_dat(table_name);
    while(i <= end-start){
        indicator = tokenize_arg_STR(vec[start+i],'\t','\t',1);
        while(j < atoi(indicator)-1){
            str_find = readLine(dat_file,10);
                free(str_find);
                j++;
            }
        
    
        //2
        for(counter = 0 ; counter < table[index].nfields ; counter++){
            str_find = tokenize_elem(dat_file,',','\n');
                if(counter == table[index].nfields - 1){
                    if(match(table[index].field[counter].type,"[Cc][Hh][Aa][Rr]"))
                        printf("'%s'\n",str_find);
                    if(match(table[index].field[counter].type,"[Ii][Nn][Tt]"))
                        printf("%d\n",atoi(str_find));
                    if(match(table[index].field[counter].type,"[Ff][Ll][Oo][Aa][Tt]"))
                        printf("%f\n",atof(str_find));
                    if(match(table[index].field[counter].type,"[Dd][Oo][Uu][Bb][Ll][Ee]"))
                        printf("%lf\n",atof(str_find));   
                }
                else{
                    if(match(table[index].field[counter].type,"[Cc][Hh][Aa][Rr]"))
                        printf("'%s', ",str_find);
                    if(match(table[index].field[counter].type,"[Ii][Nn][Tt]"))
                        printf("%d, ",atoi(str_find));
                    if(match(table[index].field[counter].type,"[Ff][Ll][Oo][Aa][Tt]"))
                        printf("%f, ",atof(str_find));
                    if(match(table[index].field[counter].type,"[Dd][Oo][Uu][Bb][Ll][Ee]"))
                        printf("%lf, ",atof(str_find));  
                }
                    free(str_find);
        }
        free(indicator);
        j++;
    i++;
    }

    //3
    fclose(dat_file);
    return;
}

void binary_search_idx( char **vec, char *key, int low, int upp, char *table_name, TABLE *table, int index, STAT *ninfo, int *check){
     int i = 0;
     int mid;
     int nelem = upp;
     char *aux = NULL;

     while (low <= upp){
        mid = (low + upp)/2;

        aux = tokenize_elem_STR(vec[mid],'\t','\t',0);
          if (strcmp(key,aux)==0){
              //Aqui encontra-se o inicio do indice buscado na lista ordenada...
                while(strcmp(key,aux)==0 && (mid-(++i)) >= 0){
                    if(aux != NULL)
                        free(aux);
                        aux = tokenize_elem_STR(vec[mid-i],'\t','\t',0);
                }
                int start = (mid-i)+1;
                    i= 0;
                
                //Aqui, realiza-se o mesmo processo para encontrar o final do
                //indice buscado na lista ordenada...
                free(aux);
                aux = tokenize_elem_STR(vec[mid],'\t','\t',0);
                while(strcmp(key,aux)==0 && (mid+(++i)) <= nelem){
                    if(aux !=NULL)
                        free(aux);
                        aux = tokenize_elem_STR(vec[mid+i],'\t','\t',0);
                }
                int end = (mid+i)-1;
                
                free(aux);
                print_find(start,end,vec,table_name,table,index);
                ninfo->recordsInLastSelectBinary += end-start+1;
                
                *check += 1;
            return;
          }

          if (strcmp(key,aux)<0)
               upp = mid-1;
          else
               low = mid+1;

        free(aux);

     }
     return;
}

void write_idx(FILE *idx_file, FILE *dat_file, char **srt_vec, int nelem, int order){
    int i, j;
    char *aux = NULL;
    for( i = 0 ; i < nelem ; i++){
        for( j = 0 ; j < nelem ; j++){
            aux = readLine(dat_file,10);
            if(aux != NULL){
                char *elem = tokenize_elem_STR(aux,',','\0',order);
                if(strcmp(srt_vec[i],elem)== 0){
                    fprintf(idx_file,"%s\t%d\n",srt_vec[i],j+1);
    
                    if(i < nelem-1){
                        if(strcmp(srt_vec[i],srt_vec[i+1])==0){
                            i++;
                        }
                    }
    
                    else{ 
                        if(elem != NULL)
                            free(elem);
                        break;
                    }
                }
            if(elem != NULL)
                free(elem);
            
            free(aux);
            aux = NULL;
            }
        }
        if(aux != NULL){
            free(aux);
            aux = NULL;
        }
        fseek(dat_file,0,SEEK_SET);
    }
    if(aux != NULL)
        free(aux);

    return;
}

char **create_sorted_vec( FILE *fp, char *param, int order, int *nelem, char *type){
    char **vec = NULL;
    char *aux = NULL;
    char *elem = NULL;
    int i = 0;

    //1st part...
    while(!feof(fp)){
        aux = readLine(fp,10);
        if(!match(aux,"^\\s*$")){
            elem = tokenize_elem_STR(aux,',','\0',order);
            vec = (char **)realloc(vec,sizeof(char *)*(i+1));
            vec[i++] = elem;
        }
        if(aux != NULL)
            free(aux);
    }

    *nelem = i;
    //2nd part...
    if(match(type,"[Cc][Hh][Aa][Rr]"))
        bubble_sort_by_param(vec,*nelem,0);
    else
        bubble_sort_by_param(vec,*nelem,1);

    return vec;
}