#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

#define DOUBLE_MAX 9999999
#define INT_MAX 99999
#define DIMENSION 4
#define FOUND -1
#define MAXDEPTH 15

// A structure to hold the neccesary parameters
typedef struct{
    char direction;
    int zeroRow, zeroCol;
    intMatrix nmatrix;
    double h;
}node;





// (1)----- PRINT FUNCTIONS -----
//Function that print ona matrix of the cube
void printString(String str){
    for(int  i = 0 ; i < (int)str.size() ; i++){
        cout << str[i];
    }
    return;
}





// (2)----- AUXILIAR FUNCTIONS -----
//Function to find the Manhattan Distance
int hamiltonDistance(intMatrix m, int dimension){
    int distance = 0;
    for(int i = 0 ; i < dimension; i++)
        for(int j = 0; j < dimension; j++)
            if(m[i][j] != ((i*4) + (j+1)) && ((i*4) + (j+1)) != 16)
                distance++;
    return distance;
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
//Function to create a array from a matrix
intVector intMatrix2intVector(intMatrix m, int row, int col){
    intVector array;
    for(int i = 0 ; i < row ; i++)
        for(int j = 0 ; j < col ; j++)
            array.push_back(m[i][j]);
    return array;
}





// (3)----- CHECK FUNCTIONS -----
//Function that verify if the current 15 puzzle set is complete
bool happy15puzzleProblem(intMatrix m, int dimension){
    for(int i = 0 ; i < dimension; i++)
        for(int j = 0; j < dimension; j++)
            if(m[i][j] != ((i*4) + (j+1)) && ((i*4) + (j+1)) != 16)
                return false;
    return true;
}
//Function to count invertion
int getInvCount(intVector array, int N){
    int inv_count = 0;
    for (int i = 0; i < N - 1; i++){
        for (int j = i + 1; j < N; j++){
            if (array[j] && array[i] && array[i] > array[j])
                inv_count++;
        }
    }
    return inv_count;
}
//Function to verify if the puzzle is sovable
bool thisPuzzleIsSovable(intMatrix m, int dimension, int zeroRow){
    // Count inversions in given puzzle
    int invCount = getInvCount(intMatrix2intVector(m,dimension,dimension),dimension*dimension);
 
    // If grid is odd, return true if inversion
    // count is even.
    if(dimension & 1)
        return !(invCount & 1);
    // grid is even
    else{
        if((dimension - zeroRow) & 1)
            return !(invCount & 1);
        else
            return invCount & 1;
    }
}
//Function to verify if a possition is valid in a matrix
bool inBounds(int x, int lower, int upper){
    return (x >= lower) && (x < upper);
}
//Function to verify if the movement is valid
bool validMove(int dir, int i, int j, int n){
    switch(dir){
        case UP:
            if(inBounds(i-1,0,n) && inBounds(j,0,n))
                return true;
            else
                return false;
        case DOWN:
            if(inBounds(i+1,0,n) && inBounds(j,0,n))
                return true;
            else
                return false;
        case RIGHT:
            if(inBounds(i,0,n) && inBounds(j+1,0,n))
                return true;
            else    
                return false;
        case LEFT:
            if(inBounds(i,0,n) && inBounds(j-1,0,n))
                return true;
            else
                return false;
    }
    return false;
}





// (4)----- 15-TILE PROBLEM FUNCTIONS -----
int dirInverse(int dir){
    if(dir == NONE)
        return ' ';
    else if(dir == UP)
        return DOWN;
    else if(dir == DOWN)
        return UP;
    else if(dir == LEFT)
        return RIGHT;
    else
        return DOWN;
}
char dirChar(int dir){
    if(dir == NONE)
        return ' ';
    else if(dir == UP)
        return 'U';
    else if(dir == DOWN)
        return 'D';
    else if(dir == LEFT)
        return 'L';
    else
        return 'R';
}
//Function to calculate the tile cost in 15 tile puzzle
int manhattanDistance(intMatrix m, int dimension){
    int cost = 0, row = 0 , col = 0, tile;
    //1. MANHATTAN DISTANCE
    for(tile = 1 ; tile < 16 ; tile++){
        //a. Finding the tile position...
        for(int i = 0 ; i < dimension ; i++){
            for(int j = 0 ; j < dimension ; j++){
                if(m[i][j] == tile){
                    row = i, col = j;
                    break;
                }
            }
        }
        
        //b. Finding the correct position of tile...
        int correctRow = 0, correctCol = 0;
        for(int i = 0 ; i < dimension ; i++){
            for(int j = 0 ; j < dimension ; j++){
                if((i*4)+(j+1) == tile){
                    correctRow = i, correctCol = j;
                    break;
                }
            }
        }
        
        //c. Calculating the cost by the minimal move to reach correct
        //position in 15-puzzle...
        cost += (abs(correctRow - row) + abs(correctCol - col));
    }
    
    //d. Returning the cost...
    return cost;
}
//Function to calculate the tile cost in 15 tile puzzle
int getCost(intMatrix m, int dimension, int tile){
    int cost = 0, row = 0 , col = 0;
    //1. HAMILTON DISTANCE
    //a. Finding the tile position...
    for(int i = 0 ; i < dimension ; i++){
        for(int j = 0 ; j < dimension ; j++){
            if(m[i][j] == tile){
                row = i, col = j;
                break;
            }
        }
    }
    
    //b. Finding the correct position of tile...
    int correctRow = 0, correctCol = 0;
    for(int i = 0 ; i < dimension ; i++){
        for(int j = 0 ; j < dimension ; j++){
            if((i*4)+(j+1) == tile){
                correctRow = i, correctCol = j;
                break;
            }
        }
    }
    
    //c. Calculating cost
    cost = (correctRow == row && correctCol == col)?(0):(1);
    
    //d. Returning the cost...
    return cost;
}
//Function to move and create a new node...
node move(node n, int dir){
    int aux, i = n.zeroRow, j = n.zeroCol;
    intMatrix m = n.nmatrix;
    double newh;
    node result;
    switch(dir){
        case UP:
            //a. Calculating the new values...
            aux = m[i][j];
            m[i][j] = m[i-1][j];
            m[i-1][j] = aux;
            newh = hamiltonDistance(m,DIMENSION);
                
            //b. Creating the new node...
            result.direction = 'U';
            result.zeroRow = i-1;
            result.zeroCol = j;
            result.nmatrix = m;
            result.h = newh;
        break;
        case DOWN:
            //a. Calculating the new values...
            aux = m[i][j];
            m[i][j] = m[i+1][j];
            m[i+1][j] = aux;
            newh = hamiltonDistance(m,DIMENSION);
                
            //b. Creating the new node...
            result.direction = 'D';
            result.zeroRow = i+1;
            result.zeroCol = j;
            result.nmatrix = m;
            result.h = newh;
        break;
        case RIGHT:
            //a. Calculating the new values...
            aux = m[i][j];
            m[i][j] = m[i][j+1];
            m[i][j+1] = aux;
            newh = hamiltonDistance(m,DIMENSION);
                
            //b. Creating the new node...
            result.direction = 'R';
            result.zeroRow = i;
            result.zeroCol = j+1;
            result.nmatrix = m;
            result.h = newh;
        break;
        case LEFT:
            //a. Calculating the new values...
            aux = m[i][j];
            m[i][j] = m[i][j-1];
            m[i][j-1] = aux;
            newh = hamiltonDistance(m,DIMENSION);
                
            //b. Creating the new node...
            result.direction = 'L';
            result.zeroRow = i;
            result.zeroCol = j-1;
            result.nmatrix = m;
            result.h = newh;
        break;
    }   
    return result;
}

//Function that verify all posibilities to solve 15 puzzle problem
double IDAStarSearch(node n, int g, int threshold, String moves){
    double f = g + n.h;
    
    //1. Verifying the heristic value...
    if( f > threshold)
        return f;
    
    //2. Verifying if this is a solution...
    if(happy15puzzleProblem(n.nmatrix,DIMENSION)){
        printString(moves);
        return FOUND;
    }
    
    //3. Moving the pieces trying to find a solution...
    int min = INT_MAX;
    for(int dir = 0 ; dir < DIMENSION ; dir++){
        //a. Verifiyng if the actual direction is valid and the movement dont back to an
        //past stage...
        if(validMove(dir,n.zeroRow,n.zeroCol,DIMENSION) && n.direction != dirInverse(dir)){
            //i. Creating the next node...
            node tempnode = move(n,dir);
                moves.push_back(dirChar(dir)); //move
                
            //ii. Recursive call with next node as current node for depth search
            int temp = IDAStarSearch(tempnode,g+1,threshold,moves);  
            
            //iii. If the movement make the puzzle solved, return to main...
            if(temp == FOUND)            
                return FOUND;
            
            //iv. If the puzzle is not solved, verify if the heuristic still safe...
            if(temp < min)                            
                min = temp;
            
                moves.pop_back(); //unmove
        }
    }
    
    //4. Return the minimum ‘f’ encountered greater than threshold
    return min;
}
//Function to solve the 15-puzzle problem
bool solve15puzzleProblem(intMatrix m, int dimension){
    //1. Finding the zero...
    int zeroRow = -1, zeroCol = -1;
    findRowAndCol(m,dimension,0,&zeroRow,&zeroCol);
    
    //2. Verifying if the puzzle is solvable...
    //- if is... trying to solve.
    //- else print on screen that it is a now solvable puzzle...
    double f = 50;
    if(thisPuzzleIsSovable(m,dimension,zeroRow)){
        
        //a. Calculating the start heuristic to problem h(n)...
        int heuristic = hamiltonDistance(m,dimension);
        
        //b. creating the start node...
        node start;
            start.direction = NONE;
            start.zeroRow = zeroRow;
            start.zeroCol = zeroCol;
            start.nmatrix = m;
            start.h = heuristic;
        
        //c. Trying to solve the puzzle
        while(f != FOUND && heuristic <= MAXDEPTH){
            //i. IDAStar running...
            f = IDAStarSearch(start,0,heuristic,String());
            
            //ii. ManhattanDistance calculation...
            int mdist = manhattanDistance(start.nmatrix,DIMENSION);
            
            //iii. Heuristic redefinition...
            heuristic = (mdist < MAXDEPTH && mdist != heuristic)?(mdist):(MAXDEPTH);
        }
    }
    
    //3. Returning the result...
    return (f == FOUND)?(true):(false);
}






// (5)----- MAIN -----
int main(){
    clock_t start, end;
    //1. Reading the number N of sets of puzzle to be played...
    int N;
    cin >> N;
    
    //2. Reading the N puzzle sets...
    intCube puzzleSet(N);
    for(int i = 0 ; i < N ; i++){
        puzzleSet[i] = intMatrix(DIMENSION);
        for(int row = 0 ; row < DIMENSION ; row++){
            puzzleSet[i][row] = intVector(DIMENSION,0);
            for(int col = 0 ; col < DIMENSION ; col++){
                cin >> puzzleSet[i][row][col];
            }
        }
    }
    
    //3. Solving the 15-puzzle problem to N puzzles sets...
    for(int n = 0 ; n < N ; n++){
        start = clock();
       //a. solving the puzzle...
       bool result = solve15puzzleProblem(puzzleSet[n],DIMENSION);
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