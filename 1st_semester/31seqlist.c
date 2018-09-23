/*
*	30 - Sequence List
* This program counts the occurrences of each number in a sequence.
*/
#include <stdlib.h>
#include <stdio.h>

float *readandsort(int n){
	//1. Reading
    int i;
	float input, *num = NULL;
	for(i = 0 ; i < n ; i++){
        scanf("%f",&input);
        num = (float *)realloc(num,sizeof(float)*(i+1));
        num[i] = input;
	}
	
	//2. Sorting (Bubble Sort)
	int j;
    float aux;
    for(i = n-1 ; i >= 1; i--) {
        for(j = 0 ; j < i ; j++) {
            if(num[j] > num[j+1]){
                aux = num[j];
                num[j] = num[j+1]; 
                num[j+1] = aux;
            }
        }
    }

    return num;
}

int main(int argc, char **argv){
	//0. Variables
	int i = 0, counter = 0, N = 0;
	float cur = 0, *num = NULL;
	
	//1. Reading the number N of inputs
    scanf("%d",&N);

	//2. Reading and sorting N real numbers
	num = (float *)malloc(sizeof(float)*N);
	num = readandsort(N);

	//3. Counting the occurrence and printing the result
    cur = num[0];
    for(i = 1; i < N ; i++){
		if(cur != num[i]){
			printf("%.1lf %d\n",cur,counter+1);
			cur = num[i];
			counter = 0;
		}
		else{
			counter++;
		}
    }
	printf("%.1lf %d\n",cur,counter+1);

	//4. Freeing the used memory
	free(num);

	//5. That's all folks... :)
	return 0;
}
