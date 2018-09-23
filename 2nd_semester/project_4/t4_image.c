#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "t4_basic.h"
#include "t4_image.h"

void free_image_matrix(struct image **image, int counter, int nmasks){
    int i;
    for(i = 0 ; i < counter ; i++){
        if(image[i]->type != NULL) free(image[i]->type);
        if(image[i]->feature_vec != NULL) free_cube((void ***)image[i]->feature_vec,nmasks,image[i]->row);
        if(image[i]->image_matrix != NULL) free_matrix((void **)image[i]->image_matrix,image[i]->row);
	if(image[i] != NULL) free(image[i]);
    }free(image);
    return;
}

static void heapsort_classfy_vec(double **vec, int n){
   int i = n/2, father, son;
   double *aux = NULL;
   while(1){
      if (i > 0) {
          i--;
          aux = vec[i];
      } else {
          n--;
          if (n == 0) return;
          aux = vec[n];
          vec[n] = vec[0];
      }

      father = i;
      son = i * 2 + 1;

      while (son < n){
          if ((son + 1 < n)  &&  (vec[son + 1][1] > vec[son][1]))
              son++;
          if (vec[son][1] > aux[1]){
             vec[father] = vec[son];
             father = son;
             son = father * 2 + 1;
          } else break;
      }
      vec[father] = aux;
   }
   return;
}

void classifying_image(struct image **image_T, int counter_T, struct image **image_E, int counter_E, int k, int nmasks){
    int counter, i, j, p, q;
    double class, *classes_vec;

    for(counter = 0 ; counter < counter_E; counter++){
    //Criando um vetor de classificacao que auxiliara e facilitara a operacao de classificacao de uma imagem...
    double **classfy_vec = (double **)malloc(sizeof(double *)*counter_T);

       for(i = 0 ; i < counter_T; i++){
          classfy_vec[i] = (double *)calloc(2,sizeof(double));
	  classfy_vec[i][0] = i;

    //Calculando a distancia Euclidiana dos pontos no espaço...
      for(j = 0 ; j < nmasks ; j++) 
	   for(p = 0 ; p < image_T[i]->row ; p++)
	     for(q = 0 ; q < 6 ; q++)
	         classfy_vec[i][1] += pow(image_E[counter]->feature_vec[j][p][q] - image_T[i]->feature_vec[j][p][q],2);
	  classfy_vec[i][1] = sqrt(classfy_vec[i][1]);        	
       }
	
	//Ordenando o vetor de caracteristicas para conhecer os pontos mais proximos da imagem em teste...
       heapsort_classfy_vec(classfy_vec, counter_T);
    
    //Analisando os k vizinhos de importancia para classificacao...
	classes_vec = (double *)malloc(sizeof(double)*k);
	for(i = 0 ; i < k ; i++)
	   classes_vec[i] = (double)image_T[(int)classfy_vec[i][0]]->img_class;   
	   
	   //Analisando qual a classe de maior frequencia e imprimindo a classe da imagem teste...
       class = who_repeat_more(classes_vec,k);
       printf("%.3lf\n",class);	

       free_matrix((void **)classfy_vec,counter_T);
	free(classes_vec);
    }
    return;
}

static double *define_features(double **matrix, int row, int ncol){
    int i;
    double *feature_vec = (double *)calloc(6,sizeof(double));
    
        for(i = 0 ; i < ncol ; i++){
            //Parametro 0 = Numeros maiores que zero...
            if(matrix[row][i] > 0.0) feature_vec[0] += 1.0;
            //Parametro 1 = NUmeros menores que zero...
            if(matrix[row][i] == 0.0) feature_vec[1] += 1.0;
            //Parametro 2 = Numeros menores que zero...
            if(matrix[row][i] < 0.0) feature_vec[2] += 1.0;
            feature_vec[3] += matrix[row][i];
            feature_vec[5] += matrix[row][i]*(log2(fabs(matrix[row][i])+1));
        }
        //Parametro 3 = Media aritmetica...
        feature_vec[3] /= ncol;
        //Parametro 5 = Entropia...
        feature_vec[5] *= -1;
        
        //Parametro 4 = Variancia...
        for(i = 0 ; i < ncol ; i++)
            feature_vec[4] += pow(matrix[row][i] - feature_vec[3],2);
        feature_vec[4] /= ncol;
    return feature_vec;
}

