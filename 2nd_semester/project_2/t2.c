#include "t2_basic.h"
#include "t2_math.h"

//T2 - Transformada de Fourier Aplicada a Audio
int main (int argc, char **argv){
    
    int i, k;
    
    //1 - Abrindo o arquivo de audio...
    FILE *faudio = fopen_rb();
    
        //1a - Lendo todo o conteudo do arquivo e armazenando em um vetor dina_
        //micamente alocado e obtendo o numero de observacoes do audio...
        int N = 0;
        t_raw *audio = fread_raw(faudio,&N);
        
        //1b - Lendo o valor dado a C pelo usuario...
        int C;
            scanf("%d%*c",&C);

    //2 - Aplicando a Transformada Discreta de Fourier para obter os coeficien_
    //tes do audio...
        t_complex *c = fourier_dtransform(audio,N);

    //3 - Calculando a magnitude para cada coeficiente...
        t_coefficient *coef = getallmag(c,N);

        //3a - Ordenando o vetor de magnitudes...
        merge_sort_amp(coef,0,(N/2));

        //3b - Descobrindo quantos são os sinais relevantes do audio (>0.1)...
        for(k = 0 ; k <= N/2 ; k++)
            if(coef[k].amplitude < 0.1)
                break;
                
        //3c - Atribuindo o valor zero aos coeficientes menos relevantes...
        for(i = C ; i <= N/2 ; i++){
            coef[i].amplitude = 0.0;
            coef[i].coef.real = 0.0;
            coef[i].coef.imaginary = 0.0;
        }
        
        //3d - Guardando os valores das magnitudes ordenadas mais relevantes...
        double *magn = (double *)malloc(sizeof(double)*C);
        for(i = 0 ; i < C ; i++)
            magn[i] = coef[i].amplitude;
        
        //3e - Retornando os coeficientes para as posicoes originais - antes
        //da ordenacao...
        merge_sort_freq(coef,0,(N/2));
        
        //3f - Aplicando a inversa para compor o novo audio.
        unsigned char *newaudio = fourier_inversedtransform(coef,N);
    
    //4 - Imprimindo na tela os resultados importantes obtidos...
    printf("%d\n",N);
    printf("%d\n",k);
    for(i = 0 ; i < C ; i++){
        if(i != C-1)
            printf("%d ",(int)magn[i]);
        else
            printf("%d\n",(int)magn[i]);
    }
    printf_raw(newaudio,N);
    
    //5 - Fechando os arquivos e liberando a memoria utilizada...
    fclose(faudio);
    
    free(audio);
    free(c);
    free(coef);
    free(magn);
    free(newaudio);
    
    return 0;
}