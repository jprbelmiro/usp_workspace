#ifndef _PROJETO1_LINKEDL_H_
#define _PROJETO1_LINKEDL_H_

#include <stdlib.h>
#include <stdio.h>
#include "projeto1_basic.h"

#include "projeto1_linkedl.c"

//Estrutura responsavel por definir um no da lista ligada simples...
typedef struct node t_node;
//Estrutura responsavel por definir a base para a criacao de uma lista ligada...
typedef struct linkedlist t_linkedl;

//Funcao responsavel por liberar toda uma lista ligada guardada na memoria...
void free_linkedl(t_linkedl *);

//Funcao responsavel por criar um no da lista ligada...
t_node *create_linkedl_node(t_node *, char *, char *);
//Funcao responsavel por criar a base da lista ligada...
t_linkedl *create_linkedl();

//Funcao responsavel por inserir um elemento na lista ligada simples...
void insert_linkedlist(t_linkedl *, char *, char *);
//Funcao responsavel por buscar um elemento na lista ligada simples...
void search_linkedlist(t_node *, char *);
//Funcao responsavel por remover um elemento na lista ligada simples...
void delete_linkedlist(t_node *, char *, t_node *, t_linkedl *);

#endif