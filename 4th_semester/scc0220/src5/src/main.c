#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

int main ( int argc, char **argv ){
    //0. Variable...
    int N = 0, T = 0, G = 0, A = 0, B = 0;
    char *tournamentName = NULL, *teamA = NULL, 
        *teamB = NULL, *teamAGoal = NULL, *teamBGoal = NULL;
    t_team *team = NULL;
    
    //1. Reading the number N  of tournaments...
    scanf("%d%*c",&N);
    
    while( N-- > 0){
        //2. Reading the name of tournamet...
        tournamentName = readLine(stdin,'\n');
        
        //3. Reading the number T of participating teams...
        scanf("%d%*c",&T);
        
        //4. Reading the T participanting teams information...
        int counter;
        team = (t_team *)calloc(T,sizeof(t_team));
        for(counter = 0 ; counter < T ; counter++)
            team[counter].name = readLine(stdin,'\n');
        sortTeamVec(team,T);

        //5. Reading the numer G of played games in this tournament...
        scanf("%d%*c",&G);
        
        //6. Reading the result of G games, tokenizing the result and building up
        //the point table...
        for(counter = 0 ; counter < G ; counter++){
            //a. reading the result (tokenized)...
            teamA = readLine(stdin,'#');
            teamAGoal = readLine(stdin,'@');
            teamBGoal = readLine(stdin,'#');
            teamB = readLine(stdin,'\n');
    
            //b. defining the teams...
            A = binaryFindTeam(teamA,team,0,T-1);
            B = binaryFindTeam(teamB,team,0,T-1);
            
            //c. defining the points...
            team[A].games += 1;
            team[B].games += 1;
            
            team[A].goals += atoi(teamAGoal);
            team[B].goals += atoi(teamBGoal);
            
            team[A].goalsOP += atoi(teamBGoal);
            team[B].goalsOP += atoi(teamAGoal);
            
            team[A].sg = team[A].goals - team[A].goalsOP;
            team[B].sg = team[B].goals - team[B].goalsOP;
            if(atoi(teamAGoal) > atoi(teamBGoal)){
                team[A].points += WIN;
                team[B].points += LOSE;
                
                team[A].win += 1;
                team[B].lose += 1;
            }
            else if(atoi(teamAGoal) < atoi(teamBGoal)){
                team[A].points += LOSE;
                team[B].points += WIN;

                team[A].lose += 1;
                team[B].win += 1;
            }
            else{
                team[A].points += TIE;
                team[B].points += TIE;
                
                team[A].tie += 1;
                team[B].tie += 1;
            }
            
            //d. Freeing the used memory...
            free_((void *)teamA);
            free_((void *)teamAGoal);
            free_((void *)teamBGoal);
            free_((void *)teamB);
        }
        
        //7. Printing the tournament result...
        sortTeamVec(team,T);
        printf("%s\n",tournamentName);
        printTeams(team,T);
        if(N != 0)
            printf("\n");
        
        //8. Freeing the used memory...
        free_((void *)tournamentName);
        destroyTeamVec(team,T);
    }
    
    return 0;
}