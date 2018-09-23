#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void freeM(double **num, int q){
    int i;
    //liberando a memoria utilizada;
    for( i = 0 ; i < q ; i++)
        free(num[i]);

    return;
}

double resultApply(double *values, int periods){
    double result = 0;
    int i;
    //somando os resultados das aplicações;
    for(i = 0 ; i < periods ; i++)
        result += values[i];

    return result;
}

double *interestApply(double *values, int periods, double **investment){
    double *value = (double *)malloc(sizeof(double)*periods);
    int i;
    //calculando o saldo pos cada periodo para cada investimento;
    for(i = 0 ; i < periods ; i++){
        if(investment[i][0] != 0)
            value[i] = (values[i] * pow(1+investment[i][2],(periods-i))) - values[i];
    }

    //aplicando a tributação e calculando o saldo final para cada investimento;
    for(i = 0 ; i < periods ; i++){
        if(investment[i][0] != 0){
            if((periods-i)>23){
                value[i] *= 0.85;
                value[i] += values[i];
            }
            else if((periods-i)>=12 && (periods-i)<=23){
                value[i] *= 0.825;
                value[i] += values[i];
            }
            else if((periods-i)>=6 && (periods-i)<=11){
                value[i] *= 0.8;
                value[i] += values[i];
            }
            else if((periods-i) <= 5){
                value[i] *=  0.775;
                value[i] += values[i];
            }
        }
    }

    return value;
}

double *valueMng(double **investment, int periods){
    double *value = (double *)calloc(periods,sizeof(double));
    int i;
    //calculando o valor real aplicado;
    for(i = 0 ; i < periods ; i++){
        if(investment[i][0] != 0)
            value[i] = investment[i][0] * investment[i][1];
    }

    return value;
}

double **readInvest(int *periods){
    double **tab = NULL;
    double value = 0;
    int i, j;

    for(i = 0 ; value != -1 ; i++){
        tab = (double **)realloc(tab,sizeof(double *)*(i+1));
        scanf("%lf",&value);

        if(value != -1){
            if(value == 0){
                tab[i] = (double *)malloc(sizeof(double)*1);
                tab[i][0] = value;
                fflush(stdin);
            }
            else{
                tab[i] = (double *)malloc(sizeof(double)*3);
                tab[i][0] = value;
                for(j = 1 ; j < 3 ; j++){
                    scanf("%lf",&value);
                    tab[i][j] = value;
                }
                fflush(stdin);
            }
        }
    }

    *periods = i-1;
    return tab;
}

int main (int argc, char **argv){
    double **investment = NULL;
    int periods = 0;

    //Montando a tabela com os investimentos;
    investment = readInvest(&periods);
    //Ajustando os valores para os valores reais aplicados;
    double *values = valueMng(investment,periods);
    //Aplicando os juros sobre os valores investidos;
    values = interestApply(values,periods,investment);
    //Calculando o resultado das aplicações ao final do periodo;
    double value = resultApply(values,periods);

    free(values);
    freeM(investment,periods);
    free(investment);

    printf("%.2lf",value);

    return 0;
}
