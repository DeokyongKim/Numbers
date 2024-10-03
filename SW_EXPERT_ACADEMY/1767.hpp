#include <iostream>
#include <cstring>
#include <vector>

#define INF 0x7fffffff
#define MAX_N 13
#define CORE 1
#define LINE 2
#define EMPTY 0

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int n, board[MAX_N][MAX_N], maxCore, minLine;

vector<COORDINATE> cores;

void printBoard() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << ' ' ;
    }
    cout << '\n';
  }
    cout << '\n';
}

void initialize() {
  maxCore = -1;
  minLine = INF;
  memset(board, 0, sizeof(int) * MAX_N * MAX_N);
  cores.clear();
}

bool isOutOfBorder(const int &x, const int &y) {
  return x < 0 || x >= n || y < 0 || y >= n;
}

bool isBorder(const int &x, const int &y) {
  return x == 0 || x == n-1 || y == 0 || y == n-1;
}

void getInput() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];

      if (board[i][j] == CORE && !isBorder(i, j)) {
        cores.push_back({i, j});
      }
    }
  }
}

int putLine(COORDINATE core, const COORDINATE &direction, int wireColor, bool isDelete) {
  int line = 0;
  
  int dx = direction.x;
  int dy = direction.y;

  // cout << "CORE: " << core.x << ", " << core.y << '\n';
  // cout << "DIRECTION: " << direction.x << ", " << direction.y << '\n';

  for (;!isBorder(core.x, core.y) ; line++) {
    int nx = core.x + dx;
    int ny = core.y + dy;

    // cout << "NX: " << nx << " NY: " << ny << '\n';

    if (!isDelete && (board[nx][ny] == CORE || board[nx][ny] == LINE)) {
      line = -1;
      break;
    }

    core = {nx, ny};

    board[nx][ny] = wireColor;
  }

  return line;
}

bool isDirectionAble(const COORDINATE &core, const COORDINATE &direction) {
  return putLine(core, direction, EMPTY, false) > 0;
}

void dfs(int coreIndex, int coreNum, int lineNum) {
  if (coreIndex == cores.size()) {
    if (coreNum == maxCore && lineNum < minLine) {
      minLine = lineNum;
      
      // cout << "NEW MIN: " << coreNum << ", " << lineNum << '\n';
      // printBoard();
    } else if (coreNum > maxCore) {
      maxCore = coreNum;
      minLine = lineNum;

      // cout << "NEW MAX: " << coreNum << ", " << lineNum << '\n';
      // printBoard();
    }

    return;
  }

  COORDINATE directions[4] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
  };

  const COORDINATE &core = cores[coreIndex];

  for (int i = 0; i < 4; i++) {
    const COORDINATE &direction = directions[i];

    if (isDirectionAble(core, direction)) {
      int line = putLine(core, direction, LINE, false);
      dfs(coreIndex+1, coreNum+1, lineNum + line);
      putLine(core, direction, EMPTY, true);
    }
  }

  dfs(coreIndex+1, coreNum, lineNum);
}

int solve() {
  initialize();

  getInput();

  dfs(0, 0, 0);

  return minLine;
}

int run() {
  int testCases;
  cin >> testCases;

  for (int i = 1; i <= testCases; i++) {
    cout << "#" << i << ' ' << solve() << '\n';
  }

  return 0;
}