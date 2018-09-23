/*
* PROGRAM - VERIFY TRIANGLES
* This program verifies if three edges build a valid triangle.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int compare(const void *a, const void *b) {
   return -(*(int *)a - *(int *)b);
}

int main(int argc, char **argv){
    //0. Variables
    int i = 0, edge[3];
    char op = 'c';

    //1. Running the main program loop 
    printf("--- Verify Triangle ---\n");
    while(op != 'E' && op != 'e'){
	//a. Request the edges length
	printf("Enter the values for the triangle edges:\n");
	for( i = 0 ; i < 3 ; i++ ){	
	    //i. reading
	    printf("|Edge %d: ",i+1);
	    scanf("%d%*c",&edge[i]);
			
	    //ii. guaranteeing that the length of the edge is positive
	    if(edge[i] <= 0){
		printf("|:: enter a number greater than 0 for the edge::\n");
		i--;
	    }
    	}

	//b. Verifying the validity of the triangle and printing the result
	//i. sorting edges
	qsort(edge,3,sizeof(int),compare);
		
	//ii. sum of edges
	if(edge[0] > edge[1]+edge[2] || edge[1] > edge[2]+edge[1] || edge[2] > edge[0]+edge[1])
	   printf("It isn't a triangle.\n\n");
		
	//iii. classifying the triangle
	else{
	    printf("By sides: ");
	    if(edge[0] == edge[1] && edge[0] == edge[2])
		printf("This is an equilateral triangle\n");
	    else if(edge[0] == edge[1] || edge[0] == edge[2] || edge[1] == edge[2])
		printf("This is a isosceles triangle.\n");
	    else
		printf("This is a scalene triangle.\n");
			
	    printf("By angle: ");
	    if(pow(edge[0],2) == pow(edge[1],2)+pow(edge[2],2))
		printf("This is a right triangle.\n\n");
	    else if(pow(edge[0],2) > pow(edge[1],2)+pow(edge[2],2))
		printf("This is a obtuse triangle.\n\n");
	    else
		printf("This is an acute triangle.\n\n");
	}
		
	//c. Request the program operation
        printf("|To exit, enter 'E' or 'e'.\n|To realize more tests, digit another character or press ENTER.\n");
        scanf("%c",&op);
        if(op != '\n') scanf("%*c");
    }

    //2. That's all folks... :)
    return 0;
}
