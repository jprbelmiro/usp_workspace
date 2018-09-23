#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "t5_basic.h"
#include "t5_stack.h"

enum{
    NO,
    YES
};

//Estrutura responsavel por definir um bloco de resultado...
typedef struct{
    int size;
    int *path;
    float distance;
}t_result;

//Funcao responsavel por liberar o vetor resultado da memoria...
void free_result(t_result *result, int count){
    int i;
    for( i = 0 ; i < count ; i++ ){
	free(result[i].path);
    }free(result);
    return;
}

//Funcao responsavel por calcular a distancia geodesica do caminho percorrido...
float geodesic_distance(int *path, int size, float **points){
    int i;
    float dist = 0;
        for(i = 0; i < size-1 ; i++)
            dist += sqrt( pow(points[path[i]-1][0] - points[path[i+1]-1][0],2) + pow(points[path[i]-1][1] - points[path[i+1]-1][1],2) );
    return dist;
}

//Funcao responsavel por avaliar se uma posicao A do vetor resultado combina/e 
//igual a uma posicao B...
int match_results(t_result A, t_result B){
    int i;
    if(A.size != B.size) return NO;
    if(A.distance != B.distance) return NO;
    for(i = 0 ; i < A.size ; i++)
	if(A.path[i] != B.path[i]) return NO;
    return YES;
}

//Funcao responsavel por apagar repeticoes que possam ter surgido durante a
//busca de todas as saidas possiveis...
t_result *delete_repeat(t_result *result, int r_count, int *aux_c){
    int i, j, k, count;
    t_result *aux_r = NULL;

    for(i = 0 ; i < r_count ; i++){
	count = 0;
	for(j = i+1 ; j < r_count ; j++){
	    if(match_results(result[i],result[j])) count++;
	}

	if(count == 0){
	    aux_r = (t_result *)realloc(aux_r,sizeof(t_result)*(*aux_c+1));
	    aux_r[*aux_c].size = result[i].size;
	    aux_r[*aux_c].path = (int *)malloc(sizeof(int)*(result[i].size)); 
	    for(k = 0 ; k < result[i].size ; k++)
	        aux_r[*aux_c].path[k] = result[i].path[k];
	    aux_r[*aux_c].distance = result[i].distance; 
	    *aux_c += 1;
	}
    }

    return aux_r;
}

//Funcao responsavel por ordernar o vetor resultado nos parametros passados...
void sort_result(t_result *result,int r_count){
    int i, j, k;
    t_result aux;

    for( i = 0 ; i < r_count-1 ; i++){
        for( j = i+1 ; j < r_count ; j++){
            if( result[i].distance > result[j].distance ){
                aux = result[i];
                result[i] = result[j];
                result[j] = aux;
            }
        }
    }
   

    for( i = 0 ; i < r_count-1 ; i++){
	for( j = i+1 ; j < r_count ; j++){
	   if( result[i].distance == result[j].distance ){
	    if( result[i].size > result[j].size ){
	        aux = result[i];
	        result[i] = result[j];
	        result[j] = aux;
	    }
	   }
	}
    }

    for( i = 0 ; i < r_count-1 ; i++){
	for( j = i+1 ; j < r_count ; j++){
	    if(result[i].distance == result[j].distance &&  result[i].size == result[j].size ){
	       for( k = 0 ; k < result[i].size ; k++ ){
		    if(result[i].path[k] < result[j].path[k]) break;
		    if(result[i].path[k] > result[j].path[k]){
	                aux = result[i];
	                result[i] = result[j];
	                result[j] = aux;
			break;
		    }
	    	}
	    }
	}
    }
    return;
}

//Funao responsavel por imprimir o resultado na tela...
void print_result(t_result *result, int r_count){
    int i, j, aux_c = 0;
    t_result *aux_r = NULL;

    sort_result(result,r_count);
    aux_r = delete_repeat(result,r_count,&aux_c);

    for(i = 0 ; i < aux_c ; i++){
	printf("%d ",aux_r[i].size);
	for(j = 0 ; j < aux_r[i].size ; j++)
	    printf("%d ",aux_r[i].path[j]);
	printf("%d\n",(int)aux_r[i].distance);
    }
    free_result(aux_r,aux_c);
    return;
}

