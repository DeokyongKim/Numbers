#include <iostream>

#define INF 0x7fffffff

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

typedef struct _SANTA {
  COORDINATE coordinate;
  int score = 0;
  bool alive = true;
  int fainting = 0;
} SANTA;

int n, turnNum, santaNum, rudolphPower, santaPower;

int board[55][55];

COORDINATE rudolph;

SANTA santas[40];

COORDINATE rudolphDirection[8] = {
  {-1, 0},
  {-1, 1},
  {0, 1},
  {1, 1},
  {1, 0},
  {1, -1},
  {0, -1},
  {-1, -1},
};

COORDINATE santaDirection[4] = {
  {-1, 0},
  {0, 1},
  {1, 0},
  {0, -1},
};

void printBoard() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == rudolph.x && j == rudolph.y) {
        cout << "R ";
      } else {
        cout << board[i][j] << ' ';
      }
    }
    cout << '\n';
  }
  cout << '\n';
}

bool isOutBoard(COORDINATE coordinate) {
  if (coordinate.x < 1 || coordinate.x > n || coordinate.y < 1 || coordinate.y > n) return true;
  return false;
}

void printSantasScore() {
  for (int i = 1; i <= santaNum; i++) {
    cout << santas[i].score << ' ';
  }
  cout << '\n';
}

bool isSantaAlive() {
  for (int i = 1; i <= santaNum; i++) {
    if (santas[i].alive) return true;
  }
  return false;
}

