#ifndef _HASH_H_
#define _HASH_H_

#include "btree.h"

typedef struct hash_table t_hashtable;
struct hash_table{
    int order;
    t_btree **entry;
};

void destroyHash(t_hashtable *);

void printHash(t_hashtable *);

void searchHash(int , t_hashtable *);

void removeHash(int , t_hashtable *);

void insertHash(int , t_hashtable *);

t_hashtable *createHash(int );

#endif