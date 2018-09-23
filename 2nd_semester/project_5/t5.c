#include <stdlib.h>
#include <stdio.h>
#include "t5_basic.h"
#include "t5_maze.h"

//T5 - Maze Runner / Labirinto da Alegria
int main(int argc, char **argv){
    int NP, NC, NS, START;
    float **maze = NULL, **chambers = NULL, **segments = NULL;
    
    //1- Lendo o numero de pontos do labirinto...
    scanf("%d",&NP);
        //- Lendo a coordenada dos NPontos do labirinto [x,y]...
        maze = create_fmatrix(NP,2);
        fill_fmatrix(maze,NP,2);
    
    //2- Lendo o numero de camaras do labirinto...
    scanf("%d%*c",&NC);
        //- Lendo o ponto em que existe uma camera e se esta esta ativa ou nao
        //para as NCameras do labirinto [ponto,nao ativo(0)/ativo(1)]...
        chambers = create_fmatrix(NC,2);
        fill_fmatrix(chambers,NC,2);
    
    //3- Lendo o numero de segmentos do labirinto...
    scanf("%d%*c",&NS);
        //- Lendo o ponto de partida e de destino para todos os NSegmentos do labirinto
        // [ponto part, ponto dest]...
        segments = create_fmatrix(NS,2);
        fill_fmatrix(segments,NS,2);  
        
    //4- Lendo o indice da camera de inicio...
    scanf("%d%*c",&START);
    
    //5- Iniciando a resolucao da labirinto e imprimindo as respostas finais...
    maze_runner(maze,chambers,segments,NP,NC,NS,START);
    
    //6- Liberando a memoria utilizada...
    free_matrix((void **)maze,NP);
    free_matrix((void **)chambers,NC);
    free_matrix((void **)segments,NS);
    
    return 0;
}
