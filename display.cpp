#include "console.h"
#include <string>
#define BOARD_SIZE 20
#define WALL_VERTICAL_STRING "┃"
#define WALL_HORIZONTAL_STRING "━"
#define WALL_RIGHT_TOP_STRING "┓"
#define WALL_LEFT_TOP_STRING "┏"
#define WALL_RIGHT_BOTTOM_STRING "┛"
#define WALL_LEFT_BOTTOM_STRING "┗"
#define SNAKE_STRING "■"
#define SNAKE_BODY_STRING "■"
#define APPLE_STRING "●"
using namespace std;
bool getIsExistApple();
int getApplePosX();
int getApplePosY();
const string SCORE_STRING = "score : ";
const string GAME_LOSE_STRING = "YOU LOSE!";
const string GAME_WIN_STRING = "YOU WIN!";
const string GAME_RESTART_STRING = "Try again? (Enter)";
// 게임 보드 판의 경계선을 그려주는 함수
void drawBoard(){
  for(int i = 0; i < BOARD_SIZE-1; i++){
    console::draw(0, i, WALL_VERTICAL_STRING);
    console::draw(i, 0, WALL_HORIZONTAL_STRING);
    console::draw(BOARD_SIZE-1, i, WALL_VERTICAL_STRING);
    console::draw(i, BOARD_SIZE-1, WALL_HORIZONTAL_STRING);
  }
  console::draw(0, 0, WALL_LEFT_TOP_STRING);
  console::draw(0, BOARD_SIZE-1, WALL_LEFT_BOTTOM_STRING);
  console::draw(BOARD_SIZE-1, 0, WALL_RIGHT_TOP_STRING);
  console::draw(BOARD_SIZE-1, BOARD_SIZE-1, WALL_RIGHT_BOTTOM_STRING);
}
// 현재 점수에 대한 정보를 그려주는 함수
void drawScore(int score){
  int SCORE_STRING_POS = (BOARD_SIZE - (SCORE_STRING+to_string(score)).size()) / 2;
  console::draw(SCORE_STRING_POS, BOARD_SIZE, SCORE_STRING+to_string(score));
}
// 뱀의 위치 정보를 바탕으로 보드판에 뱀을 그리는 함수
void drawSnake(int (*snakePos)[2], int snakeLength){
  for(int i = 1; i < BOARD_SIZE-1; i++) for(int j = 1; j < BOARD_SIZE-1; j++) console::draw(i, j, " ");
  console::draw(snakePos[0][0], snakePos[0][1], SNAKE_STRING);
  for(int i = 1; i < snakeLength; i++) console::draw(snakePos[i][0], snakePos[i][1], SNAKE_BODY_STRING);
}
// 사과의 위치 정보를 바탕으로 보드판에 사과를 그려주는 함수
void drawApple(){
  if(!getIsExistApple()) return;
  console::draw(getApplePosX(), getApplePosY(), APPLE_STRING);
}
// 게임이 어떤 상태로 종료되었는지 안내문을 그려주는 함수
void drawGameOverWindow(int flag){
  string str = flag == 1 ? GAME_WIN_STRING : GAME_LOSE_STRING;
  int str_pos = (BOARD_SIZE - str.size()) / 2;
  int restart_pos = (BOARD_SIZE - string(GAME_RESTART_STRING).size()) / 2;
  console::draw(str_pos, (BOARD_SIZE - 2) / 2, str);
  console::draw(restart_pos, (BOARD_SIZE-2) / 2 + 1, GAME_RESTART_STRING);
}
// 보드판의 크기를 반환하는 함수
int GET_BOARD_SIZE(){ return BOARD_SIZE; }