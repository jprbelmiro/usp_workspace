#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Activitie{
    public:
    int start, end;
    Activitie(int , int );
    
    void setStart(int s){
        start = s;
        return;
    }
    int getStart(){
        return start;
    }
    
    void setEnd(int e){
        end = e;
        return;
    }
    int getEnd(){
        return end;
    }
};
Activitie::Activitie(int s, int e){
    start = s;
    end = e;
}

class Test{
    int Nact;
    std::vector<Activitie> A;
    
    public:
    Test(int);
    
    void setNact(int n){
        Nact = n;
        return;
    }
    int getNact(){
        return Nact;
    }
    
    void pushAct(Activitie a){
        A.push_back(a);
        return;
    }
    void popAct(){
        A.pop_back();
        return;
    }
    
    std::vector<Activitie> getActVec(){
        return A;
    }
    void setActVec(std::vector<Activitie> a){
        A = a;
        return;
        
    }
};
Test::Test(int n){
    Nact = n;
}

bool endTimeSort(const Activitie & A, const Activitie & B) {
    return (A.end < B.end);
}

bool compatibleActivitie(std::vector<Activitie> Vec, Activitie A){
    bool flag = true;
    for(int i = 0 ; i < (int) Vec.size() ; i++)
        if(Vec[i].start + (Vec[i].end - Vec[i].start) > A.start)
            flag = false;
    return flag;
}

int main() {
    int T, N; 
    std::vector<Test> Tests;
    
    //1. Reading the number of tests T...
    cin>>T;
    
    //3. For each test, reading the N activities, and for each activitie
    //reading the start and end time...
    for(int i = 0; i < T ; i++){
        cin >> N;
        Tests.push_back(Test(N));
        for(int j = 0; j < Tests[i].getNact(); j++){
            int s, e;
            cin >> s >> e;
            Activitie A = Activitie(s,e);
            Tests[i].pushAct(A);
        }
    }
    
    //3. Applying a Greedy Algorithm to find the solution...
    //a. Sorting the activities by the end time...
    for(int i = 0 ; i < T ; i++){
        std::vector<Activitie> curvec = Tests[i].getActVec(); 
        std::sort (curvec.begin(),curvec.end(),endTimeSort);
        
        //b. Searching...
        std::vector<Activitie> A;
        A.push_back(curvec[0]);
        for(int j = 1 ; j < (int)curvec.size() ; j++)
            if(compatibleActivitie(A,curvec[j]))
                A.push_back(curvec[j]);
        
        //c. Printing the result...
        cout << A.size() << endl;
    }
    
}
