#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;
enum eDir{STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3,
   RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cBall{

private:
  int x, y;
  int originalX, originalY;
  eDir direction;
public:
  cBall(int posX, int posY){
    originalX = posX;
    originalY = posY;
    x = posX, y = posY;
    direction = STOP;
  }

  void reset(){
    x = originalX, y = originalY;
    direction = STOP;
  }
  void changeDirection(eDir d){
    direction = d;
  }
  void randomDir(){
    direction = (eDir) (rand()% 6 +1);
  }
  inline int getX() {return x;}
  inline int getY() {return y;}
  inline eDir getDirection() {return direction;}
  void move(){
    switch(direction){
      case STOP:
        break;
      case LEFT:
        x--;
        break;
      case UPLEFT:
        x--;
        y--;
        break;
      case DOWNLEFT:
        x--;
        y++;
        break;
      case RIGHT:
        x++;
        break;
      case UPRIGHT:
        x++;
        y--;
        break;
      case DOWNRIGHT:
        x++;
        y++;
        break;
      default:
        break;
    }
  }

  friend ostream & operator << (ostream & o, cBall c){
    o << "Ball [" << c.x << "," << c.y <<"][" << c.direction << "]";
    return o;
  }
};

class cPaddle{
private:
  int x, y;
  int originalX, originalY;
public:
  cPaddle(){
    x = y = 0;
  }

  cPaddle(int posX, int posY) : cPaddle() {
    originalX = posX;
    originalY = posY;
    x = posX;
    y = posY;
  }
  inline void reset() { x = originalX; y = originalY;}
  inline int getX() {return x;}
  inline int getY() {return y;}
  inline void moveUp() {y--;}
  inline void moveDown() {y++;}

  friend ostream & operator << (ostream & o, cPaddle c){
    o << "Paddle [" << c.x << "," << c.y << "]";
    return o;
  }
};

class cGameManager{
private:
  int width, height;
  int score1, score2;
  char up1, down1, up2, down2;
  bool quit;
  cBall * ball;
  cPaddle * player1;
  cPaddle * player2;

public:
  cGameManager(int w, int h){
    srand(time(0));
    quit = false;
    up1 = 'w'; up2 = 'o';
    down1 = 's'; down2 = 'l';
    score1 = score2 = 0;
    width = w; height = h;
    ball = new cBall(w/2, h/2);
    player1 = new cPaddle(1, h/2 - 3);
    player2 = new cPaddle(w-2, h/2 -3);
  }
  ~cGameManager(){
    delete ball, player1, player2;
  }
  void scored(cPaddle *player){
    if (player == player1){
      score1++;
    }
    else if (player == player2){
      score2++;
    }
    ball->reset();
    player1->reset();
    player2->reset();
  }

  void Draw(){
    system("cls");
    for (int i = 0; i< width + 2; i++){
      cout << "\xB2";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width + 1; j++) {
        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player2X = player2->getX();
        int player1Y = player1->getY();
        int player2Y = player2->getY();

        if (j == 0 || j == width)
          cout << "\xB2";

        //ball
        if (ballX == j && ballY == i)
          cout << "O";
        //player 1
        else if (player1X == j && (player1Y == i || player1Y + 1 == i ||
                                    player1Y + 2 == i || player1Y + 3 == i))
          cout << "\xB2";
          //player 1
        else if (player2X == j && (player2Y == i || player2Y + 1 == i ||
                                    player2Y + 2 == i || player2Y + 3 == i))
          cout << "\xB2";
        else
          cout << " ";
      }
      cout << endl;
    }
    for (int i = 0; i < width + 2; i ++)
      cout << "\xB2";
    cout << endl;

    cout << "P1 Score: " << score1 << endl << "P2 Score: " << score2 << endl;
  }

  void Input(){
    ball->move();

    int ballX = ball->getX();
    int ballY = ball->getY();
    int player1X = player1->getX();
    int player2X = player2->getX();
    int player1Y = player1->getY();
    int player2Y = player2->getY();

    if (_kbhit()){
      char curr = _getch();
      if (curr == up1){
        if(player1Y > 0)
          player1->moveUp();
      }
      if (curr == up2){
        if (player2Y > 0)
          player2->moveUp();
      }
      if (curr == down1) {
        if(player1Y + 4 < height)
          player1->moveDown();
      }
      if (curr == down2) {
        if (player2Y + 4 < height)
          player2->moveDown();
      }
      if (curr == 'q' || curr == 'p'){
        quit = true;
      }
    }
  }

  void Logic(){
    int ballX = ball->getX();
    int ballY = ball->getY();
    int player1X = player1->getX();
    int player2X = player2->getX();
    int player1Y = player1->getY();
    int player2Y = player2->getY();

    //left paddle
    for (int i = 0; i < 4; i++)
      if (ballX == player1X + 1)
        if (ballX == player1X + i)
          ball -> changeDirection((eDir)((rand()%3) + 4));

    //left paddle
    for (int i = 0; i < 4; i++)
      if (ballY == player1Y + 1)
        if (ballY == player1Y + i)
          ball -> changeDirection((eDir)((rand()%3) + 1));

    //bottom wall
    if (ballY == height - 1)
      ball -> changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
      
  }

  void run(){
    while (!quit){
      Draw();
      Input();
      Logic();
    }
  }
};
int main(){
  cGameManager c(40,20);
  c.run();
  return 0;
  // cBall c(0,0);
  // cout <<c << endl;
  // c.randomDir();
  // cout << c << endl;
  // c.move();
  // cout << c << endl;
  // c.randomDir();
  // c.move();
  // cout << c << endl;
  // return 0;
}
