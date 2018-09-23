#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"
#include "hash.h"

void hashDestroy(t_hashtable **hash){
    int i = 0;
    t_entry *element= NULL;
    for(i = 0 ; i < (*hash)->size ; i++){
        element = (*hash)->table[i];
        while(element != NULL){
            (*hash)->table[i] = element->next;
            free(element->value);
            free(element);
            element = (*hash)->table[i];
        }
    }
    free((*hash)->table);
    free((*hash));
    return;
}

void hashPrint(t_hashtable *hash){
    int i = 0;
    t_entry *element= NULL;
    for(i = 0 ; i < hash->size ; i++){
        printf("[%d] ",i);
        element = hash->table[i];
        while(element != NULL){
            printf("(%s) ",element->value);
            element = element->next;
        }printf("\n");
    }
    return;
}

int hashing(t_hashtable *hashtable, char *value){
    int i = 0;
	unsigned long int hashkey = 1;
    int primes[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

	// Hashing the value...
	while(i < strlen(value)) {
	    i++;
		hashkey *= (primes[toupper(value[i]) % 25]);
		hashkey = hashkey % hashtable->size;
	}

	return hashkey;
}

int hashCount(t_hashtable *hash, char *value){
    int key = hashing(hash,value), count = 0;
    t_entry *element = hash->table[key];
    
    while(element != NULL){
        if(strcmp(element->value,value)==0)
            count++;
        element = element->next;
    }
    return count;
}

t_entry *hashNewPair(int key, char *value){
	t_entry *newpair = (t_entry *)malloc(sizeof(t_entry));
	    newpair->key = key;
        newpair->value = strdup(value);
        newpair->next = NULL;
	return newpair;
}

int hashSet(t_hashtable *hashtable, char *value){
	int key = 0, ret = 0;
	t_entry *newpair = NULL, *next = NULL, *last = NULL;

    //1. Calculating the key
	key = hashing(hashtable,value);

    //2. Taking the next pointer to new element...
	next = hashtable->table[key];

	while( next != NULL && strcmp(value,next->value ) > 0 ) {
		last = next;
		next = next->next;
	}

	//3. Set the new element...
	/*if( next != NULL && strcmp(value,next->value) == 0 ) {
	    ret = 0;
		free(next->value);
		next->value = strdup(value);
	} 
	else{*/
	    ret = 1;
		newpair = hashNewPair(key,value);

		if(next == hashtable->table[key]){
			newpair->next = next;
			hashtable->table[key] = newpair;
		} 
		else if( next == NULL ) {
			last->next = newpair;
		} 
		else {
			newpair->next = next;
			last->next = newpair;
		}
	//}
	
	//4. Return to the function call...
	//0 = the value already exists in hash...
	//1 = new value inserted...
	return ret;
}

t_hashtable *createHashTable(int size){
	int i = 0;
	t_hashtable *hashtable = NULL;

    //0. Verifying the hash size...
	if( size < 1 ) 
	    return NULL;

    //1. Allocate the table itself...
	hashtable = (t_hashtable *)malloc(sizeof(t_hashtable));

	//2. Allocate pointers to the head nodes...
	hashtable->table = (t_entry **)malloc(sizeof(t_entry *)*size);
	for( i = 0; i < size; i++ ) {
		hashtable->table[i] = NULL;
	}
	hashtable->size = size;

    //3. Returning the created hashtable...
	return hashtable;	
}