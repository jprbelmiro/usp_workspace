#include <stdio.h>
#include <hash.h>

enum{
    INSERTION = 1,
    REMOVAL,
    SEARCH,
    PREVIEW,
    SHUTDOWN
};

int main(void){
    int op, key;
    t_hash H;
    createHash(&H);
    
    printf("Bem vindo ao manipulador de HASH TABLES de 16 posicoes\n");
    do{
        printf("As opções de interacao sao: \n");
        printf("1. Insercao\n2. Remocao\n3. Busca\n4.Visualizacao\n5. Finaliza a execucao\n");
        printf("- Digite a opcao desejada: \n");
        scanf("%d", &op);
        switch(op){
            case INSERTION:
                printf("Voce selecionou a operacao de insercao.\n");
                do{
                    printf("Digite o numero que deseja inserir na HASH: ");
                    scanf("%d", &key);
                    if(key >= 0) insertHash(&H, key);
                }while(key != -1);
                break;
            case REMOVAL:
                printf("Voce selecionou a operacao de remocao.\n");
                do{
                    printf("Digite o numero que deseja remover da HASH: ");
                    scanf("%d", &key);
                    if(key >= 0) removeHash(&H, key);
                }while(key != -1);
                break;
            case SEARCH:
                printf("Voce selecionou a operacao de busca.\n");
                do{
                    printf("Digite o numero que deseja buscar na HASH: ");
                    scanf("%d", &key);
                    if(key >= 0) printf("%d\n", searchItemHash(&H, key));
                }while(key != -1);
                break;
            case PREVIEW:
                printf(":: VISUALIZACAO - HASH ::\n");
                printHash(&H);
                break;
            case SHUTDOWN:
                printf("Execucao finalizada. Agradecemos a preferencia.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }while(op != 5);
    
    destroyHash(&H);
    return 0;
}