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

COORDINATE sharkMoveDictionary[64][3];

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
  };

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
  };

  int curFishSize = fishes.size();
  
  for (int i = 0; i < curFishSize; i++) {
    int tryCnt = 0;
    int curDir = fishes[i].dir;

    if (!fishes[i].alive) continue;

    for(; !isAbleToMoveFish({fishes[i].location, curDir, fishes[i].alive}) && tryCnt < 8; curDir = (curDir - 1 + 8) % 8, tryCnt++);
    
    if (tryCnt == 8) continue;

    cout << curDir << '\n';

    int x = fishes[i].location.x;
    int y = fishes[i].location.y;
    int dir = curDir;
    fishes[i].dir = dir;

    int dx = direction[dir].x;
    int dy = direction[dir].y;

    int nx = x + dx;
    int ny = y + dy;

    board[x][y].fishNum--;
    board[nx][ny].fishNum++;

    fishes[i].alive = false;

    fishes.push_back({{nx, ny}, dir, true});
  }
}

int getProperSharkDictionaryIndex() {
  int maxIdx = 0, max = -1;

  for (int dicIdx = 0; dicIdx < 64; dicIdx++) {
    COORDINATE direction[3] = {
      sharkMoveDictionary[dicIdx][0],
      sharkMoveDictionary[dicIdx][1],
      sharkMoveDictionary[dicIdx][2],
    };

    COORDINATE tmpShark = shark;

    bool unable = false;
    int sum = 0;
    for (int dir = 0; dir < 3; dir++) {
      int dx = direction[dir].x;
      int dy = direction[dir].y;

      tmpShark.x += dx;
      tmpShark.y += dy;

      if (tmpShark.x <= 0 || tmpShark.x > 4 || tmpShark.y <= 0 || tmpShark.y > 4) {
        unable = true;
        break;
      }

      for (int i = 0; i < fishes.size(); i++) {
        if (fishes[i].alive && fishes[i].location.x == tmpShark.x && fishes[i].location.y == tmpShark.y) {
          sum++;
        }
      }
    }

    if (!unable) {
      if (max < sum) {
        max = sum;
        maxIdx = dicIdx;
      }
    }
  }

  return maxIdx;
}

void moveSharkByDictionaryIndex(int dicIdx) {
  COORDINATE direction[3] = {
      sharkMoveDictionary[dicIdx][0],
      sharkMoveDictionary[dicIdx][1],
      sharkMoveDictionary[dicIdx][2],
    };

  for (int dir = 0; dir < 3; dir++) {
    int dx = direction[dir].x;
    int dy = direction[dir].y;

    shark.x += dx;
    shark.y += dy;

    board[shark.x][shark.y].fishNum = 0;
    board[shark.x][shark.y].smell = 2;

    for (int i = 0; i < fishes.size(); i++) {
      if (fishes[i].alive && fishes[i].location.x == shark.x && fishes[i].location.y == shark.y) {
        fishes[i].alive = false;
      }
    }
  }
}

void moveShark() {
  int properSharkDictionaryIndex = getProperSharkDictionaryIndex();

  moveSharkByDictionaryIndex(properSharkDictionaryIndex);
}

void removeSmell() {
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      if (board[i][j].smell > 0) board[i][j].smell--;
    }
  }
}

void setSharkMoveDictionary() {
  int cnt = 0;

  COORDINATE direction[4] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        sharkMoveDictionary[cnt][0] = direction[i];
        sharkMoveDictionary[cnt][1] = direction[j];
        sharkMoveDictionary[cnt][2] = direction[k];
        cnt++;
      }
    }
  }
}

int getTotalFishCount() {
  int cnt = 0;

  for (int i = 0; i < fishes.size(); i++) {
    if (fishes[i].alive) cnt++;
  }

  return cnt;
}

void printBoard() {
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      cout << board[i][j].fishNum << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

void solve() {
  setSharkMoveDictionary();

  for (int i = 0; i < magicNum; i++) {
    // for duplication
    vector<FISH> tmpFishes;

    // make replica
    for (int i = 0; i < fishes.size(); i++) {
      if (fishes[i].alive) tmpFishes.push_back(fishes[i]);
    }

    moveFishes();

    printBoard();

    moveShark();

    printBoard();

    removeSmell();

    // put replica
    for (int i = 0; i < tmpFishes.size(); i++) {
      fishes.push_back(tmpFishes[i]);
      board[tmpFishes[i].location.x][tmpFishes[i].location.y].fishNum++;
    }

    printBoard();
  }

  cout << getTotalFishCount() << '\n';
}

int run() {
  cin >> fishNum >> magicNum;

  for (int i = 0; i < fishNum; i++) {
    FISH tmpFish;
    cin >> tmpFish.location.x >> tmpFish.location.y >> tmpFish.dir;
    fishes.push_back({tmpFish.location, tmpFish.dir-1, true});
    board[tmpFish.location.x][tmpFish.location.y].fishNum++;
  }

  cin >> shark.x >> shark.y;

  printBoard();

  solve();

  return 0;
}