static double convolution_pixel(double **auxmatrix, double **mask, int d, int add, int row, int col){
    int i, j;
    double sum = 0.0;

    for( i = row ; i < row + d ; i++){
        for(j = col ; j < col + d ; j++){
            sum += (auxmatrix[i][j]*mask[i-row][j-col]);
        } 
    }

    return sum;
}

static double **resize_image(int nrow_i, int ncol_i, int nrow_f, int ncol_f, double **image){
    int i, j;
    double **newimage = (double **)calloc(nrow_f,sizeof(double *));
    
    for( i = 0 ; i < nrow_f ; i++ ){
        newimage[i] = (double *)calloc(ncol_f,sizeof(double));
        for( j = 0 ; j < ncol_f ; j++ ){
            if(i >= (nrow_f-nrow_i)/2 && j >= (ncol_f-ncol_i)/2 && i < nrow_i+((nrow_f-nrow_i)/2)  && j < ncol_i+((nrow_f-nrow_i)/2) )
                newimage[i][j] = image[i-((nrow_f-nrow_i)/2)][j-((ncol_f-ncol_i)/2)];
        }
    }
    
    return newimage;
}

double **convolution(double **image, double **mask, int m_mask, int nrow, int ncol){
    int i, j, add = m_mask/2;
    double **auxmatrix = resize_image(nrow,ncol,nrow+(2*add),ncol+(2*add),image);
   double **newimage = (double **)malloc(sizeof(double *)*nrow);
    
    for(i = 0; i < nrow ; i++){
        newimage[i] = (double *)malloc(sizeof(double)*ncol);
        for(j = 0 ; j < ncol ; j++){
            newimage[i][j] = convolution_pixel(auxmatrix,mask,m_mask,add,i,j);
        }
    }
    
    free_matrix((void **)auxmatrix,nrow+(2*add));
    
    return newimage;
}

struct image *readImage(FILE *img_file){
    int i, j;
    unsigned char c;
    char *aux = NULL;
    struct image *img = (struct image *)malloc(sizeof(struct image));
    
    img->img_class = -1;
    img->type = readLine(img_file);
    
    aux = tokenize(img_file);
        img->col = atoi(aux);
            free(aux);
            
    aux = tokenize(img_file);
        img->row = atoi(aux);
            free(aux);
            
    aux = tokenize(img_file);
        img->max_value = atoi(aux);
            free(aux);
    
    img->feature_vec = NULL;
    
    img->image_matrix = create_dmatrix(img->row,img->col);
    for( i = 0 ; i < img->row ; i++ ){
        for( j = 0 ; j < img->col ; j++ ){
                fread(&c,1,1,img_file);
                img->image_matrix[i][j] = c;
        }
    }
    
    return img;
}

struct image *featuring_image(FILE *file, double ***masks, int nmasks, int m){
    int i, j;
    
    //1-Lendo o nome do arquivo a ser aberto e abrindo-o...
    FILE *aux_fp = NULL;
    char *image_name = readLine(file);
    aux_fp = fopen(image_name,"rb");
        
        //Caso ele nao exista, retorna-se nulo da funcao...
	    if(aux_fp == NULL){
	        free(image_name);
	        return NULL;
	    }

    //2-Lendo o arquivo aberto...
    struct image *img = readImage(aux_fp);
        
        //Fechando o arquivo e liberando seu nome...
        free(image_name);
        fclose(aux_fp);

    //3-Realizando sucessivas convoluções em cima da imagem aberta...
    double **aux_matrix = NULL;
    img->feature_vec = (double ***)malloc(sizeof(double **)*nmasks);
    for(i = 0 ; i < nmasks ; i++){
        aux_matrix = convolution(img->image_matrix,masks[i],m,img->row,img->col);
        //Construindo o vetor de caracteristicas...
	img->feature_vec[i] = (double **)malloc(sizeof(double *)*img->row);
        for(j = 0 ; j < img->row ; j++)
           img->feature_vec[i][j] = define_features(aux_matrix,j,img->col);
        free_matrix((void **)aux_matrix,img->row);
    }
    
    //4-Retornando a imagem resultado...
    return img;
}
