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

int boardRow, boardCol, board[30][30], wallNum;
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

bool isSpreadable(COORDINATE from, COORDINATE to, int dir) {
  if (dir == 0) {
    return isSpreadableToRight();
  } else if (dir == 1) {
    return isSpreadableToLeft();
  } else if (dir == 1) {
    return isSpreadableToUp();
  } else if (dir == 1) {
    return isSpreadableToDown();
  }
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

  if (newX < 0 || newX >= boardRow || newY < 0 || newY >= boardCol) return;

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
        if (isSpreadable({cur.x, ny}, {nx, ny}, dir) && nx >= 0 && nx < boardRow && ny >= 0 && ny < boardCol) {

        }
      }
    }
  }
}

void blowWind() {
  for (int i = 0; i < airconditioners.size(); i++) {
    spreadWind(airconditioners[i]);
  }
}

void solve() {
  whlie(true) {
    if (chocolateCnt > 100) {
      cout << 101 << '\n';
      return;
    }

    blowWind();
  }
}

int run() {
  cin >> boardRow >> boardCol >> standardTemperature;

  for (int i = 0; i < boardRow; i++) {
    for (int j = 0; j < boardCol; j++) {
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

    walls.push_back(tmp);
  }

  solve();
}