#ifndef _AMGRAPH_H_
#define _AMGRAPH_H_

typedef struct adjacency_matrix t_amgraph;
struct adjacency_matrix{
    int nedges;
    int nvertex;
    int directed;
    int **adj_matrix;
};

void destroy_amgraph(t_amgraph *);
void print_minorendge_amgraph(t_amgraph *);
void print_transp_amgraph(t_amgraph *);
void print_matrix_adjvertex(t_amgraph *, int );
void print_amgraph(t_amgraph *);
void insert_edge_amgraph(t_amgraph **, int , int , int );
void remove_edge_amgraph(t_amgraph **, int , int );
void initialize_amgraph(t_amgraph **, int );
t_amgraph *create_amgraph(int , int , int );

#endif