#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef enum{
    penny = 1,
    nickel = 5,
    dime = 10,
    quarter = 25,
    halfdollar = 50
}coin;

typedef vector<int> intvector;

int countPossibilities(int ncoins, int coinchange, intvector coins, int *memo){
    if(coinchange == 0 && ncoins < *memo){
        *memo = ncoins;
        return 1;
    }
    if(coinchange < 0)
        return 0;
        
    int count = 0;
    for(int i = 0 ; i < (int)coins.size() ; i++)
        count += countPossibilities(ncoins+1,coinchange-coins[i],coins,memo);
    return count;
}

int main(){
    //1. Running the programming while exist input...
    //a. Initializing the coin vector...
    intvector coins(5,0);
    coins[0] = penny;
    coins[1] = nickel;
    coins[2] = dime;
    coins[3] = quarter;
    coins[4] = halfdollar;
    
    int coinchange = 0;
    while(scanf("%d%*c",&coinchange) > 0){
        //2. Descoverying the number of permutations are possible to build the change...
        int memo = coins[0]*coinchange+1;
        int nways = countPossibilities(0,coinchange,coins,&memo);
        
        //3. Printing the result...
        if(nways == 1)
            printf("There is only one way to produce %d cents change.\n",coinchange);
        else
            printf("There are %d ways to produce %d cents change.\n",nways,coinchange);
    }cout << endl;
    
    //4. Thats all folks :)...
    return 0;
}