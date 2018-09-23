#include <stdlib.h>
#include <stdio.h>

typedef struct object object;

typedef enum {
    UrSoBadInThisGame,
    FirstBlood
} CSboolean;

struct object{
    int qtt_points;
    double *x;
    double max_x, min_x;
    double *y;
    double max_y, min_y;
    double *z;
    double max_z, min_z;
};

void FindBoundingBox( object *obj ){
    int i;

    // Atribuindo um valor real e valido aos maximos e minimos, inicialmente,
    //ou seja, pertencente ao universo de cada coordenada, para que a comparação
    //seja efetiva...
    obj->max_x = obj->x[0];
    obj->min_x = obj->x[0];
    obj->max_y = obj->y[0];
    obj->min_y = obj->y[0];
    obj->max_z = obj->z[0];
    obj->min_z = obj->z[0];

    // Encontrando as coordenadas maximas e minimas para x,y e z...
    for(i  = 0 ; i < obj->qtt_points ; i++){
            //coordenada x...
        if(obj->max_x < obj->x[i])
            obj->max_x = obj->x[i];
        if(obj->min_x > obj->x[i])
            obj->min_x = obj->x[i];

            //coordenada y...
        if(obj->max_y < obj->y[i])
            obj->max_y = obj->y[i];
        if(obj->min_y > obj->y[i])
            obj->min_y = obj->y[i];

            //coordenada z...
        if(obj->max_z < obj->z[i])
            obj->max_z = obj->z[i];
        if(obj->min_z > obj->z[i])
            obj->min_z = obj->z[i];
    }


    return;
}

CSboolean FindHit( object *obj, object *bala ){
    // Aqui é feita a analise se houve colisão ou não da bala com o personagem...
    //Caso aconteça...
    if( obj->max_x >= bala->max_x && obj->min_x <= bala->min_x
        && obj->max_y >= bala->max_y && obj->min_y <= bala->min_y
        && obj->max_z >= bala->max_z && obj->min_z <= bala->min_z){
            return FirstBlood;
    }

    //Caso contrario...
    else return UrSoBadInThisGame;

}

void printHit( object *obj, object *bala){
    // Entrando com Box da bala...
    //minimos...
    scanf("%lf%*c",&bala->min_x);
    scanf("%lf%*c",&bala->min_y);
    scanf("%lf%*c",&bala->min_z);
    //maximos...
    scanf("%lf%*c",&bala->max_x);
    scanf("%lf%*c",&bala->max_y);
    scanf("%lf%*c",&bala->max_z);

    FindBoundingBox(obj);
    CSboolean hit = FindHit(obj,bala);

    // Caso aconteça...
    if(hit)
        printf("COLISAO\n");
    // Caso contrario...
    else if(!hit)
        printf("NULL\n");
    // Isso não é para acontecer...
    else
        printf("Eu nao sei o que esta acontecendo...");

    return;
}

void printBoudingBox( object *obj){

    FindBoundingBox(obj);

    printf("%.4lf %.4lf %.4lf \n", obj->min_x,obj->min_y,obj->min_z);
    printf("%.4lf %.4lf %.4lf \n", obj->max_x,obj->max_y,obj->max_z);

    return;
}

void printObject( object *obj){
    int i;

    for( i = 0 ; i < obj->qtt_points ; i++){
        printf("%.4lf %.4lf %.4lf \n", obj->x[i], obj->y[i], obj->z[i]);
    }

    return;
}

void inforead( FILE *fp , object *obj){
    int i;
    fscanf(fp,"%d%*c",&obj->qtt_points);

    obj->x = malloc(sizeof(double)*obj->qtt_points);
    obj->y = malloc(sizeof(double)*obj->qtt_points);
    obj->z = malloc(sizeof(double)*obj->qtt_points);
    for( i = 0 ; i < obj->qtt_points ; i++){
        fscanf(fp,"%lf%*c%lf%*c%lf%*c",&obj->x[i],&obj->y[i],&obj->z[i]);
    }

    return;
}

FILE *open2read(char *name){
    FILE *fp = NULL;
        fp = fopen(name,"r");

        if(fp == NULL){
            printf("Nao foi possivel abrir o arquivo...");
            printf("O programa vai ser encerrado...");
            exit(1);
        }

    return fp;
}

char *readLine(){
    int counter = 0;
    char c;
    char *s = NULL;
    do{
        c = fgetc(stdin);
        s = (char *)realloc(s,sizeof(char)*(counter+1));
        s[counter++] = c;
    }while(c != 10);
        s[counter - 1] = '\0';

    return s;
}

int main ( int argc, char **argv){
	// PROVA 3 - Counter Strike
    // Lendo uma opção inteira...
    int opc;
        scanf("%d%*c", &opc);

    // Lendo o nome do arquivo que contem os pontos que descrevem
    //o personagem e abrindo-o...
    char *input_file_name = readLine();
    FILE *input_file = open2read(input_file_name);

    // Lendo as informações do arquivo...
        object *obj = malloc(sizeof(object));
            inforead(input_file,obj);

    // Iniciando a opção escolhida ...
    if(opc == 1){
        printObject(obj);
    }
    else if(opc == 2){
        printBoudingBox(obj);
    }
    else if(opc == 3){
        object *bala = malloc(sizeof(object));
        printHit(obj,bala);
        free(bala);
    }
    else printf("Opcao invalida...");

    // Liberando a memoria utilizada e fechando os arquivos abertos...
    free(input_file_name);
    fclose(input_file);
    free(obj->z);
    free(obj->y);
    free(obj->x);
    free(obj);

    return 0;
}
