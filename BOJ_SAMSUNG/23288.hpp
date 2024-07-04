#include <iostream>
#include <queue>

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int n, m, board[30][30], moveNum, score, curDir;

COORDINATE cur = {0, 0};

int dice[6] = {2, 4, 1, 3, 5, 6};

int getDownSideOfDice() {
  return dice[5];
}

COORDINATE direction[4] = {
  {0, 1},
  {1, 0},
  {0, -1},
  {-1, 0},
};

void rollDice(int dir) {
  int tmpDice[6];

  for (int i = 0; i < 6; i++) tmpDice[i] = dice[i];
  
  if (dir == 0) {
    dice[0] = tmpDice[0];
    dice[1] = tmpDice[5];
    dice[2] = tmpDice[1];
    dice[3] = tmpDice[2];
    dice[4] = tmpDice[4];
    dice[5] = tmpDice[3];
  } else if (dir == 1) {
    dice[0] = tmpDice[5];
    dice[1] = tmpDice[1];
    dice[2] = tmpDice[0];
    dice[3] = tmpDice[3];
    dice[4] = tmpDice[2];
    dice[5] = tmpDice[4];
  } else if (dir == 2) {
    dice[0] = tmpDice[0];
    dice[1] = tmpDice[2];
    dice[2] = tmpDice[3];
    dice[3] = tmpDice[5];
    dice[4] = tmpDice[4];
    dice[5] = tmpDice[1];
  } else if (dir == 3) {
    dice[0] = tmpDice[2];
    dice[1] = tmpDice[1];
    dice[2] = tmpDice[4];
    dice[3] = tmpDice[3];
    dice[4] = tmpDice[5];
    dice[5] = tmpDice[0];
  }
}

void moveDice() {
  int dx = direction[curDir].x;
  int dy = direction[curDir].y;

  int nx = cur.x + dx;
  int ny = cur.y + dy;

  if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
    rollDice(curDir);
    cur = {nx, ny};
  } else {
    curDir = (curDir + 2) % 4;

    dx = direction[curDir].x;
    dy = direction[curDir].y;

    nx = cur.x + dx;
    ny = cur.y + dy;

    rollDice(curDir);
    cur = {nx, ny};
  }
}

int getScore() {
  int curBoard = board[cur.x][cur.y];

  int cnt = 0;

  queue<COORDINATE> q;
  int visited[30][30] = {0, };

  q.push(cur);
  visited[cur.x][cur.y] = 1;
  cnt++;

  while(!q.empty()) {
    int x = q.front().x;
    int y = q.front().y;
    q.pop();

    for (int dir = 0; dir < 4; dir++) {
      int dx = direction[dir].x;
      int dy = direction[dir].y;

      int nx = x + dx;
      int ny = y + dy;

      if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
        if (!visited[nx][ny] && board[nx][ny] == curBoard) {
          visited[nx][ny] = 1;
          q.push({nx, ny});
          cnt++;
        }
      }
    }
  }

  return curBoard * cnt;
}

void addScore() {
  score += getScore();
}

void makeDirection() {
  int downSide = getDownSideOfDice();
  int curBoard = board[cur.x][cur.y];

  if (curBoard < downSide) {
    curDir = (curDir + 1) % 4;
  } else if (curBoard > downSide) {
    curDir = (curDir - 1 + 4) % 4;
  }
}

void solve() {
  for (int moveCnt = 0; moveCnt < moveNum; moveCnt++) {
    moveDice();
    addScore();
    makeDirection();
  }

  cout << score << '\n';
}

int run() {
  cin >> n >> m >> moveNum;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j <m; j++) {
      cin >> board[i][j];
    }
  }
  
  solve();

  return 0;
}