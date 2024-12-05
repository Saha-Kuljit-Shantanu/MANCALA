# include "iGraphics.h"
# include<windows.h>
#include<mmsystem.h>
#include<math.h>
//#include<iostream>
#include<cstdlib>
///#include"AIvAI.cpp"
#include"AIvAI2.cpp"

//#define W1 107
//#define W2 103
using namespace std;

typedef struct{

    int posx;
    int posy;
    int beads;

} Position;

Position slot[14];
//Position tempslot[14];
int cnt;
int heuristicChoice;
int AIMove = -1;
bool isPlayerMove = true;
bool gameInit = false;
bool gameOver = false;
char x[2];


/*int storage_gap(){

    return tempslot[7].beads - tempslot[0].beads;

}*/

int playerBeadCount(){

    int pbc = 0;
    for(int i=1; i<7;i++){

        pbc = pbc + slot[i].beads;
    }

    return pbc;


}

/*int playerTempBeadCount(){

    int pbc = 0;
    for(int i=1; i<7;i++){

        pbc = pbc + tempslot[i].beads;
    }

    return pbc;


}*/

int AIBeadCount(){

    int abc = 0;

    for(int i=8; i<14;i++){

        abc = abc + slot[i].beads;
    }

    return abc;

}

/*int AITempBeadCount(){

    int abc = 0;

    for(int i=8; i<14;i++){

        abc = abc + tempslot[i].beads;
    }

    return abc;

}

bool game_over(){

    return (playerTempBeadCount() == 0) || (AITempBeadCount() == 0)

}

int gamepit_gap(){

    return playerTempBeadCount()-AITempBeadCount();

}

int heuristic_1(){

    return storage_gap();

}

int heuristic_2(){

    return W1*storage_gap() + W2*gamepit_gap();

}

int heuristic_3(){

    return W1*storage_gap() + W2*gamepit_gap();

}
*/



///Player game pits 1 to 6
///Player storage pit 7
///AI game pits 8 to 13
///AI storage pit 0

