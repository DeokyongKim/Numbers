// 1H 19M

#include <iostream>
#include <queue>

#define MAP_SIZE 5
#define PART_SIZE 3

using namespace std;

typedef struct _COORDINATE {
  int x; 
  int y;
} COORDINATE;

int maxTurn, candidateNum, board[10][10], candidates[310];

void printArray(int array[10][10]) {
  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      cout << array[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

bool isOutOfBound(int x, int y) {
  if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE) return true;
  return false;
}

void getInput() {
  cin >> maxTurn >> candidateNum;

  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      cin >> board[i][j];
    }
  }

  for (int i = 0; i < candidateNum; i++) {
    cin >> candidates[i];
  }
}

int visited[10][10] = {0, };

void clearVisited() {
  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      visited[i][j] = 0;
    }
  }
}

int bfs(int array[10][10], int x, int y, bool erase) {
  int score = 0;

  int variety = array[x][y];

  COORDINATE directions[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
  };

  queue<COORDINATE> q;

  visited[x][y] = 1;
  q.push({x, y});
  score++;

  int mapping[10][10] = {0, };

  while(!q.empty()) {
    int curX = q.front().x;
    int curY = q.front().y;
    mapping[curX][curY] = 1;
    q.pop();

    for (int i = 0; i < 4; i++) {
      int dx = directions[i].x;
      int dy = directions[i].y;

      int nx = curX + dx;
      int ny = curY + dy;

      if (!isOutOfBound(nx, ny) && !visited[nx][ny] && array[nx][ny] == variety) {
        visited[nx][ny] = 1;
        q.push({nx, ny});
        score++;
      }
    }
  }

  // cout << "BFS SCORE: " << score <<'\n';

  if (score < 3) {
    return 0;
  } else {
    if (erase) {
      for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
          if (mapping[i][j]) array[i][j] = 0;
        }
      }
    }

    return score;
  }
}

int getRuinValue(int array[10][10], bool erase) {
  int score = 0;

  clearVisited();
  
  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      if (array[i][j] == 0) {
        visited[i][j] = 1;
        continue;
      }
      if (!visited[i][j]) {
        score += bfs(array, i, j, erase);
      }
    }
  }

  return score;
}

void rotateArray(int array[10][10], COORDINATE center) {
  int startX = center.x-1, endX = center.x+1;
  int startY = center.y-1, endY = center.y+1;

  int tmpArray[10][10];

  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      tmpArray[i][j] = array[i][j];
    }
  }

  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      tmpArray[i + startX][j + startY] = array[PART_SIZE-1-j + startX][i + startY];
    }
  }

  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      array[i][j] = tmpArray[i][j];
    }
  }
}

void rotateArrayByRotateType(int array[10][10], COORDINATE center, int rotateType) {
  for (int i = 0; i <= rotateType; i++) {
    rotateArray(array, center);
  }
}

int getScoreAfterRotation(int x, int y, int rotationType) {
  int tmpBoard[10][10];

  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      tmpBoard[i][j] = board[i][j];
    }
  }

  rotateArrayByRotateType(tmpBoard, {x, y}, rotationType);

  return getRuinValue(tmpBoard, false);
}

typedef struct _MaxCenterAndRotateType {
  COORDINATE maxCenter;
  int rotateType;
} MaxCenterAndRotateType;

MaxCenterAndRotateType getMaxCenterAndRotateType() {
  COORDINATE maxCenter;
  int maxScore = -1; 
  int rotateType = 0;

  for (int rotationType = 0; rotationType < 3; rotationType++) {
    for (int j = 1; j < MAP_SIZE-1; j++) {
      for (int i = 1; i < MAP_SIZE-1; i++) {
        int score = getScoreAfterRotation(i, j, rotationType);

        if (score > maxScore) {
          maxScore = score;
          maxCenter = {i, j};
          rotateType = rotationType;
        }
      }
    }
  }

  return {maxCenter, rotateType};
}

void explore() {
  MaxCenterAndRotateType maxCenterAndRotateType = getMaxCenterAndRotateType();
  
  COORDINATE center = maxCenterAndRotateType.maxCenter;
  int rotateType = maxCenterAndRotateType.rotateType;

  rotateArrayByRotateType(board, center, rotateType);
}

int refillIndex = 0;
void refillRuin() {
  if (refillIndex == candidateNum) return;

  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = MAP_SIZE-1; j >= 0; j--) {
      if (board[j][i] == 0 && refillIndex < candidateNum) {
        board[j][i] = candidates[refillIndex++];
      } 
    }
  }
}

int getTotalRuinValue() {
  int score = 0;

  while(true) {
    // cout << "VALUATING:\n";
    int partScore = getRuinValue(board, true);
    // printArray(board);

    if (partScore == 0) break;

    score += partScore;

    refillRuin();
    // cout << "AFTER REFILL:\n";
    // printArray(board);
  }

  return score;
}

void solve() {
  for (int turn = 0; turn < maxTurn; turn++) {    
    explore();

    // cout << "AFTER EXPLORE: \n";
    // printArray(board);

    int score = getTotalRuinValue();

    if (score == 0) break; 

    cout << score << ' ';
  }
}

int run() {
  getInput();

  solve();

  return 0;
}