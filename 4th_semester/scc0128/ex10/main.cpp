#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef char* t_dna;
typedef vector<t_dna> t_sequence;
typedef vector<t_sequence> t_case;

const int N = 1010;
int qt[N * N]; 
int nxt[N * N][26]; 
int nodes;

void insert(int i, string& s, int f, int at = 0){ 
    qt[i] |= f; 
    if (at == s.size()) 
        return; 
        
    int& c = nxt[i][int(s[at])]; 
    if (!c) 
        c = ++nodes; 
        
    insert(c, s, f, at + 1);
}

void searchingForLCS(t_sequence dnas, t_sequence *result){
    //1. Adding the sufixes to sufix trie and adding the
    //reapetable elements to result vec...
    for(int i = 0 ; i < (int) dnas.size() ; i++){
        for(int j = 0 ; j < (int) dnas.size() ; j++)
        insert(dnas[i][j],result,j,0);
    }
        
    
    //2. Formating the result...
    
    //3. Printing...
    return;
}

void printCases(t_case cases){
    for(int i = 0 ; i < (int)cases.size() ; i++){ 
        printf("Case %d:\n",i+1);
        for(int j = 0 ; j < (int) cases[i].size() ; j++){
            printf("word(%d) = %s\n",j+1,cases[i][j]);
        }printf("\n");
    }
    return;
}

t_dna readDNA(FILE *inputfile){
    char c;
    int counter = 0;
    t_dna dna = NULL;
    do{
        c = fgetc(inputfile);
        dna = (char *)realloc(dna,sizeof(char)*(counter+1));
        dna[counter++] = c;
    }while(c != 10 && c != 11 && c != 12 && c != 13 && c != EOF);
    dna[counter-1] = '\0';
    
    return dna;
}

t_case readingCases(){
    int n = -1;
    t_dna dna = NULL;
    t_case cases;
    
    while((dna = readDNA(stdin)) != NULL && !feof(stdin) && dna[0] != EOF){
        if(strlen(dna) == 0 || n == -1){
            n++;
            cases.push_back(t_sequence());
        }
        if(strlen(dna) > 0)
            cases[n].push_back(dna);
    }
    
    return cases;
}

int main(){
    //1. Reading the cases - dna sequences...
    t_case cases = readingCases();
    
    //2. Running the ncases...
    for(int n = 0 ; n < (int)cases.size() ; n++){
        sufixtrie = createSufixTrie();
        //a. Building the sufix trie to this case and
        //searching for the longest common sequence...
        t_sequence result;
        searchingForLCS(cases[n],&result);
        result.clear();
    }
    
    //3. Thats all folks :)...
    cases.clear();
    return 0;
}