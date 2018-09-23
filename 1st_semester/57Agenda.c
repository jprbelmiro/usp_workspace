#include <stdlib.h>
#include <stdio.h>

typedef struct agenda agendas;

struct agenda {
    char **data;
    char **hora;
    char *atividade;
};


void freeNote(int num_events, agendas *note ){

    int i, j;
    for(i = 0; i < num_events; i++){
        for(j = 0; j < 3 ; j++){
            free((note+i)->data[j]);
            free((note+i)->hora[j]);
        }
        free((note+i)->data);
        free((note+i)->hora);
        free((note+i)->atividade);
    }

    return;
}

char *readLine(){
    char c;
    char *string = NULL;
    int counter = 0;
    do{
        c = fgetc(stdin);
        string = (char *)realloc(string, sizeof(char)*(counter+1));
        string[counter++] = c;
    }while(c != 10);
    string[counter - 1] = '\0';

    return string;
}

void printTab(int num_events, agendas *note ){  //(4.0) Funcao responsável por imprimir as informaçoes armazenadas...

    int i;
    for(i = 0 ; i < num_events ; i++){
        printf("%s/%s/%s - ",(note+i)->data[0],(note+i)->data[1],(note+i)->data[2]);

        printf("%s:%s:%s\n",(note+i)->hora[0],(note+i)->hora[1],(note+i)->hora[2]);

        printf("%s\n",(note+i)->atividade);
    }

        return;
}


void readTab(int num_events, agendas *note ){           //(3.0) Esta funcao é responsável por escrever na tabela
    int i,j;                                            //as informaçoes desejadas pelo usuario...

    for(i = 0; i < num_events ; i++){
        //recebendo as data;
        (note+i)->data = malloc(sizeof(int *)*3);
        for(j = 0 ; j < 3 ; j++){
            (note+i)->data[j] = readLine();
        }

        //recebendo as hora;
        (note+i)->hora = malloc(sizeof(int)*3);
        for(j = 0; j < 3 ; j++){
            (note+i)->hora[j] = readLine();
        }

        //recebendo atividade;
        (note+i)->atividade = readLine();
    }

        return;
}

int main ( int argc, char **argv){

    int num_events;                 //(1.0) Inicialmente, o usuario entra com o numero de eventos que deseja
    scanf("%d%*c",&num_events);     //marcar em sua agenda.

    agendas *note = NULL;                                   //(2.0) Cria-se uma "tabela" com o tamanho necessário
    note = realloc (note, sizeof(agendas)*num_events);      //para armazenar os eventos desejados pelo usuario.

    readTab(num_events,note);       //(3.0) Escrevendo as informaçãos no agenda.

    printTab(num_events,note);      //(4.0) Imprimindo as informações que estao na agenda.

    freeNote(num_events,note);      //(5.0) Liberando a memoria utilizada.
    free(note);

    return 0;
}
