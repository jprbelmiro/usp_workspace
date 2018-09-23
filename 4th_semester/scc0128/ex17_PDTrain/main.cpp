#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define INTMIN 0
#define MAX(X,Y) (X>Y)?(X):(Y)

typedef vector<int> intvector;

int LIS(int idx, intvector LISvec, intvector carweight){
    if(LISvec[idx] != -1)
        return LISvec[idx];
    
    int ans = INTMIN;
    for(int i = idx-1 ; i >= 0 ; i--){
        if(carweight[i] < carweight[idx])
            ans = MAX(LISvec[i]+1,ans);
    }
    return ans;
}

int main(){
    //1. Reading the number of test cases...
    int ncases = 0;
    cin >> ncases;
    
    //2. Runing the ncases of test...
    while(ncases-- > 0){
        //3. Reading the number of cars...
        int ncars = 0;
        cin >> ncars;
        
        //4. Reading the cars weight...
        intvector carweight(ncars,0);
        for(int i = 0 ; i < ncars ; i++)
            cin >> carweight[i];
        
        //5. Applying LIS Dynamic method 
        intvector LISvec(ncars,-1);
        LISvec[0] = 1;
        int max = 1;
        for(int i = 1 ; i < ncars ; i++){
            LISvec[i] = LIS(i,LISvec,carweight);   
            if(LISvec[i] > max)
                max = LISvec[i];
        }
        
        //6. Printing the result...
        cout << max << "\n";
    }
    
    //7. Thats all folks :)...
    return 0;
}