//Funcao responsavel por contruir o vetor de resultado que sera impresso ao final
//da resolucao do labirinto...
void build_result(t_stack *path, float **maze, t_result **result, int result_count){
    int counter = path->size - 1;
    double distance = 0;
    int *valid_path = (int *)malloc(sizeof(int)*(path->size));
    t_elem *aux_elem = path->top;

    //-Criando um vetor com os caminhos...
    while(aux_elem != NULL){
        valid_path[counter--] = aux_elem->elem;
        aux_elem = aux_elem->down;
    }
    
    //-Calculando a distancia percorrida
    distance = geodesic_distance(valid_path,path->size,maze);
    
    //-Imprimindo o resultado final...
    *result = (t_result *)realloc(*result,sizeof(t_result)*(result_count+1));
    (*result)[result_count].size = path->size;
    (*result)[result_count].path = valid_path;
    (*result)[result_count].distance = distance;
    
    return;
}

//Funcao responsavel por analisar se um destino ja nao foi percorrido em um ca_
//minho a fim de evitar a rota em circulos...
int repeat_in_path(int dest, t_stack *path_taken){
    t_elem *aux = path_taken->top;
    while(aux != NULL){
        if(aux->elem == dest)
            return YES;
        else aux = aux->down;
    }
    return NO;
}

//Funcao responsavel por definir o caminho a ser seguido...
int define_way(int *pos, int **mem_seg, float **segments, t_stack *path_taken,int NS){
    int i,dest;
    for( i = 0 ; i < NS ; i++ ){
	if(mem_seg[*pos-1][i] == 0){
	    *pos == abs(segments[i][0]) ? (dest = segments[i][1]) : (dest = segments[i][0]);
	    if(!repeat_in_path(dest,path_taken)){
	    	mem_seg[*pos-1][i] = 1;
	    	*pos = dest;
	   	 mem_seg[*pos-1][i] = 1;
	        return i;
	    }else{
		mem_seg[*pos-1][i] = 1;
	    }
	}
    }
    return -1;
}

//Funcao responsavel por limpar a memoria de segmentos ja percorridos para pontos
//diferentes do atual...
void clear_backpos(int bpos, int *mem_seg, float **segments, int NS){
    int i;
    for( i = 0 ; i < NS ; i++ ){
	mem_seg[i] = 1;
	if( bpos == abs(segments[i][0]) || bpos == abs(segments[i][1]) )
	    if( segments[i][0] > 0 && segments[i][1] > 0 )
		mem_seg[i] = 0;
    }
}

//Funcao responsavel por tracar todos os possiveis caminhos de um ponto...
void alternative_ways(int NP, int **mem_segments, float **segments, int NS ){
    int i, j, pos;
    for( i = 0 ; i < NP ; i++ ){
	    pos = i+1;
	    for( j = 0 ; j < NS ; j++ ){
	        mem_segments[i][j] = 1;
	        if( pos == abs(segments[j][0]) || pos == abs(segments[j][1]))
	    	    if( segments[j][0] > 0 && segments[j][1] > 0 )
		            mem_segments[i][j] = 0;
	    }		
    }
    return;
}

//Funcao responsavel por verificar se um ponto ja percorrido continua sendo um
//ponto de caminhos alternativos ou nao com base na memoria de segmentos...
void analysis_way_point( int pos, t_stack *alt_way, int *mem_seg, int NS){
    int i, counter = 0;
    if(pos != alt_way->top->elem) return;

    for( i = 0 ; i < NS ; i++ ){
        if(mem_seg[i] == 0) counter++;
    }
    if(counter < 1) pop_stack(alt_way);
}

//Funcao resposavel por verificar se a atual posicao e um ponto com caminhos al_
//ternativos (mais de um caminho para percorrer)...
void way_point( int pos, t_stack *alt_way, int *mem_seg, int NS ){
    int i, counter = 0;
    for( i = 0 ; i < NS ; i++ ){
        if(mem_seg[i] == 0) counter++;
    }
    if(counter > 1){
	if(!repeat_in_path(pos,alt_way))
	 push_stack(alt_way,pos);
    }
}

