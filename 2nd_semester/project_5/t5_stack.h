#ifndef _T5_STACK_H_
#define _T5_STACK_H_

typedef struct stack_elem t_elem;
struct stack_elem{
    int elem;
    t_elem *down;
};

typedef struct stack{
    t_elem *top;
    int size;
} t_stack;

//Funcao responsavel por imprimir uma pilha na tela...
void print_stack(t_elem *);

//Funcao responsavel por criar e retornar o elemento de uma pilha...
t_elem *create_elem(int , t_elem *);

//Funcao responsavel por criar e retornar uma pilha armazenada na memoria...
t_stack *create_stack();

//Funcao responsavel por retirar o elemento do topo de uma pilha...
void pop_stack(t_stack *);

//Funcao responsavel por inserir um novo elemento em uma pilha...
void push_stack(t_stack *, int );

#endif