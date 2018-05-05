#include<string>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<conio.h>
#include<time.h>

using namespace std;

const int KEY_LEFT = 'a',KEY_RIGHT ='d',KEY_UP ='w',KEY_DOWN ='s';
const int HEIGHT=25,WIDTH=40;
bool hasntWon=true;
int hp=100;
unsigned char healthbar[10] = {'+','+','+','+','+','+','+','+','+','+'};

enum DirectionX {Right,Left};
enum DirectionY {Up,Down};
struct Player{
char sprite;
int x;
int y;
};

struct Enemy{
      char sprite;
      int x;
      int y;
      DirectionX pastDirX;
      DirectionY pastDirY;
      };

unsigned char MoveEnemy(Enemy& enemy,unsigned char maze[HEIGHT][WIDTH],int i,int j,string& smove,bool& nc){
     if(nc){
        //possible up,down,right,left
        bool psbUp=false;
        bool psbDown=false;
        bool psbRight=false;
        bool psbLeft=false;

        //is it possible in all given directions?
        if(maze[enemy.y][enemy.x+1] !='+'){//RIGHT
            psbRight=true;
        }
        if(maze[enemy.y][enemy.x-1] !='+'){//LEFT
            psbLeft=true;
        }
         if(maze[enemy.y+1][enemy.x] !='+'){//DOWN
            psbDown=true;
        }
         if(maze[enemy.y-1][enemy.x] !='+'){//UP
            psbUp=true;
        }

        //movement tracking
        enum Mv{up,right,down,left,NA};
        Mv move = NA;

        //previous movement
        if(smove=="up"){
            move =up;
        }
        else if(smove=="right"){
            move =right;
        }
        else if(smove=="down"){
            move =down;
        }
        else if(smove=="left"){
            move =left;
        }
        else{
            move = NA;
        }

        //if previous movement is x was right,but now it's not possible to move to the right
        if(enemy.pastDirX==Right && !psbRight){
            if(enemy.pastDirY==Up){//was the past movement in Y UP?
                if(psbUp){//is it possible to move up
                    move =up;
                }
                else if(psbDown && move != up){//if not is it possible to move down as long as we didn't come from up?
                    move =down;
                }
                else if(psbLeft){//or is it then possible to move left
                    move =left;
                }
                else{//if there is no other choice move up
                    move =down;
                }
            }
            else{//was the past movement in Y down?
                if(psbDown){//is it possible to move down?
                    move =down;
                }
             else if(psbUp && move != down){//if not is it possible to move up as long as we come from down?
                move =up;
             }
             else if(psbLeft){//or is it then possible to move left?
                move =left;
             }
             else{//if there is no other choice move up
                move =up;
             }
            }
        }
        else if(enemy.pastDirX==Right && psbRight){
            move = right;//if we can move right and we want to go right,go right.
        }
        else if(enemy.pastDirX == Left && !psbLeft){//STORY REPEATS LIKE THIS FOR ALL DIRECTIONS
            if(enemy.pastDirY == Up){
                if(psbUp){
                    move = up;
                }
                else if(psbDown && move != up){
                    move=down;
                }
                else if(psbRight){
                    move=right;
                }
                else {
                    move=down;
                }
            }
            else{
                if(psbDown){
                    move =down;
                }
                else if(psbUp && move !=down){
                    move =up;
                }
                else if(psbRight){
                    move =right;
                }
                else{
                    move=up;
                }
            }
        }
        else if(enemy.pastDirX == Left && psbLeft){
            move=left;
        }
        else if(enemy.pastDirY == Up && !psbUp){
            if(enemy.pastDirX == Right){
                if(psbRight){
                    move=right;
                }
                else if (psbLeft && move !=right){
                    move=left;
                }
                else if (psbDown){
                    move=down;
                }
                else{
                    move=left;
                }
            }
            else{
                if(psbLeft){
                    move = left;
                }
                else if(psbRight && move != left){
                    move=right;
                }
                else if(psbDown){
                    move=down;
                }
                else{
                    move=right;
                }
            }
        }
        else if(enemy.pastDirY == Up && psbUp){
            move=up;
        }
        else if(enemy.pastDirY == Down && !psbDown){
            if(enemy.pastDirX==Right){
                if(psbRight){
                    move=right;
                }
                else if(psbLeft && move != right){
                    move=left;
                }
                else if(psbUp){
                    move=up;
                }
                else{
                    move =left;
                }
            }
            else{
                if(psbLeft){
                    move=left;
                }
                else if(psbRight && move != left){
                    move=right;
                }
                else if(psbRight){
                    move=up;
                }
                else{
                    move=right;
                }
            }
        }

else if (enemy.pastDirY==Down && psbDown)
{
    move = down;
}// what is the said movement =

       switch(move){
   case up:
    //set variables accordingly
    maze[enemy.y][enemy.x]=   ' ';
    enemy.pastDirY= Up;
    smove = "up";
    enemy.y--;
    break;
   case right:
    maze[enemy.y][enemy.x]=' ';
    enemy.pastDirX=Right;
    smove= "right";
    enemy.x++;
    break;
   case down:
    maze[enemy.y][enemy.x]=' ';
    enemy.pastDirY=Down;
    smove= "right";
    enemy.y++;
    break;
   case left:
    maze[enemy.y][enemy.x]=' ';
    enemy.pastDirX=Left;
    smove= "left";
    enemy.x--;
    break;
   case NA:
    smove= "NA";
    break;
       }
    }
    nc= false;
    return maze[i][j];
}
void delay(clock_t a)
{
    clock_t start;
    start  = clock();
    while(clock()-start<a)
    {

    }
}

