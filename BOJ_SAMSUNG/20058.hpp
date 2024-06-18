#include <iostream>
#include <queue>

using namespace std;

int nUp, n, cutCnt, board[80][80], cutList[1010];

void particlize(int cutLenUp) {
  int cutLen = 1 << cutLenUp;

  for (int row = 0; row < n; row += cutLen) {
    for (int col = 0; col < n; col += cutLen) {
      // get particle
      int partial[80][80] = {0, };
      for (int i = 0; i < cutLen; i++) {
        for (int j = 0; j < cutLen; j++) {
          partial[i][j] = board[row + i][col + j]; 
        }
      }

      // rotate 90 deg
      for (int i = 0; i < cutLen; i++) {
        for (int j = 0; j < cutLen; j++) {
          board[i + row][j + col] = partial[cutLen-1-j][i];
        }
      }
    }
  }
}

void meltIce() {
  int dirX[4] = {1, 0, -1, 0};
  int dirY[4] = {0, 1, 0, -1};

  int meltBoard[80][80] = {0, };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 0) continue;

      int aroundIceNum = 0;

      for (int dir = 0; dir < 4; dir++) {
        int dx = dirX[dir], dy = dirY[dir];
        int nx = i + dx;
        int ny = j + dy;

        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
          if (board[nx][ny] > 0) {
            aroundIceNum++;
          }
        }
      }

      if (aroundIceNum < 3) meltBoard[i][j] = 1;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (meltBoard[i][j]) board[i][j]--;
    }
  }
}

int getEntireIce() {
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] > 0) ans += board[i][j];
    }
  }

  return ans;
}

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int bfs(int x, int y) {
  int size = 0;

  queue<COORDINATE> q;
  int visited[80][80] = {0, };

  q.push({x, y});
  visited[x][y] = 1;
  board[x][y] = -1;
  size++;

  COORDINATE direction[4] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
  };

  while(!q.empty()) {
    COORDINATE cur = q.front();
    int curX = cur.x;
    int curY = cur.y;
    q.pop();

    for (int dir = 0; dir < 4; dir++) {
      int dx = direction[dir].x;
      int dy = direction[dir].y;

      int nx = curX + dx;
      int ny = curY + dy;
      if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
        if (!visited[nx][ny] && board[nx][ny] > 0) {
          size++;
          q.push({nx, ny});
          visited[nx][ny] = 1;
          board[nx][ny] = -1;
        }
      }
    }
  }

  return size;
}

int getLargestIce() {
  int max = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] > 0) {
        int curSize = bfs(i, j);
        if (max < curSize) max = curSize;
      }
    }
  }

  return max;
}

void printBoard() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

void solve() {
  for (int i = 0; i < cutCnt; i++) {
    particlize(cutList[i]);

    meltIce();
  }


  cout << getEntireIce() << '\n' << getLargestIce() << '\n';
}

int run() {
  cin >> nUp >> cutCnt;

  n = 1 << nUp;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
    }
  }

  for (int i = 0; i < cutCnt; i++) cin >> cutList[i];

  solve();
  
  return 0;
}