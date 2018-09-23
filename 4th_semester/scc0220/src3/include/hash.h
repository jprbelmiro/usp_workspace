#ifndef _HASH_H_
#define _HASH_H_

typedef struct entry_s t_entry;
struct entry_s {
	int key;
	char *value;
	t_entry *next;
};

typedef struct hashtable_s t_hashtable;
struct hashtable_s {
	int size;
	t_entry **table;	
};

void hashDestroy(t_hashtable **);
void hashPrint(t_hashtable *);
int hashCount(t_hashtable *, char *);
t_entry *hashNewPair(int , char *);
int hashing(t_hashtable *, char *);
int hashSet(t_hashtable *, char *);
t_hashtable *createHashTable(int );

#endif