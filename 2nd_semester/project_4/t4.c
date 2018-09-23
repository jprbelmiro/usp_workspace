#include <stdlib.h>
#include <stdio.h>
#include "t4_basic.h"
#include "t4_image.h"

//T4 - Convolucao KNN
int main(int argc, char **argv){
    int m, nmasks, k;
    int counter_T = 0, counter_E = 0;
    double ***masks = NULL;
    t_image **image_T = NULL, **image_E = NULL;
    FILE *T_file = NULL, *C_file = NULL, *E_file = NULL; 
    
    //1.Recebendo um arquivo de entrada com uma lista dos nomes das imagens no 
    //formato PGM correspondente ao conjunto de treinamento...
    T_file = fopen_r();
    
    //2.Recebendo um arquivo de entrada com cada uma das classes das imagens do 
    //conjunto de treinamento...
    C_file = fopen_r();
    
    //3.Recebendo um arquivo de entrada com uma lista dos nomes das imagens PGM 
    //correspondente ao conjunto de teste...
    E_file = fopen_r();
    
    //4.Recebendo o numero de mascaras de convolucao...
    scanf("%d%*c",&nmasks);
        
    //5.Recebendo o parametro m que define o numero de linhas e colunas de cada 
    //mascara de convolucao (lembre-se que as mascaras serao definidas somente 
    //por matrizes quadradas)...
    scanf("%d%*c",&m);
        
    //6.Recebendo os valores (celulas) de cada uma das matrizes de convolucao...
    masks = create_dcube(nmasks,m,m);
    fill_dcube(masks,nmasks,m,m);
    
    //7.Recebendo o valor de K para o algoritmo de K vizinhos mais proximos...
    scanf("%d%*c",&k);

    //8. Aplicaando as convolucoes sobre todas as imagens do conjunto de treinamento,
    //gerando os vetores de caracterısticas (um vetor por imagem)...
    while(!feof(T_file)){
        image_T = (t_image **)realloc(image_T,sizeof(t_image *)*(counter_T+1));
        image_T[counter_T] = featuring_image(T_file,masks,nmasks,m);
	
	if(feof(T_file)) break;

	fscanf(C_file,"%d%*c",&image_T[counter_T]->img_class);	
	 counter_T++;
    }
    
    //9. Aplicando as convolucoes sobre todas as imagens do conjunto de teste, 
    //gerando os vetores de caracterısticas (um vetor por imagem)...
    while(!feof(E_file)){
	image_E = (t_image **)realloc(image_E,sizeof(t_image *)*(counter_E+1));
	image_E[counter_E] = featuring_image(E_file,masks,nmasks,m);

	if(feof(E_file)) break;
	
	image_E[counter_E]->img_class = -1;
	counter_E++;
    }
   
    //10. Rodando K vizinhos mais proximos e classificando as imagens de teste...
    classifying_image(image_T,counter_T,image_E,counter_E,k,nmasks);
    
    //11.Liberando a memoria utilizada e fechando os arquivos abertos...
    free_image_matrix(image_T,counter_T,nmasks);
    free_image_matrix(image_E,counter_E,nmasks);
    free_cube((void ***)masks,nmasks,m);
    fclose(E_file);
    fclose(C_file);
    fclose(T_file);
    
    return 0;
}
