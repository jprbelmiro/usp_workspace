#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAXCOST 40000000;

typedef vector<int> intvector;
typedef vector<intvector> intmatrix;

bool bfs(intmatrix rGraph, int s, int t, intvector *parent, int size){
    vector<bool> visited(size,false);
    queue <int> q;
    q.push(s);
    visited[s] = true;
    (*parent)[s] = -1;
 
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int v = 0; v < size; v++){
            if (visited[v] == false && rGraph[u][v] > 0){
                q.push(v);
                (*parent)[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}
 
void mincutFordFulkerson(intmatrix graph, int s, int t, int size){
    int u, v;
    
    //1. Creating the residual matrix...
    intmatrix rGraph(size);  
    for(u = 0; u < size; u++){
        rGraph[u] = intvector(size,0);
        for (v = 0; v < size; v++){
            rGraph[u][v] = graph[u][v];
        }
    }
    
    //2. Initilizing the maxflow and the parent vector...
    int max_flow = 0;
    intvector parent(size);
    
    //3. While not reach the best path...
    while(bfs(rGraph, s, t, &parent, size)){
        //a. initializing the curent path flow...
        int path_flow = MAXCOST;
        
        //b. Searching for the low cost way...
        for (v = t ; v != s ; v = parent[v]){
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        
        //c. updating the flows on residual graph...
        for (v = t; v != s ; v = parent[v]){
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        
        //d. updating the maxflow...
        max_flow += path_flow;
    }
    
    //4. Printing the parents...
    u = t;
    while(u != -1){
        cout << u << " " << parent[u] << endl;
        u = parent[u];
    }
    return;
}

int main(){
    //1. Reading the number n of cities and the number m
    //of conections...
    int n, m;
    while((scanf("%d %d",&n,&m) != -1) && n != 0 && m != 0){
        //2. Creating an intmatrix...
        intmatrix matrix(n);
        for(int i = 0 ; i < n ; i++)
            matrix[i] = intvector(n,0);
        
        //3. Reading an adjmatrix...
        for(int i = 0 ; i < m ; i++){
            int a, b, cost;
            scanf("%d %d %d",&a,&b,&cost);
            matrix[a-1][b-1] = cost;
        }
        
        //4. Trying to find the min cut to this conections...
        mincutFordFulkerson(matrix,0,1,n);
        cout << "\n";
        
        //5. Clearing the matrix...
        for(int i = 0 ; i < n ; i++)
            matrix[i].clear();
        matrix.clear();
    }
    
    //5. Thats all folks :)...
    return 0;
}