#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "hash.h"

void destroyHash(t_hashtable *ht){
    int i = 0;
    for( i = 0 ; i < ht->order ; i++){
        destroyBTree(ht->entry[i]);
    }free_(ht->entry);
    free_(ht);
}

void printHash(t_hashtable *ht){
    int i = 0, arg = 0, pastsize = 0;
    for( i = 0 ; i < ht->order ; i++){
        int nelem = sizeBTree(ht->entry[i]->root);
        arg = nelem;
        
        if(i > 0 && nelem > 0 && pastsize > 0) printf(", ");
        
        if(nelem > 1) printf("(");
            
            printInOrder(ht->entry[i]->root,&arg);
            
        if(nelem > 1) printf(")");
        pastsize = (pastsize < nelem)?(nelem):(pastsize);
    }printf("\n");
}

void searchHash(int key, t_hashtable *ht){
    //1. Calculating the key's index...
    int idx = (key % ht->order);
    //2. Searching the key in your own idx...
    searchBTree(key,ht->entry[idx]->root);
}

void removeHash(int key, t_hashtable *ht){
    //1. Calculating the key's index...
    int idx = (key % ht->order);
    //2. Inserting the key in your own idx...
    deleteBTNode(key,&(ht->entry[idx]->root));
}

void insertHash(int key, t_hashtable *ht){
    //1. Calculating the key's index...
    int idx = (key % ht->order);
    //2. Inserting the key in your own idx...
    insertBTree(key,0,&(ht->entry[idx]->root));
}

t_hashtable *createHash(int order){
    t_hashtable *hash = (t_hashtable *)malloc(sizeof(t_hashtable));
        hash->order = order;
        hash->entry = (t_btree **)malloc(sizeof(t_btree *)*order);
    
    int i = 0;
    for(i = 0 ; i < order ; i++)
        hash->entry[i] = createBTree();
    
    return hash;
}