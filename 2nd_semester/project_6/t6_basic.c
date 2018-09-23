#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void heapsort_strings(char **strings, int n){
   int i = n/2, father, son;
   char *aux = NULL;
   
   while(1){
      if(i > 0){
          i--;
          aux = strings[i];
      } 
      else{
          n--;
          if(n == 0) return;
          aux = strings[n];
          strings[n] = strings[0];
      }
      
      father = i;
      son = (i * 2)+1;
      
      while(son < n) {
          if((son + 1 < n)  &&  (strcmp(strings[son + 1],strings[son])>0)) son++;
          if(strcmp(strings[son],aux)>0){
             strings[father] = strings[son];
             father = son;
             son = father * 2 + 1;
          } else break;
      }
      
      strings[father] = aux;
   }
   
   return;
}

FILE *fopen_r(){
    FILE *file = NULL;
    char *file_name = NULL;
    
    while(file == NULL){
        scanf("%ms",&file_name);
        file = fopen(file_name,"r");
        
        if(file == NULL) printf("Invalid file. Try another.\n");
            free(file_name);
    }
    
    return file;
}