int getDistance(COORDINATE a, COORDINATE b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int getClosestSantaId() {
  int minIdx = 0, minDist = INF;

  for (int i = 1; i <= santaNum; i++) {
    if (!santas[i].alive) continue;

    int dist = getDistance(rudolph, santas[i].coordinate);

    if (minDist >= dist) {
      if (minDist == dist) {
        if (santas[minIdx].coordinate.x == santas[i].coordinate.x) {
          if (santas[minIdx].coordinate.y < santas[i].coordinate.y) {
            minIdx = i;
            minDist = dist;
          }
        } else if (santas[minIdx].coordinate.x < santas[i].coordinate.x) {
          minIdx = i;
          minDist = dist;
        }
      } else {
        minIdx = i;
        minDist = dist;
      }
    }
  }

  return minIdx;
}

int getClosestRudolphDirectionId(int santaId) {
  int minDist = getDistance(rudolph, santas[santaId].coordinate);
  
  int minIdx = -1;

  for (int i = 0; i < 8; i++) {
    int dx = rudolphDirection[i].x;
    int dy = rudolphDirection[i].y;

    int nx = rudolph.x + dx;
    int ny = rudolph.y + dy;

    if (isOutBoard({nx, ny})) continue;

    int dist = getDistance({nx, ny}, santas[santaId].coordinate);

    if (dist < minDist) {
      minIdx = i;
      minDist = dist;
    }
  }

  return minIdx;
}

void santaCrashSanta(int dirIdx, int crashSantaId) {
  int dx = rudolphDirection[dirIdx].x;
  int dy = rudolphDirection[dirIdx].y;

  for (int santaId = crashSantaId; santaId != 0; ) {
    int x = santas[santaId].coordinate.x;
    int y = santas[santaId].coordinate.y;

    int nextSantaId = board[x][y];

    board[x][y] = santaId;

    int nx = x + dx;
    int ny = y + dy;

    santas[nextSantaId].coordinate = {nx, ny};

    if (isOutBoard({nx, ny})) {
      santas[nextSantaId].alive = false;
      break;
    }

    santaId = nextSantaId;
  }
}

void rudolphCrashSanta(int dirIdx) {
  int santaId = board[rudolph.x][rudolph.y]; 
  
  int dx = rudolphDirection[dirIdx].x * rudolphPower;
  int dy = rudolphDirection[dirIdx].y * rudolphPower;

  int nx = santas[santaId].coordinate.x + dx;
  int ny = santas[santaId].coordinate.y + dy;

  board[santas[santaId].coordinate.x][santas[santaId].coordinate.y] = 0;
  
  santas[santaId].coordinate = {nx, ny};

  santas[santaId].fainting = 2;

  santas[santaId].score += rudolphPower;

  if (isOutBoard({nx, ny})) {
    santas[santaId].alive = false;
  } else if (board[nx][ny] > 0) {
    santaCrashSanta(dirIdx, santaId);
  } else {
    board[nx][ny] = santaId;
  }
}

void moveRudolph() {
  int closestSantaId = getClosestSantaId(); 
  // cout << closestSantaId << '\n';

  int closestRudolphDirectionId = getClosestRudolphDirectionId(closestSantaId);

  int dx = rudolphDirection[closestRudolphDirectionId].x;
  int dy = rudolphDirection[closestRudolphDirectionId].y;

  rudolph.x += dx;
  rudolph.y += dy;

  if (board[rudolph.x][rudolph.y] > 0) {
    rudolphCrashSanta(closestRudolphDirectionId);
  }
}

int getClosestSantaDirectionId(int id) {
  int minIdx = -1, minDist = getDistance(rudolph, santas[id].coordinate);

  int x = santas[id].coordinate.x;
  int y = santas[id].coordinate.y;

  for (int i = 0; i < 4; i++) {
    int dx = santaDirection[i].x;
    int dy = santaDirection[i].y;

    int nx = x + dx;
    int ny = y + dy;

    if (isOutBoard({nx, ny}) || board[nx][ny] > 0) continue;

    int dist = getDistance(rudolph, {nx, ny});

    if (dist < minDist) {
      minDist = dist;
      minIdx = i;
    }
  }

  return minIdx;
}

int getOppositeDirIdx(int dirIdx) {
  if (dirIdx == 0) return 2;
  if (dirIdx == 1) return 3;
  if (dirIdx == 2) return 0;
  if (dirIdx == 3) return 1;
}

int santaDirIdxToRudolphDirIdx(int dirIdx) {
  if (dirIdx == 0) return 0;
  if (dirIdx == 1) return 2;
  if (dirIdx == 2) return 4;
  if (dirIdx == 3) return 6;
}

void santaCrashRudolph(int dirIdx, int id) {
  int oppositeDirIdx = getOppositeDirIdx(dirIdx);

  int dx = santaDirection[oppositeDirIdx].x * santaPower;
  int dy = santaDirection[oppositeDirIdx].y * santaPower;

  int x = santas[id].coordinate.x;
  int y = santas[id].coordinate.y;

  int nx = x + dx;
  int ny = y + dy;

  board[x][y] = 0;

  santas[id].coordinate = {nx, ny};

  santas[id].fainting = 1;

  santas[id].score += santaPower;

  if (isOutBoard({nx, ny})) {
    santas[id].alive = false;
  } else if (board[nx][ny] > 0) {
    santaCrashSanta(santaDirIdxToRudolphDirIdx(oppositeDirIdx), id);
  } else {
    board[nx][ny] = id;
  }
}

void moveSanta(int id) {
  int closestSantaDirectionId = getClosestSantaDirectionId(id);

  if (closestSantaDirectionId == -1) return;

  int x = santas[id].coordinate.x;
  int y = santas[id].coordinate.y;

  int dx = santaDirection[closestSantaDirectionId].x;
  int dy = santaDirection[closestSantaDirectionId].y;

  santas[id].coordinate = {x + dx, y + dy};

  board[x][y] = 0;

  // cout << "MOVING SANTA\n";
  // printBoard();

  if (x + dx == rudolph.x && y + dy == rudolph.y) {
    santaCrashRudolph(closestSantaDirectionId, id);
  } else {
    board[x + dx][y + dy] = id;
  }
}

void moveSantas() {
  for (int i = 1; i <= santaNum; i++) {
    if (!santas[i].alive) continue;

    if (santas[i].fainting > 0) {
      santas[i].fainting--;
      // cout << i << " : fainting\n";
    } else {
      // cout << i << " MOVED\n";
      moveSanta(i);
    }
  }
}

void addSantasScore() {
  for (int i = 1; i <= santaNum; i++) {
    if (santas[i].alive) {
      santas[i].score++;
    }
  }
}

void solve() {
  for (int turnCnt = 0; turnCnt < turnNum; turnCnt++) {
    // cout << "TURN: " << turnCnt << '\n';

    moveRudolph();

    moveSantas();

    addSantasScore();

    // printBoard();

    if (!isSantaAlive()) {
      break;
    }
  }

  printSantasScore();
}

int run() {
  cin >> n >> turnNum >> santaNum >> rudolphPower >> santaPower;

  cin >> rudolph.x >> rudolph.y;

  for (int i = 1; i <= santaNum; i++) {
    int santaId;
    cin >> santaId >> santas[santaId].coordinate.x >> santas[santaId].coordinate.y;

    santas[santaId].score = 0;
    santas[santaId].alive = true;
    santas[santaId].fainting = 0;

    board[santas[santaId].coordinate.x][santas[santaId].coordinate.y] = santaId;
  }

  solve();

  return 0;
}