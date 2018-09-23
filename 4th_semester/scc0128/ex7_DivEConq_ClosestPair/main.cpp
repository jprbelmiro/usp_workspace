#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

#define MIN(X,Y) (X<Y)?(X):(Y)
#define EUCLIDIANDIST(A,B) sqrt((B.first - A.first)*(B.first - A.first) + (B.second - A.second)*(B.second - A.second))

typedef pair<int,int> point;
typedef vector<int> vi;

bool lowY(const point & A, const point & B) {
    return (A.second < B.second);
}

bool lowX(const point & A, const point & B) {
    return (A.first < B.first);
}

double ComputeHalfLineX(vector< point > p){
    double half = 0;
    
    vector< point > aux = p;
    std::sort(p.begin(),p.end(),lowX);
    
    half = (aux[(int)p.size()/2].first + aux[(int)p.size()/2 + 1].first)/2;
    
    return half;
}

double compareWithNeighbors(vector< point > p , int actp , double dist, int nneighbors){
    double result = dist;
    for(int i = 0 ; i < nneighbors && i < (int) p.size() ; i++)
        if(i != actp && dist > EUCLIDIANDIST(p[actp],p[i]))
            result = EUCLIDIANDIST(p[actp],p[i]);
    return result;
}

double Closest_Pair(vector< point > p, int level){
    //1. Computing the x coordinate of half line...
    double halfLine_X = ComputeHalfLineX(p);
    
    //2. Separating the left half points and the
    //right half points...
    vector< point > left_half, right_half;
    for(int i = 0 ; i < (int) p.size() ; i++)
        if(p[i].first <= halfLine_X && i < (int) p.size()/2)
            left_half.push_back(p[i]);
        else
            right_half.push_back(p[i]);
    //a. Verifying the division...
    if(left_half.empty() || right_half.empty())
        return 999999999;
        
    //3. DIVIDE!
    double left_dist = Closest_Pair(left_half,level+1);
    double right_dist = Closest_Pair(right_half,level+1);
    double dist = MIN(left_dist,right_dist);
    
    //4. Deleting all points further than dist 
    //from separation line...
    vector< point > source;
    for(int i = 0 ; i < (int) p.size() ; i++)
        source.push_back(p[i]);
        
    for(int i = 0 ; i < (int) p.size() ; i++)
        if(p[i].first > halfLine_X + dist )
            p.erase(p.begin() + i);
    
    //5. Sorting the points by y coordinate...
    std::sort(p.begin(),p.end(),lowY);
    
    //6. Comparing distance between each point
    //and next 11 neighbors...
    for(int i = 0 ; i < (int) p.size() ; i++)
        dist = compareWithNeighbors(p,i,dist,11);
    
    //7. CONQUER!
    if(level == 0){
    for(int i = 0 ; i < (int) p.size() ; i++)
        for(int j = 0 ; j < (int) p.size() ; j++ )
            if(dist == EUCLIDIANDIST(p[i],p[j]) && i != j){
                for(int k = 0 ; k < (int) source.size() ; k++){
                    if((p[i].first == source[k].first && p[i].second == source[k].second) 
                    || (p[j].first == source[k].first && p[j].second == source[k].second))
                        cout << k << " ";
                }
                printf("%.6lf\n",dist);
                i = (int) p.size();
                break;
            }
    }
    return dist;
}

int main(){
    //1. Reading the number N of points...
    int N;
    cin >> N;
    
    //2. Reading the N points...
    int x, y;
    vector< point > p;
    for(int i = 0 ; i < N ; i++){
        cin >> x >> y;
        p.push_back(make_pair(x,y));
    }
        
    //3. Applying a Division and Conquer Algorithm to
    //find the closest-pair point of problem...]
    Closest_Pair(p,0);

    //4. Thats all folks :)...
    return 0;
}