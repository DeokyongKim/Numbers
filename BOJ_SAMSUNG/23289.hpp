#include <iostream>
#include <vector>
#include <queue>

#define INF 0x7fffffff

using namespace std;

typedef struct _WALL {
  int x;
  int y;
  int t;
} WALL;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

typedef struct _AIRCONDITIONER {
  int x;
  int y;
  int dir;
} AIRCONDITIONER;

vector<WALL> walls;

vector<COORDINATE> suspects;

vector<AIRCONDITIONER> airconditioners;

int n, m, board[30][30], wallNum;
int standardTemperature;

int chocolateCnt;

bool isSpreadableToRight(COORDINATE from, COORDINATE to) {
  for (int i = 0; i < walls.size(); i++) {
    if (from.x-1 == to.x && from.y+1 == to.y) {
      // x, y -> x-1, y+1
      if (walls[i].x == from.x-1 && walls[i].y == from.y && walls[i].t == 0) {
        return false;
      }
      if (walls[i].x == from.x-1 && walls[i].y == from.y && walls[i].t == 1) {
        return false;
      }
    } else if (from.x == to.x && from.y+1 == to.y) {
      // x, y -> x, y+1
      if (walls[i].x == from.x && walls[i].y == from.y && walls[i].t == 1) {
        return false;
      }
    } else if (from.x+1 == to.x && from.y+1 == to.y) {
      // x, y -> x+1, y+1
      if (walls[i].x == from.x && walls[i].y == from.y && walls[i].t == 0) {
        return false;
      }
      if (walls[i].x == from.x+1 && walls[i].y == from.y && walls[i].t == 1) {
        return false;
      }
    }
  }

  return true;
}

bool isSpreadableToLeft(COORDINATE from, COORDINATE to) {
  for (int i = 0; i < walls.size(); i++) {
    if (from.x-1 == to.x && from.y-1 == to.y) {
      // x, y -> x-1, y-1
      if (walls[i].x == from.x-1 && walls[i].y == from.y && walls[i].t == 0) {
        return false;
      }
      if (walls[i].x == from.x-1 && walls[i].y == from.y-1 && walls[i].t == 1) {
        return false;
      }
    } else if (from.x == to.x && from.y-1 == to.y) {
      // x, y -> x, y-1
      if (walls[i].x == from.x && walls[i].y == from.y-1 && walls[i].t == 1) {
        return false;
      }
    } else if (from.x+1 == to.x && from.y-1 == to.y) {
      // x, y -> x+1, y-1
      if (walls[i].x == from.x && walls[i].y == from.y && walls[i].t == 0) {
        return false;
      }
      if (walls[i].x == from.x+1 && walls[i].y == from.y-1 && walls[i].t == 1) {
        return false;
      }
    }
  }

  return true;
}

bool isSpreadableToUp(COORDINATE from, COORDINATE to) {
  for (int i = 0; i < walls.size(); i++) {
    if (from.x-1 == to.x && from.y-1 == to.y) {
      // x, y -> x-1, y-1
      if (walls[i].x == from.x-1 && walls[i].y == from.y-1 && walls[i].t == 0) {
        return false;
      }
      if (walls[i].x == from.x && walls[i].y == from.y-1 && walls[i].t == 1) {
        return false;
      }
    } else if (from.x-1 == to.x && from.y == to.y) {
      // x, y -> x-1, y
      if (walls[i].x == from.x-1 && walls[i].y == from.y && walls[i].t == 0) {
        return false;
      }
    } else if (from.x-1 == to.x && from.y+1 == to.y) {
      // x, y -> x-1, y+1
      if (walls[i].x == from.x-1 && walls[i].y == from.y+1 && walls[i].t == 0) {
        return false;
      }
      if (walls[i].x == from.x && walls[i].y == from.y && walls[i].t == 1) {
        return false;
      }
    }
  }

  return true;
}

bool isSpreadableToDown(COORDINATE from, COORDINATE to) {
  for (int i = 0; i < walls.size(); i++) {
    if (from.x+1 == to.x && from.y-1 == to.y) {
      // x, y -> x+1, y-1
      if (walls[i].x == from.x && walls[i].y == from.y-1 && walls[i].t == 0) {
        return false;
      }
      if (walls[i].x == from.x && walls[i].y == from.y-1 && walls[i].t == 1) {
        return false;
      }
    } else if (from.x+1 == to.x && from.y == to.y) {
      // x, y -> x+1, y
      if (walls[i].x == from.x && walls[i].y == from.y && walls[i].t == 0) {
        return false;
      }
    } else if (from.x+1 == to.x && from.y+1 == to.y) {
      // x, y -> x+1, y+1
      if (walls[i].x == from.x && walls[i].y == from.y && walls[i].t == 1) {
        return false;
      }
      if (walls[i].x == from.x && walls[i].y == from.y+1 && walls[i].t == 0) {
        return false;
      }
    }
  }

  return true;
}

bool isSpreadable(COORDINATE from, COORDINATE to, int dir) {
  if (dir == 0) {
    return isSpreadableToRight(from, to);
  } else if (dir == 1) {
    return isSpreadableToLeft(from, to);
  } else if (dir == 2) {
    return isSpreadableToUp(from, to);
  } else if (dir == 3) {
    return isSpreadableToDown(from, to);
  }

  return false;
}

