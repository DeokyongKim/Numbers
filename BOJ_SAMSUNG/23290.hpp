#include <iostream>
#include <vector>

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

typedef struct _FISH {
  COORDINATE location;
  int dir;
  bool alive;
} FISH;

typedef struct _BOARD {
  int fishNum;
  int smell;
} BOARD;

int fishNum, magicNum;

BOARD board[5][5];

vector<FISH> fishes;

COORDINATE shark;

bool isAbleToMoveFish(FISH fish) {
  int dir = fish.dir;
  int x = fish.location.x;
  int y = fish.location.y;

  COORDINATE direction[8] = {
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
  }

  int dx = direction[dir].x;
  int dy = direction[dir].y;

  int nx = x + dx;
  int ny = y + dy;

  if (nx <= 0 || nx > 4 || ny <= 0 || ny > 4) return false;
  if (shark.x == nx && shark.y == ny) return false;
  if (board[nx][ny].smell > 0) return false;

  return true;
}

void moveFishes() {
  COORDINATE direction[8] = {
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
  }
  
  for (int i = 0; i < fishes.size(); i++) {
    int tryCnt = 0;

    for(; !isAbleToMoveFish(fishes[i]) && tryCnt < 8; fishes[i].dir = (fishes[i].dir - 1 + 8) % 8, tryCnt++);

    if (tryCnt == 8) continue;

    int x = fishes[i].location.x;
    int y = fishes[i].location.y;
    int dir = fishes[i].dir;

    int dx = direction[dir].x;
    int dy = direction[dir].y;

    int nx = x + dx;
    int ny = y + dy;

    board[x][y].fishNum--;
    board[nx][ny].fishNum++;
    board[nx][ny].smell += 2;

    fishes.push_back({{nx, ny}, dir, true});
  }
}

void moveShark() {

}

void removeSmell() {
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      if (board[i][j].smell > 0) board[i][j].smell--;
    }
  }
}

void solve() {
  for (int i = 0; i < magicNum; i++) {
    // for duplication
    vector<FISH> tmpFishes;

    // make replica
    for (int i = 0; i < fishes.size(); i++) {
      if (fishes[i].alive) tmpFishes.push_back(fishes[i]);
    }

    moveFishes();

    moveShark();

    removeSmell();

    // put replica
    for (int i = 0; i < tmpFishes.size(); i++) {
      fishes.push_back(tmpFishes[i]);
      board[tmpFishes[i].location.x][tmpFishes[i].location.y].fishNum++;
      board[tmpFishes[i].location.x][tmpFishes[i].location.y].smell += 2;
    }
  }
}

int run() {
  cin >> fishNum >> magicNum;

  for (int i = 0; i < fishNum; i++) {
    FISH tmpFish;
    cin >> tmpFish.location.x >> tmpFish.location.y >> tmpFish.dir;
    fishes.push_back({tmpFish.location, tmpFish.dir-1, true});
    board[tmpFish.location.x][tmpFish.location.y].fishNum++;
    board[tmpFish.location.x][tmpFish.location.y].smell = 2;
  }

  cin >> shark.x >> shark.y;

  solve();
}