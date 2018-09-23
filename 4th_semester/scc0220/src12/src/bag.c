#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "bag.h"

void destroybag(t_bag *bag){
    if(bag->nitens > 0)
        free_(bag->itens);
    free_(bag);
}

int getminofthebag(t_bag *bag){
    int i = 0, min = INT_MAX;
    for(i = 0 ; i < bag->nitens ; i++)
        min = (min > bag->itens[i])?(bag->itens[i]):(min);
    return min;
}
int getmaxofthebag(t_bag *bag){
    int i = 0, max = INT_MIN;
    for(i = 0 ; i < bag->nitens ; i++)
        max = (max < bag->itens[i])?(bag->itens[i]):(max);
    return max;
}

boolean existinbag(int x, t_bag *bag){
    int i = 0;
    for(i = 0 ; i < bag->nitens ; i++)
        if(bag->itens[i] == x)
            return TRUE;
    return FALSE;    
}

void putonbag(int x, t_bag *bag){
    bag->itens = (int *)realloc(bag->itens,sizeof(int)*((bag->nitens)+1));
    bag->itens[bag->nitens++] = x;
}
int getfromendbag(int x, t_bag *bag){
    int i = 0, j = 0;
    
    if(bag->nitens == 1){
        free_(bag->itens);
        bag->itens = NULL;
        bag->nitens--;
        return 0;
    }
    
    for( i = (bag->nitens)-1 ; i >= 0 ; i--){
        if(bag->itens[i] == x){
            int *newitens = NULL;
            newitens = (int *)realloc(newitens,sizeof(int)*((bag->nitens)-1));
            for(j = 0 ; j < i ; j++)
                newitens[j] = bag->itens[j];
                
            for(j = j+1 ; j < bag->nitens ; j++)
                newitens[j-1] = bag->itens[j];
            
            free_(bag->itens);
            bag->itens = newitens;
            bag->nitens--;
            return i;
        }
    }
    return -1;
}
int getfromstartbag(int x, t_bag *bag){
    int i = 0, j = 0;
    
    if(bag->nitens == 1){
        free_(bag->itens);
        bag->itens = NULL;
        bag->nitens--;
        return 0;
    }
    
    for( i = 0 ; i < bag->nitens ; i++){
        if(bag->itens[i] == x){
            int *newitens = NULL;
            newitens = (int *)realloc(newitens,sizeof(int)*((bag->nitens)-1));
            for(j = 0 ; j < i ; j++)
                newitens[j] = bag->itens[j];
                
            for(j = j+1 ; j < bag->nitens ; j++)
                newitens[j-1] = bag->itens[j];
            
            free_(bag->itens);
            bag->itens = newitens;
            bag->nitens--;
            return i;
        }
    }
    return -1;
}

t_bag *createbag(){
    t_bag *bag = (t_bag *)malloc(sizeof(t_bag)*1);
    bag->itens = NULL;
    bag->nitens = 0;
    return bag;
}