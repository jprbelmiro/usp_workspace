#ifndef _DLLIST_H_
#define _DLLIST_H_

typedef struct double_linked_list_node t_dllnode;
struct double_linked_list_node{
    int elem;
    t_dllnode *next, *prev;
};

typedef struct double_linked_list t_dllist;
struct double_linked_list{
    int size;
    t_dllnode *start, *end;
};

void printDLL(t_dllist *);
void destroyDLL(t_dllist *);
t_dllnode *createDLLNode(int );
void popFrontDLL(t_dllist **dll);
int getBackElemDLL(t_dllist *dll);
int getFrontElemDLL(t_dllist *dll);
void pushBackDLL(int , t_dllist **);
void pushFrontDLL(int , t_dllist **);
t_dllist *createDLL();

#endif