char *readLine(FILE *finput){
    char *string = NULL;
    int counter = 0;
    char c = 0;
    
    do{
        c = fgetc(finput);
        string = (char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10 && c != 11 && c != 12 && c != 13 && c != EOF);
    
    string[counter-1] = '\0';
    return string;
}

unsigned char *fread_raw(FILE *fp, int *N){
    unsigned char *audio = NULL;
    
    fseek(fp, 0, SEEK_END);
    *N = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
       audio = (unsigned char *)malloc(sizeof(unsigned char)*(*N));
       fread(audio,1,(*N),fp);
    
    return audio;
}

void printf_raw(unsigned char *audio, int N){
    int i;
    for(i = 0 ; i < N ; i++)
        printf("%d\n", audio[i]);
    return;
}

FILE *fopen_rb(){
    FILE *fp = NULL;
    char *name = NULL;
    
    do{
        name = readLine(stdin);
        fp = fopen(name,"rb");
        if(fp == NULL)
            printf("Invalid file, try annother.\n");
        free(name);
    }while(fp == NULL);
    
    return fp;
}
