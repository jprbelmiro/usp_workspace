#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX(X,Y) (X>Y)?(X):(Y)

typedef vector<int> intvector;
typedef vector<intvector> intmatrix;
typedef vector< pair<int,int> > pairvector;

int maxgold;

int sumoffirst(pairvector v){
    int sum = 0;
    for(int i = 0 ; i < (int)v.size() ; i++)
        sum += v[i].first;
    return sum;
}

int sumofsecond(pairvector v){
    int sum = 0;
    for(int i = 0 ; i < (int)v.size() ; i++)
        sum += v[i].second;
    return sum;
}

void findMaxGold(pairvector act, intvector P, intvector W, int maxw){
    if(sumofsecond(act) > maxw)
        return;
    
    for(int i = 0 ; i < (int)P.size() ; i++){
        act.push_back(make_pair(P[i],W[i]));
        
        if(sumoffirst(act) > maxgold && sumofsecond(act) <= maxw)
            maxgold = sumoffirst(act);
        
        int p = P[i];
        P.erase(P.begin()+i);
        int w = W[i];
        W.erase(W.begin()+i);  
        
        findMaxGold(act,P,W,maxw);
        
        intvector::iterator it;
        it = P.begin();
        P.insert(it+i,p);
        it = W.begin();
        W.insert(it+i,w);
        
        act.pop_back();
    }
    
    return;
}

int maxInMatrix(intmatrix M, int row, int col){
    int max = 0;
    for(int i = 0 ; i < row ; i++)
        for(int j = 0 ; j < col ; j++)
            if(max < M[i][j])
                max = M[i][j];
    return max;
}

int bestSuperSale(intvector P, intvector W, intvector MW){
    int maxprice = 0;
        
    //1. Running the algorithm...
    for(int p = 0 ; p < (int)MW.size() ; p++){
        
        //a. Creating the matrix M of possibilities of weight...
        intmatrix M((int)P.size());
        for(int i = 0 ; i < (int)P.size() ; i++)
            M[i] = intvector(MW[p],0);
        
        //b. Creating the matrix G of possibilities of weight...
        intmatrix G((int)P.size());
        for(int i = 0 ; i < (int)P.size() ; i++)
            G[i] = intvector(MW[p],0);
        
        
        //c. Searching for the max weight...
        for(int i = 1 ; i < (int)P.size() ; i++){
            for(int j = 0 ; j < MW[p] ; j++)
                if(MW[p] < W[i])
                    M[i][j] = M[i-1][j];
                else
                    M[i][j] = MAX(M[i-1][j],W[i] - M[i-1][MW[p] - W[i]]);
        }
        
        //d. Searching for the max gold...
        int maxweight = maxInMatrix(M,(int)P.size(),(int)MW[p]);
        maxgold = 0;
        findMaxGold(pairvector(),P,W,maxweight);
        
        //e. Summing the value...
        maxprice += maxgold;
    }
        
    return maxprice;
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
        
        //d. Reading the max weight each people can carry...
        intvector MW(G,0);
        for(int i = 0 ; i < G ; i++)
            cin >> MW[i];
        
        //e. Descoverying the max goods this family can buy...
        cout << bestSuperSale(P,W,MW) << endl;
    }
    
    //3. Thats all folks :)...
    return 0;
}