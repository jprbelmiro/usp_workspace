#include <stdlib.h>
#include <stdio.h>

#define block 0
#define freeWay 1

//FREEMATRIX - Funcao responsavel por liberar uma matriz qualquer da memoria...
void freeMatrix(void **matrix, int n){
    int i = 0;
    for(i = 0 ; i < n ; i++)
        if(matrix[i])
            free(matrix[i]);
    if(matrix)
        free(matrix);
    return;
}

//FILLINTMATRIX - Funcao responsavel por preencher uma matriz de tamanho rowxcol
//com valores entrados pelo usuario (teclado/stdin)...
void fillIntMatrix(int row, int col, int ***matrix){
    int i, j;
    for(i = 0 ; i < row ; i++)
        for(j = 0 ; j < col ; j++)
            scanf("%d%*c",&((*matrix)[i][j]));
    return;
}

//ALLOCINTMATRIX - Funcao responsavel por alocar uma matriz de inteiros na 
//memoria de tamanho rowxcol...
int **allocIntMatrix(int row, int col){
    int i, **matrix = (int **)malloc(sizeof(int *)*row);
    for(i = 0 ; i < row ; i++)
        matrix[i] = (int *)malloc(sizeof(int)*col);
    return matrix;
}

//SEACHFREEWAY - Funcao responsavel por encontrar o ponto de partida dado uma
//direcao inicial como proposto para este problema...
void searchFreeWay(char mazeDirection, int *xPos, int *yPos, int row, int col, int **maze){
    int i;
    switch(mazeDirection){
        case 'N':
            for(i = 0 ; i < col ; i++){
                if(maze[0][i] == freeWay){
                    *xPos = 0;
                    *yPos = i;
                    break;
                }
            }
        break;
        
        case 'S':
            for(i = 0 ; i < col ; i++){
                if(maze[row-1][i] == freeWay){
                    *xPos = row-1;
                    *yPos = i;
                    break;
                }
            }
        break;
        
        case 'L':
            for(i = 0 ; i < row ; i++){
                if(maze[i][col-1] == freeWay){
                    *xPos = i;
                    *yPos = col-1;
                    break;
                }
            }
        break;
        
        case 'O':
            for(i = 0 ; i < row ; i++){
                if(maze[i][0] == freeWay){
                    *xPos = i;
                    *yPos = 0;
                    break;
                }
            }
        break;
    }
    
    return;
}

//EXISTFREEWAY - Funcao responsavel por contar e retornar o numero de
//caminhos livres dado uma posicao x,y...
int existFreeWay(int xPos, int yPos, int row, int col, int **maze){
    int freeWayCounter = 0;
    if(xPos-1 > 0 && maze[xPos-1][yPos] == freeWay)
        freeWayCounter++;
    if(xPos+1 < row && maze[xPos+1][yPos] == freeWay)
        freeWayCounter++;
    if(yPos-1 > 0 && maze[xPos][yPos-1] == freeWay)
        freeWayCounter++;
    if(yPos+1 < col && maze[xPos][yPos+1] == freeWay)
        freeWayCounter++;
        
    return freeWayCounter;
}

//MAZERUN - Funcao responsavel por percorrer o labirinto proposto neste problema
void mazeRun(int row, int col, int **maze, char mazeEnter, char mazeExit){
    //0. Variaveis...
    int xPos = -1, yPos = -1, xExit = -1, yExit = -1, wayCounter = 0;
    int **intersections = NULL, nIntersections = 0;
    
    //1. Verificando e procurando pela coordenada de entrada...
    searchFreeWay(mazeEnter,&xPos,&yPos,row,col,maze);
    if(xPos == -1 && yPos == -1){
        printf("Nao existe saida %c - %c.",mazeEnter,mazeExit);
        return;
    }
    
    //2. Verificando e procurando pela coordenada de saida...
    searchFreeWay(mazeExit,&xExit,&yExit,row,col,maze);
    if(xExit == -1 && yExit == -1){
        printf("Nao existe saida %c - %c.",mazeEnter,mazeExit);
        return;
    }
    
    //3. Percorrendo a matriz tentando alcancar a saida desejada...
    while((xPos != xExit || yPos != yExit)){
        //a. Bloqueando o caminho ja percorrido...
        maze[xPos][yPos] = block;
        
	    //b. Verificando se existe caminho livre
        wayCounter = existFreeWay(xPos,yPos,row,col,maze);
        if(wayCounter == 0){
            if(nIntersections == 0)
                break;
            else{
                while(nIntersections != 0 && wayCounter == 0){
                    nIntersections--;
                    xPos = intersections[nIntersections][0];
                    yPos = intersections[nIntersections][1];
                    free(intersections[nIntersections]);
                    wayCounter = existFreeWay(xPos,yPos,row,col,maze);
                }
            }
        }

        //c. Caso exista, verificando se a posicao atual
	    //representa uma interseccao de n caminhos diferentes...
	    //- a posicao interseccao e guardada para caso seja
	    //necessário se retornar a ela...
        if(wayCounter > 1){
		    intersections = (int **)realloc(intersections,sizeof(int *)*(nIntersections+1));
		    intersections[nIntersections++] = (int *)malloc(sizeof(int)*2);
		    intersections[nIntersections-1][0] = xPos;
		    intersections[nIntersections-1][1] = yPos;
	    }
		
	    //d. Tomando uma nova direcao...
	    if(xPos-1 > 0 && maze[xPos-1][yPos] == freeWay)
            xPos--;
        else if(xPos+1 < row &&maze[xPos+1][yPos] == freeWay)
            xPos++;
        else if(yPos-1 > 0 && maze[xPos][yPos-1] == freeWay)
            yPos--;
        else if(yPos+1 < col && maze[xPos][yPos+1] == freeWay)
            yPos++;
	    
    }
    
    //4. Verificando se vou morrer congelado ou escapar do labirinto...
    if(xPos == xExit && yPos == yExit)
        printf("Existe saida %c - %c.",mazeEnter,mazeExit);
    else
        printf("Nao existe saida %c - %c.",mazeEnter,mazeExit);
    
    //5. Liberando a memoria usada e retornando para a chamada da funcao...
    freeMatrix((void **)intersections,nIntersections);
    return;
}

//MAIN - Funcao principal do programa...
int main(int argc, char **argv){
    //0. Variaveis
    char mazeEnter, mazeExit;
    int row, col, **maze;
    
    //1. Lendo as entradas para o problema
    //a. Lendo as direcao da entrada e da saida...
    scanf("%c%*c%c%*c",&mazeEnter,&mazeExit);
    
    //b. Lendo o tamanho da matriz e alocando a na
    //memoria...
    scanf("%d%*c%d%*c",&row,&col);
    maze = allocIntMatrix(row,col); 
    
    //2. Lendo os elementos da matriz...
    fillIntMatrix(row,col,&maze);
    
    //3.Percorrendo o labirinto que preciso escapar para nao
    //morrer congelado e imprimindo na tela se tenho chances
    //de viver... :c
    mazeRun(row,col,maze,mazeEnter,mazeExit);
    
    //4. Liberando a memoria usada e encerrando o programa...
    freeMatrix((void **)maze,row);
    return 0;
}