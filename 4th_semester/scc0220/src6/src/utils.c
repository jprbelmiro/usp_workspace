#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"

int validateMatrioskas(int *mtrsk, int size){
    int i = 1, counter = 0, result = 0;
    int *mtrsksize = NULL;
    
    //1. Verifying the number of Matrioskas can be build...
    mtrsksize = (int *)realloc(mtrsksize,sizeof(int)*(counter+1));
    mtrsksize[counter] = mtrsk[0];
    while(i < size){
        if(mtrsksize){
            if(abs(mtrsksize[counter]) == abs(mtrsk[i])){
                counter--;
                if(counter == -1){
                    free(mtrsksize);
                    mtrsksize = NULL;
                }
            }
            else if(mtrsk[i] < mtrsk[i-1] && mtrsk[i-1] > 0 && mtrsk[i] < 0){
                counter++;
                result++;
                mtrsksize = (int *)realloc(mtrsksize,sizeof(int)*(counter+1));
                mtrsksize[counter] = mtrsk[i];
            }
            else if(mtrsk[i] < mtrsk[i-1] && mtrsk[i-1] < 0 && mtrsk[i] < 0){
                free(mtrsksize);
                return 0;
            }
            else if(abs(mtrsksize[counter]) < abs(mtrsk[i])){
                free(mtrsksize);
                return 0;
            }
        }
        else{
            counter++;
            result++;
            mtrsksize = (int *)realloc(mtrsksize,sizeof(int)*(counter+1));
            mtrsksize[counter] = mtrsk[i];
        }
        i++;
    }
    
    return result+1;
}

int *readingCase(int *size){
    //1. Creating dll...
    *size = 0;
    int *mtrks = NULL;
    
    //2. Building up the dll and verifying if exist any chance
    //for this case be an sucess case...
    int number = 1, sum = 0;
    while(scanf("%d%*c",&number) != 0 && number != 0){
        sum += number;
        mtrks = (int *)realloc(mtrks,sizeof(int)*((*size)+1));
        mtrks[(*size)++] = number;
    }
    
    //3. Returning the dll...
    if(sum != 0){
        free(mtrks);
        *size = 0;
        return NULL;
    }
    return mtrks;
}