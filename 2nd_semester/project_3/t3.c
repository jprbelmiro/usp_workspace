#include "t3_huff.h"

//T3 - Compactacao de Huffman
int main (int argc, char **argv){
    //1 - Abrindo um arquivo para compactacao ou para descompactacao...
    //  a. A "bandeira" indica qual e a operacao que sera realizada sendo:
    //     - flag = 0 : compactacao de um arquivo de texto ".txt".
    //     - flag = 1 : descompactacao de um arquivo de texto ".huff".
    int huff_flag;
    FILE *input_file = huff_fopen(&huff_flag);
    
    switch(huff_flag){
        case 0:
            huff_compact(input_file); //Caso seja realizada a compactacao, e
                                //impresso na tela o resultado desta...
            break;
        
        case 1:
            huff_descompact(input_file);//Caso seja realizada a descompactacao,
                                //e impresso na tela o resultado desta...
            break;
    }
    
    //2 - Fechando os arquivos abertos e liberando a memoria utilizada...
    fclose(input_file);
    
    return 0;
}