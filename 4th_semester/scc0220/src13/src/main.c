#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "sort.h"
#include "match.h"

void printvector(int *vector,int N){
    int i = 0;
    for(i = 0 ; i < N ; i++)
        printf("%d ",vector[i]);
    printf("\n");
}

int main ( int argc, char **argv ){
    //0. Variable...
    int i = 0, O = 0, N = 0, *vector = NULL, *C = NULL, *M = NULL;
    char **algorithm = NULL;
    
    //1. Reading the number of algorithms O and the size
    //of vector...
    scanf("%d%*c%d%*c%*c",&O,&N);
    
    //2. Reading the name of O algorithms...
    algorithm = readWords(O,stdin,' ');
    
    //3. Reading the inputvec...
    vector = readIntVector(N);
    
    //4. Realizing the requested sort...
    C = (int *)calloc(O,sizeof(int));
    M = (int *)calloc(O,sizeof(int));
    for(i = 0 ; i < O ; i++){
        int *auxvec = copyIntVec(vector,N);
        
        if(match(algorithm[i],"^\\s*BUBBLESORT\\s*$"))
            bubblesort(auxvec,N,&(C[i]),&(M[i]));
        else if(match(algorithm[i],"^\\s*INSERTIONSORT\\s*$"))
            insertionsort(auxvec,N,&(C[i]),&(M[i]));
        else if(match(algorithm[i],"^\\s*MERGESORT\\s*$"))
            mergesort(auxvec,0,N-1,&(C[i]),&(M[i]));
        else if(match(algorithm[i],"^\\s*HEAPSORT\\s*$"))
            heapsort(auxvec,N,&(C[i]),&(M[i]));  
        else if(match(algorithm[i],"^\\s*QUICKSORT\\s*$"))
            quicksort(auxvec,0,N-1,&(C[i]),&(M[i]));  
            
        free_(auxvec);
    }

    //5. Printing result...
    int min = C[0], max = C[0], mini = 0, maxi = 0;
    //a. Min C and Max C...
    for(i = 1 ; i < O ; i++){
       if(min > C[i]){
           min = C[i];
           mini = i;
       }
       if(max < C[i]){
           max = C[i];
           maxi = i;
       }
    }
    printf("Menor C: %s\nMaior C: %s\n",algorithm[mini],algorithm[maxi]);
    
    //b. Min M and Max M...
    min = M[0], max = M[0], mini = 0, maxi = 0;
    for(i = 1 ; i < O ; i++){
       if(min > M[i]){
           min = M[i];
           mini = i;
       }
       if(max < M[i]){
           max = M[i];
           maxi = i;
       }
    }
    printf("Menor M: %s\nMaior M: %s\n",algorithm[mini],algorithm[maxi]);
    
    //6. Freeing used memory...
    freeMatrix((void **)algorithm,O);
    free_((void *)vector);
    free_(C);
    free_(M);
    
    //7. Thats all folks ;)...
    return 0;
}