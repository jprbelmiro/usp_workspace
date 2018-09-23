#include <stdlib.h>
#include <stdio.h>
#include "rbnop.h"

void formatLeftZeroRBN(t_rbn *num){
    while(getDigit(&(num->big_endian),0) == 0 && num->ndigits > 1){
        removeDigit(&(num->big_endian),0);
        removeDigit(&(num->little_endian),num->ndigits-1);
        num->ndigits--;
    }
    return;
}

static void swapRealyBigNumbers(t_rbn **A, t_rbn **B){
    t_rbn *aux = *A;
    *A = *B;
    *B = aux;
    return;
}

int cmpRealyBigNumbers(t_rbn *A, t_rbn *B){
    if(A->negative && !(B->negative))
        return -1;
    if(!(A->negative) && B->negative)
        return 1;
    if(A->ndigits - B->ndigits != 0)
        return A->ndigits - B->ndigits;
        
    int i = 0;
    for(i = 0 ; i < A->ndigits ; i++)
        if(getDigit(&(A->big_endian),i) - getDigit(&(B->big_endian),i) != 0)
            return getDigit(&(A->big_endian),i) - getDigit(&(B->big_endian),i);
            
    return 0;
}

t_rbn *cpyRealyBigNumbers(t_rbn *source){
    t_rbn *number = createRealyBigNum();
    number->ndigits = 0;
    number->negative = source->negative;
    int i = 0;
    for(i = 0 ; i < (source->ndigits) ; i++)
        addDigit(&number,getDigit(&(source)->big_endian,i));
    return number;
}

t_rbn *sumRealyBigNumbers(t_rbn *A,t_rbn *B){
    int signalA = A->negative, signalB = B->negative;
    if(A->negative != B->negative){
        A->negative = FALSE;
        B->negative = FALSE;
        if(cmpRealyBigNumbers(A,B)<0){
            A->negative = signalB;
            B->negative = signalB;
            return subRealyBigNumbers(B,A);
        }
        else{
            B->negative = signalA;
            A->negative = signalA;
            return subRealyBigNumbers(A,B);
        }
    }
    
    //0. Variables...
    int i = 0, carry = 0, limit = 0, aux = 0;
    t_rbn *result = NULL;
    
    //1. Allocating the result...
    result = createRealyBigNum();
    result->negative = A->negative;
    
    //2. Sum...
    limit = MIN(A->ndigits,B->ndigits);
    for(i = 0 ; i < limit ; i++){
        aux = getDigit(&(A->little_endian),i) + getDigit(&(B->little_endian),i) + carry;
        carry = aux / 10;
        addDigit(&result,aux - 10 * carry);
    }
    limit = MAX(A->ndigits,B->ndigits);
    for(i = i ; i < limit ; i++){
        if(limit == A->ndigits)
            aux = getDigit(&(A->little_endian),i) + carry;
        else
            aux = getDigit(&(B->little_endian),i) + carry;
        carry = aux / 10;
        addDigit(&result,aux - 10 * carry);
    }
    if(carry != 0)
        addDigit(&result,carry);
    
    //3. Swap big-endian with little-endian... 
    t_rbdigit *swap = result->big_endian;
    result->big_endian = result->little_endian;
    result->little_endian = swap;
    return result;
}

