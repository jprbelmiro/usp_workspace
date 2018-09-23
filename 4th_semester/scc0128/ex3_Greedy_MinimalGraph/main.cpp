#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include "UnionFind.h"
using namespace std;


typedef pair<int,int> point;
typedef vector<int> vi;
class Graph{
    private:
    public:
        int nvertex, nedges;
        
        Graph();
        vector< pair<int,point> > EdgeList;
};
Graph::Graph(){}

int main(){
    int m, n;
    int x, y, z;
    Graph g;
    
    while(scanf("%d %d",&m,&n) != EOF && m != 0 && n != 0){
        //1. Reading the number of junctions m and the number of 
        //roads n in Byteland...
        while(!(m >= 1 && m <= 200000) || !(n >= m-1 && n <= 200000))
            cin >> m >> n;
        
        //2. Reading the roads and your length to build up the graph
        //of Byteland's roads...
        g.EdgeList.clear();
        g.nvertex = m; g.nedges = n;
        
        int totalMeters = 0;
        for(int i = 0 ; i < g.nedges ; i++){
            scanf("%d %d %d",&x,&y,&z);
            g.EdgeList.push_back(make_pair(z, point(x,y)));
            totalMeters += z;
        }
        
        //3. Sorting the EdgeList from min lenght to max...
        sort(g.EdgeList.begin(), g.EdgeList.end());
        
        //4. Building up a disjoint union with the vertex
        //of Byteland...
        int mst_cost = 0;
        UnionFind uf(g.nvertex);
        
        //5. Applying the Kruskal Greedy Algorithm to solve the problem...
        for(int i = 0 ; i < g.nedges ; i++){
            pair<int, point> front = g.EdgeList[i];
            if(!uf.isSameSet(front.second.first, front.second.second)){
                mst_cost += front.first;
                uf.unionSet(front.second.first, front.second.second);
            }
        }
        
        //6. Printing the result...
        printf("%d\n",totalMeters - mst_cost);
        
    }
}