#include <string.h>
#define NO -1

//ESTRUTURA --------------------------------------------------------------------
typedef struct binary_list{
    char symbol;
    int *binary;
    int nbits;
}t_binlist;

//ESTRUTURA ARVORE -------------------------------------------------------------
typedef struct node{
    char *symbol;
    int nsymbol;
    int frequency;
    int bit;
    struct node *left;
    struct node *right;
}t_node;

typedef struct list{
    t_node *elem;
    int nelem;
}t_list;

typedef struct tree{
    t_node *root;
}t_tree;

//FUNCOES AUXILIARES  ----------------------------------------------------------
//------------------------- LIBERACAO DE MEMORIA -------------------------------
//Funcao responsavel por desalocar uma lista binaria da mamoria...
void freebinl(t_binlist *binl, int n){
    int i;
    for(i = 0 ; i < n ; i++)
        free(binl[i].binary);

    free(binl);
    return;
}

//Funcao responsavel por desalocar uma arvore binaria da memoria...
void freetree(t_tree *tree, t_node *leaf){
    if(leaf == NULL)
        return;
    
    freetree(tree,leaf->left);
    freetree(tree,leaf->right);
    
    free(leaf->symbol);
    free(leaf);
    return;
}

//------------------------ IMPRESSAO / TOKANIZE --------------------------------
//Funcao responsavel por concatenar duas strings de caracteres...
char *sumsymbols(char *s1, char *s2){
    int i,j, counter = 0;
    char c;
    char *string = NULL;
    
    for(i = 0 ; i < 2; i++){
        j = 0;
        do{
            (i == 0 )? (c = s1[j++]) : (c = s2[j++]);
            if(c != '\0'){
                string = (char *)realloc(string,sizeof(char)*(counter+1));
                string[counter++] = c;
            }
        }while(c != '\0');
    }
    string = (char *)realloc(string,sizeof(char)*(counter+1));
    string[counter++] = '\0';
    
    return string;
}

//Funcao responsavel por verificar se um binario lido corresponde a outro exis_
//tente na lista de binarios de Huffman. Caso haja correspondencia, a funcao
//retorna ao usuario qual a posicao na lista binaria do binario correspondente..
int digit_match(int *vec, int len, t_binlist *bin, int nsymbol){
    int i,j;
    
    for(i = 0 ; i < nsymbol ; i++){
        if(len == bin[i].nbits){
            for(j = 0 ; j < len ; j++){
                if(vec[j] != bin[i].binary[j])
                    break;
            }
            if(j == len)
                return i;
        }
    }
    
    return -1;
}

//Funcao responsavel por realizar de fato a descompactacao de um arquivo .huff e
//imprimir na tela o texto descompactado...
void printtext(FILE *fp, t_binlist *bin, int nsymbol){
    
    char c;
    int i,j = 0,counter = 0, binary, last_binary;
    int *binary_vec = NULL, *aux = NULL;
    
    //Criando um vetor que contem o "texto compactado"...
    while(!feof(fp)){
        c = fgetc(fp);
        last_binary = binary;
        if(!feof(fp)){
            for(i = 0; i < 8 ; i++){
                binary = c;
                binary_vec = (int *)realloc(binary_vec,sizeof(int)*(counter+1));
                (binary & 128>>i) == 0? (binary_vec[counter++] = 0) : (binary_vec[counter++] = 1);
            }
        }
    }
    
    //Imprimindo na tela a mensagem compactada...
    for(i = 0; i < counter-16; i++){
        aux = (int *)realloc(aux,sizeof(int)*(j+1));
        aux[j++] = binary_vec[i];
        if((binary = digit_match(aux,j,bin,nsymbol)) != -1){
            j = 0;
            free(aux);
            aux = NULL;
            printf("%c",bin[binary].symbol);
        }
    }
    
    for(; i < counter - 16 + last_binary; i++){
        aux = (int *)realloc(aux,sizeof(int)*(j+1));
        aux[j++] = binary_vec[i];
        if((binary = digit_match(aux,j,bin,nsymbol)) != -1){
            j = 0;
            free(aux);
            aux = NULL;
            printf("%c",bin[binary].symbol);
        }
    }printf("\n");
    
    if(aux != NULL) free(aux);
    free(binary_vec);
    
    return;
}

