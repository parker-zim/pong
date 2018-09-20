#include <iostream>

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
    direction = stop;
  }
  void changeDirection(eDir d){
    direction = d;
  }
  void randomDir(){
    direction = (eDir) (rand()% 6 +1);
  }
  inline int getX() {return x};
  inline int getY() {return y};
  inline eDir getDirection() {retrun direction};
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
}


int main(){

  return 0;
}
