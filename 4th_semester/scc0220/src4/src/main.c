#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rbnop.h"

int main(int argc, char **argv){
    //0. Variables...
    char *operation = NULL;
    t_rbn *numberA = NULL, *numberB = NULL, *result = NULL;
    
    //1. Reading the name of desired operation and
    //two numbers to operate...
    operation = readLine(stdin,13);
    numberA = readRealyBigNum(stdin,13);
    numberB = readRealyBigNum(stdin,13);
    
    //2. Operating...
    if(strcmp(operation,"SOMA")==0)
        result = sumRealyBigNumbers(numberA,numberB);
    else if(strcmp(operation,"SUBTRACAO")==0)
        result = subRealyBigNumbers(numberA,numberB);
    else if(strcmp(operation,"MULTIPLICACAO")==0)
        result = multRealyBigNumbers(numberA,numberB);
    else if(strcmp(operation,"DIVISAO")==0)
        result = divRealyBigNumbers(numberA,numberB);
    else
        printf("Invalid operation.\n");
    
    //3. Printing the result...
    if(result)
        printRealyBigNum(result);
    
    //4. Freeing the used memory...
    free_(operation);
    destroyRealyBigNum(numberA);
    destroyRealyBigNum(numberB);
    destroyRealyBigNum(result);
    return 0;
}