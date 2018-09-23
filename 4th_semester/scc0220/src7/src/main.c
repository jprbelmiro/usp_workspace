#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"

int main ( int argc, char **argv ){
    //0. Variable...
    int ncases = 0, card = 0;
    t_dllist *deck = NULL, *tablecards = NULL;
    
    //1. Reading the number of cases...
    scanf("%d%*c",&ncases);
    
    //2. Searching for result...
    while(ncases-- > 0){
        //a. Reading the cards...
        deck = createDLL();
        while(scanf("%d%*c",&card) != -1 && card != 0)
            pushBackDLL(card,&deck);

        //b. Creating table cards deck...
        tablecards = createDLL();
           
        //c. Applying the suggest algorithm...
        while(deck->size != 1){
            //i. taking the top card...
            card = getFrontElemDLL(deck);
            popFrontDLL(&deck);
            
            //ii. putting on the table...
            pushBackDLL(card,&tablecards);
            
            //iii. putting the new top card on
            //back of deck...
            card = getFrontElemDLL(deck);
            popFrontDLL(&deck);
            pushBackDLL(card,&deck);
        }
        
        //d. Printing the result...
        printf("Cartas jogadas: ");
        printDLL(tablecards);
        
        printf("Carta restante: ");
        printDLL(deck);
        
        //e. Freeing the deck of memory...
        destroyDLL(deck);
    }
    
    //3. Thats all folks ;)...
    return 0;
}