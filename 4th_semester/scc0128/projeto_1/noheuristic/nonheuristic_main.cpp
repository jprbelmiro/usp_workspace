#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;
typedef vector<int> intVector;
typedef vector<intVector> intMatrix;
typedef vector<intMatrix> intCube;
typedef vector<char> String;


enum{
  NONE = -1,
  RIGHT,
  LEFT,
  UP,
  DOWN
};

#define ZEROISHERE(X) (X==0)?(true):(false)
#define MAXDEPTH 20

//Function that print ona matrix of the cube
void printString(String str){
    for(int  i = 0 ; i < (int)str.size() ; i++){
        cout << str[i];
    }
    return;
}

//Function that print ona matrix of the cube
void printIntMatrix(intMatrix m, int nrow, int ncol){
    for(int i = 0 ; i < nrow ; i++){
        for(int  j = 0 ; j < ncol ; j++){
            cout << m[i][j] << " ";
        }cout << endl;
    }
    return;
}

//Function that print the entire cube
void printCube(intCube cube, int N, int nrow, int ncol){
    for(int i = 0; i < N; i ++){
        printIntMatrix(cube[i], nrow, ncol);
    }
    return;
}

//Function to find the row and col of an element in a matrix
void findRowAndCol(intMatrix m, int dimension, int elem, int *row, int *col){
    for(int i = 0 ; i < dimension ; i++){
        for(int j = 0 ; j < dimension ; j++){
            if(m[i][j] == elem){
                *row = i, *col = j;
                return;
            }
        }
    }
    return;
}

//Function that verify if the actual 15 puzzle set is complete
bool happy15puzzleProblem(intMatrix m, int dimension){
    for(int i = 0 ; i < dimension; i++)
        for(int j = 0; j < dimension; j++)
            if(m[i][j] != ((i*4) + (j+1)) && ((i*4) + (j+1)) != 16)
                return false;
    return true;
}

//Function that verify all posibilities to solve 15 puzzle problem
bool solve15puzzleProblemRecursion(intMatrix m, int dimension, int zeroRow, int zeroCol, int past, String moves){
    if(happy15puzzleProblem(m,dimension) || (int)moves.size() == MAXDEPTH){
        if((int)moves.size() < 15){
            printString(moves);
            return true;
        }
        return false;
    }
    
    for(int direction = 0 ; direction < 4 ; direction++){
        switch(direction){
            case RIGHT:
                if(zeroCol < dimension-1 && past != LEFT){
                    m[zeroRow][zeroCol] = m[zeroRow][zeroCol+1];
                    m[zeroRow][zeroCol+1] = 0;
                    moves.push_back('R');
                    if (solve15puzzleProblemRecursion(m,dimension,zeroRow,zeroCol+1,RIGHT,moves)) return true;
                    moves.pop_back();
                    m[zeroRow][zeroCol+1] = m[zeroRow][zeroCol];
                    m[zeroRow][zeroCol] = 0;
                }
            break;
            case LEFT:
                if(zeroCol > 0 && past != RIGHT){
                    m[zeroRow][zeroCol] = m[zeroRow][zeroCol-1];
                    m[zeroRow][zeroCol-1] = 0;
                    moves.push_back('L');
                    if (solve15puzzleProblemRecursion(m,dimension,zeroRow,zeroCol-1,LEFT,moves)) return true;
                    moves.pop_back();
                    m[zeroRow][zeroCol-1] = m[zeroRow][zeroCol];
                    m[zeroRow][zeroCol] = 0;
                }
            break;
            case UP:
                if(zeroRow > 0 && past != DOWN){
                    m[zeroRow][zeroCol] = m[zeroRow-1][zeroCol];
                    m[zeroRow-1][zeroCol] = 0;
                    moves.push_back('U');
                    if (solve15puzzleProblemRecursion(m,dimension,zeroRow-1,zeroCol,UP,moves)) return true;
                    moves.pop_back();
                    m[zeroRow-1][zeroCol] = m[zeroRow][zeroCol];
                    m[zeroRow][zeroCol] = 0;
                }
            break;
            case DOWN:
                if(zeroRow < dimension-1 && past != UP){
                    m[zeroRow][zeroCol] = m[zeroRow+1][zeroCol];
                    m[zeroRow+1][zeroCol] = 0;
                    moves.push_back('D');
                    if (solve15puzzleProblemRecursion(m,dimension,zeroRow+1,zeroCol,DOWN,moves)) return true;
                    moves.pop_back();
                    m[zeroRow+1][zeroCol] = m[zeroRow][zeroCol];
                    m[zeroRow][zeroCol] = 0;
                }
            break;
            
        }
    }
    
    return false;
}

//Function to solve the 15-puzzle problem
bool solve15puzzleProblem(intMatrix m, int dimension){
    //1. Finding the zero...
    int zeroRow = -1, zeroCol = -1;
    findRowAndCol(m,dimension,0,&zeroRow,&zeroCol);
    
    //2. Trying to solve the puzzle...
    bool solvable_flag = solve15puzzleProblemRecursion(m,dimension,zeroRow,zeroCol,NONE,String());
    
    //3. Returning the result...
    return solvable_flag;
}

int main(){
    clock_t start, end;
    //1. Reading the number N of sets of puzzle to be played...
    int N;
    cin >> N;
    
    //2. Reading the N puzzle sets...
    intCube puzzleSet(N);
    for(int i = 0 ; i < N ; i++){
        puzzleSet[i] = intMatrix(4);
        for(int row = 0 ; row < 4 ; row++){
            puzzleSet[i][row] = intVector(4,0);
            for(int col = 0 ; col < 4 ; col++){
                cin >> puzzleSet[i][row][col];
            }
        }
    }
    
    //3. Solving the 15-puzzle problem to N puzzles sets...
    for(int n = 0 ; n < N ; n++){
        start = clock();
       //a. solving the puzzle...
       bool result = solve15puzzleProblem(puzzleSet[n],4);
       end = clock();
       
       //b. printing result...
        if(result)
            cout << " - Execution Time: " << (end-start)/CLOCKS_PER_SEC << "s = " << (end-start) << " clocks."<< endl;
        else
            cout << "This puzzle is not solvable.\n";
    }
    
    //4. Thats all folks :)...
    return 0;
}