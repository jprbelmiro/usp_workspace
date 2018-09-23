#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void print_Tibonacci( int n , double *seq ){    // Responsável por imprimir na tela a sequencia de Tribonacci de n elementos...
    int i;
    for( i = 0 ; i < n ; i++){
        printf("%.1lf", seq[i]);
        if( i < n-1 )
            printf(" ");
        if( i == n-1 )
            printf("\n");

    }

    return;
};

double avarage_YTribonacci( int n , double *seq){   // Responsável por calcular a media aritimetica de uma sequencia
                                                    //de Tribonacci de n elementos, contudo partindo da metade desta
                                                    //até o fim...
    int i;
    double sum = 0;
    for( i = n/2 ; i < n ; i++ ){
        sum += seq[i];
    }

    double avarage = sum/(n/2);

    return avarage;
};

double avarage_Tribonacci( int n , double *seq ){   // Responsável por calcular a media aritimetica de uma sequencia
                                                    //de Tribonacci de n elementos...
    int i;
    double sum = 0;
    for( i = 0 ; i < n ; i++ )
        sum += seq[i];

    return sum/n;
};

void pearson_Tribonacci( int n , double *seq ){ // Responsavel por calcular a correlação Linear de Pearson
                                                //para uma sequencia seq de Tribonacci...
    int i;
    double p;
    double avaragex = avarage_Tribonacci(n/2,seq);
    double avaragey = avarage_YTribonacci(n,seq);

    double cov = 0;
        for( i = 0 ; i <  n/2 ; i++)
            cov += (seq[i]-avaragex)*(seq[(n/2)+i] - avaragey);

    double varx = 0, vary = 0;
        for( i = 0 ; i <  n/2 ; i++){
            varx += pow(seq[i]-avaragex,2);
            vary += pow(seq[(n/2)+i] - avaragey,2);
        }

        p = (cov/(sqrt(varx*vary)));
        printf("%.4lf", p);

        return;
};

void Tribonacci ( int n , int level , double **seq){ //Responsável por criar a sequencia de Tribonacci recursivamente...
    if(level == n){
        return;
    }

    *(seq) = (double *)realloc(*seq,sizeof(double)*(level+1));

    if(level < 2){
        *(*(seq)+level) = 0.0;
    }

    if(level == 2){
        *(*(seq)+level) = 1.0;
    }


    if(level > 2){
        *(*(seq)+level) = *(*(seq)+level-1) + *(*(seq)+level-2) + *(*(seq)+level-3);
    }

    return Tribonacci(n,level+1,seq);
}

int main ( int argc, char **argv){
    //1) Entrando com o valor da operação que se deseja
    //realizar e a quantidade de numeros que se deseja
    //para a sequencia de Tribonacci...
    int opt, n;
        scanf("%d%*c%d%*c",&opt,&n);

    //2) Criando a sequencia de Fibonnaci de 'n' elementos...
    int level = 0;
    double *seq = NULL;
    double avarage;
        Tribonacci(n,level,&seq);

    //3) Iniciando a operação escolhida
    switch(opt){
        case 1:
            print_Tibonacci(n,seq);
            break;

        case 2:
            avarage = avarage_Tribonacci(n,seq);
                printf("%.4lf",avarage);
            break;

        case 3:
            pearson_Tribonacci(n,seq);
            break;
    }

    //4) Liberando a memória alocada...
    free(seq);

    return 0;
}
