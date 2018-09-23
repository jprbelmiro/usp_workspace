#ifndef _HASH_H_
#define _HASH_H_

#include <dllist.h>
//t_hash é um vetor de listas
typedef t_list *t_hash;

void createHash(t_hash *H);
void removeHash(t_hash *H, t_item item);
void insertHash(t_hash *H, t_item item);
void printHash(t_hash *H);
int searchItemHash(t_hash *H, t_item item);
void destroyHash(t_hash *H);

#endif