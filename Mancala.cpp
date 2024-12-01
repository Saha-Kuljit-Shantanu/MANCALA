#include<iostream>

#define W1 29
#define W2 37
#define W3 53
#define W4 71

int hwin[4];

using namespace std;

/// 0 storage pit for AI 2
/// 1-6 collection pits for AI 1
/// 7 storage pits for AI 1
/// 8-13 collection pits for AI2

typedef struct {

    int board[14];
    int myextramove;
    int opextramove;
    int mycapturebead;
    int opcapturebead;

} paradigms;

int maxBeadCount(paradigms p){

    int maxbc =0;

    for(int i=1;i<7;i++){

        maxbc = maxbc+ p.board[i];
    }

    return maxbc;

}

int minBeadCount(paradigms p){

    int minbc =0;

    for(int i=8;i<14;i++){

        minbc = minbc+ p.board[i];
    }

    return minbc;

}

int heuristic_1(paradigms p){

    return ( p.board[7]-p.board[0] );
}

int heuristic_2(paradigms p){

    return W1* heuristic_1(p) + W2*( maxBeadCount(p)-minBeadCount(p) ) ;
}

int heuristic_3(paradigms p,bool player){

    if(player == true) return heuristic_2(p) + W3*p.myextramove;
    else return heuristic_2(p) - W3*p.opextramove;

}

int heuristic_4(paradigms p,bool player){

    if(player == true) return heuristic_3(p,player) + W4*p.mycapturebead;
    else return heuristic_3(p,player) - W4*p.opcapturebead;

}

bool isGameOver(paradigms p){

    return (maxBeadCount(p) == 0) || (minBeadCount(p) == 0);

}

paradigms makeMove(paradigms p,bool player,int mv){

    int kbead,ki,j = -1;

    kbead = p.board[mv];
    ki = mv;
    p.board[mv] = 0;

    for(int i=0;i<kbead;i++){

        j = (i+ki+1)%14;
        p.board[j] = p.board[j] + 1;

    }

    ///Check for empty pit

    if(player == true && j>0 && j<7 && p.board[j] == 1 && p.board[14-j] != 0){

        p.board[7] = p.board[7] + 1 + p.board[14-j];
        p.board[j] = 0;
        p.board[14-j] = 0;
        p.mycapturebead = p.mycapturebead + p.board[7];

    }

    if(player == false && j>7 && j<14 && p.board[j] == 1 && p.board[14-j] != 0){

        p.board[0] = p.board[0] + 1 + p.board[14-j];
        p.board[j] = 0;
        p.board[14-j] = 0;
        p.opcapturebead = p.opcapturebead + p.board[0];

    }

    ///Check extra move

    if(player == true && j == 7){

        p.myextramove = p.myextramove+1;

    }

    if(player == false && j == 0){

        p.opextramove = p.opextramove+1;


    }

    return p;




}

int minimax(paradigms p,int depth, int alpha,int beta,bool maxPlayer,int choice){

    if(depth == 0 || isGameOver(p) == true ){

        if(choice == 1) return heuristic_1(p);
        if(choice == 2) return heuristic_2(p);
        if(choice == 3) return heuristic_3(p,maxPlayer);
        if(choice == 4) return heuristic_4(p,maxPlayer);
    }

    if(maxPlayer == true){

        int maxval = INT_MIN;

        for(int i=1;i<7 ;i++){

            if(p.board[i] == 0) continue;


            paradigms q = makeMove(p,true,i);
            int eval;
            if(q.myextramove == p.myextramove) eval = minimax(q,depth -1, alpha,beta,false,choice);
            else eval = minimax(q,depth, alpha,beta,true,choice);

            maxval = max(maxval,eval);
            alpha = max(alpha,eval);
            if(beta <= alpha) break;
        }

        return maxval;
    }

    else{

        int minval = INT_MAX;

        for(int i=8;i<14 ;i++){

            if(p.board[i] == 0) continue;

            paradigms q = makeMove(p,false,i);
            int eval;
            if(q.opextramove == p.opextramove) eval = minimax(q,depth-1 , alpha,beta,true,choice);
            else eval = minimax(q,depth, alpha,beta,false,choice);

            minval = min(minval,eval);
            beta = min(beta,eval);
            if(beta <= alpha) break;
        }

        return minval;
    }

}

