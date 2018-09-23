#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *readLine2(){

    char s;
    char *string = NULL;
    int counter = 0;

    do{ s=fgetc(stdin);
        string=(char *)realloc(string,sizeof(char)*(counter+1));
        string[counter++]=s;
        }while(s != 10);
            string[counter-1]='\0';

return string;
}

char *readLine(){//função responsável por ler e armazenar uma mensagem
                // do usuario.

    char s; // s = representa um caractere. (1 byte - STACK);
    char *string = NULL; // ponteiro responsável por armazenar
                        // uma mensagem do usuario. (8 bytes - STACK);
    int counter = 0; // counter = representa um inteiro (4 bytes - STACK);

    do{ s=fgetc(stdin); // "s" recebe um caractere do teclado.
        string=(char *)realloc(string,sizeof(char)*(counter+1)); //Um espaço de memória
                                                // é alocado na HEAP para o armazenamento
                                                // de "informação".
        string[counter++]=s; // o ponteiro ("string") armazena o "caractere/mensagem" contida em "s"
                            // na memoria HEAP. (o endereço de cada caractere é definido pelo valor
                            // de "counter")
        }while(s != 10); // define a condição para interromper o laço "do".
            string[counter-1]='\0'; //define o "caractere de parada" de leitura da string.

return string;//retorna a mensagem contida em "string" para readLine e libera a memoria alocada pelas
                //variaveis nesta função.
}

char main(){

    int n;
    scanf("%d",&n);
    char *m;


    int len=strlen(readLine()); // len = recebe um inteiro correspondente
                                //ao "tamanho" da "mensagem". (4 bytes - STACK);

    m=(char *)malloc(sizeof(char)*len); //Aloca um espaço de memória.
                                    // (sizeof(char)*len bytes - HEAP);
    m=readLine(); // Atribui ao ponteiro "m" a mensagem digitada na funçao readLine();


    int op; // op = representa um inteiro que define qual criptografia sera
            // realizada(1 para CESAR e 2 para VEGENERE). (4 bytes - STACK);
    scanf("%d",&op); // atribui ao inteiro "op" o valor digitado pelo usuario.

//------CESAR-----------------------------------------------------------------
    if(op == 1){

        int k,i=0; //k = inteiro que representa o valor do deslocamento na
                    // criptografia Cesar. (4 bytes - STACK);
                   //i = inteiro que auxiliara na leitura da mensagem e na
                    // sua criptografia. (4 bytes - STACK);

        scanf("%d",&k); // Atribui a k o valor digitado.
        if(k>=25){ k = k % 25;} //Ajusta o valor de "k" para este, quando incrementado,
                                // representar uma letra.
        else{k=k;}

        // O laço "for" será responsavel criptografar e posteriormente imprimir
        // a "nova mensagem". Ele acontecerá até que toda a mensagem seja criptografada.
        for(;i<n;i++){
        if(m[i]>=64 && m[i]<=90-k){
            printf("%c",m[i]+k);
        }
        if(m[i]<=90 && m[i]>90-k){
            printf("%c",m[i]-90+64+k);
        }
        if(m[i]<64 || m[i]>90){
            printf("%c",m[i]);
        }
    }
    }
//-----VEGENERE---------------------------------------------------------------
    if(op == 2){
        int s; // s = inteiro responsável por determinar o tamanho da chave para
                // a criptografia Vegenere. (4 bytes - STACK);
        scanf("%d",&s); // Atribui a "s" o tamanho da chave para criptografia.

        int j = 0,i = 0; // j e i = inteiros que auxiliarão na leitura da mensagem e na
                    // sua criptografia. (4 bytes cada - STACK);
        char *c; // ponteiro responsável por receber a chave da criptografia (8 bytes - STACK);
        int tam=strlen(readLine()); // tam = recebe um inteiro correspondente
                                //ao "tamanho" da "chave". (4 bytes - STACK);
        c=(char *)malloc(sizeof(char)*tam);//Aloca um espaço de memória.
                                    // (sizeof(char)*tam bytes - HEAP);
        c=readLine2(); // Atribui ao ponteiro "c" a mensagem/chave digitada na funçao readLine2();

        // O laço "for" será responsavel criptografar e posteriormente imprimir
        // a "nova mensagem". Ele acontecerá até que toda a mensagem seja criptografada.
        for(;i<n;i++){
            if(m[i]>64 && m[i]<126){
                printf("%c",((m[i]+c[j]) % 26)+65);
                j++;
            } else {printf("%c",m[i]);}

            if(j==s){j=0;}
        }
        free(c);// liberação da memoria alocada  na HEAP para o ponteiro "c";
    }
//----------------------------------------------------------------------------
        free(m);//liberação da memoria alocada na HEAP para o ponteiro "m";

return 0; //"Encerra" o programa.
}
