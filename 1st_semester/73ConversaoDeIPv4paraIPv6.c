#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

enum{
    no,
    yes
};

void convert2IPv6( int *IPv4 ){
    int i, zero;

    printf(":::::ffff");
    for( i = 0 ; i < 4 ; i++ ){
            printf(":");

            //primeiro bloco...
            if((IPv4[i]>>4 & 255) != 0){
                if((IPv4[i]>>4 & 255) < 10)printf("%d",IPv4[i]>>4 & 255);
                else printf("%x",IPv4[i]>>4 & 255);
                zero = no;
            }
            else zero = yes;

            //segundo bloco...
            if((IPv4[i] & 15) != 0){
                if((IPv4[i] & 15) < 10)printf("%d",IPv4[i] & 15);
                else printf("%x",IPv4[i] & 15);
                zero = no;
            }
            else if( (IPv4[i] & 15) == 0 && zero == no){
                printf("%d",IPv4[i] & 15);
            }


            i++;

            //primeiro bloco...
            if((IPv4[i]>>4 & 255) != 0){
                if((IPv4[i]>>4 & 255) < 10)printf("%d",IPv4[i]>>4 & 255);
                else printf("%x",IPv4[i]>>4 & 255);
                zero = no;
            }
            else if((IPv4[i]>>4 & 225) == 0 && zero == no)
                printf("%d",IPv4[i]>>4 & 255);

            //segundo bloco...
            if((IPv4[i] & 15) != 0){
                if((IPv4[i] & 15) < 10)printf("%d",IPv4[i] & 15);
                else printf("%x",IPv4[i] & 15);
                zero = no;
            }
            else if((IPv4[i] & 15) == 0 && zero == no){
                printf("%d",IPv4[i] & 15);
            }


        }

    return;
}

int *readanIPv4(){
    int i;
    int *ip = malloc(sizeof(int)*4);

    for( i = 0 ; i < 4 ; i++ ){
        scanf("%d%*c",&ip[i]);
    }

    return ip;
}

int main ( int argc, char **argv){
    // Lendo um endereço IPv4...
    int *IPv4 = readanIPv4();

    // Convertendo IPv4 para IPv6...
        convert2IPv6(IPv4);

    free(IPv4);

   return 0;
}
