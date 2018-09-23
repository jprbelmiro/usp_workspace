#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef vector<char> str;

void printWord(str word){
    for(int i = 0 ; i < (int) word.size() ; i++)
        printf("%c",word[i]);
    return;
}

void permutationOfWord(str word, str result, int *nresults){
    if((int)word.size() == 0){
        if(*nresults != 0)
            cout << endl;

        printWord(result);
        (*nresults)++;
        return;
    }
    
    char c = word.front();
    word.erase(word.begin());
    for(int i = 0 ; i < (int)result.size()+1; i++){
        if(result.size() == 0){
            result.push_back(c);
            permutationOfWord(word,result,nresults);
            result.pop_back();
        }
        else{
            str::iterator it = result.begin();
            result.insert(it+i,c);
            permutationOfWord(word,result,nresults);
            result.erase(result.begin()+i);
        }
    }
    str::iterator it = word.begin();
    word.insert(it,c);
    
    return;
}

int main(){
    //1. Reading the word and processing the permutation...
    char c;
    int counter = 0, nresults = 0;
    str word, result;
    while((c = fgetc(stdin)) != EOF && !feof(stdin)){
        if(counter != 0 && c != EOF)
            cout << endl << endl;
            
        //a. Reading the word...
        word.push_back(c);
        do{
            c = fgetc(stdin);
            word.push_back(c);
        }while(c != '\n');
        word.pop_back();
        
        //b. Creating a list with all permutation...
        nresults = 0;
        permutationOfWord(word,result,&nresults);
        
        //c. Cleaning...
        word.clear();
        result.clear();
        counter++;
    }
    
    //2. Thats all folks :)...
    return 0;
}