#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void freeM(double **matrix, int n){
    int i;                                                                          //Função: freeM(double **, int)
    for( i = 0 ; i < n; i++)                                                        //- Responsável por liberar a memória alocada para
        free(matrix[i]);                                                            //matrizes criadas anteriormente...

    return;
}

void Major_Minor(double *major, double *minor, double **img_matrix, int row, int col){
    int i, j;                                                                       //Função: Major_Minor(double *, double *, double **
    for(i = 0 ; i < row ; i++){                                                     //int, int)
        for(j = 0 ; j < col ; j++){                                                 //- Responsável por analizar uma matriz e retornar
            if(*major < img_matrix[i][j])                                           //o valor maximo e minimo que existe nela...
                *major = img_matrix[i][j];
            if(*minor > img_matrix[i][j])
                *minor = img_matrix[i][j];
        }
    }

    return;
}

double **createM(int row, int col){
    int i;                                                                          //Função: createM(int, int)
    double **matrix = (double **)calloc(row,sizeof(double *));                      //- Responsável por criar uma matriz na memória
        for(i = 0 ; i < row ; i++)                                                  //para o usuário com as dimensões escolhidas por
            matrix[i] = (double *)calloc(col,sizeof(double));                       //ele...

    return matrix;
}

double Convolution_Pixel(double **aux_img_matrix, double **filter_matrix, int d, int add, int row, int col){
    double sum = 0;                                                                 //Função: Convolution_Pixel(double **, double **,
    int i, j;                                                                       //int, int, int, int)
                                                                                    //- Responsável por realizar a convolução de
    for( i = row ; i < row + d ; i++){                                              //duas matrizes - Observe que ele retorna
        for(j = col ; j < col + d ; j++){                                           //o valor de pixel por pixel da matriz imagem
            sum += (int)(aux_img_matrix[i][j]*filter_matrix[d+row-1-i][d+col-1-j]); //convulucionada, cabendo ao usuario definir
        }                                                                           //o ponto de inicio e parada da convolução...
    }

    return sum;
}

