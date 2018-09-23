#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include "tree.h"

int countBlackPixels(t_node *fnode, t_node *snode, int order){
    if(!fnode || !snode)
        return 0;
    if(ISBLACK(fnode->elem,snode->elem))
        return (1024/(int)(pow(4,(MAX(fnode->level,snode->level)))));

    //. Recursive count...
    int i, nblackpoints = 0;
    for(i = 0 ; i < order ; i++)
        if(fnode->child && snode->child)
            nblackpoints += countBlackPixels(fnode->child[i],snode->child[i],order);
        else if(fnode->child)
            nblackpoints += countBlackPixels(fnode->child[i],snode,order);
        else if(snode->child)
            nblackpoints += countBlackPixels(fnode,snode->child[i],order);
    //. Computing...
    return nblackpoints;
}

int main ( int argc, char **argv ){
    //0. Variable...
    int testCase = 0, N = 0, blackPixels = 0;
    string firstImg = NULL, secondImg = NULL;
    t_tree *firstTree = NULL, *secondTree = NULL;
    
    //1. Reading the number of test cases...
    scanf("%d%*c",&N);
    
    //2. Solving the N test cases...
    for(testCase = 1 ; testCase <= N ; testCase++){
        //a. Reading the Pedro's images...
        firstImg = readLine(stdin,'\n');
        secondImg = readLine(stdin,'\n');
        
        //b. Building the trees...
        firstTree = buildupTree(firstImg,4);
        secondTree = buildupTree(secondImg,4);
        
        //c. Counting the number of black pixels...
        blackPixels = countBlackPixels(firstTree->root,secondTree->root,firstTree->order);
        
        //d. Printing the result...
        printf("%d %d pixels pretos.",testCase, blackPixels);
        if(testCase != N)
            printf("\n");
            
        //e. Destroying trees and img...
        free_(firstImg);
        free_(secondImg);
        destroyTree(firstTree);
        destroyTree(secondTree);
    }
    
    //3. Thats all folks ;)...
    return 0;
}