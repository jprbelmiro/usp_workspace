#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void freeM(char **num, int q){
    int i;
    //liberando a memoria utilizada;
    for( i = 0 ; i < q ; i++)
        free(num[i]);

    return;
}

int CountDec(char *string){
    int decimal = 0, i = 0;
    char c;
    //definindo o numero de casa decimais do numero;
    for( i = 0 ; i < strlen(string) ; i++){
        c = string[i];
        if(c == '.') decimal = strlen(string) - (i+1);
    }

    return decimal;
}

int Define_pot(char *string){
    int potencia = 0, i;
    char c;
    //definindo a potencia do numero;
    for( i = 0 ; i < strlen(string) ; i++){
        c = string[i];
        if(c != '-' && c != '.') potencia++;
    }

    return potencia-1;
}

double ConvertStoI(char *s){
    double alpha = 0;
    int i;

//Convertendo uma string em numero;
    //analisando qual a potencia do numero;
    int p = Define_pot(s);

    for( i = 0 ; i < strlen(s) ;i++){
        if(s[i] != '-' && s[i] != '.'){
            alpha += (s[i] - '0')*(pow(10,p));
            p -= 1;
        }
    }

    //analisando se o numero é negativo;
    if(s[0] == '-') alpha = alpha*(-1);

    //analisando o numero de casa decimais do numero
    int Dec = CountDec(s);
        if(Dec != 0) alpha /= pow(10,Dec);

    return alpha;
}

char *readOne(char *aux, int *j){
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

double Numeric_Op(char *expression, int until, int value, int start){
    char **nums = NULL;
    int Qtdd_num = 0;
    int i, j = start;

//Descobrindo a quantidade de numeros da operação;
    for( i = start ; i < until-1 ; i++ ){
        if(expression[i] == ' ')
            Qtdd_num++;
    }

//Lendo e transformando o texto em numeros;
    double *numeros = NULL;
    nums = (char **)malloc(sizeof(char *)*Qtdd_num);

    //Lendo um numero por vez
    for(i = 0 ; i < Qtdd_num ; i++){
        nums[i] = readOne(expression, &j);
    }

    //Convertendo o numero no formato de texto para double;
    for( i = 0 ; i < Qtdd_num ; i++){
        numeros = (double *)realloc(numeros, sizeof(double)*(i+1));
        numeros[i] = ConvertStoI(nums[i]);
    }
    //Liberando a memória utilizada;
    freeM(nums,Qtdd_num);
    free(nums);

    //Operando sobre a 'expressão menor';
    double result = value;
    if(expression[until-1] == '+'){
        for(i = 0 ; i < Qtdd_num ; i++)
            result += numeros[i];
    }
    else if(expression[until-1] == '-'){
        for(i = 0 ; i < Qtdd_num ; i++)
            result -= numeros[i];
    }
    else if(expression[until-1] == '*'){
        if(result == 0){
            result = numeros[0];
            for(i = 1 ; i < Qtdd_num ; i++)
            result *= numeros[i];
        }
        else
            for(i = 0 ; i < Qtdd_num ; i++)
                result *= numeros[i];
    }
    else if(expression[until-1] == '/'){
        if(result == 0){
            result = numeros[0];
            for(i = 1 ; i < Qtdd_num ; i++)
            result /= numeros[i];
        }
        else
            for(i = 0 ; i < Qtdd_num ; i++)
                result /= numeros[i];
    }

    free(numeros);

    return result;
}

int readUntil(char *expression, int last){
    //Descobrindo até onde vai a operação setada;
    char c;
    do{
        c = expression[last];
        last++;
    }while(c != '\0' && c != '+' && c != '-' && c != '*' && c != '/');

    return last;
}

double Polish_Operation(char *expression){
    int until = 0, i, start = 0;
    double result = 0;

    for(i = 0 ; i < strlen(expression) ;){
        //Descobrindo a posicao dos sinais de operação;
        until = readUntil(expression,until+2);
        //realizando de fato as operações na forma numerica;
        result = Numeric_Op(expression,until,result,start);
        //definindo a posição de inicio de leitura;
        start = until + 1;
        //avançando a posicao de leitura
        i = until + 1;
    }

    return result;
}

char *readLine(){
    char *string = NULL;
    char c;
    int counter = 0;
    do{
        c = fgetc(stdin);
        string = (char *)realloc(string, sizeof(char)*(counter+1));
        string[counter++] = c;
    } while (c != 10);
    string[counter - 1] = '\0';

    return string;
}


int main (int argc, char **argv){
//(1) Lendo a expressão na forma polonesa;
    char *expression = readLine();

//(2) Realizando as operações;
    double result = Polish_Operation(expression);
    printf("%lf",result);

    free(expression);

    return 0;
}
