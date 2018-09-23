#ifndef _UTILS_H_
#define _UTILS_H_

#define MIN(X,Y) (X<Y)?X:Y

typedef enum{
    LOSE = 0,
    TIE,
    WIN = 3
}gameResult;

typedef enum{
    FALSE = 0,
    TRUE
}boolean;

typedef struct team{
    char *name;
    int points, goals, goalsOP, games;
    int win, tie, lose, sg;
}t_team;

void destroyTeamVec(t_team *, int);
void printTeams(t_team *, int );
int binaryFindTeam(char *, t_team *, int , int );
char *stringToUpper(char *);
void sortTeamVec(t_team *, int);

void free_(void *);
void freeMatrix(void **, int);
char *readLine(FILE *, char);

#endif