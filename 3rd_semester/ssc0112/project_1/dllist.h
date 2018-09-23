#ifndef _DDLIST_H_
#define _DDLIST_H_

//item sera o valor do inteiro
typedef int t_item;
//nó salva um inteiro(t_item) e o endereco do prox no
typedef struct node {
	t_item item;
	struct node *prox;
	struct node *ant;
} t_node;

//t_list aponta pra cabeca da lista
typedef t_node *t_list;

void createList(t_list *lista);
void insertList(t_list *lista, t_item item);
void removeItemList(t_list *lista, t_item item);
int FindItemInList(t_list lista, t_item item);
void printList(t_list lista);
int emptyList(t_list *lista);
void destroyList(t_list *lista);

#endif