//Funcao responsavel por imprimir na tela o valor dos bytes do texto compactado.
void printbinary(FILE *fp, t_binlist *bin, int n){
    fseek(fp,0,SEEK_SET);
    
    char c;
    int *binary_vec = NULL;
    int i, j,sum, size = 0,counter;
	
    while(!feof(fp)){
	    c = fgetc(fp);
	    if(c != EOF){
	       counter = 0;
	        while( c != bin[counter].symbol) counter++;
	        for(i = 0 ; i < bin[counter].nbits ; i++){
	               binary_vec = (int *)realloc(binary_vec,sizeof(int)*(size+1));
	               binary_vec[size++] = bin[counter].binary[i];
	        }
	    }
    }
    
    counter = size;
    for( i = 0 ; i < 8 - (counter % 8) ; i++){
        binary_vec = (int *)realloc(binary_vec,sizeof(int)*(size+1));
        binary_vec[size++] = 0;
    }
        
    for( i = 0 ; i < size/8 ; i++){
        sum = 0;
        for(j = 0 ; j < 8 ; j++){
            sum += binary_vec[j+i*8]*pow(2,7-j);
        }
        printf("%d\n",sum);
    }
        
    printf("%d\n",counter % 8);

    free(binary_vec);

    return;
}

//Funcao responsavel por percorrer uma arvore binaria em ordem com intuito de
//retornar ao usuario o caminho de bits para cada folha da arvore de Huffman,
//guardando-os em uma "lista binaria"...
void inOrder(t_node *node, int **bitway, int counter, t_binlist *binl,int *n){
    
    int i;
    
    if(node->left == NULL && node->right == NULL){
        binl[*n-1].symbol = (*node).symbol[0];
	    binl[*n-1].nbits = counter;

        binl[*n-1].binary = (int *)malloc(sizeof(int)*counter);
        for(i = 0 ; i < counter ; i++)
	        binl[*n-1].binary[i] = (*bitway)[i];


	    *n -= 1;
    }

	else if(node){
	   *bitway = (int *)realloc(*bitway,sizeof(int)*(counter+1));
	   
	   (*bitway)[counter] = 0;
	   inOrder(node->left,bitway,counter+1,binl,n);

	   (*bitway)[counter] = 1;
	   inOrder(node->right,bitway,counter+1,binl,n);
    }

    return;
}

//---------------------- ORDENACAO / ANALISE -----------------------------------
//Funcao responsavel por ordenar uma lista binaria...
void mergesort_binlist(t_binlist *vec, int start, int end) {
    int i, j, k, mid;
    t_binlist *aux;

    if(start == end) return;

    mid = (start + end ) / 2;
    mergesort_binlist(vec, start, mid);
    mergesort_binlist(vec, mid + 1, end);

    i = start;
    j = mid + 1;
    k = 0;
    aux = (t_binlist *)malloc(sizeof(t_binlist)*(end - start + 1));

    while(i < mid + 1 || j  < end + 1){
        if (i == mid + 1 ) {
            aux[k] = vec[j];
            j++;
            k++;
        }
        else {
            if (j == end + 1){
                aux[k] = vec[i];
                i++;
                k++;
            }
            else {
                if(vec[i].symbol < vec[j].symbol) {
                    aux[k] = vec[i];
                    i++;
                    k++;
                }
                else{
                    aux[k] = vec[j];
                    j++;
                    k++;
                }
            }
        }
    }
    
    for(i = start ; i <= end; i++)
        vec[i] = aux[i - start];
    
    free(aux);
    
    return;
}

//Funcao responsavel por ordenar uma lista de Huffman...
void mergesort_list(t_node *vec, int start, int end) {
    int i, j, k, mid;
    t_node *aux;

    if(start == end) return;

    mid = (start + end ) / 2;
    mergesort_list(vec, start, mid);
    mergesort_list(vec, mid + 1, end);

    i = start;
    j = mid + 1;
    k = 0;
    aux = (t_node *)malloc(sizeof(t_node)*(end - start + 1));

    while(i < mid + 1 || j  < end + 1){
        if (i == mid + 1 ) {
            aux[k] = vec[j];
            j++;
            k++;
        }
        else {
            if (j == end + 1){
                aux[k] = vec[i];
                i++;
                k++;
            }
            else {
                if(vec[i].frequency == vec[j].frequency){
                    if(strcmp(vec[i].symbol,vec[j].symbol)<0) {
                        aux[k] = vec[i];
                        i++;
                        k++;
                    }
                    else{
                        aux[k] = vec[j];
                        j++;
                        k++;
                    } 
                }
                else{
                    if(vec[i].frequency < vec[j].frequency) {
                        aux[k] = vec[i];
                        i++;
                        k++;
                    }

                    else{
                        aux[k] = vec[j];
                        j++;
                        k++;
                    }
                }
            }
        }
    }
    
    for(i = start ; i <= end; i++) {
        vec[i] = aux[i - start];
    }
    free(aux);
}

