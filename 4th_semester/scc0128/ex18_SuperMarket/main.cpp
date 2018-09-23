#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX(X,Y) (X>Y)?(X):(Y)

typedef vector<int> intvector;
typedef vector<intvector> intmatrix;

int value(int idx, int w, intvector P, intvector W, intmatrix memo){
    if(idx == (int)W.size()|| w == 0)
        return 0;
    if(memo[idx][w] != -1)
        return memo[idx][w];
    if(W[idx] > w)
        return memo[idx][w] = value(idx+1,w,P,W,memo);
    
    return MAX(value(idx+1,w,P,W,memo),P[idx]+value(idx+1,w-W[idx],P,W,memo));
}

int main(){
    //1. Reading the number T of test cases...
    int T = 0;
    cin >> T;
    
    //2. Running the T test cases...
    while(T-- > 0){
        //a. Reading the number N of objects...
        int N = 0;
        cin >> N;
        
        //b. Reading the price P and the weight W of N objects...
        intvector P(N,0), W(N,0);
        for(int i = 0 ; i < N ; i++)
            cin >> P[i] >> W[i];
            
        //c. Reading the number of people in a group...
        int G = 0;
        cin >> G;
        
        //d. Creating the memo matrix...
        intmatrix memo(N);
        for(int i = 0 ; i < N ; i++)
            memo[i] = intvector(30,-1);
        
        //e. Reading the max weight each people can carry and
        //starting to solve the problem...
        int ans = 0;
        intvector MW(G,0);
        for(int i = 0 ; i < G ; i++){
            cin >> MW[i];
            ans += value(0,MW[i],P,W,memo);
        }
        
        //f. Printing the result...
        cout << ans << endl;
    }
    
    //3. Thats all folks :)...
    return 0;
}