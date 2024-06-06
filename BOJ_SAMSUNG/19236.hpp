#include <iostream>

using namespace std;

typedef struct _DIRECTION {
  int first;
  int second;
} DIRECTION;

typedef struct _FISH {
  int x;
  int y;
  int dir;
} FISH;

DIRECTION direction[8] = {
  {-1, 0},
  {-1, -1},
  {0, -1},
  {1, -1},
  {1, 0},
  {1, 1},
  {0, 1},
  {-1, 1},
};

int isDead[20] = {0, };

FISH fishes[20] = {0, };

int board[5][5] = {0, };

int ans = 0;

void solve(int sharkX, int sharkY, int sharkDir, int sum, int SEA[5][5], FISH FISHLIST[20]) {
  int nx = sharkX + direction[sharkDir].first;
  int ny = sharkY + direction[sharkDir].second;

  // cout << "X: " << sharkX << " Y: " << sharkY << " DIR: " << sharkDir << " SUM: " << sum << '\n';

  if (nx >= 4 || nx < 0 || ny >= 4 || ny < 0) {
      // cout << "SUM: " << sum << '\n';
    if (sum > ans) {
      ans = sum;
    }
    return;
  }
  
  // copy sea
  int sea[5][5] = {0, };
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      sea[i][j] = SEA[i][j];
    }
  }

  // copy fish
  FISH fishList[20] = {0, };
  for (int i = 1; i <= 16; i++) {
    fishList[i].x = FISHLIST[i].x;
    fishList[i].y = FISHLIST[i].y;
    fishList[i].dir = FISHLIST[i].dir;
  }

  // move fishes
  for (int i = 1; i <= 16; i++) {
    if (isDead[i]) continue;

    // make direction
    int nfx;
    int nfy;

    int tryNum = 0;
    while(true) {
      if (tryNum == 8) break;

      nfx = fishList[i].x + direction[fishList[i].dir].first;
      nfy = fishList[i].y + direction[fishList[i].dir].second;

      if (nfx >= 4 || nfx < 0 || nfy >= 4 || nfy < 0 || sea[nfx][nfy] == -1) {
        if (fishList[i].dir == 7) fishList[i].dir = 0;
        else fishList[i].dir++;
      } else {
        break;
      }

      tryNum++;
    }

    // if fish can't move
    if (tryNum == 8) continue;

    int fx = fishList[i].x;
    int fy = fishList[i].y;

    if (sea[nfx][nfy] > 0) {
      int nextFishId = sea[nfx][nfy];
      int curFishId = sea[fx][fy];

      fishList[curFishId].x = nfx;
      fishList[curFishId].y = nfy;
      fishList[nextFishId].x = fx;
      fishList[nextFishId].y = fy;

      sea[nfx][nfy] = curFishId;
      sea[fx][fy] = nextFishId;
    } else if (sea[nfx][nfy] == 0) {
      fishList[i].x = nfx;
      fishList[i].y = nfy;

      sea[nfx][nfy] = i;
      sea[fx][fy] = 0;
    }
  }

  // cout << "AFTER FISH: \n";
  // for (int i = 0; i < 4; i++) {
  //   for (int j = 0; j < 4; j++) {
  //     cout << sea[i][j] << '\t';
  //   }
  //   cout << '\n';
  // }
  // cout << '\n';

  bool moved = false;
  // move shark
  int gain = 1;
  while (true) {
    int nextX = sharkX + gain * direction[sharkDir].first;
    int nextY = sharkY + gain * direction[sharkDir].second;

    gain++;
    if (gain > 4) break;

    if (nextX >= 4 || nextX < 0 || nextY >= 4 || nextY < 0 || sea[nextX][nextY] == 0) continue;

    if (sea[nextX][nextY] > 0) {
      sea[sharkX][sharkY] = 0;
      
      int id = sea[nextX][nextY];

      int nextSharkDir = fishList[id].dir;

      moved = true;

      isDead[id] = 1;
      sea[nextX][nextY] = -1;
      // cout << "AFTER SHARK: \n";
      // for (int i = 0; i < 4; i++) {
      //   for (int j = 0; j < 4; j++) {
      //     cout << sea[i][j] << '\t';
      //   }
      //   cout << '\n';
      // }
      // cout << '\n';
      solve(nextX, nextY, nextSharkDir, sum + id, sea, fishList);
      isDead[id] = 0;
      sea[nextX][nextY] = id;
      
      sea[sharkX][sharkY] = -1;
    }
  }

  if (!moved) {
    if (sum > ans) {
      ans = sum;
    }
    return;
  }
}

int run() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int size, dir;
      cin >> size >> dir;
      fishes[size].dir = dir - 1;
      fishes[size].x = i;
      fishes[size].y = j;
      board[i][j] = size;
    }
  }

  // shark to 0,0
  isDead[board[0][0]] = 1;
  int tmpSum = board[0][0];
  board[0][0] = -1; // -1 means shark

  solve(0, 0, fishes[tmpSum].dir, tmpSum, board, fishes);

  cout << ans << '\n';

  return 0;
}