//Funcao responsavel por analisar se um elemento ja foi inserido uma lista...
int repeatelem(t_list *list, char c){
    int i;
    for(i = 0; i < list->nelem ; i++){
        if(list->elem[i].symbol[0] == c)
            return i;
    }
    return -1;
}

//--------------------------- CRIACAO ------------------------------------------
//Funcao responsavel por  criar uma lista binaria...
t_binlist *createbinlist(FILE *fp, int *n){
    int counter;
    t_binlist *bin = NULL;
    char *string = NULL;
    
    //Inicializando as variaveis...
    fseek(fp,0,SEEK_SET);
    counter = 0;
    
    while(!match((string = readLine(fp)),"^\\s*-\\s*$")){
    
        bin = (t_binlist *)realloc(bin,sizeof(t_binlist)*(counter+1));
        bin[counter].symbol = string[0];
        bin[counter].nbits = 0;
        bin[counter].binary = digit_readString(string,&bin[counter].nbits);
        
        free(string);
        counter++;
    }
    free(string);
    
    mergesort_binlist(bin,0,counter-1);
    *n = counter;
    
    return bin;
}

//Funcao responsavel por criar folhas/nos de uma arvore binaria de Huffman...
void createleaf(t_list *list){
    
    //1 - Alocando na memoria um no/folha (esquerda)...
    t_node *leftleaf = (t_node *)malloc(sizeof(t_node));
    if(list->elem[0].nsymbol == 1){
	leftleaf->bit = 0;
        leftleaf->left = NULL;
        leftleaf->right = NULL;
        leftleaf->symbol = list->elem[0].symbol;
        leftleaf->frequency = list->elem[0].frequency;
        leftleaf->nsymbol = list->elem[0].nsymbol;
    }
    else{
	leftleaf->bit = 0;
        leftleaf->left = list->elem[0].left;
        leftleaf->right = list->elem[0].right;
        leftleaf->symbol = list->elem[0].symbol;
        leftleaf->frequency = list->elem[0].frequency;
        leftleaf->nsymbol = list->elem[0].nsymbol;
    }

    //2 - Alocando na memoria um no/folha (direita)...
    t_node *rightleaf = (t_node *)malloc(sizeof(t_node));
    if(list->elem[1].nsymbol == 1){
	rightleaf->bit = 1;
        rightleaf->left = NULL;
        rightleaf->right = NULL;
        rightleaf->symbol = list->elem[1].symbol;
        rightleaf->frequency = list->elem[1].frequency;
        rightleaf->nsymbol = list->elem[1].nsymbol;
    }
    else{
	rightleaf->bit = 1;
	rightleaf->left = list->elem[1].left;
        rightleaf->right = list->elem[1].right;
        rightleaf->symbol = list->elem[1].symbol;
        rightleaf->frequency = list->elem[1].frequency;
        rightleaf->nsymbol = list->elem[1].nsymbol;
    }
    
    //3 - Criando o no "pai" dos dois nos filhos alocados anteriormente...
    t_node *fatherleaf = (t_node *)malloc(sizeof(t_node));{
	fatherleaf->bit = -1;
        fatherleaf->left = leftleaf;
        fatherleaf->right = rightleaf;
        fatherleaf->symbol = sumsymbols(list->elem[0].symbol,list->elem[1].symbol);
        fatherleaf->frequency = rightleaf->frequency + leftleaf->frequency;
        fatherleaf->nsymbol = leftleaf->nsymbol + rightleaf->nsymbol;
    }
    
    //4 - Copiando as informacoes da lista para um vetor auxiliar...
    int i;
    t_node *auxvec = (t_node *)malloc(sizeof(t_node)*list->nelem-1);
    for(i = 1 ; i < list->nelem ; i++)
        auxvec[i-1] = list->elem[i];
        free(list->elem);    
    
    //5 - Recriando a lista...    
    list->nelem -= 1;
    list->elem = NULL;
    list->elem = (t_node *)realloc(list->elem,sizeof(t_node)*list->nelem);
    for(i = 0 ; i < list->nelem ; i++)
        list->elem[i] = auxvec[i];
        free(auxvec);
    
    list->elem[0].bit = fatherleaf->bit;
    list->elem[0].symbol = fatherleaf->symbol;
    list->elem[0].frequency = fatherleaf->frequency;
    list->elem[0].nsymbol = fatherleaf->nsymbol;
    list->elem[0].left = fatherleaf->left;
    list->elem[0].right = fatherleaf->right;
    free(fatherleaf);
    
    return;
}

