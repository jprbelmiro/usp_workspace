#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct quadrado{
    double x;
    double y;
    double l;
}quadrado;

typedef struct retangulo{
    double x1;
    double y1;
    double x2;
    double y2;
}retangulo;

typedef struct circulo{
    double x;
    double y;
    double r;
}circulo;

double dist( double a, double b){
    double dist = 0;

    dist = abs(a - b);

    return dist;
}

 double min( double a, double b, double c, double d){
    double min;

    if(a <= b && a <= c && a <= d) min = a;
    if(d <= b && d <= c && d <= a) min = d;
    if(c <= b && c <= a && c <= d) min = c;
    if(b <= a && b <= c && b <= d) min = b;

    return min;
 }


 double max( double a, double b, double c, double d){
    double max;
    if(a >= b && a >= c && a >= d) max = a;
    if(d >= b && d >= c && d >= a) max = d;
    if(c >= b && c >= a && c >= d) max = c;
    if(b >= a && b >= c && b >= d) max = b;

    return max;
 }

void quadrados( int N ){
    int i, j;
    quadrado *Q = malloc(sizeof(quadrado)*N);

    for( i = 0 ; i < N ; i++ ){
        scanf("%lf%*c",&Q[i].x);
        scanf("%lf%*c",&Q[i].y);
        scanf("%lf%*c",&Q[i].l);
    }

    // -> Para haver colisao entre dois quadrados é necessário que a distancia entre seus
    //centros seja menor ou igual a soma da metade de suas diagonais, no pior caso...
    for(i = 0 ; i < N ; i++ ){
        for( j = i+1 ; j < N ; j++ ){
            if(sqrt(pow(Q[i].x - Q[j].x,2)+pow(Q[i].y - Q[j].y,2)) <= ((Q[i].l*sqrt(2))/2)+((Q[j].l*sqrt(2)))){
                printf("SIM\n");
                return;
            }
        }
    }

    printf("NAO\n");

    return;
}

void retangulos( int N ){
    int i, j;
    retangulo *R = malloc(sizeof(retangulo)*N);

    for( i = 0 ; i < N ; i++ ){
        scanf("%lf%*c",&R[i].x1);
        scanf("%lf%*c",&R[i].y1);
        scanf("%lf%*c",&R[i].x2);
        scanf("%lf%*c",&R[i].y2);
    }

    // -> Para haver colisao entre dois retangulos é necessário que exista um ponto pelo menos contido no
    //outro. Para conferir tal propriedade, faz-se a soma dos lados do retangulo em um eixo e compara-se
    //com a distancia do ponto maximo no eixo até o minimo, caso o primeiro seja maior que o segundo,
    //compara-se o outro eixo e caso este também seja maior, houve colisão...
    for(i = 0 ; i < N ; i++ ){
        for( j = 0 ; j < N ; j++){
            if( j != i) {
                if(dist(R[i].x1,R[i].x2)+dist(R[j].x1,R[j].x2) >= dist(max(R[i].x1,R[i].x2,R[j].x1,R[j].x2),
                                                                           min(R[i].x1,R[i].x2,R[j].x1,R[j].x2))){
                        if(dist(R[i].y1,R[i].y2)+dist(R[j].y1,R[j].y2) >= dist(max(R[i].y1,R[i].y2,R[j].y1,R[j].y2),
                                                                           min(R[i].y1,R[i].y2,R[j].y1,R[j].y2))){
                            printf("SIM\n");
                            return;
                        }
                    }
                }
        }
    }

    printf("NAO\n");

    return;
}

void circulos( int N ){
    int i, j;
    circulo *C = malloc(sizeof(circulo)*N);

    for( i = 0 ; i < N ; i++ ){
        scanf("%lf%*c",&C[i].x);
        scanf("%lf%*c",&C[i].y);
        scanf("%lf%*c",&C[i].r);
    }

    // -> Para haver colisao entre dois circulos é necessário que a distancia entre seus centros
    //seja menor ou igual ao raio de um somado ao do outro...
    for(i = 0 ; i < N ; i++ ){
        for( j = i+1 ; j < N ; j++ ){
            if(sqrt(pow(C[i].x - C[j].x,2)+pow(C[i].y - C[j].y,2)) <= C[i].r+C[j].r){
                printf("SIM\n");
                return;
            }
        }
    }

    printf("NAO\n");

    return;
}

int main ( int argc , char **argv ){
    // Lendo o tipo de objeto...
    char opc;
        scanf("%c%*c",&opc);

    // Lendo um inteiro N...
    int N;
        scanf("%d%*c",&N);

    // Lendo as dimensoes de cada N objetos do tipo opt e imprimindo na tela
    //se houve sobreposição ou não...
    switch(opc){
        case 'c':
            circulos(N);
            break;

        case 'r':
            retangulos(N);
            break;

        case 'q':
            quadrados(N);
            break;

    }

    return 0;
}
