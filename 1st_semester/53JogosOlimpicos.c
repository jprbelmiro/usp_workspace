#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void freeDeep(char ***Tab, int N){
    int i, j;
    for(i = 0 ; i < N ; i++){
        for( j = 0 ; j < 4 ; j++){
            free(Tab[i][j]);
        }
    }

    for(i = 0 ; i < N ; i++){
        free(Tab[i]);
    }

    return;
}

void printTab(char ***Tab, int N){
    int i, j;
    for(i = 0 ; i < N ; i++){
        for(j = 0 ; j < 4 ; j++){
            printf("%s ",Tab[i][j]);
        }
        printf("\n");
    }

    return;
}

int ConvertStoI(char *Tab){
    int medalhas = 0;
    int p = strlen(Tab), i;
    for( i = 0 ; i < p ; i++){
        medalhas += (Tab[i] - '0')*(pow(10,p-(i+1)));
    }
    return medalhas;
}

void Organize(char ***Tab, int N){
    int i , j, counter = 0, qtdd_med1, qtdd_med2;
    char **aux;
//ordenando por ouro;
    for(i = 0; i < N-1 ; i++){
        for(j = i+1 ; j < N ; j++){
            qtdd_med1 = ConvertStoI(Tab[i][1]);
            qtdd_med2 = ConvertStoI(Tab[j][1]);
            if(qtdd_med1 < qtdd_med2){
                aux = Tab[i];
                Tab[i] = Tab[j];
                Tab[j] = aux;
            }
        }
    }

//ordenando por prata de ouro iguais;
    for(i = 0; i < N-1 ; i++){
        for(j = i+1 ; j < N ; j++){
            qtdd_med1 = ConvertStoI(Tab[i][1]);
            qtdd_med2 = ConvertStoI(Tab[j][1]);
            if(qtdd_med1 == qtdd_med2){
                qtdd_med1 = ConvertStoI(Tab[i][2]);
                qtdd_med2 = ConvertStoI(Tab[j][2]);
                if(qtdd_med1 < qtdd_med2){
                    aux = Tab[i];
                    Tab[i] = Tab[j];
                    Tab[j] = aux;
                }
            }
        }
    }

//ordenando por bronze de ouro e prata iguais;
//ordenando por prata de ouro iguais;
    for(i = 0; i < N-1 ; i++){
        for(j = i+1 ; j < N ; j++){
            qtdd_med1 = ConvertStoI(Tab[i][1]);
            qtdd_med2 = ConvertStoI(Tab[j][1]);
            if(qtdd_med1 == qtdd_med2){
                qtdd_med1 = ConvertStoI(Tab[i][2]);
                qtdd_med2 = ConvertStoI(Tab[j][2]);
                if(qtdd_med1 == qtdd_med2){
                    qtdd_med1 = ConvertStoI(Tab[i][3]);
                    qtdd_med2 = ConvertStoI(Tab[j][3]);
                    if(qtdd_med1 < qtdd_med2){
                        aux = Tab[i];
                        Tab[i] = Tab[j];
                        Tab[j] = aux;
                    }
                }
            }
        }
    }

    return;
}

char *Separate(char *aux, int *j){
    int counter = 0;
    char c;
    char *string = NULL;
    do{
        c = aux[(*j)++];
        string = (char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != ' ' && c != '\0');
        string[counter-1] = '\0';


    return string;
}

char *readLine(){
    int counter = 0;
    char c;
    char *string = NULL;
    do{
        c = fgetc(stdin);
        string = (char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10);
        string[counter-1] = '\0';


    return string;
}

char ***createTab(int N){
    char ***tab = (char ***)malloc(sizeof(char **)*N);
    char *aux;
    char *sigla,*ouro, *prata, *bronze;
    int i,j;
    for( i = 0 ; i < N ; i++)
        tab[i] = (char **)malloc(sizeof(char *)*4);

    for(i = 0 ; i < N ; i++){
            j = 0;
            aux = readLine();
            sigla = Separate(aux,&j);
            ouro = Separate(aux,&j);
            prata = Separate(aux,&j);
            bronze = Separate(aux,&j);
            tab[i][0] = sigla;
            tab[i][1] = ouro;
            tab[i][2] = prata;
            tab[i][3] = bronze;
        free(aux);
    }

    return tab;
}

int main(int argc, char **argv){
//Entrando com o numero 'N' de países...
    int N;
    scanf("%d%*c",&N);

    //criando a tabela olimpica;
    char ***Tab = createTab(N);

//Ordenando o placar final...
    Organize(Tab, N);
    //imprimindo a tabela olimpica;
    printTab(Tab,N);

//Free;
    freeDeep(Tab,4);
    free(Tab);

    return 0;
}
