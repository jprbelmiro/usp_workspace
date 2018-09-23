#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "match.h"
#include "hash.h"

#define ORDER 100

int main ( int argc, char **argv ){
    //0. Variable...
    char *string = NULL, *elem = NULL;
    t_hashtable *hash = createHash(ORDER);
    
    //1. Operating on binary tree...
    while(!match((string = readLine(stdin,'\n')),"^\\s*f\\s*$")){
        //i) insert
        if(match(string,"^\\s*i\\s+[-]*[0-9]+\\s*$")){
            elem = tokenize(string,1,' ');
            insertHash(atoi(elem),hash);
            free_(elem);
        }
        //b) search
        else if(match(string,"^\\s*b\\s+[-]*[0-9]+\\s*$")){
            elem = tokenize(string,1,' ');
            searchHash(atoi(elem),hash);
            free_(elem);
        }
        //r) remove
        else if(match(string,"^\\s*r\\s+[-]*[0-9]+\\s*$")){
            elem = tokenize(string,1,' ');
            removeHash(atoi(elem),hash);
            free_(elem);
        }
        //p) print
        else if(match(string,"^\\s*p\\s*$")){
            printHash(hash);
        }
        free_(string);
    }free_(string);
    
    //2. Freeing the used memory...
    destroyHash(hash);
    
    //3. Thats all folks ;)...
    return 0;
}