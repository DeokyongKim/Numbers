#include <iostream>

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int n, board[60][60], m;

int numbers[4];

void printArray(int arr[60][60]) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << arr[i][j] << '\t';
    }
    cout << '\n';
  }
  cout << '\n';
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

            return cnt;
          }
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

            return cnt;
          }
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

  return 0;
}

int getScore() {
  return numbers[1] + 2 * numbers[2] + 3 * numbers[3];
}

void changeBall() {
  //하나의 그룹은 두 개의 구슬 A와 B로 변한다. 구슬 A의 번호는 그룹에 들어있는 구슬의 개수이고, B는 그룹을 이루고 있는 구슬의 번호이다. 구슬은 다시 그룹의 순서대로 1번 칸부터 차례대로 A, B의 순서로 칸에 들어간다. 다음 그림은 구슬이 변화한 후이고, 색은 구분하기 위해 위의 그림에 있는 그룹의 색을 그대로 사용했다. 만약, 구슬이 칸의 수보다 많아 칸에 들어가지 못하는 경우 그러한 구슬은 사라진다.
  // shit..
}

void solve() {
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

    printArray(board);
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