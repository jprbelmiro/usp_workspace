#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "amgraph.h"

void destroy_amgraph(t_amgraph *graph){
    int i;
    for(i = 0 ; i < graph->nvertex ; i++){
        free(graph->adj_matrix[i]);
    }free(graph->adj_matrix);
    free(graph);
    return;
}

void print_minorendge_amgraph(t_amgraph *graph){
    int i, j, minor = INT_MAX, x, y;
   
    for(i = 0 ; i < graph->nvertex ; i++){
        for(j = 0 ; j < graph->nvertex ; j++){
            if(graph->adj_matrix[i][j] >= 0 &&
                minor > graph->adj_matrix[i][j]){
                    minor = graph->adj_matrix[i][j];
                    x = i;
                    y = j;
            }
        }
    }
    
    if(graph->directed){
        if(x < y) printf("%d %d\n",x,y);
        else printf("%d %d\n",y,x);
            return;
    }
    else printf("%d %d\n",x,y);
    
    return;
}

void print_matrix_adjvertex(t_amgraph *graph, int vertex){
    int i;
    for(i = 0 ; i < graph->nvertex ; i++){
        if(graph->adj_matrix[vertex][i] >= 0)
            printf("%d ",i);            
    }printf("\n");
    return;
}

void print_transp_amgraph(t_amgraph *graph){
    int i, j;
    if(graph->directed){
        for(i = 0 ; i < graph->nvertex ; i++){
            for(j = 0 ; j < graph->nvertex ; j++){
                if(graph->adj_matrix[j][i] < 0){
                    printf(". ");
                }
                else{
                    printf("%d ",graph->adj_matrix[j][i]);
                }
            }printf("\n");
        }
    }
    return;
}

void print_amgraph(t_amgraph *graph){
    int i, j;
    for(i = 0 ; i < graph->nvertex ; i++){
        for(j = 0 ; j < graph->nvertex ; j++){
            if(graph->adj_matrix[i][j] < 0){
                printf(". ");
            }
            else{
                printf("%d ",graph->adj_matrix[i][j]);
            }
        }printf("\n");
    }
    return;
}

void insert_edge_amgraph(t_amgraph **graph, int v1, int v2, int weight){
    if((*graph)->directed){
        (*graph)->adj_matrix[v1][v2] = weight;   
    }
    else{
        (*graph)->adj_matrix[v1][v2] = weight;
        (*graph)->adj_matrix[v2][v1] = weight;
    }
    return;
}

void remove_edge_amgraph(t_amgraph **graph, int v1, int v2){
    if((*graph)->directed){
        (*graph)->adj_matrix[v1][v2] = -1;   
    }
    else{
        (*graph)->adj_matrix[v1][v2] = -1;
        (*graph)->adj_matrix[v2][v1] = -1;
    }
    return;
}

void initialize_amgraph(t_amgraph **graph, int nedges){
    int i, v1, v2, weight;
    for(i = 0 ; i < nedges ; i++){
        scanf("%d%*c",&v1);
        scanf("%d%*c",&v2);
        scanf("%d%*c",&weight);
        if((*graph)->directed){
            (*graph)->adj_matrix[v1][v2] = weight;
        }
        else{
            (*graph)->adj_matrix[v1][v2] = weight;
            (*graph)->adj_matrix[v2][v1] = weight;
        }
    }
    return;
}

int **create_set_sqrmatrix(int n, int set){
    int i, j, **matrix = (int **)malloc(sizeof(int *)*n);
    for(i = 0 ; i < n ; i++){
        matrix[i] = (int *)malloc(sizeof(int)*n);
        for(j = 0 ; j < n ; j++){
            matrix[i][j] = set;
        }
    }
    return matrix;
}

t_amgraph *create_amgraph(int nvertex, int nedges, int directed){
    t_amgraph *graph = (t_amgraph *)malloc(sizeof(t_amgraph));
        graph->nvertex = nvertex;
        graph->nedges = nedges;
        graph->directed = directed;
        graph->adj_matrix = create_set_sqrmatrix(nvertex,-1);
    return graph;
}
