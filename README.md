C++Programming 3주차 과제 2번 - SnakeGame

[ 실행 방법 ]
1. cmd 또는 git bash를 실행시킨다.
2. 원하는 디렉터리로 이동한다.
3. 그 다음 아래와 같은 순서로 명령어를 수행한다.
4. git clone https://github.com/belight2/snakeGame snakegame
5. cd ./snakegame
6. g++ -Werror -c -std=c++11 console.cpp
7. g++ -Werror -c main.cpp game.cpp display.cpp util.cpp
8. g++ -o main.exe console.o main.o game.o display.o util.o
9. .\main.exe

main.cpp : 메인 함수
util.cpp : 게임 진행에 필요한 정보와 함수 모음
display.cpp : 게임 정보를 화면에 출력하는 함수 모음
game.cpp : 게임 수행 쿼리 관리

< MOVE_DELAY >
game.cpp 내에 전처리되어있음
1 ~ 60으로 값을 변경해 화면 출력 갱신 속도를 조절할 수 있음

< BOARD_SIZE >
display.cpp 내에 전처리되어있음
4 ~ 20으로 값을 변경해 게임 보드판의 크기를 조절할 수 있음
