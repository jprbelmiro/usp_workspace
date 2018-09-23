/*                              TRABALHO 5 - DEQUE
    Inicialmente, pede-se ao usuário que entre com um número que representará
a operação que deseja realizar - no caso, o problema que deseja resolver.

    1) The Last Word
    - Para se resolver o "LastWord" segue-se os seguintes passos...
        1.a) Primeiro, cria-se um deque vazio...
        1.b) Depois, entra-se com a string de caracteres que dará origem ao desafio...
        1.c) E assim começa a resolução de fato do problema...
        Neste desafio, é necessário se alcançar a "palavra vencedora" (que é
        a maior palavra na ordem lexicográfica) somente usando a estrutura de
        dados de uma Lista Duplamente Encadeada. Então...
            1.i) Percorre-se toda a string armazenando elemento por elemento em um deque...
            1.ii) Caso seja o inicio do deque, cria-se um Nó que tem os extremos apontados
            para NULL...
            1.iii) Caso não seja, analisa-se onde vai ser colocado o novo elemento...
            1.iv) Ao fim, o resultado é impresso na tela...
        1.d) Por fim, libera-se a memória utilizada...


    2) Strings
    - Para se resolver o "Strings" segue-se os seguintes passos...
        2.a) Primeiro, cria-se um deque vazio...
        2.b) Depois, entra-se com duas strings de caracteres...
            - A string 'A' representará a string antes da organização encadeada e a string 'B'
            que representa uma possivel string de A pós encadeamento...
        2.c) E assim começa a resolução do desafio "Strings"...
        Para resolver este desafio, é necessário verificar se a string B entrada anteriormente
        realmente representa uma string encadeada de A. Para fazer isto é utilizada uma função
        recursiva para que todos os casos sejam tratados, mas levam-se em considerações alguns
        pontos especificos para otimização desta analise.
        Lembrando que sua resolução basicamente é a desconstrução do deque com mesmas caracte_
        risticas da string B, partindo da ultima letra da string de A, até a primeira.
        - Os pontos levados em conta são...
            2.i) Caso a letra de A analisada seja diferente da frente do deque B e do inicio
        do deque B, pode-se afirmar que B nao é um resultado de A.
            2.ii) Caso a letra de A analisada seja igual à frente do deque e igual ao inicio do
        deque, não é possível afirmar nada sem a análise de ambos os casos (desmontando o deque
        pelo inicio e desmontando pelo fim), sendo o resultado uma "soma" dos dois (uma vez que
        caso ele seja "TRUE" em uma das partes tem-se B como resultado do encadeamento de A).
            2.iii) Caso a letra de A analisada seja diferente da frente ou do inicio do deque, "des_
        monta-se" o deque partindo do inicio caso a letra seja igual ao elemento contido no Nó de
        inicio e partindo do fim caso a letra seja igual ao elemento contido no ultimo nó.
            2.iv) Caso acabe a string de A, pode-se afirmar que B é resultado de A.
        2.d) Por fim, libera-se a memória utilizada...

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum{
    no,
    yes
}answer;

/* Estrutura que armazena um elemento do Deque. */
typedef struct Node Node;

struct Node{
    Node *prev;
    char elem;
    Node *next;
};

/* Estrutura que armazena o Deque completo (referência para os Nodes encadeados). */
typedef struct Deque Deque;

struct Deque{
    Node *start;
    Node *end;
};

/* Aloca um Deque vazio na Heap. */
Deque *create(){
    Deque *whiteboard = (Deque *)calloc(1,sizeof(Deque));
    return whiteboard;
}

/* Retorna 1 caso o Deque esteja vazio e 0 caso contrário. */
int empty(Deque *board){
    if( board->start == NULL && board->end == NULL ) return 1;
        else return 0;
}

/* Remove o elemento da frente do Deque. */
void pop_front(Deque *board){
    Node *aux = board->end->prev;
        free(board->end);

	if(aux == NULL)
        board->start = NULL;
	else
        aux->next = NULL;

    board->end = aux;

	return;
}

/* Remove o elemento de trás do Deque. */
void pop_back(Deque *board){
    Node *aux = board->start->next;
        free(board->start);

	if(aux == NULL)
        board->end = NULL;
	else
        aux->prev = NULL;

    board->start = aux;

	return;
}

/* Remove todos os elementos do Deque. */
void clear(Deque *board){
    while(!empty(board))
        pop_front(board);

    return;
}

/* Remove todos os elementos e desaloca o Deque. */
void destroy(Deque *board){
    clear(board);
        free(board);
    return;
}

