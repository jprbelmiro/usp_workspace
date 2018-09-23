/*
*	42 - Tic tac toe
* This program simulates a Tic tac toe game.
*/
#include <stdlib.h>
#include <stdio.h>

#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

int finishgame(int **table, int nrow, int ncol, int gameround){
	if(gameround < 5)
		return 0;
	
	//(1) Row Victory
	if(table[0][0]==table[0][1] && table[0][0]==table[0][2] &&
    table[0][0]*table[0][1]*table[0][2] != 0)
    	return (gameround % 2 != 0)?(PLAYER1):(PLAYER2);

    else if( table[1][0]==table[1][1] && table[1][0]==table[1][2] &&
    table[1][0]*table[1][1]*table[1][2] != 0)
        return (gameround % 2 != 0)?(PLAYER1):(PLAYER2);

    else if(table[2][0]==table[2][1] && table[2][0]==table[2][2] &&
    table[2][0]*table[2][1]*table[2][2] != 0)
		return (gameround % 2 != 0)?(PLAYER1):(PLAYER2);
   
	//(2) Col Victory
    else if(table[0][0]==table[1][0] && table[0][0]==table[2][0] &&
    table[0][0]*table[1][0]*table[2][0] != 0)
        return (gameround % 2 != 0)?(PLAYER1):(PLAYER2);

    else if(table[0][1]==table[1][1] && table[0][1]==table[2][1] &&
    table[0][1]*table[1][1]*table[1][2] != 0)
        return (gameround % 2 != 0)?(PLAYER1):(PLAYER2);
       
    else if(table[0][2]==table[1][2] && table[0][2]==table[2][2] &&
    table[0][2]*table[1][2]*table[2][2] != 0)
		return (gameround % 2 != 0)?(PLAYER1):(PLAYER2);

	//(3) Diag Victory
    else if(table[0][0]==table[1][1] && table[0][0]==table[2][2] &&
    table[0][0]*table[1][1]*table[2][2] != 0)
		return (gameround % 2 != 0)?(PLAYER1):(PLAYER2);
   
    else if(table[0][2]==table[1][1] && table[0][2]==table[2][0] &&
    table[0][2]!= 0 && table[1][1]!= 0 && table[2][0] != 0)
		return (gameround % 2 != 0)?(PLAYER1):(PLAYER2);
	
	return 0;
}

void freematrix(void **matrix, int nrow){
	int i;
	for(i = 0 ; i < nrow ; i++)
		free(matrix[i]);
	free(matrix);
	return;
}

void printintmatrix(int **matrix, int nrow, int ncol){
	int i, j;
    for(i = 0 ; i < 3  ; i++){
        for(j = 0 ; j < 3 ; j++){
            printf("%d ",matrix[i][j]);
        }printf("\n");
    }
    return;
}

void initializeintmatrix(int **matrix, int nrow, int ncol, int init){
    int i, j;
    for(i = 0 ; i < nrow  ; i++)
        for(j = 0 ; j < ncol ; j++)
            matrix[i][j] = init;
}

void setintmatrix(int **matrix, int row, int col, int set){
     matrix[row][col] = set;
     return;
}

void createintmatrix(int ***matrix, int nrow, int ncol){
	int i;
	*matrix = (int **)malloc(sizeof(int *)*nrow);
	for(i = 0 ; i < nrow ; i++)
		(*matrix)[i] = malloc(sizeof(int)*ncol);
	return;
}

int main (int argc, char **argv){
	//0. Variables
	int row, col;
    int result = 0, gameround = 0, **table = NULL;

	//1. Initializing the table
	createintmatrix(&table,3,3);
    initializeintmatrix(table,3,3,EMPTY);

	//2. Starting game
	while(!(result = finishgame(table,3,3,gameround)) && gameround < 9){
		//a. advancing round
		gameround++;
		
		//b. play
		scanf("%d %d",&row,&col);
		
		//c. set
		if(gameround % 2)
			setintmatrix(table,row,col,PLAYER1);
		else
			setintmatrix(table,row,col,PLAYER2);
	}
	
	//3. Printing the result
	if(!result)
		printf("empate");
	else
		printf("%d",result);

	//4. Freeing the used memory
	freematrix((void **)table,3);
	
	//5. That's all folks... :)
    return 0;
}