t_rbn *subRealyBigNumbers(t_rbn *A,t_rbn *B){
    int signalA = A->negative, signalB = B->negative;
    A->negative = FALSE;
    B->negative = FALSE;
    if(signalA != signalB){
        if(cmpRealyBigNumbers(A,B)<0){
            A->negative = signalA;
            B->negative = signalA;
            return sumRealyBigNumbers(A,B);
        }
        else{
            A->negative = signalA;
            B->negative = signalA;
            return sumRealyBigNumbers(A,B);
        }
    }
    A->negative = signalA;
    B->negative = signalB;
    
    //0. Variables...
    int i = 0, carry = 0, limit = 0, aux = 0;
    t_rbn *result = NULL;
    
    //1. Allocating the result...
    result = createRealyBigNum();
    if(cmpRealyBigNumbers(A,B)<0){
        if(signalA == TRUE)
            result->negative = FALSE;
        else
            result->negative = TRUE;
        swapRealyBigNumbers(&A,&B);
    }
    else
        result->negative = signalA;
    
    //2. Sub...
    limit = MIN(A->ndigits,B->ndigits);
    for(i = 0 ; i < limit ; i++){
        aux = getDigit(&(A->little_endian),i) - getDigit(&(B->little_endian),i) - carry;
        if(aux < 0){
            carry = 1;
            aux = 10 + aux;
        }
        else carry = 0;
        addDigit(&result,aux);
    }
    limit = MAX(A->ndigits,B->ndigits);
    for(i = i ; i < limit ; i++){
        if(limit == A->ndigits)
            aux = getDigit(&(A->little_endian),i) - carry;
        else
            aux = getDigit(&(B->little_endian),i) - carry;
        if(aux < 0){
            carry = 1;
            aux = 10 - aux;
        }
        else carry = 0;
        addDigit(&result,aux);
    }
    
    //3. Swap big-endian with little-endian...
    t_rbdigit *swap = result->big_endian;
    result->big_endian = result->little_endian;
    result->little_endian = swap;
    formatLeftZeroRBN(result);
    return result;
}

t_rbn *multRealyBigNumbers(t_rbn *A,t_rbn *B){
    if(cmpRealyBigNumbers(A,B)<0)
        swapRealyBigNumbers(&A,&B);
    
    //0. Variables...
    int i = 0, j = 0, digit = 0, carry = 0;
    t_rbn *result = NULL, *num1 = NULL, *num2 = NULL;
    t_rbdigit *swap = NULL;
    
    //1. Allocating the result and aux...
    result = createRealyBigNum();
    result->negative = A->negative;
    addDigit(&result,0);
        
    //2. Mult...
    for(i = 0 ; i < B->ndigits ; i++){
        num1 = createRealyBigNum();
        num1->negative = A->negative;
        for(j = 0 ; j < i ; j++)
            addDigit(&num1,0);
        for(j = 0 ; j < A->ndigits ; j++){
            digit = ((getDigit(&(A->little_endian),j))*getDigit(&(B->little_endian),i))+carry;
            carry = digit / 10;
            addDigit(&num1,digit - 10 * carry);
        }
        if(carry != 0)
            addDigit(&num1,carry);
        if(num2)
            destroyRealyBigNum(num2);
        num2 = cpyRealyBigNumbers(result);
        destroyRealyBigNum(result);
    
        swap = num1->big_endian;
        num1->big_endian = num1->little_endian;
        num1->little_endian = swap;
        
        result = sumRealyBigNumbers(num1,num2);
        destroyRealyBigNum(num1);
        carry = 0;
    }
    destroyRealyBigNum(num2);
    
    //3. Verifying the signal and returning value...
    if(A->negative != B->negative)
        result->negative = TRUE;
    else
        result->negative = FALSE;
    return result;
}

t_rbn *divRealyBigNumbers(t_rbn *A,t_rbn *B){
    //0. Variables...
    boolean signalA = A->negative, signalB = B->negative;
    int i = 0, counter = 0;
    t_rbn *result = NULL, *num = NULL, *aux = NULL;
    
    //1. Allocating the result and aux...
    result = createRealyBigNum();
    result->negative = A->negative;
        
    //2. Div...
    if(signalA != signalB)
        A->negative = signalB;
    num = createRealyBigNum();
    for(i = 0 ; i < A->ndigits ; i++){
        counter = 0;
        addDigit(&num,getDigit(&(A->big_endian),i));
        formatLeftZeroRBN(num);
        
        while(cmpRealyBigNumbers(num,B)>=0){
            aux = num;
            num = subRealyBigNumbers(aux,B);
            destroyRealyBigNum(aux);
            counter++;
            formatLeftZeroRBN(num);
        }
        
        addDigit(&result,counter);
    }
    destroyRealyBigNum(num);
    
    //3. Verifying the signal, format left zero and returning value...
    A->negative = signalA;
    formatLeftZeroRBN(result);
    
    if(signalA != signalB)
        result->negative = TRUE;
    else
        result->negative = FALSE;
    return result;
}