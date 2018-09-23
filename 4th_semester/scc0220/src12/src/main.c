#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "bag.h"

int main ( int argc, char **argv ){
    //0. Variable...
    int sflag = 0, pqflag = 0, qflag = 0, max = INT_MIN;;
    int n = 0, x = 0, op = 0, nput = 0, nget = 0;

    t_bag *bag = NULL;
    
    
    //1. Analysing the bag type while exist operations...
    while(scanf("%d%*c",&n) > 0 && n > 0){
        sflag = 0; pqflag = 0; qflag = 0;
        max = INT_MIN, nput = 0, nget = 0;
        //1. Creating bag...
        bag = createbag();
        
        //3. Reading and making the n operations...
        while(n-- > 0){
            scanf("%d%*c%d%*c",&op,&x);
            
            switch(op){
                case 1:
                    max = (max < x)?(x):(max);
                    putonbag(x,bag);
                    nput++;
                break;
                case 2:
                    if(bag->nitens > 0 && existinbag(x,bag)){
                        pqflag += abs(max - x);
                        
                        if(bag->itens[0] == x && bag->itens[(bag->nitens)-1] == x){
                            getfromstartbag(x,bag);
                            getfromendbag(x,bag);
                        }
                        else if(bag->itens[0] == x){
                            sflag++;
                            getfromstartbag(x,bag);
                        }
                        else if(bag->itens[(bag->nitens)-1] == x){
                            qflag++;
                            getfromendbag(x,bag);
                        }
                        else{
                            sflag++; qflag++;
                            getfromstartbag(x,bag);
                        }
                        
                        max = getmaxofthebag(bag);
                        nget++;
                    }
                break;
            }
        }
        
        //4. Analysing the result and printing it...
        if(sflag == 0 && qflag != 0 && pqflag != 0)
            printf("pilha\n");
        else if(sflag != 0 && qflag == 0 && pqflag != 0)
            printf("fila\n");
        else if(sflag != 0 && qflag != 0 && pqflag == 0)
            printf("fila de prioridade\n");
        else if((sflag != 0 && qflag != 0 && pqflag != 0) || (nput == 0 || nget == 0))
            printf("impossivel\n");
        else
            printf("incerto\n");
        
        //5. Freeing the used memory...
        destroybag(bag);
    }
    
    //6. Thats all folks ;)...
    return 0;
}