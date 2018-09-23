#ifndef _UTILS_H_
#define _UTILS_H_

void free_(void *);
void freeMatrix(void **, int);
void sortStrings(char ***, int, int);
void formatString(char **);
char *readLine(FILE *, char);
FILE *fopen_(char *, char *);

#endif