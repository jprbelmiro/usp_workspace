/*
* PROGRAM 01 - VARIABLE TYPES SIZE
* This program print on screen each variable type and your size (byte).
*/
#include <stdio.h>

int main () {
    //1. Printing on screen
    printf ("char = %d bytes\n", (int)sizeof(char));
    printf ("unsigned int = %d bytes\n", (int)sizeof(unsigned int));
    printf ("short int = %d bytes\n", (int)sizeof(short int));
    printf ("int = %d\n", (int)sizeof(int));
    printf ("long int = %d bytes\n", (int)sizeof(long int));
    printf ("unsigned long int = %d bytes\n", (int)sizeof(unsigned long int));
    printf ("long long int = %d bytes\n", (int)sizeof(long long int));
    printf ("float = %d bytes\n", (int)sizeof(float));
    printf ("double = %d bytes\n", (int)sizeof(double));
    printf ("long double = %d bytes\n", (int)sizeof(long double));

    //2. That's all folks... :)
    return 0;
}
