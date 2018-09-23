#ifndef _LLGRAPH_H_
#define _LLGRAPH_H_

typedef struct linkedlist_vertex t_llvertex;
struct linkedlist_vertex{
    int index;
    int weight;
    t_llvertex *next;
};

typedef struct linkedlist_graph t_llgraph;
struct linkedlist_graph{
    int nedges;
    int nvertex;
    int directed;
    t_llvertex *vertex_list;
};

void destroy_llgraph(t_llgraph *);
void print_minorendge_llgraph(t_llgraph *);
void print_transp_llgraph(t_llgraph *);
void print_list_adjvertex(t_llgraph *, int );
void print_llgraph(t_llgraph *);
void insert_edge_llgraph(t_llgraph **, int , int , int );
void remove_edge_llgraph(t_llgraph **, int , int );
void initialize_llgraph(t_llgraph **, int );
t_llgraph *create_llgraph(int , int , int );

#endif