enum{
    TXT_FLAG,
    HUFF_FLAG
};

int *digit_readString(char *string, int *n){
    char c = 0;
    int counter = 0;
    int *digits = NULL;
    
    do{
        c = string[counter++];
        if(isdigit(c)){
            digits = (int *)realloc(digits,sizeof(int)*(*n+1));
            digits[(*n)++] = c - '0';
        }
    }while(c != '\0');
    
    return digits;
};

char *readLine(FILE *input_file){
    char c = 0;
    int counter = 0;
    char *string = NULL;
    
    do{
        c = fgetc(input_file);
        string = (char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10 && c != 11 && c != 12 && c != 13 && c != EOF);
    
    string[counter-1] = '\0';
    
    return string;
};

FILE *huff_fopen( int *flag ){
    char *filename = NULL;
    FILE *file = NULL;
    
    //1- Lendo o nome do arquivo o qual se deseja abrir e tentado abri-lo em
    //seguida...
    filename = readLine(stdin);
    file = fopen(filename,"r");
        
    //2- Caso o arquivo nao seja aberto...
    if(file == NULL)
        printf("Invalid file (Inexistent file). Try another...\n");
        
    //3- Caso ele seja aberto...  
    else{
        //a. Verifica-se se o arquivo possui extensao '.txt' ...
        if(match(filename,"[.][Tt][Xx][Tt]")){
            free(filename);
            *flag = TXT_FLAG;
            return file;                
        }
        //b. Ou extensao '.huff' ...
        else if(match(filename,"[.][Hh][Uu][Ff][Ff]")){
            free(filename);
            *flag = HUFF_FLAG;
            return file;
        }
        //c. Caso nao possua nenhuma das extensoes validas...
        else printf("Invalid file (Invalid Extension). Try another...\n"); 
    }
    
    //4- Caso nao seja possivel abrir um arquivo valido devido algum parametro
    //anterior, libera-se a memoria usada e fecha-se o arquivo, caso ele esteja
    //aberto...
    free(filename);
    if(file != NULL)
        fclose(file);
    
    //5- Tenta-se abrir outro arquivo, desta vez valido...
    return huff_fopen(flag);
};