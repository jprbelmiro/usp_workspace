#ifndef _UTILS_H_
#define _UTILS_H_

typedef char* string;

typedef enum{
    FALSE = 0,
    TRUE
}boolean;

void free_(void *);
void freeMatrix(void **, int );
void printCharMatrix(char **, int , int);
char *tokenize (char *, int , char );
char *readLine(FILE *, char);
char **createCharMatrix(int , int );

#endif