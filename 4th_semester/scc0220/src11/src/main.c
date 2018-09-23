#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "avl.h"
#include "match.h"

int main ( int argc, char **argv ){
    //0. Variable...
    char *string = NULL, *elem = NULL;
    t_avltree *tree = createAVLTree();
    
    //1. Operating on binary tree...
    while(!match((string = readLine(stdin,'\n')),"^\\s*X\\s*$")){
        
        if(match(string,"^\\s*I\\s+[-]*[0-9]+\\s*$")){
            elem = tokenize(string,1,' ');
            insertAVLTree(tree,atoi(elem));
            free_(elem);
        }
        else if(match(string,"^\\s*D\\s+[-]*[0-9]+\\s*$")){
            elem = tokenize(string,1,' ');
            deleteAVLNode(tree,atoi(elem));
            free_(elem);
        }
        else if(match(string,"^\\s*B\\s+[-]*[0-9]+\\s*$")){
            elem = tokenize(string,1,' ');
            t_anode *snode = searchAVLTree(tree,atoi(elem));
            if(snode)
                printf("Encontrado\n");
            else
                printf("Nao encontrado\n");
            free_(elem);
        }
        else if(match(string,"^\\s*N\\s*$")){
            printf("InOrdem: ");
            printInOrder(tree->root);
            printf("\n");
        }
        else if(match(string,"^\\s*E\\s*$")){
            printf("PreOrdem: ");
            printPreOrder(tree->root);
            printf("\n");
        }
        else if(match(string,"^\\s*O\\s*$")){
            printf("PosOrdem: ");
            printPosOrder(tree->root);
            printf("\n");
        }
        else if(match(string,"^\\s*L\\s*$")){
            printf("Largura: ");
            printBFS(tree->root);
            printf("\n");
        }
        else if(match(string,"^\\s*Y\\s*$")){
            printf("InOrdem: ");
            printInOrder(tree->root);
            printf("\n");
            printf("PreOrdem: ");
            printPreOrder(tree->root);
            printf("\n");
            printf("PosOrdem: ");
            printPosOrder(tree->root);
            printf("\n");
            printf("Largura: ");
            printBFS(tree->root);
            printf("\n");
        }
        
        free_(string);
    }free_(string);
    
    //2. Freeing the used memory...
    destroyAVLTree(tree);
    
    //3. Thats all folks ;)...
    return 0;
}