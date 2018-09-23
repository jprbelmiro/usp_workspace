#ifndef _PROJETO1_SKIPL_H_
#define _PROJETO1_SKIPL_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "projeto1_linkedl.h"

#include "projeto1_skipl.c"

typedef struct snode t_snode;
typedef struct skiplist t_skipl;

void free_skipl(t_skipl *, t_snode *, int);

int randlevel(int );
t_snode *create_skiplist_snode( char *, char *, t_snode *,t_snode *);
t_skipl *create_skiplist();

void insert_skiplist(t_snode *, char *, char *, int, int, t_snode *);
void search_skiplist(t_snode *, char *);
void delete_skiplist(t_snode *, char *);

#endif