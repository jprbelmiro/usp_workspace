#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void swap(int *vector, int i, int j){
    int aux = vector[i];
        vector[i] = vector[j];
        vector[j] = aux;
    return;
}

void insertionsort(int *vector, int size, int *C, int *M){
   int i, key, j;
   for (i = 1; i < size; i++){
       key = vector[i];
       (*M)++;
       j = i-1;
       while (j >= 0 && vector[j] > key){
           (*C)++;
           vector[j+1] = vector[j];
           (*M)++;
           j = j-1;
       }
       vector[j+1] = key;
       (*M)++;
   }
   return;
}

void bubblesort(int *vector, int size, int *C, int *M){
    int i, j;
    for(i = size-1 ; i > 0; i--){
        for(j = 0; j < i; j++){
            (*C)++;
            if(vector[j] > vector[j+1]){
                swap(vector,j,j+1);
                (*M)+=3;
            }
        }
    }
    return;
}

static void merge(int *vector, int start, int mid, int end, int *C, int *M){
    int i = 0, lp = start, rp = mid+1, size = (end-start)+1;
    int *auxvec = (int *)malloc(sizeof(int)*size);
    (*M)+=size;
    for(i = 0 ; i < size ; i++){
        if(lp < mid+1 && rp <= end){
            (*C)++;
            auxvec[i] = (vector[lp] < vector[rp])?(vector[lp++]):(vector[rp++]);
            (*M)++;
        }
        else if(lp < mid+1){
            auxvec[i] = vector[lp++];
            (*M)++;
        }
        else{
            auxvec[i] = vector[rp++];
            (*M)++;
        }
    }
    for(i = 0 ; i < size ; i++){
        vector[i+start] = auxvec[i];
        (*M)++;
    }
        
    free(auxvec);
    return;
}
void mergesort(int *vector, int start, int end, int *C, int *M){
    if(start < end) {
        int mid = start+(end-start)/2;
        //1. Divide...
        mergesort(vector,start,mid,C,M);
        mergesort(vector,mid+1,end,C,M);
        //2. Conquer...
        merge(vector,start,mid,end,C,M);
    }
    return;
}

static void heapify(int *vector, int size, int i, int *C, int *M){
    int largest = i, l = 2*i + 1, r = 2*i + 2;

    
    if(l < size){
        (*C)++;
        if(vector[l] > vector[largest])
            largest = l;
    }
    
    if(r < size){
        (*C)++;
        if(vector[r] > vector[largest])
            largest = r;
    }
 
    if(largest != i){
        swap(vector,i,largest);
        (*M)+=3;
        heapify(vector,size,largest,C,M);
    }
    return;
}
void heapsort(int *vector, int size, int *C, int *M){
    //1. Build heap...
    int i;
    for (i = (size/2)-1 ; i >= 0; i--)
        heapify(vector,size,i,C,M);
        
    for(i = size-1; i >= 0; i--){
        swap(vector,0,i);
        (*M)+= 3;
        heapify(vector,i,0,C,M);
    }
    return;
}

void quicksort(int *a, int left_index, int right_index, int *C, int *M){
	int left, right, pivot;
	if(left_index >= right_index) 
	    return;

	left = left_index;
	right = right_index;

	pivot = a[(left_index + right_index) /2];
	(*M)++;

	while(left <= right) {
	    (*C)++;
		while(a[left] < pivot){
		    left++;
		    (*C)++;
		}
		(*C)++;
		while(a[right] > pivot){
		    right--;
		    (*C)++; 
		}
		if(left <= right) {
			swap(a,left,right);
			(*M)+=3;
			left++; right--;
		}
	}
    
	quicksort(a,left_index,right,C,M);
	quicksort(a,left,right_index,C,M);   
}