/* Insere o primeiro nó do Deque. */
void push_new(Deque *board, char c){
    Node *nodes = (Node *)malloc(sizeof(Node));

    nodes->elem = c;
    nodes->next = NULL;
    nodes->prev = NULL;
        board->start = nodes;
        board->end = nodes;
    return;
}

/* Insere um elemento na frente (na cabeça) do Deque. */
void push_front(Deque *board, char c){
    Node *nodes = (Node *)malloc(sizeof(Node));
    nodes->elem = c;
    nodes->prev = board->end;
    nodes->next = NULL;
        board->end->next = nodes;
        board->end = nodes;
    return;
}

/* Insere um elemento atrás (na cauda) do Deque. */
void push_back(Deque *board, char c){
    Node *nodes = (Node *)malloc(sizeof(Node));
    nodes->elem = c;
    nodes->prev = NULL;
    nodes->next = board->start;
        board->start->prev = nodes;
        board->start = nodes;
    return;
}

/* Retorna o elemento armazenado na frente do Deque. */
char front(Deque *board){
    return board->end->elem;
}

/* Retorna o elemento armazenado atrás do Deque. */
char back(Deque *board){
    return board->start->elem;
}

/* Retorna a quantidade de elementos do Deque. */
int size(Deque *board){
    int counter = 0;
	Node *aux = board->start;

	while(aux != NULL){
		aux = aux->next;
		counter++;
	}

	return counter;
}

/* Auxilia a função print na impressão de forma recursiva. */
void recursive_print(Node *nodes){
    if(nodes->next == NULL){
            printf("%c",nodes->elem);
            return;
    }

    printf("%c",nodes->elem);
        return recursive_print(nodes->next);
}

/* Imprime todos os elementos armazenados no Deque. */
void print(Deque *board){
        recursive_print(board->start);
    return;
}

/* Aloca e retorna uma string que esta na memoria HEAP. */
char *readLine(){
    char c, *string = NULL;
    int counter = 0;

    do{
        c = fgetc(stdin);
        string = (char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10);
    string[counter-1] = '\0';

    return string;
}

/* Verifica se é possível ou não uma resposta igual a entrada B. */
answer isPossibru( char *A, Node *back, Node *front, int i ){
        if( i < 0 )                                             // 2.iv)
            return yes;

        if( A[i] != back->elem && A[i] != front->elem ){        // 2.i)
                return no;
        }

        else if( A[i] == back->elem && A[i] == front->elem ){   // 2.ii)
                return (isPossibru(A,back->next,front,i-1) + isPossibru(A,back,front->prev,i-1));
        }

        else{
            if( A[i] == front->elem)                            // 2.iii)
                return (isPossibru(A,back,front->prev,i-1));
            else
                return (isPossibru(A,back->next,front,i-1));
        }
}

/* Cria um Deque com as caracteristicas dadas pela string B. */
void createStrings_deque( char *B , Deque *board ){
    int i;
    for( i = 0 ; i < strlen(B) ; i++ ){
        if( i == 0){
            push_new(board,B[i]);
        }
        else{
            push_front(board,B[i]);
        }
    }
}

/* Retorna uma resposta dizendo se é possível esta solução B ou não. */
void solveStrings( char *A , char *B , Deque *board ){
    createStrings_deque(B,board);
        answer ok = isPossibru(A,board->start,board->end,size(board)-1);
        if(ok) printf("S\n");
        else printf("N\n");

    return;
}

/* Resolve o problema "Strings" ( Seletiva UFMG para III MMP ) . */
void Strings(){
    Deque *board = create();    //2.a)

    char *A = readLine();       //2.b)
    char *B = readLine();

        solveStrings(A,B,board); //2.c)

    destroy(board);             //2.d)
    free(A);
    free(B);

    return;
}

/* Descobre a palavra certa do desafio */
void solveTLW( char *s , Deque *board ){
    int i;
    for( i = 0 ; i < strlen(s) ; i++){                      //1.i)

        if( i == 0){                                        //1.ii)
            push_new(board,s[i]);
        }

        else{                                               //1.iii)
            if( s[i] >= board->start->elem )
                push_back(board,s[i]);
            else
                push_front(board,s[i]);
        }

    }

    print(board);   //1.iv)

    return;
}

/* Resolve o desafio "The Last Word". */
void TheLastWord(){
    Deque *board = create();    //<---- 1.a)
    char *S = readLine();       //<---- 1.b)

        solveTLW(S,board);      //<----1.c)

    destroy(board);             //<---- 1.d)
    free(S);

    return;
}

/* Inicia o programa e escolhe qual desafio será resolvido */
int main(int argc, char *argv[]){
    int op;
        scanf("%d%*c",&op);

    switch(op){
        case 1:
            TheLastWord();
            break;

        case 2:
            Strings();
            break;
    }

	return 0;
}
