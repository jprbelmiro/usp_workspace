#ifndef _TREE_H_
#define _TREE_H_

typedef struct node t_node;
struct node{
    int elem, level, order;
    t_node **child;
};

typedef struct tree t_tree;
struct tree{
    int nnodes, nlevels, order;
    t_node *root;
};

void freeNode(t_node *);

void destroyTree(t_tree *);

void printTree(t_node *);

t_node *createNode(int , int , int );

t_tree *createTree(int );

t_tree *buildupTree(char *, int );

#endif