#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void print_JL( int n , double *seq ){    // Responsável por imprimir na tela a sequencia de Tetranacci de n elementos...
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

double varJL( int n , double *seq ){
    int i;
    double var = 0.0;
    double arith = 0.0;

    // Calculando a média aritmetica da sequencia...
    for( i = 0 ; i < n ; i++ ){
        arith +=  seq[i];
    }
        arith /= n;

    // Calculando a variancia da sequencia...
    for( i = 0 ; i < n ; i++ ){
        var += pow(seq[i] - arith,2);
    }
        var /= n;

    return var;
}

double distanciaChebyshev( int n, double *seq){
    int i;
    double cheby;
    double *all_values = malloc(sizeof(double)*n/2);

    for( i = 0 ; i < n/2 ; i++ ){
        all_values[i] = abs(seq[i] - seq[(n/2)+i]);
    }

    cheby = all_values[i];
    for( i = 0 ; i < n/2 ; i++ )
        if( cheby < all_values[i])
            cheby = all_values[i];

    free(all_values);

    return cheby;
}

void JacobsLucas( double **seq , int n , int level){
    if(level == n) return;

    if(level == 0){
        *seq = (double *)realloc(*seq,sizeof(double)*(level+1));
        *(*seq+level) = 2.0;
    }
    if(level == 1){
        *seq = (double *)realloc(*seq,sizeof(double)*(level+1));
        *(*seq+level) = 1;
    }
    if(level >= 2){
        *seq = (double *)realloc(*seq,sizeof(double)*(level+1));
        *(*seq+level) = *(*seq+level-1) + (2* *(*seq+level-2));
    }

    return JacobsLucas(seq,n,level+1);
}

int main ( int argc , char **argv ){
    //1) Aceitando como entrada uma opçao inteira e um tamanho...
    int opt, n;
        scanf("%d%*c%d%*c",&opt,&n);

    //2) Gerando a sequencia de Jacobsthal Lucas...
    int level = 0;
    double *seq = NULL;
        JacobsLucas(&seq, n, level);

    //3) Iniciando a operação escolhida
    double variancia, chebyshev;
    switch(opt){
        case 1:
            print_JL(n,seq);
            break;

        case 2:
            variancia = varJL(n,seq);
            printf("%.4lf\n",variancia);
            break;

        case 3:
            chebyshev = distanciaChebyshev(n,seq);
            printf("%.4lf\n",chebyshev);
            break;
    }

    free(seq);

    return 0;
}
