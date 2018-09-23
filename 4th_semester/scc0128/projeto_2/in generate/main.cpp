#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

typedef vector<int> intvector;

#define MAXLENGTH 1000
#define NCUTS 50

int main(){
    //1. Creating the .in file...
    for(int length = 2 ; length < MAXLENGTH ; length++){
        for(int cuts = 1 ; cuts < NCUTS ; cuts++){
            intvector cp(MAXLENGTH-1,0);
            for(int i = 0 ; i < MAXLENGTH-1 ; i++)
                cp[i] = i+1;
                
            cout << length << endl;
            cout << cuts << endl;
            int counter = 1;
            for(int i = 0 ; i < cuts-1 ; i++){
                int point = rand() % (length - counter);
                cout << cp[point] << " ";
                cp.erase(cp.begin()+point);
                counter++;
            }cout << endl;
        }
    }
    
    //2. Thats all folks :)...
    return 0;
}