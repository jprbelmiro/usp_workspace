#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

int main ( int argc, char **argv ){
    //0. Variable...
    int L = 0, nmtrks = 0, size = 0, *mtrks = NULL;
    
    //1. Reading the L cases of Matrioska Creation...
    scanf("%d%*c",&L);
    
    //2. Searching for the solution in these L cases..
    while(L-- > 0){
        //a. Reading the case...
        mtrks = readingCase(&size);

        //b. Validating the Matrioska case...
        nmtrks = 0;
        if(mtrks != NULL)
            nmtrks = validateMatrioskas(mtrks,size);
            
        //c. Printing the result...
        if(nmtrks != 0)
            printf("=) Matrioska %d\n",nmtrks);
        else
            printf("=( Tente novamente\n");
        
        //d. Freeing the used case...
        free(mtrks);
    }
    
    //3. Thats all folks ;)...
    return 0;
}