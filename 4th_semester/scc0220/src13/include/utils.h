#ifndef _UTILS_H_
#define _UTILS_H_

#define INT_MAX 999999999
#define INT_MIN -99999999

typedef enum{
    FALSE = 0,
    TRUE
}boolean;

void free_(void *);

void freeMatrix(void **, int );

int *copyIntVec(int *, int );

int *readIntVector(int );

char *readLine(FILE *, char );
char **readWords(int , FILE *, char );

#endif