void iDraw(){

    iClear();
    iSetColor(255,255,125);
    iFilledRectangle(100,200,100,200);
    iSetColor(250,0,0);
    iFilledCircle(150,300,30,200);

    if(gameInit == false){
        iSetColor(0,0,0);
        iText(140,290,"0",GLUT_BITMAP_TIMES_ROMAN_24);
        slot[0] = {140,290,0};
    }
    else{
        if(slot[0].beads != 0) iSetColor(0,255,0);
        else iSetColor(0,0,0);

        //char* x = new char[1];
        //x[0] = slot[0].beads + 48;
        sprintf(x, "%d", slot[0].beads);
        iText(slot[0].posx,slot[0].posy,x,GLUT_BITMAP_TIMES_ROMAN_24);

    }

    iSetColor(20,0,200);
    iText(70,290,"0",GLUT_BITMAP_TIMES_ROMAN_24);



    for(int i=0;i<6;i++){
        iSetColor(10,155,155);
        iFilledRectangle(210+110*i,200,100,90);
        iSetColor(250,0,0);
        iFilledCircle(260+110*i,245,30,200);
        iSetColor(20,0,200);
        sprintf(x, "%d", i+1);
        iText(250+110*i,170,x,GLUT_BITMAP_TIMES_ROMAN_24);
        if(gameInit == false){
            iSetColor(0,255,0);
            iText(250+110*i,235,"4",GLUT_BITMAP_TIMES_ROMAN_24);
            slot[i+1] = {250+110*i,235,4};
        }

        else{

            if(slot[i+1].beads != 0) iSetColor(0,255,0);
            else iSetColor(0,0,0);
            //char* x = new char[1];
            //x[0] = slot[i+1].beads + 48;
            //itoa(slot[i+1].beads,x,10);
            sprintf(x, "%d", slot[i+1].beads);
            iText(slot[i+1].posx,slot[i+1].posy,x,GLUT_BITMAP_TIMES_ROMAN_24);
        }

        iSetColor(10,0,155);
        iFilledRectangle(210+110*i,310,100,90);
        iSetColor(250,0,0);
        iFilledCircle(260+110*i,355,30,200);
        iSetColor(20,0,200);
        if(AIMove+ i == 13) iSetColor(255,255,255);
        sprintf(x, "%d", 13-i);
        iText(250+110*i,420,x,GLUT_BITMAP_TIMES_ROMAN_24);
        if(gameInit == false){

            iSetColor(0,255,0);
            iText(250+110*i,345,"4",GLUT_BITMAP_TIMES_ROMAN_24);
            slot[13-i] = {250+110*i,345,4};
        }

        else{


            if(slot[13-i].beads != 0) iSetColor(0,255,0);
            else iSetColor(0,0,0);
            //char* x = new char[1];
            //x[0] = slot[13-i].beads + 48;
            //itoa(slot[13-i].beads,x,10);
            sprintf(x, "%d", slot[13-i].beads);
            iText(slot[13-i].posx,slot[13-i].posy,x,GLUT_BITMAP_TIMES_ROMAN_24);
        }

    }

    iSetColor(125,250,250);
    iFilledRectangle(870,200,100,200);
    iSetColor(250,0,0);
    iFilledCircle(920,300,30,200);
    if(gameInit== false){
        iSetColor(0,0,0);
        iText(910,290,"0",GLUT_BITMAP_TIMES_ROMAN_24);
        slot[7] = {910,290,0};
    }

    else{

        if(slot[7].beads != 0) iSetColor(0,255,0);
        else iSetColor(0,0,0);
        sprintf(x, "%d", slot[7].beads);
        iText(slot[7].posx,slot[7].posy,x,GLUT_BITMAP_TIMES_ROMAN_24);
    }

    iSetColor(20,0,200);
    iText(990,290,"7",GLUT_BITMAP_TIMES_ROMAN_24);


    iSetColor(0,120,120);
    if(isPlayerMove == true && gameOver == false) iText(100,100,"Player's Turn",GLUT_BITMAP_TIMES_ROMAN_24);

    else if(isPlayerMove == false && gameOver == false){
            iText(100,500,"AI's Turn",GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(220,220,220);
            iFilledRectangle(300,500,100,30);
            iSetColor(0,0,215);
            iText(330,510,"Click here",GLUT_BITMAP_TIMES_ROMAN_10);
            iSetColor(0,120,120);
    }

    else if (gameOver == true) {
            iText(300,500,"GameOver!",GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(220,220,220);
            iFilledRectangle(250,600,250,60);
            iSetColor(100,0,200);
            if(slot[0].beads > slot[7].beads ) iText(280,620,"WINNER | AI",GLUT_BITMAP_TIMES_ROMAN_24);
            else if(slot[0].beads == slot[7].beads ) iText(280,620,"MATCH DRAW",GLUT_BITMAP_TIMES_ROMAN_24);
            else iText(280,620,"WINNER | Player",GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(20,0,200);
            iText(220,560,"SCORE : AI ",GLUT_BITMAP_TIMES_ROMAN_24);
            sprintf(x, "%d", slot[0].beads);
            iText(360,560,x,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(390,560,"-",GLUT_BITMAP_TIMES_ROMAN_24);
            sprintf(x, "%d", slot[7].beads);
            iText(420,560,x,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(450,560," Player",GLUT_BITMAP_TIMES_ROMAN_24);

    }

    //if(gameOver == true) cout << gameOver;


}

void iKeyboard(unsigned char key){

    if(key == '8'){

        for(int i=0;i<13;i++){

            cout << slot[i].posx << " " << slot[i].posy << endl;
            //printf("A");

        }

        cout << gameOver << endl;
    }

}

void iSpecialKeyboard(unsigned char key){



}

void iMouse(int button,int state,int mx,int my)
{
    int kbead,ki;
    //int bm = -1;

    ///Make the bead count of move pit 0 storing the bead and slot count


    if(isPlayerMove == true && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

        for(int i=1;i<7;i++){

            if( mx < slot[i].posx+30 && mx > slot[i].posx-30 && my > slot[i].posy- 30 && my< slot[i].posy + 30 ){

                gameInit = true;
                kbead = slot[i].beads;
                ki = i;
                slot[i].beads = 0;
                break;
                //iSetColor(0,0,0);
                //iText(slot[i].posx,slot[i].posy,"0",GLUT_BITMAP_TIMES_ROMAN_24);
            }

            //return;
        }

    }

    if(isPlayerMove == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){


        if( (mx < 500 && mx >300)&& (my < 530 && my > 500) ) ;
        else return;

        kbead = slot[AIMove].beads;
        ki = AIMove;
        slot[AIMove].beads = 0;



       /* for(int i=8;i<14;i++){

            if( mx < slot[i].posx+30 && mx > slot[i].posx-30 && my > slot[i].posy- 30 && my< slot[i].posy + 30 ){
                kbead = slot[i].beads;
                ki = i;
                slot[i].beads = 0;
                break;

            }

            //return;
        }*/


    }

    int j=-1;

    ///Increase the bead count of the following bead count amount of slots by 1

    for(int i=0;i<kbead;i++){

        j = (i+ki+1)%14;
        if( (j == 0 && isPlayerMove == true) || (j == 7 && isPlayerMove == false)) kbead++;
        else slot[j].beads = slot[j].beads +1;


    }

    if(j== -1) return;

    ///Console Print Board

    if(isPlayerMove == true) cout << "Player's Turn : " << ki << endl << endl;
    else cout << "AI's Turn : " << ki << endl << endl;

    cout << slot[0].beads << "\t";

    for(int c=13;c>7;c--){

        cout << slot[c].beads << " ";
    }
    cout << endl << "\t" ;

    for(int c=1;c<7;c++){

        cout << slot[c].beads << " ";
    }

    cout << "\t" << slot[7].beads ;
    cout << endl << endl;



    ///Check for empty Pit


    if(isPlayerMove == true && j > 0 && j < 7 && slot[j].beads == 1 && slot[14-j].beads != 0){

        slot[7].beads = slot[7].beads + 1 + slot[14-j].beads ;

        slot[j].beads = 0 ;
        slot[14-j].beads = 0;

    }

    if(isPlayerMove == false && j > 7 && j < 14 && slot[j].beads == 1 && slot[14-j].beads != 0){

        slot[0].beads = slot[0].beads + 1 + slot[14-j].beads ;

        slot[j].beads = 0 ;
        slot[14-j].beads = 0;

    }

    ///Check for game Over





    if(playerBeadCount() == 0){

        gameOver =  true;
        slot[0].beads = slot[0].beads + AIBeadCount();
        for(int i=8; i<14;i++){

            slot[i].beads = 0;
        }


       // cout << "G : " << gameOver << endl;
       // return;

    }

    if(AIBeadCount() == 0){

        gameOver =  true;
        slot[7].beads = slot[7].beads + playerBeadCount();
        for(int i=1; i<7;i++){

            slot[i].beads = 0;
        }


       // cout << "G : " << gameOver << endl;
       // return;

    }


    if(isPlayerMove == true && j != 7){

        isPlayerMove = false;
    }

    else if(isPlayerMove == false && j != 0){

        isPlayerMove = true;
    }

    if(isPlayerMove == true){

        AIMove = -1;
    }

    if(isPlayerMove == false){

        paradigms p ;

        for(int i= 0;i<14; i++){

            p.board[i] = slot[i].beads;
        }
        int depth = 8;
        p.myextramove = 0;
        p.opextramove = 0;
        p.mycapturebead = 0;
        p.opcapturebead = 0;

        AIMove = opBestMove(p,depth,heuristicChoice);
    }


}
void iMouseMove(int mx,int my)
{

}

int main()
{


    heuristicChoice = getHeuristic() + 1;
    //PlaySound("fts.wav",NULL,SND_ASYNC|SND_LOOP);
    iInitialize(1200,700,"Mancala");

}

///3,4,2,6,3,6,3,6,2...