void spreadWind(AIRCONDITIONER airconditioner) {
  COORDINATE direction[4] = {
    {0, 1},
    {0, -1},
    {-1, 0},
    {1, 0},
  };

  typedef struct _BOARD {
    int x;
    int y;
    int temperature;
  } BOARD;

  int dir = airconditioner.dir;
  int dx = direction[dir].x;
  int dy = direction[dir].y;

  int newX = airconditioner.x + dx;
  int newY = airconditioner.y + dy;

  if (newX < 0 || newX >= n || newY < 0 || newY >= m) return;

  queue<BOARD> q;
  int visited[30][30] = {0, };

  q.push({newX, newY, 5});
  visited[newX][newY] = 5;

  while(!q.empty()) {
    if (q.front().temperature == 1) {
      q.pop();
      continue;
    }

    BOARD cur = q.front();
    q.pop();

    int spread[3] = {-1, 0, 1};

    if (dx == 0) {
      int ny = cur.y + dy;

      for (int i = 0; i < 3; i++) {
        int nx = cur.x + spread[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
          if (isSpreadable({cur.x, cur.y}, {nx, ny}, dir)) {
            q.push({nx, ny, cur.temperature-1});
            visited[nx][ny] = cur.temperature-1;
          }
        }
      }
    } else if (dy == 0) {
      int nx = cur.x + dx;

      for (int i = 0; i < 3; i++) {
        int ny = cur.y + spread[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
          if (isSpreadable({cur.x, cur.y}, {nx, ny}, dir)) {
            q.push({nx, ny, cur.temperature-1});
            visited[nx][ny] = cur.temperature-1;
          }
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      board[i][j] += visited[i][j];
    }
  }
}

void blowWind() {
  for (int i = 0; i < airconditioners.size(); i++) {
    spreadWind(airconditioners[i]);
  }
}

bool isAdjustable(COORDINATE a, COORDINATE b) {
  COORDINATE from, to;
  
  if (a.x == b.x) {
    if (a.y < b.y) {
      from = a;
      to = b;
    } else {
      from = b;
      to = a;
    }
  } 
  
  if (a.y == b.y) {
    if (a.x < b.x) {
      from = a;
      to = b;
    } else {
      from = b;
      to = b;
    }
  }

  for (int i = 0; i < walls.size(); i++) {
    if (from.x == to.x) {
      if (walls[i].x == from.x && walls[i].y == from.y && walls[i].t == 1) return false;
    } else if (from.y == to.y) {
      if (walls[i].x == from.x && walls[i].y == from.y && walls[i].t == 0) return false;
    }
  }

  return true;
}

void adjustTemperature() {
  COORDINATE direction[4] = {
    {0, 1},
    {0, -1},
    {-1, 0},
    {1, 0},
  };
  
  int tmpBoard[30][30] = {0, };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int sum = 0;
      
      for (int dir = 0; dir < 4; dir++) {
        int dx = direction[dir].x;
        int dy = direction[dir].y;

        int nx = i + dx;
        int ny = j + dy;
        if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
          if (board[i][j] > board[nx][ny] && isAdjustable({i, j}, {nx, ny})) {
            int sub = board[i][j] - board[nx][ny];

            tmpBoard[nx][ny] += (sub / 4);
            sum += (sub / 4);
          }
        }
      }

      tmpBoard[i][j] -= sum;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      board[i][j] += tmpBoard[i][j];
    }
  }
}

void reduceTemperature() {
  for (int i = 0; i < n; i++) {
    if (board[i][0] > 0) board[i][0]--;
    if (board[i][m-1] > 0) board[i][m-1]--;
  }

  for (int j = 0; j < m; j++) {
    if (board[0][j] > 0) board[0][j]--;
    if (board[n-1][j] > 0) board[n-1][j]--;
  }
}

bool isAllOverStandardTemperature() {
  for (int i = 0; i < suspects.size(); i++) {
    if (board[suspects[i].x][suspects[i].y] < standardTemperature) return false;
  }
  return true;
}

void printBoard() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << board[i][j] << '\t';
    }
    cout << '\n';
  }
  cout << '\n';
}

void solve() {
  while(true) {
    if (chocolateCnt > 100) {
      cout << 101 << '\n';
      return;
    }

    blowWind();             // 1
    printBoard();

    adjustTemperature();    // 2 
    printBoard();

    reduceTemperature();    // 3

    chocolateCnt++;         // 4

    printBoard();

    if (isAllOverStandardTemperature()) {
      break;
    }
  }

  cout << chocolateCnt << '\n';
}

int run() {
  cin >> n >> m >> standardTemperature;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int tmp;
      
      cin >> tmp;

      if (tmp >= 1 && tmp <= 4) {
        airconditioners.push_back({i, j, tmp-1});
      } else if (tmp == 5) {
        suspects.push_back({i, j});
      }
    }
  }

  cin >> wallNum;

  for (int i = 0; i < wallNum; i++) {
    WALL tmp;
    cin >> tmp.x >> tmp.y >> tmp.t;

    walls.push_back({tmp.x-1, tmp.y-1, tmp.t});
  }

  solve();

  return 0;
}