//Funcao resposavel por realizar o retorno de um caminho sem saida para um ponto
//de caminhos alternativos...
//- Este retorno e feito em cima da pilha que mostra o caminho tomado para se al_
//cancar a posicao atual...
int return_on_stack(t_stack *path_taken, t_stack *alt_way, int **mem_segments, float **segments, int NS){
    int aux = path_taken->top->elem;
    
    //-Analisando se existem caminhos alternativos...
    if(alt_way->size != 0 ) analysis_way_point(path_taken->top->elem,alt_way,mem_segments[path_taken->top->elem-1],NS);
    
    //-Retornando posicoes no labirinto...
    while(path_taken->size != 0 && alt_way->size != 0 && path_taken->top->elem != alt_way->top->elem ){
    	 aux = path_taken->top->elem;
	     pop_stack(path_taken);
	     clear_backpos(aux,mem_segments[aux-1],segments,NS);
	        analysis_way_point(path_taken->top->elem,alt_way,mem_segments[path_taken->top->elem-1],NS);    
    }
    
    //-Caso nenhum possivel caminho seja encontrado, libera-se o caminho tracado
    //e encerra-se a busca...
    if(alt_way->size == 0 && aux == path_taken->top->elem){
	    while(path_taken->size != 0)
	        pop_stack(path_taken);
	    return -1;
    }
    //-Caso contrario retorna-se a nova posicao
    return path_taken->top->elem;
}

//Funcao responsavel por analisar se o ponto atual do labirinto e uma camara de
//saida...
int isValidChamber(int pos, float **chambers, int NC){
    int i;
    for(i = 0 ; i < NC ; i++)
        if(pos == chambers[i][0] && chambers[i][1] == 1)
            return YES;
    return NO;
}

//Funcao responsavel por verificar se um certo numero inteiro e valido no inter_
//valo passado...
int isValid(int num, int low, int top){
    return num > low && num <= top;
}

void maze_runner(float **maze, float **chambers, float **segments, int NP, int NC, int NS, int START){
    int pos = START, bpos, way, result_count = 0;
    int **mem_segments = NULL;
    t_result *result = NULL;
    
    //1- Criando as pilhas que serao responsavel por auxiliar o percurso dentro 
    //do labirinto...
    t_stack *path_taken = create_stack();
    t_stack *alt_way = create_stack();
    
    //2- Criando uma matrix de memoria para os caminhos ja percorridos a fim de
    //nao andar em circulos no labirinto...
    mem_segments = create_imatrix(NP,NS);

    //3- Encontrando todos os caminhos possiveis para cada ponto...
    alternative_ways(NP,mem_segments,segments,NS);

    //4- Percorrendo o labirinto ate se encontrar todas as saidas possiveis...
    //-Inicializando a pilha para nao ferir a condicao de parada...
    push_stack(path_taken,pos);
    while(path_taken->size != 0){
        //a. Analisando se a atual posicao e uma camara valida de saida...
        //- Caso seja, o resultado e armazenado no vetor resultado...
        if(isValidChamber(pos,chambers,NC)){
            build_result(path_taken,maze,&result,result_count);
	        result_count += 1;
	    }

        //b. Analisando o ponto atual e seus possiveis caminhos
	    //alternativos e definindo por qual caminho seguir...
	    //- bpos armazena a posicao anterior ao novo caminho...
	    bpos = pos;
	    way_point(pos,alt_way,mem_segments[pos-1],NS);
	    way = define_way(&pos, mem_segments, segments, path_taken,  NS);

	    //c. Se este for um caminho valido, o processo continua...
	    //-Caso contrario, retorna-se na pilha ate uma posicao de caminho valido...
	    if(isValid(way,-1,NS-1))
	        push_stack(path_taken,pos);
	    else pos = return_on_stack(path_taken,alt_way,mem_segments,segments,NS);
	
	    //d. Se a pilha de pontos com caminhos alternativos estiver vazia ou a 
	    //posicao anterior ao novo caminho for diferente do ultimo ponto de cami_
	    //nhos alternativos, limpa-se os caminhos ja percorridos (exceto os refe_
	    //rentes ao ponto atual) a fim de que seja possivel reutilizar tal segemento,
	    //por outros caminhos alternativos...
	    if(alt_way->top == NULL || (alt_way->top != NULL &&  bpos != alt_way->top->elem)) 
	        clear_backpos(bpos,mem_segments[bpos-1],segments,NS);
    }
    
    //5- Imprimindo o resultado na tela...
    print_result(result,result_count);
    
    //6- Liberando toda a memoria utilizada no processo...
    free_result(result,result_count);
    free_matrix((void **)mem_segments,NP);
    free(path_taken);
    free(alt_way);
    
    return;
}
