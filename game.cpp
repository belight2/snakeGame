#include "console.h"
#include <ctime>
#define MOVE_DELAY 15
using namespace std;
void fillInitInfo(int *snakePos, int &scroe, int &snakeLength, int &dir);
void drawBoard();
void drawScore(int score);
void drawSnake(int (*snakePos)[2], int snakeLength);
void handleInput(int &dir, int snakeLength);
void moveSnake(int (*snakePos)[2], int &snakeLength, int dir);
bool getIsExistApple();
void createApple();
void drawApple();
int isGameOver(int *snakeHeadPos, int snakeLength);
void drawGameOverWindow(int flag);
bool gameHandleInput();
int score = 0;
int snakeLength = 1;
int snakePos[405][2];
int dir = 0;
// 게임 진행을 위한 쿼리 수행
void playGame(){
  console::init();
  fillInitInfo(snakePos[0], score, snakeLength, dir);
  int flag{};
  console::clear();
  drawBoard();
  while(true){
    drawScore(score);
    if(!getIsExistApple()) createApple();
    moveSnake(snakePos, snakeLength, dir);
    drawSnake(snakePos, snakeLength);
    drawApple();
    handleInput(dir, snakeLength);
    if(flag = isGameOver(snakePos[0], snakeLength), flag) break;
    for(int i = 0; i < MOVE_DELAY; i++) console::wait();
  }
  while(true){
    drawGameOverWindow(flag);
    if(gameHandleInput()) break;
    for(int i = 0; i < MOVE_DELAY; i++) console::wait();
  }
}
// 점수 정보를 반환하는 함수
int& getScore(){ return score; } 