#ifndef _UTILS_H_
#define _UTILS_H_

#define MAX(X,Y) (X>Y)?X:Y
#define MIN(X,Y) (X<Y)?X:Y
#define BOOLINV(X) (X==TRUE)?FALSE:TRUE

typedef enum{
    FALSE = 0,
    TRUE
}boolean;

void free_(void *);
short digittoshort(char );
boolean isanumber(char *);
char *readLine(FILE *, char);

#endif