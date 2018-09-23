#ifndef _T2_MATH_H_
#define _T2_MATH_H_

#include <stdlib.h>
#include <stdio.h> 
#include <math.h>

#include "t2_math.c"

//Estrutura responsavel por determinar uma forma para numeros complexos,ou seja,
//da a uma variavel uma parte real (double) e uma imaginaria (double)...
typedef struct complex t_complex;
//Estrutura responsavel por determinar uma forma para os coefficientes da trans_
//formada de fourier, dando a uma variavel uma amplitude, uma frequencia e um
//complexo (que relaciona a variavel a uma magnitude)...
typedef struct coefficient t_coefficient;

//Funcao responsavel por realizar a Transformada Discreta de Fourier...
struct complex *fourier_dtransform(unsigned char *, int );
//Funcao responsavel por realizar a Transformada Inversa de Fourier...
unsigned char *fourier_inversedtransform(struct coefficient *, int );

//Funcao responsavel por realizar a ordenacao dos coeficientes de um sinal de 
//audio depois da passagem de uma Transformada de Fourier sobre ele - a ordena_
//cao e decrescente, levando em consideracao a amplitude de cada sinal...
void merge_sort_amp(struct coefficient *vec, int start, int end);
//Funcao responsavel por realizar a ordenacao dos coeficientes de um sinal de 
//audio depois da passagem de uma Transformada de Fourier sobre ele - a ordena_
//cao e crescente, levando em consideracao a frequencia de cada sinal...
void merge_sort_freq(struct coefficient *vec, int start, int end);

//Funcao responsavel por calcular a magnitude de cada sinal de audio passado 
//como argumento para a funcao e retornar tais valores em um "vetor" dinamica_
//mente alocado...
struct coefficient *getallmag( struct complex * , int );

#endif
