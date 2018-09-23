#ifndef _AVL_H_
#define _AVL_H_

#define LEFTHEAVY(X) (X>=2)?(1):(0)
#define RIGHTHEAVY(X) (X<=-2)?(1):(0)

typedef struct avlnode t_anode;
struct avlnode {
    int elem;
	t_anode *left,*right;
};

typedef struct avltree t_avltree;
struct avltree {
	t_anode *root;
};

// CREATION FUNCTONS -------------------------------------------------------
t_avltree *createAVLTree();
t_anode *createAVLNode(int );

// GET PROP FUNCTIONS ------------------------------------------------------
int getAVLHeight(t_anode *);
int getBalanceFactor(t_anode * );
t_anode *getMinAVLNode(t_anode *);
t_anode *getMaxAVLNode(t_anode *);

// INSERT FUNCTIONS ---------------------------------------------------------
void insertAVLTree(t_avltree *, int  );

// DELETE AND FREE FUNCTIONS ------------------------------------------------
void deleteAVLNode(t_avltree *, int);
void destroyAVLTree(t_avltree *);

// SEARCH FUNCTIONS ---------------------------------------------------------
t_anode *searchAVLTree(t_avltree *,int );

// PRINT FUNCTIONS ----------------------------------------------------------
void printPosOrder(t_anode *);
void printInOrder(t_anode *);
void printPreOrder(t_anode *);
void printBFS(t_anode *);


#endif