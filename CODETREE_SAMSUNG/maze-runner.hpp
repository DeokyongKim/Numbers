#include <iostream>
#include <vector>

#define MAX_N 15
#define INF 0x7fffffff

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int n, maze[MAX_N][MAX_N], gameTime, gamerNum;

int totalMovedRange;

COORDINATE exitCell;

vector<COORDINATE> gamers;

void printGamers() {
  for (int i = 0; i < gamers.size(); i++) {
    cout << '{' << gamers[i].x << ", " << gamers[i].y << '}' << ", ";
  }
  cout << '\n';
}

void printMaze() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << maze[i][j] << ' ';
    }
    cout << '\n';
  }
    cout << '\n';
}

bool isOutOfBound(int x, int y) {
  if (x < 0) return true;
  if (y < 0) return true;
  if (x >= n) return true;
  if (y >= n) return true;
  return false;
}

void getInput() {
  cin >> n >> gamerNum >> gameTime;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> maze[i][j];
    }
  }

  for (int i = 0; i < gamerNum; i++) {
    int a, b;
    cin >> a >> b;
    gamers.push_back({a-1, b-1});
  }

  cin >> exitCell.x >> exitCell.y;

  exitCell.x--;
  exitCell.y--;
}

int abs(int a) {
  if (a >= 0) return a;
  return -1 * a;
}

int getDistance(COORDINATE a, COORDINATE b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

COORDINATE getDirectionToExit(COORDINATE gamer) {
  COORDINATE directions[4] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
  };

  int minDist = INF;
  COORDINATE minDirection = {0, 0};

  for (int i = 0; i < 4; i++) {
    int dx = directions[i].x;
    int dy = directions[i].y;

    int nx = gamer.x + dx;
    int ny = gamer.y + dy;

    if (!isOutOfBound(nx, ny) && minDist > getDistance({nx, ny}, exitCell) && maze[nx][ny] == 0) {
      minDist = getDistance({nx, ny}, exitCell);
      minDirection = directions[i];
    }
  }

  return minDirection;
}

void moveGamer(int id) {
  COORDINATE gamer = gamers[id];

  COORDINATE directionToExit = getDirectionToExit(gamer);

  COORDINATE nextCell = {gamer.x + directionToExit.x, gamer.y + directionToExit.y};

  if (
      (directionToExit.x == 0 && directionToExit.y == 0) ||
      isOutOfBound(nextCell.x, nextCell.y) || 
      getDistance(gamer, exitCell) <= getDistance(nextCell, exitCell)
    ) {
      return;
    } 
  
  // cout << "DIST: " << getDistance(gamer, exitCell) << ' ' << getDistance(nextCell, exitCell) <<'\n';

  gamers[id] = nextCell;
  totalMovedRange++;

  if (gamers[id].x == exitCell.x && gamers[id].y == exitCell.y) {
    gamers.erase(gamers.begin() + id);
  }
}

void moveGamers() {
  for (int i = gamers.size()-1; i >= 0; i--) {
    moveGamer(i);
  }
}

typedef struct SQUARE {
  COORDINATE start;
  int length;
} SQUARE;

bool isGamerInSquare(COORDINATE gamer, SQUARE square) {
  int x = square.start.x;
  int y = square.start.y;
  int length = square.length;
  return gamer.x >= x && gamer.x < x + length && gamer.y >= y && gamer.y < y + length;
}

bool isTargetForRotation(int x, int y, int length) {
  bool isGamerIn = false;
  bool isExitIn = isGamerInSquare(exitCell, {x, y, length});
  
  for (int i = 0; i < gamers.size(); i++) {
    if (isGamerInSquare(gamers[i], {x, y, length})) {
      isGamerIn = true;
      break;
    }
  }

  return isGamerIn && isExitIn;
}

SQUARE getRotateSquare() {
  SQUARE rotateSquare = {
    {0, 0},
    INF,
  };

  for (int len = 2; len <= n; len++) {
    for (int i = 0; i + len <= n; i++) {
      for (int j = 0; j + len <= n; j++) {
        if (isTargetForRotation(i, j, len) && rotateSquare.length > len) {
          rotateSquare = {
            {i, j},
            len
          };
        }
      }
    }
  }

  return rotateSquare;
}

void rotateMaze(SQUARE square) {
  int newMaze[MAX_N][MAX_N] = {0, };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      newMaze[i][j] = maze[i][j];
    }
  }
  
  for (int i = 0; i < square.length; i++) {
    for (int j = 0; j < square.length; j++) {
      newMaze[i + square.start.x][j + square.start.y] = maze[square.length - j - 1 + square.start.x][i + square.start.y];
      if (newMaze[i + square.start.x][j + square.start.y] > 0) {
        newMaze[i + square.start.x][j + square.start.y]--;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      maze[i][j] = newMaze[i][j];
    }
  }

  exitCell = {
    (exitCell.y - square.start.y) + square.start.x,
    square.length - (exitCell.x - square.start.x) - 1 + square.start.y,
  };

  for (int i = 0; i < gamers.size(); i++) {
    if (isGamerInSquare(gamers[i], square)) {
      gamers[i] = {
        (gamers[i].y - square.start.y) + square.start.x,
        square.length - (gamers[i].x - square.start.x) - 1 + square.start.y,
      };
    }
  }
}

void rotationStage() {
  SQUARE rotateSquare = getRotateSquare();

  // cout << "SQUARE: " << rotateSquare.start.x << " " << rotateSquare.start.y << " " << rotateSquare.length << '\n';

  if (rotateSquare.length == INF) return;

  rotateMaze(rotateSquare);
}

void oneSecond() {
  // printGamers();
  moveGamers();
  // printGamers();

  rotationStage();
  // printGamers();
  // cout << "EXIT: " << exitCell.x << ", " << exitCell.y << '\n';
}

void solve() {
  // printMaze();
  for (int sec = 0; sec < gameTime; sec++) {
    // cout << "\nSEC: " << sec+1 << '\n';
    oneSecond();
  // printMaze();

    if (gamers.size() == 0) break;
  }

  cout << totalMovedRange << '\n' << exitCell.x+1 << ' ' << exitCell.y+1 << '\n';
}

int run() {
  getInput();

  solve();

  return 0;
}