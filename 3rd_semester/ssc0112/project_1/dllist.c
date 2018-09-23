#include <stdio.h>
#include <stdlib.h>
#include <dllist.h>


void createList(t_list *lista){
	*lista = NULL;
}

//Argumentos: passa uma lista por referencia e um item como argumento
//Funcao: cria-se então um novo nó com o item e insere-o ordenado na lista
//Retorno: não há retorno
void insertList(t_list *lista, t_item item){
	t_node *p, *new_node;
	p = *lista;
	
	new_node = (t_node *) malloc(sizeof(t_node));
	if (new_node == NULL){
		printf("Erro: memoria insuficiente\n");
		exit(EXIT_FAILURE);
	}
	
	new_node->item = item;
	//caso de lista vazia
	if(*lista == NULL || (*lista)->item > item){
		//rearranjando os ponteiros
		new_node->ant = NULL;
		new_node->prox = *lista;
		if(*lista != NULL) (*lista)->ant = new_node;
		*lista = new_node;
		return;
	}
	
	//buscando posicao de forma sequencial
	while(p->prox != NULL && p->prox->item < item)p = p->prox;
	
	//rearranjando os ponteiros
	new_node->ant = p;
	new_node->prox = p->prox;
	if(p->prox != NULL) p->prox->ant = new_node;
	p->prox = new_node;
}

//Args: recebe como argumento uma t_list lista e um t_item item
//Funcao: procura um nó com item igual ao item passado por argumento
//Retorno: Retorna o nó buscado, caso ele nao existir retornar NULL
t_node *searchItemList(t_list lista, t_item item){
	t_node *p = lista;
	while(p != NULL && p->item != item)p = p->prox;
	return p;
}

//Argumentos: recebe a lista e o item como argumentos 
//Funcao: procura o nó na lista em que o item é igual ao 
//item passado como argumento e então remove-se esse nó 
//apos o rearranjo dos ponteiros da lista, caso nao existir
//nó com item igual ao consultado a funcao não faz nada
//Retorno: nao há retorno
void removeItemList(t_list *lista, t_item item){
	t_node *p;
	//buscando nó de forma sequencial
	p = searchItemList(*lista, item);
	//caso nao for encontrado encerrar procedimento
	if(p == NULL) return;
	//tratando caso de remocao na cabeça
	if(p == *lista){
		p = (*lista)->prox;
		if(p != NULL) p->ant = NULL;
		free(*lista);
		*lista = p;
		return;
	}
	//rearranjando os ponteiros e removendo o nó
	if(p->prox != NULL) p->prox->ant = p->ant;
	p->ant->prox = p->prox;
	free(p);
}

//Argumentos: recebe um t_list e um t_item como argumentos
//Funcao: procura o nó de forma sequencial
//Retorno: caso o nó existir retorno é 1,
//caso o contrario retorno é 0
int FindItemInList(t_list lista, t_item item){
	t_node *p = searchItemList(lista, item);
	return p != NULL;
}

//Args: recebe uma lista como argumento
//Funcao: imprime todos os itens da lista em uma linha
//retorno: nao ha retorno
void printList(t_list lista){
	t_node *p = lista;
	while(p != NULL){
		printf("%d ", p->item);
		p = p->prox;
	}
	
	printf("\n");
}

//argumentos: recebe uma lista
//funcao: verifica se a lista esta vazia
//Retorno: retorna 1 caso a lista estiver vazia,
//caso contrario, retorna 0
int emptyList(t_list *lista){
	return (*lista == NULL);
}

//liberando estruta da memoria
void destroyListRecursive(t_node *node){
	if(node == NULL) return;
	destroyListRecursive(node->prox);
	free(node);
}
void destroyList(t_list *lista){
	destroyListRecursive(*lista);
}