#include "console.h"
#include <cstdlib>
#include <ctime>
using namespace std;
int GET_BOARD_SIZE();
int& getScore();
/* RIGHT, BOTTOM, LEFT, TOP
   worm의 이동 방향에 따른 변화값 */
const int dx[4] = { 1, 0, -1, 0 };
const int dy[4] = { 0, 1, 0, -1 };
// 게임 보드판의 크기
const int BOARD_SIZE = GET_BOARD_SIZE();
/* snake의 위치 정보
   isSnake[x][y] : (x, y) 위치에 snake의 몸통이나 머리가 위치하는가
   true = snake가 있음, false : snake가 없음 */
bool isSnakeArea[40][40];
// 현재 보드판 내에 사과가 존재하는지 여부
bool isExistApple = 0;
// 사과의 위치 정보
int ApplePos[2];
// snake의 머리가 몸통가 부딪혔는지 여부
bool collisionFlag = 0;
// 게임 시작 전 필요한 정보를 초기화하는 함수
void fillInitInfo(int *snakePos, int &score, int &snakeLength, int &dir){
  snakePos[0] = (BOARD_SIZE-2) / 2 ;
  snakePos[1] = (BOARD_SIZE-2) / 2 ;
  isSnakeArea[snakePos[0]][snakePos[1]] = 1;
  score = 0; snakeLength = 1; dir = 0;
  for(int i = 0; i < BOARD_SIZE; i++) for(int j = 0; j < BOARD_SIZE; j++) isSnakeArea[i][j] = 0;
}
// 키보드 입력에 따른 방향 전환
void handleInput(int &dir, int snakeLength){
  if(console::key(console::K_LEFT) && ( dir != 0 || snakeLength == 1 )) dir = 2;
  if(console::key(console::K_DOWN) && (dir != 3 || snakeLength == 1)) dir = 1;
  if(console::key(console::K_RIGHT) && (dir != 2 || snakeLength == 1)) dir = 0;
  if(console::key(console::K_UP)&& (dir != 1 || snakeLength == 1)) dir = 3;
  if(console::key(console::K_ESC)) exit(1);
}
// 게임 종료 후 재시작여부와 종료 여부를 확인하는 함수 
bool gameHandleInput(){
  if(console::key(console::K_ESC)) exit(1);
  if(console::key(console::K_ENTER)) return 1;
  return 0;
}
// snake의 머리가 사과 위치에 도달했는지 확인하는 함수
bool isEatApple(int nx, int ny){
  if(nx != ApplePos[0] || ny != ApplePos[1]) return 0;
  getScore() += 10;
  isExistApple = 0;
  return 1;
}
/*현재 위치가 뱀이 위치한 곳인지 확인
 이동하려고 하는 위치에 뱀이 존재하는지 확인하는 함수 */
bool isCollideSnakeBody(int x, int y){
  return isSnakeArea[x][y];
}
/* 뱀이 이동해야할 위치 정보를 기반으로
   충돌여부, 사과를 먹었는지 여부를 확인하고,
   이를 바탕으로 뱀의 위치 정보를 갱신함 */
void moveSnake(int (*snakePos)[2], int &snakeLength, int dir){
  int nx = snakePos[0][0] + dx[dir];
  int ny = snakePos[0][1] + dy[dir];
  int ex = snakePos[snakeLength-1][0];
  int ey = snakePos[snakeLength-1][1];
  collisionFlag = isCollideSnakeBody(nx, ny);
  isSnakeArea[nx][ny] = 1;
  isEatApple(nx, ny) ? snakeLength++ : isSnakeArea[ex][ey] = 0;
  for(int i = snakeLength-2; i >= 0; i--){
    swap(snakePos[i+1][0], snakePos[i][0]);
    swap(snakePos[i+1][1], snakePos[i][1]);
  }
  snakePos[0][0] = nx;
  snakePos[0][1] = ny;
}
/* 사과가 보드판 내에 존재하지 않는다면 생성해주는 함수 */
void createApple(){
  if(isExistApple) return;
  isExistApple = 1;
  int rndarray[400];
  int idx = 0;
  for(int i = 1; i < BOARD_SIZE-1; i++){
    for(int j = 1; j < BOARD_SIZE-1; j++){
      if(isSnakeArea[i][j]) continue;
      rndarray[idx++] = i*100 + j;
    }
  }
  srand((unsigned int)time(NULL));
  int rnd_idx = rand() % idx;
  ApplePos[0] = rndarray[rnd_idx] / 100;
  ApplePos[1] = rndarray[rnd_idx] % 100; 
}
// 뱀의 머리가 보드판 밖으로 벗어났는지 여부를 확인하는 함수
bool checkOutOfRange(int *snakeHeadPos){
  int x = snakeHeadPos[0]; int y = snakeHeadPos[1];
  return x < 1 || x > BOARD_SIZE-2 || y < 1 || y > BOARD_SIZE-2;
}
/* 게임 종료 조건이 만족하는지 확인하고 그에 따른 상태값을 반환하는 함수
   0 : THE_GAME_IS_NOT_OVER
   1 : GAME_OVER_AND_WIN
   2 : GAME_OVER_AND_LOSE */
int isGameOver(int *snakeHeadPos, int snakeLength){
  if(checkOutOfRange(snakeHeadPos) || collisionFlag ) return 2;
  if(snakeLength == (BOARD_SIZE-2)*(BOARD_SIZE-2)) return 1;
  return 0;
}
// 사과의 x 좌표값 반환
int getApplePosX(){ return ApplePos[0]; }

// 사과의 y 좌표값 반환
int getApplePosY(){ return ApplePos[1]; }

// 사과의 존재 여부에 관한 값 반환
bool getIsExistApple(){ return isExistApple; }