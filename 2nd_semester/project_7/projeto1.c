#include "projeto1_TADlist.h"

//Projeto 1 - Domain Name Server (DNS)
int main(int argc, char **argv){
    //Inicializando as variaveis...
    int N;
    char *O = NULL, *E = NULL, *C = NULL, *IP = NULL, *command_line = NULL;
    
    //1 - Lendo o numero de operações que serão realizadas e criando a 'base' da
    //lista ligada simples e da skip list...
    N = inNumber(stdin);
    t_linkedl *linkedl = create_linkedl();
    t_skipl *skipl = create_skiplist(N);
    
    //2 - Enquanto nao forem feitas as N operacoes solicitadas...
    while(N > 0){
        //a. Lendo a linha de comando entrada e tokanizando-a em Operacao(numero
        //- string), Estrutura (numero - string), Site/Servidor (string) e IP 
        //(string) - a linha e guardada na memoria...
        command_line = readLine(stdin);
        O = tokenize(0,command_line);
        E = tokenize(1,command_line);
        C = tokenize(2,command_line);
        IP = tokenize(3,command_line);

        //b. Iniciando a operacao entrada na estrutura escolhida...
        switch(atoi(O)){
            case 0:
                if(atoi(E) == 0)
                    insert_linkedlist(linkedl,C,IP);
                else if(atoi(E) == 1){
                    skipl->size += 1;
                    insert_skiplist(skipl->start[skipl->nlevel-1], C, IP, skipl->nlevel-1, randlevel(SKIPLIST_MAX_LEVEL(N)), NULL);
                }
                else
                    printf("Invalid struct...\n\n");
                break;
                
            case 1:
                if(atoi(E) == 0)
                    delete_linkedlist(linkedl->start,C,NULL,linkedl);
                else if(atoi(E) == 1){
                    skipl->size -= 1;
                    delete_skiplist(skipl->start[skipl->nlevel-1],C);
                }
                else
                    printf("Invalid struct...\n\n");
                break;   
                
            case 2:
                if(atoi(E) == 0)
                    search_linkedlist(linkedl->start,C);
                else if(atoi(E) == 1)
                    search_skiplist(skipl->start[skipl->nlevel-1],C);
                else
                    printf("Invalid struct...\n\n");
                break;
                
            default:
                printf("Invalid operation.\n\n");
        }
        
        //c. Liberando a linha de comando digitada da memoria e contabilizando
        //uma operacao...
        free(command_line);
        free(O); O = NULL;
        free(E); E = NULL;
        free(C); C = NULL;
        free(IP); IP = NULL;
        N--;
    }
    
    //3- Liberando a memoria utilizada nas listas...
    free_linkedl(linkedl);
    free_skipl(skipl,skipl->start[skipl->nlevel-1],skipl->nlevel-1);
    
    return 0;
}