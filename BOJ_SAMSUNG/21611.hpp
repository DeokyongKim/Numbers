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

  for (int len = 1; len < n; len++) {
    for (int i = 0; i < len; i++) {
      if (board[x][y] == 0) return;
      v.push_back({board[x][y], true});
      x += dir;
    }

    for (int i = 0; i <= len; i++) {
      if (board[x][y] == 0) return;
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

    if (v[i].alive && cnt == index) {
      v[i].alive = false;
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

  int deleting = 0;

  for (int len = 1; len <= dist; len++) {
    x += dx;
    y += dy;

    deleteByStandardIndex(standardBoard[x][y] - deleting);

    deleting++;
  }
}

void deleteByVectorIndexAndCount(int index, int erasing, int erasingCnt) {
  int cnt = 0;

  for (; index >= 0; index--) {
    if (v[index].alive && v[index].number == erasing) {
      v[index].alive = false;
      cnt++;
    }

    if (cnt == erasingCnt) break;
  }
}

bool reduce() {
  int cnt = 0;

  bool did = false;

  int erasing = 0;
  int erasingCnt = 0;

  int i = 0;

  bool over = false;

  for (; i < v.size(); i++) {
    if (v[i].alive && v[i].number != 0) {
      cnt++;

      if (cnt >= n * n) {
        if (erasingCnt >= 4) {
          numbers[erasing] += erasingCnt;

          did = true;

          deleteByVectorIndexAndCount(i-1, erasing, erasingCnt);

          over = true;
        }

        erasingCnt = 0;

        break;
      }

      if (erasing == v[i].number) {
        erasingCnt++;
      } 
      
      if (erasing != v[i].number) {
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

  if (!did) {
    int isSame = 0;
    int sameCnt = 0;
    for (int i = 0; i < v.size(); i++) {
      if (!v[i].alive) continue;
      
      if (isSame == 0) {
        isSame = v[i].number;
        sameCnt++;
        continue;
      }

      if (isSame != v[i].number) {
        return false;
      } 

      if (isSame == v[i].number) sameCnt++;
    }

    deleteByVectorIndexAndCount(v.size() - 1, isSame, sameCnt);

    numbers[isSame] += sameCnt;
  }

  return did;
}

void changeBall() {
  int groupNum = 0;
  int groupCnt = 0;

  int curSize = v.size();

  int cnt = 0;

  for (int i = 0; i < curSize; i++) {
    if (!v[i].alive || v[i].number == 0) continue;

    if (cnt >= n * n) {
      v[i].alive = false;
      continue;
    }

    if (groupNum == 0) {
      groupNum = v[i].number;
      groupCnt++;
      v[i].alive = false;
    } else if (groupNum == v[i].number) {
      groupCnt++;
      v[i].alive = false;
    } else {
      if (cnt < n * n) v.push_back({groupCnt, true});
      cnt++;
      if (cnt < n * n) v.push_back({groupNum, true});
      cnt++;

      groupNum = v[i].number;
      groupCnt = 1;
      v[i].alive = false;
    }
  }

  if (groupCnt > 0) {
    if (cnt < n * n) v.push_back({groupCnt, true});
    cnt++;
    if (cnt < n * n) v.push_back({groupNum, true});
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