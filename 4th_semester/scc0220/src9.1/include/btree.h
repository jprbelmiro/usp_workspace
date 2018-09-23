#ifndef _BTREE_H_
#define _BTREE_H_

typedef struct bnode t_bnode;
struct bnode{
    int elem, level, order;
    t_bnode *left, *right;
};

typedef struct btree t_btree;
struct btree{
    t_bnode *root;
};

void freeBNode(t_bnode *);

void destroyBTree(t_btree *);

int heightBTree(t_bnode *);

void printBFS(t_bnode *);

void printPosOrder(t_bnode *);

void printInOrder(t_bnode *);

void printPreOrder(t_bnode *);

t_bnode *createBNode(int , int );

void insertBTree(int , int , t_bnode **);

t_btree *createBTree();

#endif