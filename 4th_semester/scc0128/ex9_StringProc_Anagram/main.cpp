#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

void preProcessKPM(string *pattern, vector< int > *freq){
    int m = (*pattern).length(), k;
    (*freq)[0] = -1;
    for (int i = 1; i < m; i++){
        k = (*freq)[i - 1];
        while (k >= 0){
            if ((*pattern)[k] == (*pattern)[i - 1])
                break;
            else
                k = (*freq)[k];
        }
        (*freq)[i] = k + 1;
    }
    return;
}

bool KMP(string pattern, string target){
    int m = pattern.length(), n = target.length();
    vector< int >freq(m);    
    
    preProcessKPM(&pattern, &freq);     
    
    int i = 0, k = 0;        
    while (i < n){
        if (k == -1)
            i++, k = 0;
            
        else if (target[i] == pattern[k]){
            i++, k++;
            if (k == m)
                return 1;
        }
        else
            k = freq[k];
    }
    return 0;
}

int main(){
    //1. Verifying the input...
    char c;
    string str;
    while(scanf("%c",&c) != EOF){
        //2. Reading the string...
        str += c;
        do{
            c = cin.get();
            if(c != '\n')
                str += c;
        }while(c!='\n');
        
        //3. Trying to forme a palindrome with
        //given word...
        //a. building the inverse string of given string...
        string invstr;
        for(int i = (int) str.size()-1 ; i >= 0 ; i--)
            invstr += str[i];
        
        //b. aplying the KMP ALgotihm to verify the matches
        //in given string and your inverse...
        string aux, result;
        for(int i = 0 ; i < (int) invstr.size() ; i++){
            aux = invstr.substr(0, invstr.size()-i);
            if(KMP(aux,str)){
                result = str + invstr.substr(invstr.size()-i,invstr.size());
                break;
            }
        }
 
        //4. Printing and cleaning the result string...
        cout << result << endl;
        
        str.clear();
        invstr.clear();
    }

    //5. Thats all folks :)...
    return 0;
}