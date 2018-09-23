#ifndef _SORT_H_
#define _SORT_H_

#define FATHER(i) ((i-1)/2)

void swap(int *, int , int );
void insertionsort(int *, int , int *, int *);
void bubblesort(int *, int ,int *, int *);
void mergesort(int *, int , int ,int *, int *);
void heapsort(int *, int ,int *, int *);
void quicksort(int *, int , int ,int *, int *);

#endif