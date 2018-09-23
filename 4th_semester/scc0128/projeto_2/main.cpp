#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

using namespace std;

#define INT_MAX 99999999
#define MIN(X,Y) (X<Y)?(X):(Y)

typedef vector<int> intvector;
typedef vector<intvector> intmatrix;

int bestCut(int length, intvector cp){
    //1. Formating the cut points vector to facilitate the algorithm...
    intvector::iterator it = cp.begin();
    cp.insert(it, 0);
    cp.push_back(length);
    
    //2. Initializing the memo matrices...
    int N = (int)cp.size();
    
    intmatrix cost(N);
    for(int i = 0 ; i < N ; i++)
        cost[i] = intvector(N,0);
    
    //3. Searching for best cut...
    int left, right, cutpos, sum = 0;
    for(right = 2 ; right < N ; right++){
        for(left = right-2 ; left >= 0 ; left--){
            //a. Setting the max cost to this cut...
            cost[left][right] = INT_MAX;
            
            //b. Minimizing the cut cost by analysis of the minor cuts...
            for(cutpos = left+1; cutpos < right ; cutpos++){
                //i. left piece + right piece
                sum = cost[left][cutpos] + cost[cutpos][right]; 
                //ii. this guarantee an optimization ...
                if(sum < cost[left][right])
                    cost[left][right] = sum;
            }
            
            //c. Updating the cut cost...
            cost[left][right] = cost[left][right] + (cp[right] - cp[left]);
        }
    }
    
    //4. Returning the mincost for the length...
    return cost[0][N-1];
}

int main(){
    //1. Solving the problem while the length of the stick is different 
    //from zero (0)...
    int length = 0;
    clock_t start, end;
    
    while(scanf("%d%*c",&length)>0 && length != 0){
        //2. Reading the number n of points of cut...
        int n = 0;
        cin >> n;
        
        //3. Reading the points of cut cp...
        intvector cp(n,0);
        for(int i = 0 ; i < n ; i++)
            cin >> cp[i];
        
        //4. Trying to find the best cuts possible (minimum cost)...
        start = clock();
        int mincost = bestCut(length,cp);
        end = clock();
        
        //5. Printing the result...
        //cout << "The minimum cutting is " << mincost << endl;
        cout << "For a bar size of " << length << " and " << n << " cuts, The minimum cutting is " << mincost << " - ";
        printf("%lf ms\n", (end - start)/(double)CLOCKS_PER_SEC);
        
    }
    
    //6. Thats all folks :)...
    return 0;
}