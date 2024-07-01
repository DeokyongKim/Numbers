#include <iostream>

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int n, board[60][60], m;

int standardBoard[60][60], tmpBoard[60][60];
int standardX, standardY;

int numbers[4];

void printArray(int arr[60][60]) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << arr[i][j] << '\t';
    }
    cout << "\n\n";
  }
  cout << "====================\n";
}

void blizard(int dir, int dist) {
  COORDINATE direction[4] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
  };

  int dx = direction[dir].x;
  int dy = direction[dir].y;

  int x = (n+1)/2;
  int y = (n+1)/2;

  for (int i = 1; i <= dist; i++) {
    x += dx;
    y += dy;

    board[x][y] = 0;
  }
}

void moveOnce() {
  int x = (n+1)/2;
  int y = (n+1)/2 - 1;

  int dir = 1;

  for (int len = 1; len <= n; len++) {
    for (int i = 0; i < len; i++) {
      if (board[x][y] == 0) {
        board[x][y] = board[x + dir][y];
        board[x + dir][y] = 0;
      }
      x += dir;
    }

    for (int i = 0; i <= len; i++) {
      if (board[x][y] == 0) {
        board[x][y] = board[x][y + dir];
        board[x][y + dir] = 0;

      }
      y += dir;
    }

    dir *= -1;
  }
}

void move(int num) {
  for (int i = 0; i < num; i++) moveOnce();
}

void initialize(int arr[60][60]) {
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      arr[i][j] = 0;
    }
  }
}

int reduce() {
  int erase[60][60] = {0, };

  int erasing = 0;
  int cnt = 0;

  int x = (n+1)/2;
  int y = (n+1)/2 - 1;

  int dir = 1;

  int sum = 0;

  for (int len = 1; len <= n; len++) {
    for (int i = 0; i < len; i++) {
      if (erasing == 0) {
        erasing = board[x][y];
        erase[x][y] = 1;
        cnt++;
      } else {
        if (board[x][y] == erasing) {
          cnt++;
          erase[x][y] = 1;
        } else {
          if (cnt >= 4) {
            for (int row = 1; row <= n; row++) {
              for (int col = 1; col <= n; col++) {
                if (erase[row][col]) {
                  board[row][col] = 0;
                }
              }
            }

            numbers[erasing] += cnt;

            sum += cnt;
          }

          if (board[x][y] == 0) return sum;

          erasing = board[x][y];
          initialize(erase);
          erase[x][y] = 1;
          cnt = 1;
        }
      }
      x += dir;
    }

    for (int i = 0; i <= len; i++) {
      if (erasing == 0) {
        erasing = board[x][y];
        erase[x][y] = 1;
        cnt++;
      } else {
        if (board[x][y] == erasing) {
          cnt++;
          erase[x][y] = 1;
        } else {
          if (cnt >= 4) {
            for (int row = 1; row <= n; row++) {
              for (int col = 1; col <= n; col++) {
                if (erase[row][col]) {
                  board[row][col] = 0;
                }
              }
            }

            numbers[erasing] += cnt;

            sum += cnt;
          }

          if (board[x][y] == 0) return sum;
          
          erasing = board[x][y];
          initialize(erase);
          erase[x][y] = 1;
          cnt = 1;
        }
      }
      y += dir;
    }

    dir *= -1;
  }

  return sum;
}

int getScore() {
  return numbers[1] + 2 * numbers[2] + 3 * numbers[3];
}

void pushTmpBoard(int first, int second) {
  if (standardX < 1 || standardX > n || standardY < 1 || standardY > n)
    return;

  // cout << "PUSH=> CNT: " << first << " NUM: " << second << '\n';

  COORDINATE direction[4] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
  };

  tmpBoard[standardX][standardY] = first;
  
  for (int dir = 0; dir < 4; dir++) {
    int dx = direction[dir].x;
    int dy = direction[dir].y;
    int nx = standardX + dx;
    int ny = standardY + dy;

    int cur = standardBoard[standardX][standardY];

    if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
      if (standardBoard[nx][ny] == cur + 1) {
        standardX = nx;
        standardY = ny;
        break;
      }
    }
  }

  tmpBoard[standardX][standardY] = second;
  
  for (int dir = 0; dir < 4; dir++) {
    int dx = direction[dir].x;
    int dy = direction[dir].y;
    int nx = standardX + dx;
    int ny = standardY + dy;

    int cur = standardBoard[standardX][standardY];

    if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
      if (standardBoard[nx][ny] == cur + 1) {
        standardX = nx;
        standardY = ny;
        break;
      }
    }
  }
}

void changeBall() {
  initialize(tmpBoard);

  standardX = (n + 1) / 2;
  standardY = (n + 1) / 2 - 1;

  int erasing = 0;
  int cnt = 0;

  int x = (n+1)/2;
  int y = (n+1)/2 - 1;

  int dir = 1;

  bool end = false;

  for (int len = 1; len <= n; len++) {
    for (int i = 0; i < len; i++) {
      if (board[x][y] == 0) {
        end = true;
        break;
      }

      if (erasing == 0) {
        erasing = board[x][y];
        cnt++;
      } else {
        if (board[x][y] == erasing) {
          cnt++;
        } else {
          pushTmpBoard(cnt, erasing);

          erasing = board[x][y];
          cnt = 1;
        }
      }
      x += dir;
    }

    if (end) break;

    for (int i = 0; i <= len; i++) {
      if (board[x][y] == 0) {
        end = true;
        break;
      }

      if (erasing == 0) {
        erasing = board[x][y];
        cnt++;
      } else {
        if (board[x][y] == erasing) {
          cnt++;
        } else {
          pushTmpBoard(cnt, erasing);

          erasing = board[x][y];
          cnt = 1;
        }
      }
      y += dir;
    }

    if (end) break;

    dir *= -1;
  }

  pushTmpBoard(cnt, erasing);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      board[i][j] = tmpBoard[i][j];
    }
  }
}

void setStandardBoard() {
  int num = n * n;

  int i = 1, j = 1;

  int dir = 1;

  for (int len = n; len >= 1; len--) {
    for (int k = 0; k < len; k++) {
      standardBoard[i][j] = num--;
      j += dir;
    }
    j -= dir;
    i += dir;

    for (int k = 0; k < len-1; k++) {
      standardBoard[i][j] = num--;
      i += dir;
    }
    i -= dir;
    j -= dir;

    dir *= -1;
  }
}

void solve() {
  setStandardBoard();

  for (int i = 0; i < m; i++) {
    int direction, distance;
    cin >> direction >> distance;

    blizard(direction-1, distance);

    move(distance);

    while(true) {
      int reduceNum = reduce();

      if (reduceNum == 0) break;

      move(reduceNum);
    }

    changeBall();
  }

  cout << getScore() << '\n';
}

int run() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> board[i][j];
    }
  }

  solve();

  return 0;
}