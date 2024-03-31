// #include "./Numbers/BOJ_SAMSUNG/14891.hpp"

#include <algorithm>
#include <iostream>
#define INF 1987654321

using namespace std;

typedef struct _CCTV {
  int x;
  int y;
  int mode;
  // int dir;
} CCTV;

int board[10][10][2];
int n, m;

CCTV cctv[10];
int cctvCnt;

int ans = INF;

int howManyLeft() {
  int num = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (board[i][j][0] == 0)
        num++;

  return num;
}

bool comp(CCTV a, CCTV b) { return a.mode > b.mode; }

void unpaintBoard(int chk) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (board[i][j][0] == chk)
        board[i][j][0] = 0;
}

void paintEachBoard(int nowX, int nowY, int chk, int dir) {
  int partialAns;
  if (dir == 1) {
    // up
    for (int i = nowX - 1; i >= 0; i--) {
      if (board[i][nowY][0] == 6)
        break;
      if (board[i][nowY][0] == 0)
        board[i][nowY][0] = chk;
    }
  } else if (dir == 2) {
    // right
    for (int i = nowY - 1; i >= 0; i--) {
      if (board[nowX][i][0] == 6)
        break;
      if (board[nowX][i][0] == 0)
        board[nowX][i][0] = chk;
    }
  } else if (dir == 3) {
    // down
    for (int i = nowX + 1; i < n; i++) {
      if (board[i][nowY][0] == 6)
        break;
      if (board[i][nowY][0] == 0)
        board[i][nowY][0] = chk;
    }
  } else if (dir == 4) {
    // left
    for (int i = nowY + 1; i < m; i++) {
      if (board[nowX][i][0] == 6)
        break;
      if (board[nowX][i][0] == 0)
        board[nowX][i][0] = chk;
    }
  }
}

int getOpposite(int idx) { return ((idx + 2) % 4) == 0 ? 4 : ((idx + 2) % 4); }
int getLeft(int idx) { return idx == 1 ? 4 : idx - 1; }
int getRight(int idx) { return idx == 4 ? 1 : idx + 1; }

void paintBoard(int chk) {
  for (int i = 0; i < cctvCnt; i++) {
    int curX = cctv[i].x;
    int curY = cctv[i].y;
    int curMode = cctv[i].mode;
    int dir = board[curX][curY][1];

    if (curMode == 1) {
      paintEachBoard(curX, curY, chk, dir);
    } else if (curMode == 2) {
      paintEachBoard(curX, curY, chk, dir);
      paintEachBoard(curX, curY, chk, getOpposite(dir));
    } else if (curMode == 3) {
      paintEachBoard(curX, curY, chk, dir);
      paintEachBoard(curX, curY, chk, getRight(dir));
    } else if (curMode == 4) {
      paintEachBoard(curX, curY, chk, dir);
      paintEachBoard(curX, curY, chk, getLeft(dir));
      paintEachBoard(curX, curY, chk, getRight(dir));
    } else if (curMode == 5) {
      paintEachBoard(curX, curY, chk, dir);
      paintEachBoard(curX, curY, chk, getRight(dir));
      paintEachBoard(curX, curY, chk, getLeft(dir));
      paintEachBoard(curX, curY, chk, getOpposite(dir));
    }
  }
}

void solve(int cctvIdx) {
  if (cctvIdx == cctvCnt) {
    // Paint board by -10;
    paintBoard(-10);
    // Get unpainted num
    int left = howManyLeft();
    // Unpaint board
    unpaintBoard(-10);
    // ans vs unpainted
    if (left < ans)
      ans = left;

    return;
  }
  for (int i = 1; i < 5; i++) {
    board[cctv[cctvIdx].x][cctv[cctvIdx].y][1] = i;
    solve(cctvIdx + 1);
    board[cctv[cctvIdx].x][cctv[cctvIdx].y][1] = 0;
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  // run();

  cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      cin >> board[i][j][0];
      if (board[i][j][0] > 0 && board[i][j][0] < 6)
        cctv[cctvCnt++] = {i, j, board[i][j][0]};
    }

  solve(0);

  cout << ans << '\n';

  return 0;
}
