#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

int vectorMax(vector< int > v){
    int max = -99999;
    for(int i = 0 ; i < (int) v.size() ; i++)
        if(max < v[i])
            max = v[i];
    return max;
}

//Checking if the selected way is valid...
//- m vesels >= count "stops" == true...
bool check(int mid, int m, vector< int > c){
	int sum = 0, count = 1;
	for(int i = 0; i < (int) c.size() ; i++){
		if(sum + c[i] > mid)
            sum = c[i], count++;
        else 
            sum += c[i];
    }

    if(m >= count) 
        return true;
    else 
        return false;
}


int gibeMeMilk(vector< int > c, int m){
    //1. Sum all vec elements...
    int sum = 0;
    for(int i = 0 ; i < (int) c.size() ; i++)
        sum += c[i];
    
    //2. Descoverying the major element in vec...
    int max = vectorMax(c);
    
    //3. Applying the Bisection Algorithm (Winterim Backpacking Trip)...
    //- Binary search for optimum result...
    int result = 0;
    while(max <= sum){
		int mid = (max+sum)/2;
		if(check(mid,m,c))
			result = mid, sum = mid - 1;
		else 
		    max = mid + 1;
	}
    
    //4. Returning the result...
    return result;
}

int main(){
    //1. Reading the number n of vessels in the 
    //conveyor belt and the number m of containers...
    int n, m;
    while(scanf("%d %d",&n,&m) != EOF && (n != 0 || m != 0)){
        //2. Reading the capacity of n vessels...
        vector< int > capacity(n);
        for(int i = 0 ; i < n ; i++)
            cin >> capacity[i];
        
        //3. Descoverying the  maximal capacity of the containers,
        //below which you can not fill the containers without increasing 
        //the number of containers...
        int result = gibeMeMilk(capacity,m);
        cout << result << endl;
    }

    //4. Thats all folks :)...
    return 0;
}