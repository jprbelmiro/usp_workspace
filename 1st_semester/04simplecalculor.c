/*
*	04 - Simple Calculator
*/
#include <stdio.h>

int main () {
    //0. Variables
    float a, b;
    char op;

    //1. Reading the values
    printf("Enter an operation (number[space]operation[space]number):\n");
    scanf("%f %c %f",&a,&op,&b);

    //2. Operating and printing the result
    switch(op){
        case '+':
            printf("%f\n", a + b);
        break;

        case '-':
            printf("%f\n", a - b);
        break;

        case '*':
            printf("%f\n", a * b);
        break;

        case '/':
            printf("%f\n", a / b);
        break;

        case '%':
            printf("%f\n", (a/ b)*100);
        break;
	default:
	    printf("unknown operation.\n");
	break;
    }

    //3. That's all folks... :)
    return 0;
}
