static char *stringcopy(char *name){
    char c;
    char *string = NULL;
    
    int i = 0;
    do{
        c = name[i++];
        string = (char *)realloc(string,sizeof(char)*i);
        string[i-1] = c;
    }while(c != '\0');
    
    return string;
}

char *tokenize(int pos, char *source){
    char c;
    char *string = NULL;
    
    int i = 0, j = 0, counter = 0;
    while(i <= pos && j <= strlen(source)){
        c = source[j++];
        if(c == '\0' && string == NULL){
            return NULL;
        }
        else if(i != pos && (c == ' ' || c == '\0') && string != NULL){
            free(string);
            string = NULL;
            counter = 0;
            i++;
        }
        else if(i == pos && (c == ' ' || c == '\0') && string != NULL){
            string = (char *)realloc(string,sizeof(char)*(counter+1));
            string[counter++] = '\0';
            if(c == '0')
                return string;
            else
                i++;
        }
        else if(c != ' ' && c != '\0'){
            string = (char *)realloc(string,sizeof(char)*(counter+1));
            string[counter++] = c;
        }
    }
    
    return string;
}

int numberOnString(char *string){
    int i, counter = 0;
    char *number = NULL;
    for(i = 0 ; i < strlen(string); i++){
        if(isdigit(string[i])){
            number = (char *)realloc(number,sizeof(char)*(counter+1));
            number[counter++] = string[i];
        }
    }
    number = (char *)realloc(number,sizeof(char)*(counter+1));
    number[counter++] = '\0';
    
    int num = atoi(number);
    free(number);
    return num;
}

char *readLine(FILE *fp){
    char c;
    int counter = 0;
    char *string = NULL;
    do{
        c = fgetc(fp);
        if(c != 10 && c != 11 && c != 12 && c != 13 && c != EOF){
            string = (char *)realloc(string,sizeof(char)*(counter+1));
            string[counter++] = c;
        }
    }while(c != 10 && c != 11 && c != 12 && c != 13 && c != EOF);
    
    string = (char *)realloc(string,sizeof(char)*(counter+1));
    string[counter] = '\0';

    return string;
}

int inNumber(FILE *fp){
    int op;
    char *string = NULL;

    do{
        string = readLine(fp);
        op = numberOnString(string);
        if(match(string,"^\\s*[0-9]{1,}\\s*$")){
            free(string);     
            return op;
        }
        else{
            printf("Invalid. Try another.\n> ");
            free(string);
            string = NULL;
        }
    }while(string == NULL);
    
    return -1;
}