int myBestMove(paradigms p,int depth,int choice){

    int maxval = INT_MIN;
    int mv = -1;

    for(int i=1;i<7 ;i++){

        if(p.board[i] == 0) continue;

        paradigms q = makeMove(p,true,i);
        int eval;
        if(q.myextramove == p.myextramove) eval = minimax(q,depth -1, INT_MIN,INT_MAX,false,choice);
        else eval = minimax(q,depth, INT_MIN,INT_MAX,true,choice);

        if(eval > maxval){

            maxval = eval;
            mv = i;

        }


    }

    return mv;

}

int opBestMove(paradigms p,int depth,int choice){

    int minval = INT_MAX;
    int mv = -1;

    for(int i=8;i<14 ;i++){

        if(p.board[i] == 0) continue;

        paradigms q = makeMove(p,false,i);
        int eval;
        if(q.opextramove == p.opextramove) eval = minimax(q,depth -1, INT_MIN,INT_MAX,true,choice);
        else eval = minimax(q,depth, INT_MIN,INT_MAX,false,choice);

        if(eval < minval){

            minval = eval;
            mv = i;

        }


    }

    return mv;

}

void game(paradigms p, bool player,int depth,int choice1,int choice2){

    cout << choice1 << " vs " << choice2 << " : ";
    while ( isGameOver(p) == false ){

        int bm = -1;
        if(player == true) bm = myBestMove(p,depth,choice1);
        else bm = opBestMove(p,depth,choice2);
        //cout << bm << endl;
        int x = p.myextramove;
        int y = p.opextramove;
        p = makeMove(p,player,bm);
        //cout << p.board[0] << "\t";
        for(int j=13;j>7;j--){

            //cout << p.board[j] << " ";
        }
        //cout << endl << "\t" ;
        for(int j=1;j<7;j++){

            //cout << p.board[j] << " ";
        }

        //cout << "\t" << p.board[7] ;
        //cout << endl;
        if (p.myextramove == x && p.opextramove == y){

            player = !player;
        }
    }

    cout << maxBeadCount(p) + p.board[7] << " " << minBeadCount(p) + p.board[0] << endl;

    if( maxBeadCount(p) + p.board[7]  >= minBeadCount(p) + p.board[0] ) hwin[choice1-1] = hwin[choice1 -1] + 1;
    if( maxBeadCount(p) + p.board[7]  <= minBeadCount(p) + p.board[0] ) hwin[choice2 -1] = hwin[choice2 -1] + 1;

}

int main(){

    paradigms p ;
    int board[14] = {0,4,4,4,4,4,4,0,4,4,4,4,4,4};
    bool player = true;

    for(int i= 0;i<14; i++){

        p.board[i] = board[i];
    }
    int depth = 6;
    p.myextramove = 0;
    p.opextramove = 0;
    p.mycapturebead = 0;
    p.opcapturebead = 0;



    //for(int i=0;i<25;i++){

        game(p,player,depth,1,2);
        game(p,player,depth,1,3);
        game(p,player,depth,1,4);
        game(p,player,depth,2,1);
        game(p,player,depth,2,3);
        game(p,player,depth,2,4);
        game(p,player,depth,3,1);
        game(p,player,depth,3,2);
        game(p,player,depth,3,4);
        game(p,player,depth,4,1);
        game(p,player,depth,4,2);
        game(p,player,depth,4,3);

        cout << hwin[0] << " " << hwin[1] << " " << hwin[2] << " " << hwin[3];
   // }







}
