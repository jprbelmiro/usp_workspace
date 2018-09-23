#ifndef _UTILS_H_
#define _UTILS_H_

typedef enum{
    FALSE = 0,
    TRUE
}boolean;

void free_(void *);
void freeMatrix(void **, int );
char *tokenize (char *, int , char );
char *readLine(FILE *, char);

#endif