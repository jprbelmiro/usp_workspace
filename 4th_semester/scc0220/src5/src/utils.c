#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void destroyTeamVec(t_team *team, int T){
    int i;
    for( i = 0 ; i < T ; i++)
        free_((void *)team[i].name);
    free_((void *)team);
    return;
}

void printTeams(t_team *team, int T){
    int i = 0;
    for(i = 0 ; i < T ; i++)
        printf("%d) %s %dp, %dj (%d-%d-%d), %dsg (%d-%d)\n",
            i+1,team[i].name,team[i].points,team[i].games,team[i].
                win,team[i].tie,team[i].lose,team[i].sg,team[i].goals,team[i].goalsOP);
    return;
}

char *stringToUpper(char *source){
    int i;
    char *string = (char *)malloc(sizeof(char)*(strlen(source)+1));
    for(i = 0 ; i < strlen(source) ; i++)
        if(96 < source[i] &&  source[i] < 123)
            string[i] = source[i] - 32;
        else
            string[i] = source[i];
    string[i] = '\0';
    return string;
}

int binaryFindTeam(char *searchTeam, t_team *teams, int left, int right){
    int mid = (left + right)/2;
    char *aux = stringToUpper(teams[mid].name);
    char *saux = stringToUpper(searchTeam);
    if (strcmp(aux,saux)==0){
        free(aux); free(saux);
        return mid;
    }
    
    if (left >= right){
        free(aux); free(saux);
        return -1;
    }
        
    else if(strcmp(aux,saux)<0){
        free(aux); free(saux);
        return binaryFindTeam(searchTeam,teams,mid+1,right);
    }
    free(aux); free(saux);
    return binaryFindTeam(searchTeam,teams,left,mid-1);
}

void sortTeamVec(t_team *team, int n){
    int k, j;
    t_team aux;
    char *strA, *strB;
    for (k = 1; k < n; k++) {
        for (j = 0; j < n - 1; j++) {
            if(team[j].points != team[j+1].points){
                if (team[j].points < team[j+1].points) {
                    aux          = team[j];
                    team[j]     = team[j+1];
                    team[j+1] = aux;
                }
            }
            else if(team[j].win != team[j+1].win){
                if (team[j].win < team[j+1].win) {
                    aux          = team[j];
                    team[j]     = team[j+1];
                    team[j+1] = aux;
                }
            }
            else if(team[j].sg != team[j+1].sg){
                if (team[j].sg < team[j+1].sg) {
                    aux          = team[j];
                    team[j]     = team[j+1];
                    team[j+1] = aux;
                }
            }
            else if(team[j].goals != team[j+1].goals){
                if (team[j].goals < team[j+1].goals) {
                    aux          = team[j];
                    team[j]     = team[j+1];
                    team[j+1] = aux;
                }
            }
            else if(team[j].games != team[j+1].games){
                if (team[j].games > team[j+1].games) {
                    aux          = team[j];
                    team[j]     = team[j+1];
                    team[j+1] = aux;
                }
            }
            else{
                strA = stringToUpper(team[j].name);
                strB = stringToUpper(team[j+1].name);
                if (strcmp(strA,strB)>0) {
                    aux          = team[j];
                    team[j]     = team[j+1];
                    team[j+1] = aux;
                }
                free(strA);
                free(strB);
            }
        }
    }
    return;
}

//------------------------------------------------------------------------------

void free_(void *pointer){
    if(pointer)
        free(pointer);
    return;
}

void freeMatrix(void **pointer, int n){
    int i;
    for( i = 0 ; i < n ; i++)
        free_(pointer[i]);
    free_(pointer);
    return;
}

char *readLine(FILE *inputfile, char delim){
    int counter = 0;
    char c = 'c', *string = NULL;
    
    do{
        c = fgetc(inputfile);
        string = (char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10 && c != 11 && c != 12 && c != 13 && c != EOF && c != delim);
    string[counter-1] = '\0';
    
    return string;
}