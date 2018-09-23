#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rbn.h"

static void printRecursiveRBN(t_rbdigit *digit){
    if(digit->next != NULL){
        printf("%hd",digit->digit);
        return printRecursiveRBN(digit->next);
    }
    printf("%hd\n",digit->digit);
    return;
}

void printRealyBigNum(t_rbn *number){
    if(number->negative)
        printf("-");
    printRecursiveRBN(number->big_endian);
    return;    
}

void removeDigit(t_rbdigit **digit, int position){
    if(position == 0){
        t_rbdigit *next = (*digit)->next;
        free(*digit);
        *digit = next;
        return;
    }
    return removeDigit(&((*digit)->next),position-1);
}

void destroyRealyBigNum(t_rbn *number){
    int i = 0;
    
    for(i = 0 ; i < number->ndigits ; i++){
        removeDigit(&(number->big_endian),0);
        removeDigit(&(number->little_endian),0);
    }
    free(number);
    return;
}

short getDigit(t_rbdigit **father_digit, int position){
    if(position != 0)
        return getDigit(&((*father_digit)->next),position-1);
    return (*father_digit)->digit;
}

static t_rbdigit *createDigit(short digit, int idx){
    t_rbdigit *newdigit = NULL;
    newdigit = (t_rbdigit *)malloc(sizeof(t_rbdigit));
    newdigit->digit = digit;
    newdigit->idx = idx;
    newdigit->next = NULL;
    return newdigit;
}

static void faddDigit(t_rbdigit **father_digit, short digit, int position ){
    if(position != 0)
        return faddDigit(&((*father_digit)->next),digit,position-1);
    
    t_rbdigit *next = NULL;
    if((*father_digit) != NULL){
        next = (*father_digit);
        *father_digit = createDigit(digit,position);
        (*father_digit)->next = next;
    }
    else
        *father_digit = createDigit(digit,position);
    return;
}

void addDigit(t_rbn **number, short digit){
    faddDigit(&((*number)->little_endian),digit,0);
    faddDigit(&((*number)->big_endian),digit,(*number)->ndigits);
    (*number)->ndigits += 1;
    return;
}

t_rbn *createRealyBigNum(){
    t_rbn *number = NULL;
    number = (t_rbn *)malloc(sizeof(t_rbn));
        number->ndigits = 0;
        number->negative = FALSE;
        number->big_endian = NULL;
        number->little_endian = NULL;
    return number;
}

t_rbn *readRealyBigNum(FILE *inputfile, char delim){
    //0. Variables...
    int i = 0;
    char *string = NULL;
    t_rbn *number = NULL;
    
    //1. Reading the number from imputfile...
    while(string == NULL){
        string = readLine(inputfile,delim);
        
        if(!isanumber(string)){
            free(string);
            string = NULL;
        }
    }
    
    //3. Creating a realy big number...
    number = createRealyBigNum();
    if(string[i] == '-'){
        number->negative = TRUE;
        i+=1;
    }
    for(i = i ; i < strlen(string) ; i++)
        addDigit(&number,digittoshort(string[i]));
    
    //4. Freeing used memory and returning...
    free_(string);
    return number;
}