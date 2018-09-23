#ifndef _RBN_H_
#define _RBN_H_

#include "utils.h"

typedef struct realy_big_digit t_rbdigit;
struct realy_big_digit{
    int idx;
    short digit;
    t_rbdigit *next;
};

typedef struct realy_big_nums t_rbn;
struct realy_big_nums{
    int ndigits;
    boolean negative;
    t_rbdigit *little_endian;
    t_rbdigit *big_endian;
};

void printRealyBigNum(t_rbn *);
void removeDigit(t_rbdigit **, int );
void destroyRealyBigNum(t_rbn *);

short getDigit(t_rbdigit **, int );
void addDigit(t_rbn **, short );
t_rbn *readRealyBigNum(FILE *, char);
t_rbn *createRealyBigNum();


#endif