#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "avl.h"

// CREATION FUNCTONS -------------------------------------------------------
t_avltree *createAVLTree(){
	t_avltree *tree = (t_avltree *)malloc(sizeof(t_avltree));
	tree->root = NULL;
	return tree;
}
t_anode *createAVLNode(int elem){
	t_anode *node = (t_anode *)malloc(sizeof(t_anode));
	node->elem = elem;
	node->left = NULL;
	node->right = NULL;
	return node;	
}
static void createBFSMatrix(t_anode *node, int ***matrix, int **sizevec, int level){
    if(node == NULL)
        return;
        
    int l = level;
    int t = (*sizevec)[l];
    (*matrix)[l] = (int *)realloc((*matrix)[l],sizeof(int)*(t+1));
    (*matrix)[l][t] = node->elem;
    (*sizevec)[l] += 1;
    
    createBFSMatrix(node->left,matrix,sizevec,level+1);
    createBFSMatrix(node->right,matrix,sizevec,level+1);
    return;
}

// GET PROP FUNCTIONS ------------------------------------------------------
int getAVLHeight(t_anode *node){
	int leftHeight = 0;
	int rightHeight = 0;

    if(!node)
        return 0;
	if( node->left ) 
	    leftHeight = getAVLHeight(node->left);
    if( node->right ) 
    	rightHeight = getAVLHeight(node->right);

	return (rightHeight > leftHeight)?(rightHeight+1):(leftHeight+1);
}
int getBalanceFactor(t_anode *node ){
	int bf = 0;
	if(!node)
	    return 0;
	if( node->left  ) 
	    bf += getAVLHeight( node->left );
	if( node->right ) 
	    bf -= getAVLHeight( node->right );

	return bf ;
}
t_anode *getMinAVLNode(t_anode *node){
    if(!node) return NULL;
    if(!(node->left))
        return node;
    return getMinAVLNode(node->left);
}
t_anode *getMaxAVLNode(t_anode *node){
    if(!node) return NULL;
    if(!(node->right))
        return node;
    return getMinAVLNode(node->right);
}

// MAINTENANCE FUNCTIONS ---------------------------------------------------
static t_anode *rotateLeftLeft(t_anode *node){
 	t_anode *a = node;
	t_anode *b = a->left;
	
	a->left = b->right;
	b->right = a;
	
	return( b );
}
static t_anode *rotateLeftRight(t_anode *node){
	t_anode *a = node;
	t_anode *b = a->left;
	t_anode *c = b->right;
	
	a->left = c->right;
	b->right = c->left; 
	c->left = b;
	c->right = a;

	return( c );
}
static t_anode *rotateRightLeft(t_anode *node ){
	t_anode *a = node;
	t_anode *b = a->right;
	t_anode *c = b->left;
	
	a->right = c->left;
	b->left = c->right; 
	c->right = b;
	c->left = a;

	return( c );
}
static t_anode *rotateRightRight(t_anode *node){
	t_anode *a = node;
	t_anode *b = a->right;
	
	a->right = b->left;
	b->left = a; 

	return( b );
}
static t_anode *balanceNode(t_anode *node){
	t_anode *newroot = NULL;

	if( node->left )
		node->left  = balanceNode(node->left);
	if( node->right ) 
		node->right = balanceNode(node->right);

	int bf = getBalanceFactor(node);

	if(LEFTHEAVY(bf)){
		if(getBalanceFactor(node->left) <= -1) 
			newroot = rotateLeftRight(node);
		else 
			newroot = rotateLeftLeft(node);
	}
	else if(RIGHTHEAVY(bf)){
		if(getBalanceFactor(node->right) >= 1)
			newroot = rotateRightLeft(node);
		else 
			newroot = rotateRightRight(node);
	}
	else
		newroot = node;
	
	return( newroot );	
}
static void balanceAVLTree(t_avltree *tree ){
	t_anode *newroot = balanceNode(tree->root);

	if( newroot != tree->root )
		tree->root = newroot;
	return;
}

