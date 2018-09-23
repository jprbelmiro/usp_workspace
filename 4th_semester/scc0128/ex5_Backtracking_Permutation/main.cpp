#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

int arrangements;

bool everybodySits(int n, vector<int> s){
    for(int i = 0 ; i < n ; i++)
        if(s[i] == -1)
            return false;
    return true;
}

bool teenageConflict(int n, vector< vector<int> >ct, vector<int>sits, int teen, int whereTeenWantSit){
    if(sits[whereTeenWantSit] != -1)
        return true;
        
    for(int i = 0 ;  i < n ; i++){
        if(i != whereTeenWantSit && sits[i] != -1){
            if(ct[teen][sits[i]] > 0 && sqrt((i - whereTeenWantSit)*(i - whereTeenWantSit)) > ct[teen][sits[i]])
                return true;
            if(ct[teen][sits[i]] < 0 && sqrt((i - whereTeenWantSit)*(i - whereTeenWantSit)) < -ct[teen][sits[i]])
                return true;
        }
    }
    
    return false;
}

void teenageBacktraking(int n, vector< vector<int> > ct,vector< int > sits, int level){
    if(level == n){
        if(everybodySits(n,sits))
            arrangements++;
        return;
    }
    
    for(int i = 0 ; i < n ; i++){
        if(!teenageConflict(n,ct,sits,level,i)){
            sits[i] = level;
            teenageBacktraking(n,ct,sits,level+1);
            sits[i] = -1;
        }
    }
    return;
}

int main(){
    //0. Variables...
    int n, m;
    int a, b;
    
    //1. Reading the size n of the group and m descriptions...
    while(scanf("%d %d",&n,&m) != EOF && (n != 0 || m != 0)){
        arrangements = 0;
        
        vector< vector<int> > constraintTable(n);
        for(int i = 0 ; i < n ; i++){
            vector<int> v = vector<int>(n);
            constraintTable[i] = v;
            for(int j = 0 ; j < n ; j++)
                constraintTable[i][j] = 0;
        }
                
        //2. Reading m constraints c of teenage a and b and
        //creating a constraint table...
        for(int i = 0 ; i < m ; i++){
            cin >> a >> b;
            cin >> constraintTable[a][b];
            constraintTable[b][a] = constraintTable[a][b];
        }
        
        //2. Initializing the sits...
        vector< int > sits(n,-1);
        
        //3. Utilizing a matrix to aplying a Backtraking technique...
        //- Harder, Better, Faster, Stronger...
        teenageBacktraking(n,constraintTable,sits, 0);
        
        //4. Printing the result...
        cout << arrangements << endl;
    }

    //5. Thats all folks :)...
    return 0;
}