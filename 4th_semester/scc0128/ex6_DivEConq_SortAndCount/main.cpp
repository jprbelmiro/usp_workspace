#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

int MergeAndCount(vector< int > A, vector< int > B){
    int r = 0;
    for(int i = 0 ; i <(int) A.size() ; i++)
        for(int j = 0 ; j <(int) B.size() ; j++)
            if(A[i] > B[j])
                r++;
    
    return r;
}

int SortAndCount(vector< int > L){
    if(L.size() <= 1)
        return 0;
    
    //DIVIDE!
    //a... the L vector...
    vector< int > A, B;
    for(int i = 0 ; i < (int)L.size();  i++){
        if(i < (double)L.size()/2)
            A.push_back(L[i]);
        if(i >= (double)L.size()/2)
            B.push_back(L[i]);
    }
    
    //b... the count...
    int ra = SortAndCount(A);
    int rb = SortAndCount(B);
    int r = MergeAndCount(A,B);
    
    //CONQUER!
    std::sort(L.begin(),L.end());
    return ra + rb + r;
}

int main(){
    //0. Variables...
    int t, n;
    
    //1. Reading the number t of tests...
    cin >> t;

    //2. Starting the t tests...
    while(t-- > 0){
        //a. reading the number of numbers to vector A...
        cin >> n;
        
        //b. creating the vector A...
        vector< int > A(n,0);
        for(int i = 0 ; i < n ; i++)
            cin >> A[i];
        
        //3. Divide and Conquer! Now!
        cout << SortAndCount(A) << endl;
        
        A.clear();
    }

    //4. Thats all folks :)...
    return 0;
}