#include <stdlib.h>
#include <stdio.h>
#include "t1b_basic.h"
#include "t1b_db.h"
#include "t1b_regex.h"

//T1 - "SGBD"
int main ( int argc , char **argv ){
//Selecionando o arquivo a ser usado...
    FILE *input_file = open_file2read();

//Iniciando da resolucao de um problema que envolve Database...
    Database_problem(input_file);

//Liberando a memoria usada e fechando os arquivos usados...
    fclose(input_file);

    return 0;
}
