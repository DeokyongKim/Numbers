#include <iostream>
#include <vector>

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int fishNum, magicNum;

vector<int> board[5][5];

COORDINATE sharkDirectionDictionary[70][3];

COORDINATE shark;

int level = 1;

int smell[5][5];

void setSharkDirectionDictionary() {
  int cnt = 0;

  COORDINATE direction[4] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1},
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        sharkDirectionDictionary[cnt][0] = direction[i];
        sharkDirectionDictionary[cnt][1] = direction[j];
        sharkDirectionDictionary[cnt][2] = direction[k];
      }
    }
  }
}

int getLeftFishNum() {
  int fishLeftCnt = 0;
  
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      fishLeftCnt += board[i][j].size();
    }
  }

  return fishLeftCnt;
}

int_least32_t getProperDirection(COORDINATE cur, int dir) {
  int cnt = 0;
  
  COORDINATE direction[8] = {
    {0, -1},
    {-1 ,-1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
  };

  while(true) {
    cnt++;

    if (cnt == 9) break;

    int nx = cur.x + direction[dir].x;
    int ny = cur.y + direction[dir].y;

    if (nx < 1 || nx > 4 || ny < 1 || ny > 4) {
      dir = (dir - 1 + 8) % 8;
      continue;
    }

    if (shark.x == nx && shark.y == ny) {
      dir = (dir - 1 + 8) % 8;
      continue;
    }

    if (smell[nx][ny] > 0) {
      dir = (dir - 1 + 8) % 8;
      continue;
    }

    return dir;
  }

  return -1;
}

void solve() {
  setSharkDirectionDictionary();

  COORDINATE fishDirection[8] = {
    {0, -1},
    {-1 ,-1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
  };

  for (int magicCnt = 0; magicCnt < magicNum; magicCnt++) {
    vector<int> tmpFishes[5][5];

    // move fishes
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        for (int k = 0; k < board[i][j].size(); k++) {          
          int properDirection = getProperDirection({i, j}, board[i][j][k]);
        
          if (properDirection == -1) {
            tmpFishes[i][j].push_back(board[i][j][k]);
          } else {
            int nx = i + fishDirection[properDirection].x;
            int ny = j + fishDirection[properDirection].y;

            tmpFishes[nx][ny].push_back(properDirection);
          }
        }
      }
    }

    // move shark
    int maxFish = 0, maxIdx = 0;

    for (int dicIdx = 0; dicIdx < 64; dicIdx++) {
      int partialSum = 0;
      COORDINATE tmpShark = {shark.x, shark.y};

      bool able = true;

      int visited[5][5] = {0, };

      for (int i = 0; i < 3; i++) {
        tmpShark.x += sharkDirectionDictionary[dicIdx][i].x;
        tmpShark.y += sharkDirectionDictionary[dicIdx][i].y;

        if (tmpShark.x < 1 || tmpShark.x > 4 || tmpShark.y < 1 || tmpShark.y > 4) {
          able = false;
          break;
        }

        if (!visited[tmpShark.x][tmpShark.y]) {
          partialSum += tmpFishes[tmpShark.x][tmpShark.y].size();

          visited[tmpShark.x][tmpShark.y] = 1;
        }
      }

      if (!able) {
        continue;
      } else {
        if (partialSum > maxFish) {
          maxFish = partialSum;
          maxIdx = dicIdx;
        }
      }
    }

    for (int i = 0; i < 3; i++) {
      shark.x += sharkDirectionDictionary[maxIdx][i].x;
      shark.y += sharkDirectionDictionary[maxIdx][i].y;

      if (tmpFishes[shark.x][shark.y].size() > 0) {
        smell[shark.x][shark.y] = level;
      }

      tmpFishes[shark.x][shark.y].clear();
    }

    // remove smell
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        if (smell[i][j] == level - 2) smell[i][j] = 0;
      }
    }

    // paste
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        for (int k = 0; k < tmpFishes[i][j].size(); k++) {
          board[i][j].push_back(tmpFishes[i][j][k]);
        }
      }
    }

    level++;
  }

  cout << getLeftFishNum() << '\n';
}

int run() {
  cin >> fishNum >> magicNum;

  for (int i = 0; i < fishNum; i++) {
    int fx, fy, fishDir;
    cin >> fx >> fy >> fishDir;

    board[fx][fy].push_back(fishDir-1);
  }

  cin >> shark.x >> shark.y;

  solve();
}