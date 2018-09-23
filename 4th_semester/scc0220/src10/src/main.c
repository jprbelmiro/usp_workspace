#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

void markLeafNodes(boolean **tree, int curnode, int nnodes, int mark){
    if((2*curnode + 1) >= nnodes){
        (*tree)[curnode] = mark;
        return;
    }
    
    markLeafNodes(tree,2*curnode + 1,nnodes,mark);
    markLeafNodes(tree,2*(curnode+1),nnodes,mark);
    return;
}

int throwTheBall(boolean **tree, int curnode){
    if((*tree)[curnode] == FALSE){
        (*tree)[curnode] = TRUE;
        return throwTheBall(tree,2*curnode+1);
    }
    else if((*tree)[curnode] == TRUE){
        (*tree)[curnode] = FALSE;
        return throwTheBall(tree,2*(curnode+1));
    }
    return curnode+1;
}

int main ( int argc, char **argv ){
    //0. Variable...
    int theight = 0, nballs = 0, result = 0;
    boolean *tree = NULL;

    //1. Reading the height of the tree and the 
    //number of balls...
    scanf("%d%*c%d%*c",&theight,&nballs);
    
    //2. Building the binary tree and marking the leafnodes...
    tree = (boolean *)calloc((pow(2,theight)-1),sizeof(boolean));
    markLeafNodes(&tree,0,(pow(2,theight)-1),-1);
    
    //3. Throwing the nballs in binary tree...
    while(nballs-- > 0)
        result = throwTheBall(&tree,0);

    //4. Printing the result...
    printf("%d\n",result);
    
    //5. Freeing the used memory...
    free_(tree);
    
    //6. Thats all folks ;)...
    return 0;
}