char *readFileInfo(FILE *fp){
    char c;                                                             //Função: readFileInfo(FILE *)
    char *string = NULL;                                                //- Responsável por realizar a leitura de um arquivo
    int counter = 0;                                                    //(no caso, um arquivo de imagem), analisando se existe
    do{                                                                 //algum comentário após a leitura do tipo deste e retornar
        c = fgetc(fp);                                                  //ao usuário uma string que contém somente o tipo do arquivo...
        string = (char *)realloc(string, sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10);
    string[counter] = '\0';

    c = fgetc(fp);
    if(c == '#'){
        do{
            c = fgetc(fp);
        }while(c != 10);
    } else ungetc(c,fp);

    string = (char *)realloc(string, sizeof(char)*(counter+1));
    string[counter] = '\0';

    return string;
}

char *readLine(){
    char c;                                                             //Função: readLine()
    char *string = NULL;                                                //- Responsável por ler uma linha na entrada padrão
    int counter = 0;                                                    //de texto até a entrada de um 'ENTER', retornando
    do{                                                                 //ao usuário uma 'string'...
        c = fgetc(stdin);
        string = (char *)realloc(string, sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10);
    string[counter - 1] = '\0';

    return string;
}

FILE *open2write(){
    FILE *fp = fopen("saida.pgm","w+");                                 //Função: open2write()
        if(fp == NULL){                                                 //- Responsável por abrir um arquivo para escrita,
            printf("Invalid write_file.\n");                            //trunca-lo (caso já exista) e analisar se esse é
            exit(1);                                                    //um arquivo é valido...
        }

    return fp;
}

FILE *open2read(){
    char *file_name = readLine();                                       //Função: open2read()
    FILE *fp = fopen(file_name,"r");                                    //- Responsável por abrir um arquivo para leitura
        if(fp == NULL){                                                 //e analisar se esse arquivo é valido...
            printf("There is no file to read.\n");
            free(file_name);
            exit(1);
        }
    free(file_name);

    return fp;
}

void Spatial_Filter(){
//(2) FILTRAGEM ESPACIAL DE UMA IMAGEM
    int i, j;

    //A.1 ABERTURA DO ARQUIVO COM A IMAGEM PARA LEITURA...                                          //-> A.1. Ao se iniciar o processo de filtragem espacial de uma imagem, em primeiro
    FILE *img_file = open2read();                                                                   //lugar, é aberto o arquivo com a imagem na qual se deseja operar...

    //A.2 ABERTURA DE UM ARQUIVO PARA A ESCRITA (SAIDA)...                                          //-> A.2. Após a abertura do 'arquivo de entrada', cria-se o arquivo de saida que
    FILE *spatial_file = open2write();                                                              //irá conter a imagem após a passagem do filtro..

    //B. ABRINDO O ARQUIVO COM O FILTRO PARA LEITURA...                                             //-> B. O filtro é escolhido a partir da abertura do arquivo que contem as informações
    FILE *filter_file = open2read();                                                                //da matriz do filtro...

    //C. CRIANDO UMA MATRIZ COM AS INFORMAÇÕES DO FILTRO LIDO...
    int dimension;                                                                                  //-> C. Com o filtro escolhido, são extraidos do arquivo deste as principais informações
    fscanf(filter_file,"%d",&dimension);                                                            //de sua matriz, assim como é criada uma matriz de uso através da leitura do arquivo...

    double **filter_matrix = createM(dimension,dimension);
    for(i = 0 ; i < dimension ; i++)
        for(j = 0 ; j < dimension ; j++)
            fscanf(filter_file,"%lf",&filter_matrix[i][j]);

    //D. CRIANDO UMA MATRIZ COM AS INFORMAÇÕES DA IMAGEM LIDA...
    int col, row, max_intense, add = dimension/2;                                                   //-> D. O mesmo é feito com a matriz da imagem: extrai-se as principais informações de sua
    char *type = readFileInfo(img_file);                                                            //matriz, assim como é criada uma matriz de uso através da leitura do arquivo...
        fscanf(img_file,"%d %d %d",&col,&row,&max_intense);                                         //- Observe, porém, que a matriz criada a partir da leitura do arquivo da imagem possui um
                                                                                                    //número de colunas e linhas adicionais em comparação com a matriz original.
    double **aux_img_matrix = createM(row+(2*add),col+(2*add));                                     //- Isto é feito para que seja possível a realização da 'convolução de matrizes' de maneira
    for( i = 0 ; i < (row+(add*2)) ; i++ ){                                                         //mais direta e simples...
        for( j = 0 ; j < (col+(add*2)) ; j++ ){
            if(i >= add && j >= add && i < row+add && j < col+add)
                fscanf(img_file,"%lf",&aux_img_matrix[i][j]);
        }
    }

    //E. REALIZANDO A CONVOLUÇÃO DE MATRIZ...
    double **img_matrix = createM(row,col);                                                         //-> E. Aqui é realizada a convolução da matriz auxiliar criada no passo D com a matriz
    for( i = 0 ; i < row ; i++ ){                                                                   //do filtro, lida e criada no passo B e C, respectivamente...
        for( j = 0 ; j < col ; j++ ){                                                               //- Observe que os valores adquiridos na convolução destas são guardados na matriz imagem
            img_matrix[i][j] = Convolution_Pixel(aux_img_matrix,filter_matrix,dimension,add,i,j);   //que contem as mesmas caracteristicas (exceto pelos valores de seus pontos) que a matriz
        }                                                                                           //da imagem original...
    }

    //F. DESCOBRINDO OS MINIMOS E MAXIMOS...
    double gmax = img_matrix[0][0], gmin = img_matrix[0][0];                                        //-> F. Neste passo, são descobertos os valores maximos e minimos de intesidade luminosa
    Major_Minor(&gmax,&gmin,img_matrix,row,col);                                                    //atribuida a matriz da imagem após a convulução da matriz auxiliar com a matriz filtro...

    //G. NORMALIZANDO OS VALORES DA MATRIZ...                                                       //-> G. Com o ponto maximo e minimo de luminosidade bem definidos, normaliza-se a matriz
    for( i = 0 ; i < row ; i++ )                                                                    //resultante a fim de manter a mesma caracteristica de luminosidade maxima da imagem
        for( j = 0 ; j < col ; j++ )                                                                //original aberta anteriormente...
            img_matrix[i][j] = (int)(max_intense*((img_matrix[i][j] - gmin)/(gmax-gmin)));

    //H. IMPRIMINDO NA TELA AS INFORÇÕES E CRIANDO UM ARQUIVO COM O RESULTADO...
    printf("%s%d %d\n%d\n",type,col,row,max_intense);
    fprintf(spatial_file,"%s%d %d\n%d\n",type,col,row,max_intense);                                 //-> H. Por fim, são impressos na tela e gravados em um arquivo de saída as informações
    for( i = 0 ; i < row ; i++ ){                                                                   //da imagem criada a partir da passagem do filtro espacial...
        for( j = 0 ; j < col ; j++ ){
            printf("%d ",(int)img_matrix[i][j]);
            fprintf(spatial_file,"%d ",(int)img_matrix[i][j]);
        }printf("\n");
         fputs("\n",spatial_file);
    }

    //I. LIBERANDO A MEMORIA ALOCADA E FECHANDO OS ARQUIVOS ABERTOS...
    fclose(img_file);                                                                               //-> I. E libera-se toda a memoria alocada no processo de filtragem espacial, além de
    fclose(filter_file);                                                                            //se fechar os arquivos abertos...
    freeM(filter_matrix,dimension);
    free(filter_matrix);
    free(type);
    freeM(aux_img_matrix,(row+(add*2)));
    free(aux_img_matrix);
    freeM(img_matrix,row);
    free(img_matrix);

    return;
}

void Negative_Img(){
//(1) PRODUÇÃO DO NEGATIVO DE UMA IMAGEM
    int i, j;

    //A. ABERTURA DO ARQUIVO COM A IMAGEM PARA LEITURA...                                           //-> A. Ao se iniciar o processo de produção de uma imagem negativa, em primeiro
    FILE *img_file = open2read();                                                                   //lugar, é aberto o arquivo com a imagem na qual se deseja operar...

    //B. CRIAÇÃO DE UM ARQUIVO DE SAIDA...                                                          //-> B. Após a abertura do 'arquivo de entrada', cria-se o arquivo de saida que
    FILE *negative_img = open2write();                                                              //irá conter a imagem negativa...

    //C. OBTENDO INFORMAÇÕES IMPORTANTES DA 'MATRIZ DA IMAGEM'...
                                                                                                    //-> C. Com os arquivos já abertos, são extraídas as principais informações da matriz
    int pixel, col, row, max_intense;                                                               //imagem contidas nos arquivos - numero de linhas e colunas da matriz, intensidade lu_
    char *type = readFileInfo(img_file);                                                            //minosa máxima da imagem e o tipo da imagem...

    fscanf(img_file,"%d %d %d",&col,&row,&max_intense);

    //D. CRIAÇÃO DA IMAGEM NEGATIVA...
    printf("%s%d %d\n%d\n",type,col,row,max_intense);                                               //-> D. Conhecendo as principais informações da imagem, começa-se de fato a produção
    fprintf(negative_img,"%s%d %d\n%d\n",type,col,row,max_intense);                                 //da imagem negativa que é obtida através da mudança dos valores dos 'pontos' em sua
    for(i = 0 ; i < row ; i++){                                                                     //matriz principal (matriz da imagem)...
        for(j = 0 ; j < col ; j++){                                                                 //- Observe que o tipo, as dimensões e a intensidade luminosa maxima são iguais na
            fscanf(img_file,"%d",&pixel);                                                           //imagem de saída e de entrada..
            printf("%d ",max_intense - pixel);
            fprintf(negative_img,"%d ",max_intense - pixel);
        }printf("\n");
         fputs("\n",negative_img);
    }

    //E. LIBERANDO A MEMORIA ALOCADA E FECHANDO OS ARQUIVOS...
    fclose(img_file);                                                                               //-> E. Com o arquivo de saída completo e com as informações da imagem impressas na
    fclose(negative_img);                                                                           //tela, são liberadas as memorias alocadas e fechados os arquivos abertos anteriormente...
    free(type);

    return;
}

int main ( int argc, char **argv ){
    //1. ESCOLHENDO A OPERAÇÃO A SER REALIZADA...
    int select_op = 0;                                                                            //1) Inicialmente, pede-se ao usuário que
    while( select_op != 1 && select_op != 2 && select_op != -1){                                  //entre com o valor que representa a operação
        scanf("%d%*c",&select_op);                                                                //que deseja realizar, sendo 1 para negativar
        if(select_op != 1 && select_op != 2 && select_op != -1){                                  //a imagem e 2 para realizar um filtro espacial.
            printf("Invalid command. Reenter the operation's number.\n");
            printf("-Usage: 1 (for 'negative_image) / 2 (for 'spatial filter'); / -1 (for exit).\n\n");
        }
    }

    //2. INICIANDO O PROCESSO ESCOLHIDO...
    if(select_op == 1) Negative_Img();                                                            //2)Após a entrada da operação inicia-se o processo escolhido através da
    else if(select_op == 2) Spatial_Filter();                                                     //analise do valor atribuido à variável 'op'...
                                                                                                  //- O programa é encerrado quando termina-se a operação escolhida, quando
                                                                                                  //ocorre algum erro ou quando 'op = -1';
    return 0;
}
