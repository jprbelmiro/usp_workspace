#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> chessBoard;

void printBoard(chessBoard board, int dimension){
    for(int i = 0 ; i < dimension ; i++){
        for(int j = 0 ; j < dimension ; j++){
            cout << board[i][j] << " ";
        }cout << endl;
    }cout << endl;
    return;
}

bool killerQueen(int qrow, int qcol, chessBoard board, int dimension){
    //1. Checking the row victims...
    for(int i = 0 ; i < dimension ; i++)
        if(board[qrow][i] == 1 && i != qcol)
            return true;
    
    //2. Checking the col victims...
    for(int i = 0 ; i < dimension ; i++)
        if(board[i][qcol] == 1 && i != qrow)
            return true;
    
    //3. Checking the primary diag victims...
    for(int i = qrow+1, j = qcol+1 ; i < dimension && j < dimension ; i++, j++)
        if(board[i][j] == 1)
            return true;
    for(int i = qrow-1, j = qcol-1 ; i >= 0 && j >= 0; i--, j--)
        if(board[i][j] == 1)
            return true;
                
    //4. Checking the secoundary diag victims..
    //3. Checking the primary diag victims...
    for(int i = qrow+1, j = qcol-1 ; i < dimension && j >= 0; i++, j--)
        if(board[i][j] == 1)
            return true;
    for(int i = qrow-1, j = qcol+1; i >= 0 && j < dimension ; i--, j++)
        if(board[i][j] == 1)
            return true;    
                
    //5. Not a killer queen...
    return false;
}

bool happyBoard(chessBoard board, int dimension){
    for(int i = 0 ; i < dimension ; i++)
        for(int j = 0 ; j < dimension ; j++)
            if(board[i][j] == 1 && killerQueen(i,j,board,dimension))
                    return false;
    return true;
}

int queenRow(chessBoard board, int col, int dimension){
    for(int i = 0 ; i < dimension ; i++)
        if(board[i][col] == 1)
            return i;
    return -1;
}

int compareWithSolutions(chessBoard board, vector<chessBoard> solutions, int dimension){
    int moves = 0, result = 8;
    for(int n = 0 ; n < (int) solutions.size() ; n++){
        moves = 0;
        for(int i = 0 ; i < dimension ; i++)
                if(queenRow(solutions[n],i,dimension) != queenRow(board,i,dimension))
                    moves++;
        
        if(result > moves)
            result = moves;
    }
    
    return result;
}

void eightQueensProblem(chessBoard board, vector<chessBoard> *solutions, int dimension, int col){
    if(!happyBoard(board,dimension))
        return;
    else if(col == 8){
        (*solutions).push_back(board);
        return;
    }
        
    for(int i = 0 ; i < dimension ; i++){
        board[i][col] = 1;
        eightQueensProblem(board,solutions,dimension,col+1);
        board[i][col] = 0;
    }
    return;
}

chessBoard readBoard(int dimension){
    int row;
    chessBoard board(8);
    for(int i = 0 ; i < dimension ; i++){
        board[i] = vi(8,0);
    }
    for(int i = 0 ; i < dimension ; i++){
        scanf("%d%*c",&row);
        board[row-1][i] = 1;
    }
    return board;
}

chessBoard createBoard(int dimension){
    chessBoard board(dimension);
    for(int i = 0 ; i < dimension ; i++)
        board[i] = vi(dimension,0);
    return board;
}

int main(){
    //1. Searchig for all solution to eight queens problem...
    vector<chessBoard> solutions;
    eightQueensProblem(createBoard(8),&solutions,8,0);

    //2. Comparing all solutions to find the minimal moves necessaries to
    //solve the problem...
    char c;
    int n = 1;
    while(!feof(stdin) && scanf("%c",&c) != EOF){
        ungetc(c,stdin);
        
        //a. Reading the start board...
        chessBoard startboard = readBoard(8);
        
        //b. Comparing the start board with the solutions
        //to find minimal moves...
        int moves = compareWithSolutions(startboard,solutions, 8);
    
        //c. Printing the result...
        cout << "Case " << n++ << ": " << moves << endl;
        
        //d. Clean the board...
        startboard.clear();
    }
    
    //3. Thats all folks :)...
    return 0;
}