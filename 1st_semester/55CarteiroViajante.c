#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double short_dist;

typedef enum {
	NO,
	YAH
} binary;

void freeM(double **matriz, int n){
// - FUNÇÃO: freeM()
// Responsavel por liberar a memoria alocada para uma matriz...
    int i;
    for( i = 0 ; i < n ; i++)
        free(matriz[i]);

    free(matriz);

    return;
}

double fat(int n){
// - FUNÇÃO: fat()
// Responsavel por calcular o fatorial de um numero dado "n"...
	if(n)
  	  return n*fat(n-1);

	else return 1;
}

double Distance_Calculator( double **coordinates, int cities, int *way){
// - FUNÇÃO: Distance_Calculator()
// Responsavel por, de fato, calcular a distancia percorrida em um caminho
//valido...
    double dist = 0;
    int i;
        for(i = 0 ; i < cities-1 ; i++){
            dist += sqrt(pow(coordinates[way[i]][0] -
                              coordinates[way[i+1]][0],2)+pow(coordinates[way[i]][1] - coordinates[way[i+1]][1],2));
        }
        dist += sqrt(pow(coordinates[way[cities-1]][0] -
                          coordinates[way[0]][0],2)+pow(coordinates[way[cities-1]][1] - coordinates[way[0]][1],2));

    return dist;
}

void Valid_Way(int *way, int cities, double **coordinates) {
// - FUNÇÃO: Valid_Way()
// Responsavel por pegar o caminho valido e calcular a distancia deste,
//comparando-o com caminhos anteriores para descobrir se este é o menor
//caminho encontrado...
    double distance = Distance_Calculator(coordinates,cities,way);
    if(short_dist == 0) short_dist = distance;
        short_dist = (short_dist > distance) ? distance : short_dist;

	return;
}

binary isValid(int *way, int cities) {
// - FUNÇÃO: isValid()
// Responsavel por analisar se o caminho é valido ou não.
// Esta analise e feita verificando se nenhuma cidade foi repitida
//no trajeto...
	int i, *aux;

	if(cities != 0)
        aux = (int *) calloc(cities, sizeof(int));

	for (i = 0; i < cities; i++) {
		if (++aux[way[i]] > 1) {
			free(aux);
			return NO;
		}
	}

	if(cities != 0)
        free(aux);

	return YAH;

}

void Travelling_Problem(int level, int cities, int *ways, double **coordinates){
// - FUNÇÃO: Travelling_Problem()
// Responsavel por, de fato, realizar todo o processo de descoberta da menor
//distancia de viagem entre as cidades entradas...
    // Observe que isto e feito de maneira totalmente recursiva...
    // Observe também que somente caminhos validos (ou seja, que nao repetem uma
    //mesma cidade na viagem) são calculados e somente considera-se casos em que
    //a primeira cidade entrada é o ponto de partida...
	int i, j, OK;
	if (level == 0) {
		if (isValid(ways, cities)) {
			Valid_Way(ways, cities, coordinates);
			return ;
		}
		return;
	}

	for (i = 0; i < cities; i++) {
        OK = YAH;
        ways[cities-level] = i;
        for(j = 0 ; j < cities-level ; j++){
            OK = ways[j] == i ? NO : YAH;
            OK = ways[0] == 0 ? YAH : NO;
        }

        if( OK )
            Travelling_Problem(level-1,cities,ways,coordinates);
	}
}

void Travelling_Sales(double **coordinates, int cities){
// - FUNÇÃO: Travelling_Sales()
// Responsavel por realizar todo o processo de descoberta da menor
//distancia de viagem entre as cidades entradas...
    int *ways = (int *)calloc(cities,sizeof(int));
        Travelling_Problem(cities,cities,ways,coordinates);

    free(ways);

    return;
}

double **readN(int consumidores){
// - FUNÇÃO: readN()
// Responsavel por ler as coordenadas de cada cidade e armazena-las em
//uma "tabela"...
    double **coord = (double **)malloc(sizeof(double *)*consumidores);
    double x, y;
    int i;
    for( i = 0 ; i < consumidores ; i++ ){
        coord[i] = (double *)malloc(sizeof(double)*2);
        scanf("%lf %lf",&x,&y);
        coord[i][0] = x;
        coord[i][1] = y;
        fflush(stdin);
    }

    return coord;
}

int main (int argc, char **argv){
//                  CARTEIRO VIAJANTE
//1) Inicialmente pede-se ao usuario que entre com um numero que
//representa a quantidade de cidades/consumidores os quais pre_
//cisa-se realizar algumas entregas...
    int consumers;
    scanf("%d",&consumers);
        //Depois pede-se que o usuario entre com as coordenadas
        //desses consumidores...
        double **coordinates = readN(consumers);

//2) Aqui inicia-se o processo de descoberta da menor distancia
//possivel de viagem para a entrega de todos os produtos a todos
//os consumidores...
        Travelling_Sales(coordinates,consumers);

//3) Ao final do processo, é impresso na tela a menor distancia
//encontrada para realizar esta tarefa de entrega passando por
//todas as cidades/consumidores uma unica vez e retornar a cidade
//de origem...
    printf("%lf",short_dist);

    //liberando posteriormente a memoria alocada para a realização da tarefa
    freeM(coordinates,consumers);

    return 0;
}
