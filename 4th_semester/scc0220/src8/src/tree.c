#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "tree.h"

void freeNode(t_node *tree){
    int i = 0;
    if(tree){
        if(tree->child)
            for(i = 0 ; i < tree->order ; i++)
                freeNode(tree->child[i]);
        free_(tree->child);
        free_(tree);
    }
    return;
}

void destroyTree(t_tree *tree){
    freeNode(tree->root);
    free_(tree);
    return;
}

void printTree(t_node *tree){
    int i = 0;
    if(tree){
        printf("%c\n",tree->elem);
        if(tree->child)
            for(i = 0 ; i < tree->order ; i++)
                printTree(tree->child[i]);
    }
    return;
}

t_node *createNode(int elem, int level, int order){
    t_node *node = (t_node *)malloc(sizeof(t_node));
        node->elem = elem;
        node->level = level;
        node->order = order;
        node->child = NULL;
    return node;
}

t_tree *createTree(int order){
    t_tree *tree = (t_tree *)malloc(sizeof(t_tree));
        tree->nnodes = 0;
        tree->nlevels = 0;
        tree->order = order;
        tree->root = NULL;
    return tree;
}

static void insertBuildup(string source, int *idx, int level, int order, t_node *node, t_tree *tree){
    if(*idx > strlen(source))
        return;
        
    int i = 0;
    node->child = (t_node **)malloc(sizeof(t_node *)*order);
    for(i = 0 ; i < order ; i++){
        node->child[i] = createNode(source[*idx],level+1,order);
        if(source[(*idx)++] == 'p')
            insertBuildup(source,idx,level+1,order,node->child[i],tree);
        tree->nnodes++;
        
        if(tree->nlevels < level)
            tree->nlevels = level;
    }
    return;
}

t_tree *buildupTree(char *source, int order){
    int idx = 1;
    t_tree *tree = createTree(order);
    
    tree->root = createNode('p',0,order);
    insertBuildup(source,&idx,0,order,tree->root,tree);
    
    return tree;
}