// INSERT FUNCTIONS ---------------------------------------------------------
void insertAVLTree(t_avltree *tree, int elem ){
	t_anode *node = NULL, *next = NULL, *last = NULL;

	if(tree->root == NULL){
		tree->root = createAVLNode(elem);
		balanceAVLTree(tree);
		return;
	} 

	next = tree->root;
	while(next != NULL) {
		last = next;

		if( elem < next->elem )
			next = next->left;
		else if( elem > next->elem ) 
			next = next->right;
		else{
			printf("Chave existente\n");
			return;
		}
	}

	node = createAVLNode(elem);
	if( elem < last->elem ) 
	    last->left = node;
	if( elem > last->elem ) 
	    last->right = node;

	balanceAVLTree(tree);
	return;
}

// DELETE AND FREE FUNCTIONS ------------------------------------------------
static t_anode* removeAVLNode(t_anode* root, int elem){
    if (root == NULL)
        return root;
        
    //0. Variables...
    t_anode *temp = NULL;
    
    //1. PERFORM STANDARD BST DELETE
    if(elem < root->elem)
        root->left = removeAVLNode(root->left,elem);
    else if( elem > root->elem )
        root->right = removeAVLNode(root->right,elem);
    else{
        //a. One child case...
        if(!(root->left) || !(root->right)){
            temp = (root->left)?(root->left):(root->right);
 
            //b. None child case...
            if(temp == NULL){
                temp = root;
                root = NULL;
            }
            else{
                *root = *temp;
            }
            free(temp);
        }
        else{
            //c. Two child case...
            temp = getMinAVLNode(root->right);
            root->elem = temp->elem;
            root->right = removeAVLNode(root->right, temp->elem);
        }
    }
    
    //c. Empty tree...
    if (root == NULL)
      return root;

    //2. GET THE BALANCE FACTOR OF THIS NODE 
    return balanceNode(root);
}
void deleteAVLNode(t_avltree *tree, int elem){
    //1. Verifying the existence of node...
    t_anode *snode = searchAVLTree(tree,elem);
    if(snode){
        printf("%d\n",snode->elem);
        //2. Real deletation of the node...
        tree->root = removeAVLNode(tree->root,elem);
    }
    else
        printf("Nao encontrado\n");
    return;
}
void destroyAVLTree(t_avltree *tree){
    while(tree->root)
        tree->root = removeAVLNode(tree->root,tree->root->elem);
    free_(tree);
    return;
}

// SEARCH FUNCTIONS ---------------------------------------------------------
t_anode *searchAVLTree(t_avltree *tree,int elem){
    if(!tree->root)
        return NULL;
    
	t_anode *current = tree->root;

	while(current && current->elem != elem) {
		if(elem > current->elem )
			current = current->right;
		else
			current = current->left;
	}

	return current;
}

// PRINT FUNCTIONS ----------------------------------------------------------
void printPosOrder(t_anode *tree){
    if(tree){
        printPosOrder(tree->left);
        printPosOrder(tree->right);
        printf("%d ",tree->elem);
    }
    return;
}
void printInOrder(t_anode *tree){
    if(tree){
        printInOrder(tree->left);
        printf("%d ",tree->elem);
        printInOrder(tree->right);
    }
    return;
}
void printPreOrder(t_anode *tree){
    if(tree){
        printf("%d ",tree->elem);
        printPreOrder(tree->left);
        printPreOrder(tree->right);
    }
    return;
}
void printBFS(t_anode *root){
    if(!root)
        return;
        
    //0. Variables...
    int i = 0, j = 0, maxlevel = 0;
    int *sizevec = NULL, **lmatrix = NULL;
        
    //1. Creating a preference level matrix...
    maxlevel = getAVLHeight(root);
    sizevec = (int *)calloc(maxlevel+1,sizeof(int));
    lmatrix = (int **)calloc(maxlevel+1,sizeof(int *));
    
    createBFSMatrix(root,&lmatrix,&sizevec,0);
    
    //2. Printing in BFS...
    for(i = 0 ; i < maxlevel ; i++){
        if(sizevec[i] != 0){
            for(j = 0 ; j < sizevec[i] ; j++)
                printf("%d ",lmatrix[i][j]);
        }
    }
    
    //3. Freeing used memory...
    for(i = 0 ; i < maxlevel ; i++){
        if(sizevec[i] != 0){
            free_(lmatrix[i]);
        }
    }free_(lmatrix);
    free_(sizevec);
    return;
}