//Funcao responsavel por criar a arvore de Huffman...
void createtree(t_tree *tree, t_list *list){
    if(list->nelem == 1){
	tree->root = list->elem;
	 return;
    }

    createleaf(list);
    mergesort_list(list->elem,0,list->nelem-1);
    return createtree(tree,list); 
}

//Funcao responsavel por criar uma lista...
void createlist(t_list *list, FILE *fp){
    char c;
    int pos;
    list->nelem = 0;
    list->elem = NULL;
    
    while(!feof(fp)){
        c = fgetc(fp);
        
        if(c != EOF){ 
            if((pos = repeatelem(list,c))==NO){
                list->elem = (t_node *)realloc(list->elem,sizeof(t_node)*((list->nelem)+1));
                list->elem[list->nelem].nsymbol = 1;
                list->elem[list->nelem].left = NULL;
                list->elem[list->nelem].right = NULL;
                list->elem[list->nelem].symbol = NULL;
                list->elem[list->nelem].symbol = 
                        (char *)realloc(list->elem[list->nelem].symbol,sizeof(char)*(list->elem[list->nelem].nsymbol+1));
                list->elem[list->nelem].symbol[0] = c;
                list->elem[list->nelem].symbol[1] = '\0';
                list->elem[list->nelem].frequency = 1;
                list->nelem += 1;
            }
            else{
                list->elem[pos].frequency +=1;
            }
        }
    }
    return;
}

//FUNCOES PRICIPAIS -----------------------------------------------------------
void huff_compact(FILE *txtfile){
    //1- Criando uma "lista" que contem cada folha da arvore e a ordenando em 
    //seguida...
    t_list *list = (t_list *)malloc(sizeof(t_list));
        createlist(list,txtfile);
        mergesort_list(list->elem,0,list->nelem-1);

    //2 - Criando a arvore caracteristica da compactacao de Huffman...
    t_tree *tree = (t_tree *)malloc(sizeof(t_tree));
        createtree(tree,list);
    
    //3 - Criando uma lista com os binarios que representam cada letra existente
    //no arquivo de entrada e ordenando-a...
    int i,j,n;
    
    n = tree->root->nsymbol;
    t_binlist *binl = (t_binlist *)malloc(sizeof(t_binlist)*n); 
    
    int *bitway = NULL;
    inOrder(tree->root, &bitway, 0,binl,&n);
    free(bitway);   

    mergesort_binlist(binl,0,tree->root->nsymbol-1);
    
    //4 - Imprimindo o resultado na tela...
    n = tree->root->nsymbol;
    for(i = 0 ; i < n ; i++){
	    printf("%c - ",binl[i].symbol);
        for(j = 0 ; j < binl[i].nbits ; j++)
	        printf("%d",binl[i].binary[j]);
	    printf("\n");   
    }printf("-\n");

    printbinary(txtfile,binl,tree->root->nsymbol); 
    
    //5 - Liberando a memoria utilizada...
    freebinl(binl,tree->root->nsymbol);
    freetree(tree,tree->root);
    free(list);
    free(tree);
    
    return;
}

void huff_descompact(FILE *huff_file){
    //1 - Lendo as informacoes contidas no arquivo para descompactação e criando
    //uma lista com as representacoes binarias de cada letra...
    int nsymbol;
    t_binlist *binl = createbinlist(huff_file,&nsymbol);
    
    //2 - Lendo o arquivo compactado e imprimindo na tela o texto...
    printtext(huff_file,binl,nsymbol);
    
    //3 - Liberando a memoria utilizada...
    freebinl(binl,nsymbol);
        
    return;
}
