#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

typedef pair<int,int> piece;

void printGame(vector<piece> game, piece last){
    for(int i = 0 ; i < (int)game.size() ; i++)
        printf("[%d-%d]",game[i].first,game[i].second);
    printf("[%d-%d]\n",last.first,last.second);
    return;
}

void playSadLonelyDominoe(int nspaces, vector<piece> spacepieces, vector<piece> game, piece last, bool *winner_flag){
    if((int)game.size() == nspaces+1){
        if(game[game.size()-1].second == last.first)
            *winner_flag = true;
        return;
    }
    
    for(int i = 0 ; i < (int)spacepieces.size() ; i++){
        if(spacepieces[i].first == game[(int)game.size()-1].second){
            piece holdpiece = spacepieces[i];
            game.push_back(spacepieces[i]);
            spacepieces.erase(spacepieces.begin()+i);
            playSadLonelyDominoe(nspaces,spacepieces,game,last,winner_flag);
            game.pop_back();
            vector<piece>::iterator it = spacepieces.begin();
            spacepieces.insert(it+i,holdpiece);
        }
        else if(spacepieces[i].second == game[(int)game.size()-1].second){
            piece inverted = make_pair(spacepieces[i].second,spacepieces[i].first);
            game.push_back(inverted);
            spacepieces.erase(spacepieces.begin()+i);
            playSadLonelyDominoe(nspaces,spacepieces,game,last,winner_flag);
            game.pop_back();
            vector<piece>::iterator it = spacepieces.begin();
            spacepieces.insert(it+i,make_pair(inverted.second,inverted.first));
        }
    }
    
    return;
}

int main(){
    //1. Reading the number of spaces...
    int nspaces = 0, mpieces = 0, a = 0, b = 0;
    while(scanf("%d%*c",&nspaces) != -1 && nspaces != 0){
        //2. Reading the number of pieces to put on spaces...
        scanf("%d%*c",&mpieces);
        
        //3. Reading the piece to put on the left and the piece
        //to put on the right...
        cin >> a >> b;
        piece leftpiece = make_pair(a,b);
        cin >> a >> b;
        piece rightpiece = make_pair(a,b);
        
        //4. Reading the m pieces to put on spaces...
        vector<piece> spacepieces;
        for(int i = 0 ; i < mpieces ; i++){
            cin >> a >> b;
            spacepieces.push_back(make_pair(a,b));
        }
        
        //5. Start the building of pieces list...
        vector<piece> gamepieces;
        gamepieces.push_back(leftpiece);
        
        //6. Playing the most lonely dominoe and printing
        //'YES' if you won this sad game...
        bool winner = false;
        playSadLonelyDominoe(nspaces,spacepieces,gamepieces,rightpiece,&winner);
        if(winner)
            cout << "YES\n";
        else 
            cout << "NO\n";
            
        //7. Restarting the pieces...
        spacepieces.clear();
    }
    
    //8. That's all folks :)...
    return 0;
}