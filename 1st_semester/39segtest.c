/*
*	39 - Seg Test
* This program verifies if a major number contains a minor number
* in your minor segments.
* Ex.: 123 and 8512358 = YES
*      123 and 9999999 = NO
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

//This function verifies if a major number contains a minor 
//number in your minor segments
void segtest(char *major, char *minor){
    int i, j, k = 0;
    int lenM = strlen(major);
    int lenm = strlen(minor);

    for(i = lenM - lenm + 1; i >= 0 ; i--){
        for(j = lenm-1 ; j >= 0 ; j--){
            if(minor[j] == major[j+i])k++;
        }
        if(k == lenm){
            printf("SIM");
            return;
        } 
        else k = 0; 
    }

    printf("NAO");

    return;
}

void swap(void *a, void *b){
	void *temp;
    temp = *(void**)a;
    *(void**)a = *(void**)b;
    *(void**)b = temp;
	return;
}

int main(int argc, char **argv){
	//0. Variables
	int major = 0, minor = 0;
	char minorstr[15], majorstr[15];
	
	//1. Entrando com os Numeros;
    scanf("%d%*c%d%*c",&major,&minor);

	//2. Verifying the major and the minor
    if(major < minor)
		swap(&major,&minor);
    printf("%d %d ",minor,major);

	//3. Passing the numbers to string
	sprintf(majorstr,"%d",major);
	sprintf(minorstr,"%d",minor);

	//4. Realizing the segment test
    segtest(majorstr,minorstr);

	//5. That's all folks... :)
    return 0;
}
