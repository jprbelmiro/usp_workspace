#ifndef _T4_IMAGE_H_
#define _T4_IMAGE_H_

//Estrutura responsavel por definir o tipo imagem para uso...
typedef struct image{
    int img_class;
    char *type;
    int col, row;
    int max_value;
    double ***feature_vec;
    double **image_matrix;
} t_image;

//Funcao responsavel por liberar uma estrutura de imagem da memoria...
void free_image_matrix(struct image **, int , int );

//Funcao responsavel por realizar uma classificacao de imagem por meio de vetores
//de caracteristicas e comparacao...
void classifying_image(struct image **, int , struct image **, int , int , int );

//Funcao responsavel por realizar a convolucao de uma matriz e uma mascara...
double **convolution(double **, double **, int , int , int );

//Funcao responsavel por realizar a leitura de um arquivo de imagem...
struct image *readImage(FILE *);

//FUncao responsavel por realizar a caracterizacao de uma imagem...
struct image *featuring_image(FILE *, double ***, int , int );

#endif
