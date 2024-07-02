#include <iostream>
#include <vector>

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

typedef struct _MARBLE {
  int number;
  bool alive;
} MARBLE;

int n, m;

int standardBoard[60][60];

vector<MARBLE> v;

int numbers[4];

void putBoardIntoVector(int board[60][60]) {
  int x = (n + 1) / 2;
  int y = (n + 1) / 2 - 1;

  int dir = 1;

  for (int len = 1; len <= n; len++) {
    for (int i = 0; i < len; i++) {
      v.push_back({board[x][y], true});
      x += dir;
    }

    for (int i = 0; i <= len; i++) {
      v.push_back({board[x][y], true});
      y += dir;
    }

    dir *= -1;
  }
}

void setStandardBoard() {
  int num = n * n - 1;

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

void deleteByStandardIndex(int index) {
  int cnt = 0;

  for (int i = 0; i < v.size(); i++) {
    if (v[i].alive) cnt++;

    if (cnt == index) {
      v[i].alive = false;
      break;
    }
  }
}

void blizard(int dir, int dist) {
  COORDINATE direction[4] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
  };

  int x = (n + 1) / 2;
  int y = (n + 1) / 2;

  int dx = direction[dir].x;
  int dy = direction[dir].y;

  for (int len = 1; len <= dist; len++) {
    x += dx;
    y += dy;

    deleteByStandardIndex(standardBoard[x][y]);
  }
}

void deleteByVectorIndexAndCount(int index, int erasing, int erasingCnt) {
  int cnt = 0;

  for (; index >= 0; index--) {
    if (cnt == erasingCnt) break;

    if (v[index].alive && v[index].number == erasing) {
      v[index].alive = false;
      cnt++;
    }
  }
}

bool reduce() {
  int cnt = 0;

  bool did = false;

  int erasing = 0;
  int erasingCnt = 0;

  for (int i = 0; i < v.size(); i++) {
    if (cnt >= n * n) break;

    if (v[i].alive) {
      if (erasing == v[i].number) {
        erasingCnt++;
      } else {
        if (erasingCnt >= 4) {
          numbers[erasing] += erasingCnt;

          did = true;

          deleteByVectorIndexAndCount(i, erasing, erasingCnt);
        }

        erasing = v[i].number;
        erasingCnt = 1;
      }
    }
  }

  if (erasingCnt >= 4) {
    numbers[erasing] += erasingCnt;

    did = true;

    deleteByVectorIndexAndCount(v.size()-1, erasing, erasingCnt);
  }

  return did;
}

void changeBall() {
  int groupNum = 0;
  int groupCnt = 0;

  for (int i = 0; i < v.size(); i++) {
    if (!v[i].alive) continue;

    if (groupNum == 0) {
      groupNum = v[i].number;
      groupCnt++;
      v[i].alive = false;
    }

    if (groupNum == v[i].number) {
      groupCnt++;
      v[i].alive = false;
    } else {
      v.push_back({groupCnt, true});
      v.push_back({groupNum, true});

      groupNum = v[i].number;
      v[i].alive = false;
    }
  }

  if (groupCnt > 0) {
    v.push_back({groupCnt, true});
    v.push_back({groupNum, true});
  }
}

int getScore() {
  return 1 * numbers[1] + 2 * numbers[2] + 3 * numbers[3];
}

void solve() {
  setStandardBoard();

  for (int i = 0; i < m; i++) {
    int direction, distance;
    cin >> direction >> distance;

    blizard(direction-1, distance);

    while(reduce());

    changeBall();
  }

  cout << getScore() << '\n';
}

int run() {
  int board[60][60];

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> board[i][j];
    }
  }

  putBoardIntoVector(board);

  solve();

  return 0;
}