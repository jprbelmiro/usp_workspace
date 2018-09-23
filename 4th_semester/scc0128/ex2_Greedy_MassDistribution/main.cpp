#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

class Specimens{
    private:
    public:
        Specimens(int);
        int mass;
        int getMass(){return mass;}
        void setMass(int m){mass = m;}
};
Specimens::Specimens(int m){
    setMass(m);
}

bool crescMassSort(const Specimens & A, const Specimens & B) {
    return (A.mass < B.mass);
} 

int main (){
    int C = 0, S = 0, M = 0;
    double AM = 0.0, IMBALANCE = 0.0;
    std::vector<double> CM;
    std::vector<Specimens> sp;
    
    while(scanf("%d %d",&C,&S) != EOF){
        //1. Reading the number of Chainbers C and the
        //number of specimens S...
        while(!(C >= 1 && C <= 5) || !(S >= 1 && S <= 2*C)){
            cin >> C;
            cin >> S;
        }
        
        //2. Reading the S specimens mass...
        for(int i = 0 ; i < S ; i++){
            cin >> M;
            if(M >= 1 && M <= 1000)
                sp.push_back(Specimens(M));
            else i--;
        }
        
        //3. Applying a Greedy Algorithm to solve the
        //problem...
        //a. Adding specimens with mass = 0 while the
        //number of specimens != 2*number of chambers...
        while(S != 2*C){
            sp.push_back(Specimens(0));
            S += 1;
        }
        
        //b. Sorting the specimens by mass...
        std::sort(sp.begin(),sp.end(),crescMassSort);
        
        //4. Calculating the IMBALANCE...
        //a. Calculating the optimal distribuition for each
        //chamber...
        for(int i = 0 ; i < C ; i++)
            CM.push_back((sp[2*C-i-1].getMass() + sp[i].getMass()));
            
        //b. Calculating the Average Mass...
        for(int i = 0 ; i < 2*C ; i++)
            AM += sp[i].mass;
        AM = AM/C;
        
        //c. Really calculating the IMBALANCE...
        for(int i = 0 ; i < C ; i++)
            IMBALANCE += fabs(CM[i] - AM);
        
        //5. Printing the result...
        printf("IMBALANCE = %.5lf\n",IMBALANCE);
        
        //6. Clear vec and variables...
        sp.clear();
        CM.clear();
        C = 0; S = 0 ; M = 0; 
        AM = 0.0 ; IMBALANCE = 0.0;
    }
    return 0;
}