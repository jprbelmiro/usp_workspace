#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void print_Tetranacci( int n , double *seq ){    // Responsável por imprimir na tela a sequencia de Tetranacci de n elementos...
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

void Manhattan_distance(int n, double *seq){    // Responsável por realizar o calculo da distancia entre pontos usando o
                                                //conceito de "city block"...
    int i;
    double distance = 0;
    for( i = 0 ; i < n/2 ; i++)
        distance += abs(seq[i]-seq[(n/2)+i]);

    printf("%.4lf",distance);

    return;
}

double quadratic_avarage_Tetranacci( int n , double *seq ){   // Responsável por calcular a media aritimetica de uma sequencia
                                                    //de Tetranacci de n elementos...
    int i;
    double sum = 0;
    for( i = 0 ; i < n ; i++ )
        sum += pow(seq[i],2);

    return sqrt(sum/n);
};

void Tetranacci(int n, int level, double **seq){
    if(level == n)
        return;

    *seq = (double *)realloc(*seq,sizeof(double)*(level+1));

    if(level < 2)
        *(*seq+level) = 0.0;

    if(level >= 2 && level < 4)
        *(*seq+level) = 1.0;

    if(level >= 4){
        *(*seq+level) = *(*seq+level-1) + *(*seq+level-2)
                            + *(*seq+level-3) + *(*seq+level-4);
    }

    return Tetranacci(n,level+1,seq);
}

int main (int argc, char **argv){
    //1) Entrando com o valor da operação que se deseja
    //realizar e a quantidade de numeros que se deseja
    //para a sequencia de Tetranacci...
    int opt, n;
        scanf("%d%*c%d%*c",&opt,&n);

    //2) Criando a sequencia de Tetranacci de 'n' elementos...
    int level = 0;
    double *seq = NULL;
    double avarage;
        Tetranacci(n,level,&seq);

    //3) Iniciando a operação escolhida
    switch(opt){
        case 1:
            print_Tetranacci(n,seq);
            break;

        case 2:
            avarage = quadratic_avarage_Tetranacci(n,seq);
                printf("%.4lf",avarage);
            break;

        case 3:
            Manhattan_distance(n,seq);
            break;
    }

    //4) Liberando a memória alocada...
    free(seq);

    return 0;
}
