#ifndef _UTILS_H_
#define _UTILS_H_

typedef char* string;

typedef enum{
    FALSE = 0,
    TRUE
}boolean;

#define MAX(X,Y) (X > Y)?(X):(Y)

#define FATHER 'p'
#define FULL 'f'
#define EMPTY 'e'

#define ISFATHER(X)  (X==FATHER)?(TRUE):(FALSE)
#define ISBLACK(X,Y)  (X==FULL || Y==FULL)?(TRUE):(FALSE)

void free_(void *);
void printString(string);
string quarter(string , int );
char *readLine(FILE *, char);

#endif