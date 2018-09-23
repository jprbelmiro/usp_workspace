#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#define TABLE_DIMENSION 5

boolean validMove(int row, int col, int size){
    if(row < 0 || row >= size)
        return FALSE;
    if(col < 0 || col >= size)
        return FALSE;
    return TRUE;
}

void slidingPuzzlePosition(int *currow,int *curcol, char **table, int size){
    int i = 0, j = 0;
    for(i = 0 ; i < size ; i++)
        for(j = 0 ; j < size ; j++)
            if(table[i][j] == ' '){
                *currow = i;
                *curcol = j;
                return;
            }
    *currow = -1;
    *curcol = -1;
    return;
}

boolean slidingPuzzleMove(char ***table, int size, char move){
    int currow, curcol;
    
    //1. Defining the curent row and col...
    slidingPuzzlePosition(&currow,&curcol,*table,size);
    
    //2. Moving...
    switch(move){
        case 'A':
            //Move Up...
            if(validMove(currow-1,curcol,TABLE_DIMENSION)){
                (*table)[currow][curcol] =  (*table)[currow-1][curcol];
                (*table)[currow-1][curcol] =  ' ';
                return TRUE;
            }
        break;
        case 'B':
            //Move Down...
            if(validMove(currow+1,curcol,TABLE_DIMENSION)){
                (*table)[currow][curcol] =  (*table)[currow+1][curcol];
                (*table)[currow+1][curcol] =  ' ';
                return TRUE;
            }
        break;
        case 'R':
            //Move Right...
            if(validMove(currow,curcol+1,TABLE_DIMENSION)){
                (*table)[currow][curcol] =  (*table)[currow][curcol+1];
                (*table)[currow][curcol+1] =  ' ';
                return TRUE;
            }
        break;
        case 'L':
            //Move Left...
            if(validMove(currow,curcol-1,TABLE_DIMENSION)){
                (*table)[currow][curcol] =  (*table)[currow][curcol-1];
                (*table)[currow][curcol-1] =  ' ';
                return TRUE;
            }
        break;
        default:
            return TRUE;
        break;
    }
    return FALSE;
}

int main ( int argc, char **argv ){
    //0. Variable...
    int i, j;
    char move = ' ';
    char **table = NULL;
    boolean puzzle_flag = TRUE;
    
    //1. Creating the slide puzzle table...
    table = createCharMatrix(TABLE_DIMENSION,TABLE_DIMENSION);
    
    //2. Reading the matrix elements...
    for(i = 0 ; i < TABLE_DIMENSION ; i++){
        for(j = 0 ; j < TABLE_DIMENSION ; j++){
            scanf("%c",&(table[i][j]));
            if(table[i][j] == '\n'){
                ungetc(table[i][j],stdin);
                table[i][j] = ' ';
            }
        }fgetc(stdin);fgetc(stdin);
    }
    
    //3. Moving the tiles in sliding puzzle table...
    while(scanf("%c",&move) > 0 && move != 'X' && puzzle_flag)
        puzzle_flag = slidingPuzzleMove(&table,TABLE_DIMENSION,move);
    
    //4. Printing the result...
    if(puzzle_flag)
        printCharMatrix(table,TABLE_DIMENSION,TABLE_DIMENSION);
    else
        printf("This puzzle has no final configuration.\n");
        
    //5. Freeing the used memory...
    freeMatrix((void **)table,TABLE_DIMENSION);
    
    //. Thats all folks ;)...
    return 0;
}