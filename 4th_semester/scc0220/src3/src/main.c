#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "hash.h"

int main(int argc, char **argv){
    //0. Variables
    int i = 0, nwords = 0, *occurrence = NULL;
    char *filename = NULL, **words = NULL, *string = NULL;
    FILE *inputfile = NULL;
    t_hashtable *hash = NULL;
    
    //1. Reading the name and openning the inputfile...
    filename = readLine(stdin,' ');
    inputfile = fopen_(filename,"r");
    
    //2. Reading the number of words to be searched in inputfile...
    scanf("%d\n",&nwords);
    words = (char **)malloc(sizeof(char *)*nwords);
    for(i = 0 ; i < nwords ; i++)
        words[i] = readLine(stdin,'\n');
    
    //3. Creating the occurrence vector and sorting the words...
    occurrence = (int *)calloc(nwords,sizeof(int));
    sortStrings(&words,0,nwords-1);
      
    //4. Creating a hashtable with all words of inputfile to optimize the
    //counting of each word...
    hash = createHashTable(101);
    while(!feof(inputfile)){
        string = readLine(inputfile,' ');
        formatString(&string);
        if(strcmp(string,"" "")!= 0 && string != NULL)
            hashSet(hash,string);
        free_(string);
    }
    
    //5. Counting the occurrence of each word in inputfile...
    for(i = 0 ; i < nwords ; i++){
        formatString(&words[i]);
        occurrence[i] = hashCount(hash,words[i]);
    }
        
    //6. Printing the result...
    for(i = 0 ; i < nwords ; i++)
        printf("%s %d\n",words[i],occurrence[i]);
    
    //. Closing opened files and freeing the memory...
    free(filename);
    fclose(inputfile);
    freeMatrix((void **)words,nwords);
    free(occurrence);
    hashDestroy(&hash);
    
    return 0;   
}