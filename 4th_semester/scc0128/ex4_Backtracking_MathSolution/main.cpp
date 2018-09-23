#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    //0. Variables...
    int x,X = 10001, y,Y = 10001, z,Z = 10001;
    int A, B, C, N = 0;
    bool solution_flag;
    
    //1. Reading the number of test cases N...
    cin >> N;
    
    //2. Applying Backtraking to solve the problem...
    while(N-- > 0){
        solution_flag = false;
        X = 10001; Y = 10001; Z = 10001;
        
        //a. Reading the operation result values...
        cin >> A >> B >> C;
        
        //b. Harder, Better, Faster, Stronger...
        for( x = 1 ; x <= 10000 && !solution_flag ; x++){
            if(((x) > A) || ((x) > B) || (((x*x)) > C))
                break;
            for( y = 1 ; y <= 10000 && !solution_flag ; y++){
                if(((x+y) > A) || ((x*y) > B) || (((x*x)+(y*y))>C))
                    break;
                for( z = 1 ; z <= 10000 && !solution_flag ; z++){
                    if(((x+y+z) > A) || ((x*y*z) > B) || (((x*x) + (y*y) + (z*z))>C))
                        break;
                    if(((x+y+z) == A) && ((x*y*z) == B) && (((x*x) + (y*y) + (z*z))==C)){
                                    X = x; Y = y; Z = z;
                                    solution_flag = true;
                                    break;
                    }
                }
            }
        }
        
        //c. if the solutions is valid, print the result...
        if(X != 10001 && Y != 10001 && Z != 10001)
            cout << X << " " << Y << " " << Z << endl;
        else
            cout << "No solution" << endl;  
    }
    //3. Thats all folks :)...
    return 0;
}