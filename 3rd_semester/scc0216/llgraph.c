#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "llgraph.h"

void destroy_llgraph(t_llgraph *graph){
    int i;
    for(i = 0 ; i < graph->nvertex ; i++){
        t_llvertex *aux = graph->vertex_list[i].next;
        while(aux != NULL){
            graph->vertex_list[i].next = aux->next;
            free(aux);
            aux = graph->vertex_list[i].next;
        }
    }
    free(graph->vertex_list);
    free(graph);
    return;
}

void print_minorendge_llgraph(t_llgraph *graph){
    int i, minorx, minory, minorvalue = INT_MAX;
    for(i = 0 ; i < graph->nvertex ; i++){
        t_llvertex *aux = graph->vertex_list[i].next;
        while(aux != NULL){
            if(minorvalue > aux->weight){
                minorvalue = aux->weight;
                minorx = i;
                minory = aux->index;
            }
            aux = aux->next;
        }
    }
    
    if(!graph->directed){
        if(minorx < minory)
            printf("%d %d\n",minorx,minory);
        else
            printf("%d %d\n",minory,minorx);
    }
    else printf("%d %d\n",minorx,minory);
    
    return;
}

void print_list_adjvertex(t_llgraph *graph, int vertex){
    t_llvertex *aux = graph->vertex_list[vertex].next;
    while(aux != NULL){
        printf("%d ",aux->index);
        aux = aux->next;
    }printf("\n");
    return;
}

void print_llgraph(t_llgraph *graph){
    int i;
    for(i = 0 ; i < graph->nvertex ; i++){
        printf("%d. ",i);
        t_llvertex *aux = graph->vertex_list[i].next;
        while(aux != NULL){
            printf("%d(%d) ",aux->index,aux->weight);
            aux = aux->next;
        }printf("\n");
    }
    return;
}

void remove_edge_llgraph(t_llgraph **graph, int v1, int v2){
    t_llvertex *pre = &((*graph)->vertex_list[v1]);
    t_llvertex *aux = (*graph)->vertex_list[v1].next;
    if(aux == NULL) return;
    
    while(aux != NULL && aux->index != v2){
        pre = aux;
        aux = aux->next;
    }
    if(aux != NULL && aux->index == v2){
        pre->next = aux->next;
        free(aux);
    }
    return;
}

t_llvertex *create_vertex(int index, int weight, t_llvertex *next){
    t_llvertex *vertex = (t_llvertex *)malloc(sizeof(t_llvertex));
        vertex->index = index;
        vertex->weight = weight;
        vertex->next = next;
    return vertex;
}

void insert_sort_edge(t_llvertex *vsource,t_llvertex *vnext, t_llvertex *vertex){
    if(vnext != NULL){
        if(vnext->index < vertex->index){
            insert_sort_edge(vsource->next,vnext->next,vertex);
            return;
        }
        else if(vnext->index == vertex->index){
            vnext->weight = vertex->weight;
            free(vertex);
            return;
        }
    }
    vertex->next = vsource->next;
    vsource->next = vertex;
    return;
}

void insert_edge_llgraph(t_llgraph **graph, int v1, int v2, int weight){
    if((*graph)->directed){
        insert_sort_edge(&((*graph)->vertex_list[v1]),(*graph)->vertex_list[v1].next,create_vertex(v2,weight,NULL));
    }
    else{
        insert_sort_edge(&((*graph)->vertex_list[v1]),(*graph)->vertex_list[v1].next,create_vertex(v2,weight,NULL));
        if(v1 != v2)
            insert_sort_edge(&((*graph)->vertex_list[v2]),(*graph)->vertex_list[v2].next,create_vertex(v1,weight,NULL));
    }
    return;
}

void initialize_llgraph(t_llgraph **graph, int nedges){
    int i, v1, v2, weight;
    for(i = 0 ; i < nedges ; i++){
        scanf("%d%*c",&v1);
        scanf("%d%*c",&v2);
        scanf("%d%*c",&weight);
        
        if((*graph)->directed){
            insert_sort_edge(&((*graph)->vertex_list[v1]),(*graph)->vertex_list[v1].next,create_vertex(v2,weight,NULL));
        }
        else{
            insert_sort_edge(&((*graph)->vertex_list[v1]),(*graph)->vertex_list[v1].next,create_vertex(v2,weight,NULL));
            if(v1 != v2)
                insert_sort_edge(&((*graph)->vertex_list[v2]),(*graph)->vertex_list[v2].next,create_vertex(v1,weight,NULL));
        }
    }
    return;
}

t_llvertex *create_vertexlist(int nvertex){
    int i;
    t_llvertex *list = (t_llvertex *)malloc(sizeof(t_llvertex)*nvertex);
    for(i = 0 ; i < nvertex ; i++){
        list[i].index = i;
        list[i].weight = 0;
        list[i].next = NULL;
    }
    return list;
}

t_llgraph *create_llgraph(int nvertex, int nedges, int directed){
    t_llgraph *graph = (t_llgraph *)malloc(sizeof(t_llgraph));
        graph->nvertex = nvertex;
        graph->nedges = nedges;
        graph->directed = directed;
        graph->vertex_list = create_vertexlist(nvertex);
    return graph;
}

void print_transp_llgraph(t_llgraph *graph){
    if(!graph->directed) return;

    int i;
    t_llgraph *trans =  create_llgraph(graph->nvertex,graph->nedges,graph->directed);
    for(i = 0 ; i < graph->nvertex ; i++){
        t_llvertex *aux = graph->vertex_list[i].next;
        while(aux != NULL){
            insert_edge_llgraph(&trans,aux->index,i,aux->weight);
            aux = aux->next;
        }
    }
    print_llgraph(trans);
    destroy_llgraph(trans);
    return;
}