int main()
{
    int m;
    char str[100]=" C      O      N      S      O      L      E",str1[100]="  R      U      N",ch;
   for(m=0;m<10;m++)
    {
        cout<<endl;
    }
    for(m=0;m<30;m++)
    {
        cout<<" ";
    }
    for(m=0;str[m]!='\0';m++)
    {
        cout<<str[m];
        delay(70);
    }
   cout<<endl<<endl<<endl;
    for(m=0;m<30;m++)
    {
        cout<<" ";
    }
    for(m=0;str1[m]!='\0';m++)
    {
        cout<<str1[m];
        delay(70);
    }

    delay(1500);
    system("cls");


     int a;
    while (a!=3){

    cout<<"1 : How to play."<<endl<<"2 : Play the GAME."<<endl<<"press 3 to quit the menu and press Q to quit the game "<<endl;

    cout<<"Please select your choice : ";
    cin>>a;
    switch (a){
    case 1 :
        cout<<endl<<"A CSE student is stuck in Laptop console while doing a project. And there are many virus up there to destroy him. help him to get him out of it . you can use : \nUp = w\nDown = s\nLeft = a\nRight = d\n\n Here > is a student and @ is virus\n\n";
        break;
    case 2 :
    srand (time (NULL));
    unsigned char maze [HEIGHT][WIDTH] ={
'+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+',
' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+','+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ','+',
'+','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ',' ','+',' ','+','+','+',' ','+','+','+',' ','+',' ','+','+','+',' ','+',' ','+',' ','+','+',' ','+',
'+',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ','+',' ','+','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ',' ','+',
'+',' ','+','+',' ','+','+','+',' ','+',' ','+',' ','+',' ',' ',' ',' ','+',' ','+','+','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+','+',
'+',' ','+',' ',' ','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+','+',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ',' ','+',
'+',' ','+',' ','+','+',' ','+',' ','+',' ',' ',' ',' ',' ',' ',' ',' ','+',' ','+','+','+',' ','+','+','+','+','+','+','+','+','+',' ','+',' ','+','+',' ','+',
'+',' ','+',' ','+',' ',' ','+',' ','+','+','+','+',' ','+','+','+',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',
'+',' ','+',' ','+','+',' ','+',' ','+',' ',' ',' ',' ','+',' ',' ',' ','+','+','+','+','+',' ','+',' ','+',' ','+',' ','+','+',' ','+','+',' ','+',' ','+','+',
'+',' ','+',' ',' ',' ',' ','+',' ','+','+','+','+',' ','+','+','+','+','+',' ',' ',' ','+',' ','+',' ','+',' ','+',' ','+','+',' ',' ','+',' ','+',' ',' ','+',
'+',' ','+','+','+','+',' ','+',' ',' ',' ',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ',' ',' ','+',' ','+',' ',' ','+',' ','+','+','+','+','+',' ','+',
'+',' ',' ',' ',' ','+',' ','+',' ','+','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+',' ','+',' ','+','+','+','+',' ',' ',' ','+',' ','+',' ','+',
'+',' ','+','+',' ',' ',' ','+',' ',' ',' ',' ','+',' ','+',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ','+',
'+',' ','+',' ',' ','+',' ','+',' ','+','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+',' ','+',' ','+','+','+','+',' ','+',' ','+',' ','+','+','+','+','+',
'+',' ','+',' ','+','+',' ','+',' ','+',' ',' ',' ',' ','+',' ','+',' ',' ','+',' ',' ',' ',' ','+',' ',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ','+',' ','+',
'+',' ','+',' ','+',' ',' ','+',' ','+','+','+','+','+','+',' ','+',' ','+','+',' ','+','+','+','+','+','+','+',' ','+',' ','+',' ',' ',' ','+',' ','+',' ','+',
'+',' ','+',' ','+',' ','+','+',' ','+',' ',' ',' ',' ',' ',' ','+',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ','+','+','+','+','+',' ','+',' ','+',
'+',' ','+',' ','+',' ',' ','+',' ','+',' ','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+',' ','+',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ','+',
'+',' ','+','+','+','+','+','+',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+',
'+',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ',' ',' ','+',
'+',' ','+','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+',' ',' ',' ','+',' ','+','+','+',' ','+',
'+',' ',' ','+',' ','+',' ','+',' ','+',' ','+',' ',' ',' ','+',' ','+',' ','+',' ','+',' ','+',' ',' ',' ',' ',' ','+','+','+',' ','+',' ','+',' ','+',' ','+',
'+',' ','+','+',' ','+',' ','+','+','+',' ','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+',' ','+',' ',' ',' ','+',' ','+',' ','+',' ','+',
'+',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',
'+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+',
};
    Player player;
    player.sprite = '>';
    player.x=0;
    player.y=1;



    Enemy enemy1;
    enemy1.sprite= '@';
    enemy1.x= rand()%WIDTH;
    enemy1.y=rand()%HEIGHT;
    enemy1.pastDirX = Left;
    enemy1.pastDirY= Up;

    while (maze[enemy1.y][enemy1.x] != ' '){
        enemy1.x=rand()%WIDTH;
        enemy1.y =rand()%HEIGHT;
    }
    if(maze[enemy1.y][enemy1.x]==' '){
        maze[enemy1.y][enemy1.x]=enemy1.sprite;
    }
        Enemy enemy2;
    enemy2.sprite= '@';
    enemy2.x= rand()%WIDTH;
    enemy2.y=rand()%HEIGHT;
    enemy2.pastDirX = Left;
    enemy2.pastDirY= Up;

    while (maze[enemy2.y][enemy2.x] != ' '){
        enemy2.x=rand()%WIDTH;
        enemy2.y =rand()%HEIGHT;
    }
    if(maze[enemy2.y][enemy2.x]==' '){
        maze[enemy2.y][enemy2.x]=enemy2.sprite;
    }
        Enemy enemy3;
    enemy3.sprite= '@';
    enemy3.x= rand()%WIDTH;
    enemy3.y=rand()%HEIGHT;
    enemy3.pastDirX = Left;
    enemy3.pastDirY= Up;

    while (maze[enemy3.y][enemy3.x] != ' '){
        enemy3.x=rand()%WIDTH;
        enemy3.y =rand()%HEIGHT;
    }
    if(maze[enemy3.y][enemy3.x]==' '){
        maze[enemy3.y][enemy3.x]=enemy3.sprite;
    }
        Enemy enemy4;
    enemy4.sprite= '@';
    enemy4.x= rand()%WIDTH;
    enemy4.y=rand()%HEIGHT;
    enemy4.pastDirX = Left;
    enemy4.pastDirY= Up;

    while (maze[enemy4.y][enemy4.x] != ' '){
        enemy4.x=rand()%WIDTH;
        enemy4.y =rand()%HEIGHT;
    }
    if(maze[enemy4.y][enemy4.x]==' '){
        maze[enemy4.y][enemy4.x]=enemy4.sprite;
    }
        Enemy enemy5;
    enemy5.sprite= '@';
    enemy5.x= rand()%WIDTH;
    enemy5.y=rand()%HEIGHT;
    enemy5.pastDirX = Left;
    enemy5.pastDirY= Up;

    while (maze[enemy5.y][enemy5.x] != ' '){
        enemy5.x=rand()%WIDTH;
        enemy5.y =rand()%HEIGHT;
    }
    if(maze[enemy5.y][enemy5.x]==' '){
        maze[enemy5.y][enemy5.x]=enemy5.sprite;
    }
    Enemy enemy6;
    enemy6.sprite= '@';
    enemy6.x= rand()%WIDTH;
    enemy6.y=rand()%HEIGHT;
    enemy6.pastDirX = Left;
    enemy6.pastDirY= Up;

    while (maze[enemy6.y][enemy6.x] != ' '){
        enemy6.x=rand()%WIDTH;
        enemy6.y =rand()%HEIGHT;
    }
    if(maze[enemy6.y][enemy6.x]==' '){
        maze[enemy6.y][enemy6.x]=enemy6.sprite;
    }
    Enemy enemy7;
    enemy7.sprite= '@';
    enemy7.x= rand()%WIDTH;
    enemy7.y=rand()%HEIGHT;
    enemy7.pastDirX = Left;
    enemy7.pastDirY= Up;

    while (maze[enemy7.y][enemy7.x] != ' '){
        enemy7.x=rand()%WIDTH;
        enemy7.y =rand()%HEIGHT;
    }
    if(maze[enemy7.y][enemy7.x]==' '){
        maze[enemy7.y][enemy7.x]=enemy7.sprite;
    }
    Enemy enemy8;
    enemy8.sprite= '@';
    enemy8.x= rand()%WIDTH;
    enemy8.y=rand()%HEIGHT;
    enemy8.pastDirX = Left;
    enemy8.pastDirY= Up;

    while (maze[enemy8.y][enemy8.x] != ' '){
        enemy8.x=rand()%WIDTH;
        enemy8.y =rand()%HEIGHT;
    }
    if(maze[enemy8.y][enemy8.x]==' '){
        maze[enemy8.y][enemy8.x]=enemy8.sprite;
    }
    Enemy enemy9;
    enemy9.sprite= '@';
    enemy9.x= rand()%WIDTH;
    enemy9.y=rand()%HEIGHT;
    enemy9.pastDirX = Left;
    enemy9.pastDirY= Up;

    while (maze[enemy9.y][enemy9.x] != ' '){
        enemy9.x=rand()%WIDTH;
        enemy9.y =rand()%HEIGHT;
    }
    if(maze[enemy9.y][enemy9.x]==' '){
        maze[enemy9.y][enemy9.x]=enemy1.sprite;
    }
    Enemy enemy10;
    enemy10.sprite= '@';
    enemy10.x= rand()%WIDTH;
    enemy10.y=rand()%HEIGHT;
    enemy10.pastDirX = Left;
    enemy10.pastDirY= Up;

    while (maze[enemy10.y][enemy10.x] != ' '){
        enemy10.x=rand()%WIDTH;
        enemy10.y =rand()%HEIGHT;
    }
    if(maze[enemy10.y][enemy10.x]==' '){
        maze[enemy10.y][enemy10.x]=enemy1.sprite;
    }

    string prevmove1 = "NA";
    string prevmove2 = "NA";
    string prevmove3 = "NA";
    string prevmove4 = "NA";
    string prevmove5 = "NA";
     string prevmove6 = "NA";
      string prevmove7 = "NA";
       string prevmove8 = "NA";
        string prevmove9 = "NA";
         string prevmove10 = "NA";

    while(hasntWon){
        maze[enemy1.y][enemy1.x] = enemy1.sprite;
        maze[enemy2.y][enemy2.x] = enemy2.sprite;
        maze[enemy3.y][enemy3.x] = enemy3.sprite;
        maze[enemy4.y][enemy4.x] = enemy4.sprite;
        maze[enemy5.y][enemy5.x] = enemy5.sprite;
        maze[enemy6.y][enemy6.x] = enemy6.sprite;
        maze[enemy7.y][enemy7.x] = enemy7.sprite;
        maze[enemy8.y][enemy8.x] = enemy8.sprite;
        maze[enemy9.y][enemy9.x] = enemy9.sprite;
        maze[enemy10.y][enemy10.x] = enemy10.sprite;


        if(maze[player.y][player.x] == ' '){
            maze[player.y][player.x] = player.sprite;
        }
        else if (maze[player.y][player.x] == '@'){
            maze[player.y][player.x] = '?';
        }
        for (int y=0; y<HEIGHT ; y++){
            cout<<endl;
            for(int x=0; x<WIDTH; x++){
                cout<<maze[y][x];
            }
        }
        cout<<endl;
        cout<<endl<<"HP :" ;
        for(int h=0; h<hp/10;h++){
            cout<<healthbar[h]<<" ";
        }
        char key = getch();
        switch (key){
    case KEY_LEFT:
        if(maze[player.y][player.x-1] != '+'){
            maze[player.y][player.x] = ' ';
            if(maze[player.y-1][player.x-1] == '@'){
                hp -= 20;
            }
                player.x--;
            }
            break;
    case KEY_UP :
        if(maze[player.y-1][player.x] != '+'){
            maze[player.y][player.x] = ' ' ;
            if(maze[player.y-1][player.x] == '@'){
                hp -=20 ;
            }
            player.y--;
        }
        break;
    case KEY_DOWN :
        if(maze[player.y+1][player.x] != '+'){
            maze[player.y][player.x] = ' ';
            if(maze[player.y+1][player.x] == '@'){
                hp -= 20;
            }
            player.y++;
        }
        break;
            case KEY_RIGHT :
        if(maze[player.y][player.x+1] != '+'){
            maze[player.y][player.x] = ' ';
            if(maze[player.y][player.x+1] == '@'){
                hp -= 20;
            }
            player.x++;
        }
        break;
            case 'q' :
                exit(0);
                break;
        }

       // int x = enemy1.x;
        //int y = enemy1.y;
        bool once1 = true ;
        bool once2 = true ;
        bool once3 = true ;
        bool once4 = true ;
        bool once5 = true ;
        bool once6 = true ;
        bool once7 = true ;
        bool once8 = true ;
        bool once9 = true ;
        bool once10 = true ;


        for(int i=0;i<HEIGHT;  i++){
            for(int j=0; j<WIDTH; j++){
                maze[i][j] = MoveEnemy(enemy1, maze, i, j, prevmove1, once1);
                maze[i][j] = MoveEnemy(enemy2, maze, i, j, prevmove2, once2);
                maze[i][j] = MoveEnemy(enemy3, maze, i, j, prevmove3, once3);
                maze[i][j] = MoveEnemy(enemy4, maze, i, j, prevmove4, once4);
                maze[i][j] = MoveEnemy(enemy5, maze, i, j, prevmove5, once5);
                maze[i][j] = MoveEnemy(enemy6, maze, i, j, prevmove6, once6);
                maze[i][j] = MoveEnemy(enemy7, maze, i, j, prevmove7, once7);
                maze[i][j] = MoveEnemy(enemy8, maze, i, j, prevmove8, once8);
                maze[i][j] = MoveEnemy(enemy9, maze, i, j, prevmove9, once9);
                maze[i][j] = MoveEnemy(enemy10, maze, i, j, prevmove10, once10);

            }
        }
        //}
   // }
//}
if(player.x==enemy1.x && player.y==enemy1.y){
        hp-=30;
}
if(player.x==enemy2.x && player.y==enemy2.y){
        hp-=30;
}
if(player.x==enemy3.x && player.y==enemy3.y){
        hp-=30;
}
if(player.x==enemy4.x && player.y==enemy4.y){
        hp-=30;
}
if(player.x==enemy5.x && player.y==enemy5.y){
        hp-=30;
}
if(player.x==enemy6.x && player.y==enemy6.y){
        hp-=30;
}
if(player.x==enemy7.x && player.y==enemy7.y){
        hp-=30;
}
if(player.x==enemy8.x && player.y==enemy8.y){
        hp-=30;
}
if(player.x==enemy9.x && player.y==enemy9.y){
        hp-=30;
if(player.x==enemy10.x && player.y==enemy10.y){
        hp-=30;
}

if(hp<=0){
    cout<<endl<<endl<<"A LOSER IS YOU!"<<endl<<endl;
    cout<<"This game is programmed by 3 students of AIUB, CSE department. they are, "<<endl<<"1 : M.E.JAKAREYA"<<endl<<"2 : MD.TANVEER ANJUM TOWSIF"<<endl<<"3 : S.M. FAHIM SHAHRIAR"<<endl;
    system("PAUSE");
    hasntWon=false;
}
if(player.x==WIDTH-1){
    cout<<endl<<endl<<"A WINER IS YOU!"<<endl<<endl;
    cout<<"This game is programmed by 3 students of AIUB, CSE department. they are, "<<endl<<"1 : M.E.JAKAREYA"<<endl<<"2 : MD.TANVEER ANJUM TOWSIF"<<endl<<"3 : S.M. FAHIM SHAHRIAR"<<endl;
    system("PAUSE");
    hasntWon=false;

}
 system("CLS");
 }


 break;

}

} }}





