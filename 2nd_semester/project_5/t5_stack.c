#include <stdlib.h>
#include <stdio.h>
#include "t5_stack.h"

t_elem *create_elem(int elem, t_elem *down_elem){
    t_elem *new_elem = (t_elem *)malloc(sizeof(t_elem));
        new_elem->elem = elem;
        new_elem->down = down_elem;
    return new_elem;
}

t_stack *create_stack(){
    t_stack *new_stack = (t_stack *)malloc(sizeof(t_stack));
        new_stack->top = NULL;
        new_stack->size = 0;
    return new_stack;
}

void print_stack(t_elem *elem){
    if(elem->down == NULL){
        printf("[\t%d\t]\n\n",elem->elem);
        return;
    }
    
    printf("[\t%d\t]\n",elem->elem);
    return print_stack(elem->down);
}

void pop_stack(t_stack *stack){
    t_elem *aux = stack->top->down;
        free(stack->top);
    stack->top = aux;
    stack->size -= 1;
    return;
}

void push_stack(t_stack *stack, int elem){
    t_elem *new_elem = create_elem(elem,stack->top);
        stack->top = new_elem;
        stack->size += 1;
    return;
}