#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"

void printDLL(t_dllist *dll){
    int i = 0;
    t_dllnode *aux = dll->start;
    for(i = 0 ; i < dll->size ; i++){
        printf("%d ",aux->elem);
        aux = aux->next;
    } printf("\n");
    return;
}

void destroyDLL(t_dllist *dll){
    if(dll == NULL)
        return;
        
    t_dllnode *aux = dll->start;
    while(aux != NULL && aux != dll->end){
        dll->start = aux->next;
        free(aux);
        aux = dll->start;
    }
    free(aux);
    free(dll);
    return;
}

t_dllnode *createDLLNode(int elem){
    t_dllnode *node = (t_dllnode *)malloc(sizeof(t_dllnode));
        node->elem = elem;
        node->next = node->prev = NULL;
    return node;
}

void pushBackDLL(int elem, t_dllist **dll){
    //1. Saving the actual start node...
    t_dllnode *aux = (*dll)->end;
    
    //2. Creating the new node...
    (*dll)->end = createDLLNode(elem);
    
    //3. Rearranging the list...
    if(aux != NULL){
        (*dll)->end->next = (*dll)->start;
        (*dll)->end->prev = aux;
        (*dll)->start->prev = (*dll)->end;
        aux->next = (*dll)->end;
    }
    else{
        (*dll)->start = (*dll)->end;
        (*dll)->end->next = (*dll)->end;
        (*dll)->end->prev = (*dll)->end;
    }
    
    //4. Incrementing dll size..
    (*dll)->size++;
    return;
}
void pushFrontDLL(int elem, t_dllist **dll){
    //1. Saving the actual start node...
    t_dllnode *aux = (*dll)->start;
    
    //2. Creating the new node...
    (*dll)->start = createDLLNode(elem);
    
    //3. Rearranging the list...
    if(aux != NULL){
        (*dll)->start->next = aux;
        (*dll)->start->prev = (*dll)->end;
        (*dll)->end->next = (*dll)->start;
        aux->prev = (*dll)->start;
    }
    else{
        (*dll)->end = (*dll)->start;
        (*dll)->start->next = (*dll)->start;
        (*dll)->start->prev = (*dll)->start;
    }

    //4. Incrementing dll size..
    (*dll)->size++;
    return;
}

void popFrontDLL(t_dllist **dll){
    if((*dll)->size == 0)
        return;
    
    //1. Saving the actual start next and prev node...
    t_dllnode *next = (*dll)->start->next;
    t_dllnode *prev = (*dll)->start->prev;

    //2. Rearranging the list...
    if((*dll)->size != 1){
        next->prev = prev;
        prev->next = next;
    }
    
    //3. Deleting the front node of memory...
    free((*dll)->start);
    (*dll)->start = next; 
    
    //4. Incrementing dll size..
    (*dll)->size--;
    return;
}

int getBackElemDLL(t_dllist *dll){
    return dll->end->elem;
}

int getFrontElemDLL(t_dllist *dll){
    return dll->start->elem;
}

t_dllist *createDLL(){
    t_dllist *dll = (t_dllist *)malloc(sizeof(t_dllist));
        dll->size = 0;
        dll->start = dll->end = NULL;
    return dll;
}