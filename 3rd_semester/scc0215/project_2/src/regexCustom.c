#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

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


int countMatch(char *string1, char *string2){
    int i = 0, counter = 0;
    char *substring = NULL;
    for( i = 0 ; i <= strlen(string1) - strlen(string2) ; i++){
        substring = readString(string1,i,i+strlen(string2),'\0');
        if(match(substring,string2))
            counter++;
        free(substring);
    }
    return counter;
}

char *tokenize ( char *string, int n, char delim){
    char c = string[0], *token = NULL;
    int counter = 0, i = 0;
    
    if(string[i] == ';' || string[i] == ',' || string[i] == delim)
        while(string[i] == ';' || string[i] == ',' || string[i] == delim) i++;
        
    while(counter < n){
        while(string[i] != ';' && string[i] != ',' && string[i] != delim) i++;
        if(string[i] == ';' || string[i] == ',' || string[i] == delim)i++;
        counter++;
    }
    
    counter = 0;
    do{
        c = string[i++];
        if(c != ';' && c != ',' && c != delim){
            token = (char *)realloc(token,sizeof(char)*counter+1);
            token[counter++] = c;
        }
    }while(c != ';' && c != ',' && c != delim && c != '\0' && c != EOF);
      
    token = (char *)realloc(token,sizeof(char)*counter+1);
    token[counter++] = '\0';
    return token;
}

char **tokenizeAll(char *string, char delim, int ntokens){
    int i = 0;
    char **tokens = NULL;
    tokens = (char **)malloc(sizeof(char *)*ntokens);
    for( i = 0 ; i < ntokens ; i++)
        tokens[i] = tokenize(string,i,';');
    return tokens;
}