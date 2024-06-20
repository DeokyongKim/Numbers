#include <iostream>
#include <queue>

using namespace std;

typedef struct _COORDI {
  int x;
  int y;
} COORDI;

typedef struct _BLOCK {
  COORDI standard;
  int blockCnt;
  int rainbowCnt;
} BLOCK;

int n, m, score;

int board[25][25];

void printBoard() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == -2) cout << '.' << '\t';
      else cout << board[i][j] << '\t';
    }
    cout << '\n';
  }
  cout << '\n';
}

BLOCK bfs(COORDI input, int localBoard[25][25], int mode) {
  queue<COORDI> q;
  int blockCnt = 1;
  int rainbowCnt = 0;
  COORDI standard = {input.x, input.y};
  int visited[25][25] = {0, };

  int inputColor = localBoard[input.x][input.y];

  q.push(input);
  visited[input.x][input.y] = 1;
  localBoard[input.x][input.y] = -2;

  COORDI direction[4] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1},
  };

  while(!q.empty()) {
    COORDI cur = q.front();
    q.pop();

    int x = cur.x;
    int y = cur.y;

    for (int dir = 0; dir < 4; dir++) {
      int dx = direction[dir].x;
      int dy = direction[dir].y;

      int nx = x + dx;
      int ny = y + dy;

      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

      if (!visited[nx][ny] && (localBoard[nx][ny] == inputColor || localBoard[nx][ny] == 0)) {
        if (localBoard[nx][ny] > 0) localBoard[nx][ny] = -2;
        if (localBoard[nx][ny] == 0 && mode == 0) rainbowCnt++;
        if (localBoard[nx][ny] == 0 && mode == 1) {
          rainbowCnt++;
          localBoard[nx][ny] = -2;
        }

        blockCnt++;
        
        q.push({nx, ny});
        visited[nx][ny] = 1;

        if (localBoard[nx][ny] == 0) continue;

        if (standard.x > nx) {
          standard = {nx, ny};
        } else if (standard.x == nx && standard.y < ny) {
          standard = {nx, ny};
        }
      }
    }
  }

  if (blockCnt < 2) return {{-1, -1}, blockCnt, rainbowCnt};

  return {standard, blockCnt, rainbowCnt};
}

BLOCK getLargestBlock() {
  BLOCK largestBlock = {{-1, -1}, 0, 0};

  int tmpBoard[25][25] = {0, };
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      tmpBoard[i][j] = board[i][j];
    }
  }
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (tmpBoard[i][j] > 0) {
        BLOCK tmp = bfs({i, j}, tmpBoard, 0);

        if (tmp.standard.x == -1) continue;

        if (tmp.blockCnt > largestBlock.blockCnt) {
          largestBlock = tmp;
        } else if (tmp.blockCnt == largestBlock.blockCnt) {
          if (tmp.rainbowCnt > largestBlock.rainbowCnt) {
            largestBlock = tmp;

          } else if (tmp.rainbowCnt == largestBlock.rainbowCnt) {
            if (tmp.standard.x > largestBlock.standard.x) {
              largestBlock = tmp;

            } else if (tmp.standard.x == largestBlock.standard.x) {
              if (tmp.standard.y > largestBlock.standard.y) {
                largestBlock = tmp;

              }
            }
          }
        }
      }
    }
  }

  return largestBlock;
}

void deleteBlock(COORDI input) {
  BLOCK largestBlock = bfs(input, board, 1);
}

bool getBoardScore() {
  BLOCK largestBlock = getLargestBlock();

  if (largestBlock.blockCnt < 2) return false;

  score += (largestBlock.blockCnt * largestBlock.blockCnt);

  deleteBlock(largestBlock.standard);

  return true;
}

void applyGravity() {
  for (int k = 0; k < n; k++) {
    for (int i = n-2; i >= 0; i--) {
      for (int j = 0; j < n; j++) {
        // don't check block
        if (board[i][j] < 0) continue;

        if (board[i+1][j] == -2) {
          board[i+1][j] = board[i][j];
          board[i][j] = -2;
        }
      }
    }
  }
}

void rotate() {
  int tmpBoard[25][25] = {0, };
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      tmpBoard[i][j] = board[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[n-1-j][i] = tmpBoard[i][j];
    }
  }
}

void moveBlock() {
  applyGravity();

  rotate();

  applyGravity();
}

void autoplay() {
  while(true) {
    if (!getBoardScore()) {
      break;
    }

    moveBlock();
  }
}

int run() {
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
    }
  }

  autoplay();

  cout << score << '\n';
}