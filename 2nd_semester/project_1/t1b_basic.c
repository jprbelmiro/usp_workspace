#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void freeMatrix(void **matrix, int nrow){
    int i;
    for( i = 0 ; i < nrow ; i++)
        if(matrix[i] != NULL)
            free(matrix[i]);

    if(matrix != NULL)
        free(matrix);

    return;
}

void bubble_sort_by_param(char **vec, int len, int op){
    int i, j;
    char *aux_c = NULL;
    double *num_vec = NULL;
    double aux_d;
    
    if(op == 0){
        for(i = len-1; i >= 1; i--){  
            for(j=0; j < i ; j++) {
                if(strcmp(vec[j],vec[j+1])>0){
                    aux_c = vec[j];
                    vec[j] = vec[j+1];
                    vec[j+1] = aux_c;
                }
            }
        }
    }
    
    else{
        num_vec = (double *)malloc(sizeof(double)*len);
        for(i = 0 ; i < len ; i++){
            num_vec[i] = atof(vec[i]);
        }
        
        for(i = len-1; i >= 1; i--){  
            for(j=0; j < i ; j++) {
                if(num_vec[j]>num_vec[j+1]){
                    aux_c = vec[j];
                    vec[j] = vec[j+1];
                    vec[j+1] = aux_c;
                    
                    aux_d = num_vec[j];
                    num_vec[j] = num_vec[j+1];
                    num_vec[j+1] = aux_d;
                }
            }
        }
        free(num_vec);
    }
    
    return;
}

char *readLine(FILE *input_file, char delimiter){
    int i = 0;
    char c;
    char *str = NULL;

    do{
        c = fgetc(input_file);
        str = (char *)realloc(str,sizeof(char)*(i+1));
        str[i++] = c;
    }while(c != delimiter && c != EOF);

    str[i-1] = '\0';

    return str;
}

void copy_file(FILE *input_file, FILE *output_file){
    int c;

    while ((c = fgetc(input_file)) != EOF)
        fputc (c, output_file);

    return;
}

char *file_name_idx(char *table_name, char *param_name){
    int i, j;

    int len1 = strlen(table_name);
    int len2 = strlen(param_name);
    char *name = (char *)calloc((len1+len2+6),sizeof(char));

    for( i = 0 ; i < (len1 + len2 + 6) ; i++){
        for( i = 0 ; i < len1 ; i++)
            name[i] = table_name[i];

            name[i++] = '-';

        for( j = 0 ; j < len2 ; j++)
            name[i++] = param_name[j];

        for(j = 0 ; j < 5 ; j++){
            if(j == 0)
                name[i++] = '.';
            else if(j == 1)
                name[i++] = 'i';
            else if(j == 2)
                name[i++] = 'd';
            else if(j == 3)
                name[i++] = 'x';
            else
                name[i++] = '\0';
        }
    }

    return name;
}

char *file_name_temp(char *file_name){
    int i;
    int len = strlen(file_name);
    char *name = (char *)malloc(sizeof(char)*(len+5));
    for( i = 0 ; i < len + 5 ; i++){
        if( i < len)
            name[i] = file_name[i];
        else{
            if(i % len == 0)
                name[i] = '.';
            if(i % len == 1)
                name[i] = 't';
            if(i % len == 2)
                name[i] = 'm';
            if(i % len == 3)
                name[i] = 'p';
            if(i % len == 4)
                name[i] = '\0';
        }
    }

    return name;
}

char *file_name_dat(char *file_name){
    int i;
    int len = strlen(file_name);
    char *name = (char *)malloc(sizeof(char)*(len+5));
    for( i = 0 ; i < len + 5 ; i++){
        if( i < len)
            name[i] = file_name[i];
        else{
            if(i % len == 0)
                name[i] = '.';
            if(i % len == 1)
                name[i] = 'd';
            if(i % len == 2)
                name[i] = 'a';
            if(i % len == 3)
                name[i] = 't';
            if(i % len == 4)
                name[i] = '\0';
        }
    }

    return name;
}

FILE *open2write_idx(char *table_name, char *param_name){
    FILE *file = NULL;

    char *name = file_name_idx(table_name,param_name);
        file = fopen(name,"a");
    free(name);

    return file;
}

FILE *open2write_tmp(char *file_name){
    FILE *file = NULL;

    char *name = file_name_temp(file_name);
        file = fopen(name,"a");
    free(name);

    return file;
}

FILE *open2write_dat(char *file_name){
    FILE *file = NULL;

    char *name = file_name_dat(file_name);
        file = fopen(name,"a");
    free(name);

    return file;
}

FILE *open2read_idx(char *table_name, char *param_name){
    FILE *file = NULL;

    char *name = file_name_idx(table_name,param_name);
        file = fopen(name,"r");
        
    free(name);

    return file;
}

FILE *open2read_tmp(char *file_name){
    FILE *file = NULL;

    char *name = file_name_temp(file_name);
        file = fopen(name,"r");
    free(name);

    return file;
}

FILE *open2read_dat(char *file_name){
    FILE *file = NULL;

    char *name = file_name_dat(file_name);
        file = fopen(name,"r");
    free(name);

    return file;
}

FILE *open_file2read(){
    FILE *file = NULL;
    char *file_name = NULL;

    while(file == NULL){
        file_name = readLine(stdin,10);

        file = fopen(file_name,"r");

        if(file == NULL){
            printf("Invalid file, enter another.\n");
            free(file_name);
        }
        else free(file_name);
    }

    return file;
}