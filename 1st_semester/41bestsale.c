/*
*   41 - Best sale
* This program shows the best sale value and the best days for a month
*/
#include <stdlib.h>
#include <stdio.h>

void bestsalesDay(int *sales, int bestsale){
    int i;
    for(i = 0; i < 31 ; i++)
        if(sales[i]== bestsale) 
			printf("%d\n",i+1);
    return;
}

int getbestsale(int *sales){
    int i = 0, bestsale = sales[i];
    for(i = 0; i < 31 ; i++)
		if(bestsale < sales[i]) 
			bestsale = sales[i];
    printf("%d\n",bestsale);
    return bestsale;
}

int main(int argc, char **argv){
	//0. Variables
	int i = 0, bestsale = 0, *sales = NULL;

	//1. Reading the sell value in the month
    sales = (int *)malloc(sizeof(int)*31);
    for(i = 0; i < 31 ; i++){
        scanf("%d",&(sales[i]));
    }

	//2. Discovering and printing the best sale value
    bestsale = getbestsale(sales);

	//3. Discovering and printing the best sale days
    bestsalesDay(sales, bestsale);

	//4. Freeing the used memory
    free(sales);

	//5. That's all folks... :)
    return 0;
}
