#include <iostream>

using namespace std;

int n, board[520][520], route[520][520];

int ans;

void move(int fromX, int fromY, int toX, int toY) {
  int dirX = toX - fromX;
  int dirY = toY - fromY;

  int val = board[toX][toY];

  int waste = 0;

  if (dirX == 0 && dirY == 1) {
    // dir: ->
    board[toX-1][toY-1] += (int)(val * 0.01);
    waste += (int)(val * 0.01);
    board[toX+1][toY-1] += (int)(val * 0.01);
    waste += (int)(val * 0.01);
    board[toX-2][toY] += (int)(val * 0.02);
    waste += (int)(val * 0.02);
    board[toX+2][toY] += (int)(val * 0.02);
    waste += (int)(val * 0.02);
    board[toX-1][toY] += (int)(val * 0.07);
    waste += (int)(val * 0.07);
    board[toX+1][toY] += (int)(val * 0.07);
    waste += (int)(val * 0.07);
    board[toX-1][toY+1] += (int)(val * 0.1);
    waste += (int)(val * 0.1);
    board[toX+1][toY+1] += (int)(val * 0.1);
    waste += (int)(val * 0.1);
    board[toX][toY+2] += (int)(val * 0.05);
    waste += (int)(val * 0.05);

    int alpha = val - waste;
    board[toX][toY + 1] += alpha;
  } else if (dirX == 0 && dirY == -1) {
    // dir : <-
    board[toX-1][toY+1] += (int)(val * 0.01);
    waste += (int)(val * 0.01);
    board[toX+1][toY+1] += (int)(val * 0.01);
    waste += (int)(val * 0.01);
    board[toX-2][toY] += (int)(val * 0.02);
    waste += (int)(val * 0.02);
    board[toX+2][toY] += (int)(val * 0.02);
    waste += (int)(val * 0.02);
    board[toX-1][toY] += (int)(val * 0.07);
    waste += (int)(val * 0.07);
    board[toX+1][toY] += (int)(val * 0.07);
    waste += (int)(val * 0.07);
    board[toX-1][toY-1] += (int)(val * 0.1);
    waste += (int)(val * 0.1);
    board[toX+1][toY-1] += (int)(val * 0.1);
    waste += (int)(val * 0.1);
    board[toX][toY-2] += (int)(val * 0.05);
    waste += (int)(val * 0.05);

    int alpha = val - waste;
    board[toX][toY-1] += alpha;
  } else if (dirX == -1 && dirY == 0) {
    // dir: ^
    board[toX+1][toY-1] += (int)(val * 0.01);
    waste += (int)(val * 0.01);
    board[toX+1][toY+1] += (int)(val * 0.01);
    waste += (int)(val * 0.01);
    board[toX][toY-2] += (int)(val * 0.02);
    waste += (int)(val * 0.02);
    board[toX][toY+2] += (int)(val * 0.02);
    waste += (int)(val * 0.02);
    board[toX][toY-1] += (int)(val * 0.07);
    waste += (int)(val * 0.07);
    board[toX][toY+1] += (int)(val * 0.07);
    waste += (int)(val * 0.07);
    board[toX-1][toY-1] += (int)(val * 0.1);
    waste += (int)(val * 0.1);
    board[toX-1][toY+1] += (int)(val * 0.1);
    waste += (int)(val * 0.1);
    board[toX-2][toY] += (int)(val * 0.05);
    waste += (int)(val * 0.05);

    int alpha = val - waste;
    board[toX - 1][toY] += alpha;
  } else if (dirX == 1 && dirY == 0) {
    // dir: v
    board[toX-1][toY-1] += (int)(val * 0.01);
    waste += (int)(val * 0.01);
    board[toX-1][toY+1] += (int)(val * 0.01);
    waste += (int)(val * 0.01);
    board[toX][toY-2] += (int)(val * 0.02);
    waste += (int)(val * 0.02);
    board[toX][toY+2] += (int)(val * 0.02);
    waste += (int)(val * 0.02);
    board[toX][toY-1] += (int)(val * 0.07);
    waste += (int)(val * 0.07);
    board[toX][toY+1] += (int)(val * 0.07);
    waste += (int)(val * 0.07);
    board[toX+1][toY-1] += (int)(val * 0.1);
    waste += (int)(val * 0.1);
    board[toX+1][toY+1] += (int)(val * 0.1);
    waste += (int)(val * 0.1);
    board[toX+2][toY] += (int)(val * 0.05);
    waste += (int)(val * 0.05);

    int alpha = val - waste;
    board[toX+1][toY] += alpha;
  }

  board[toX][toY] = 0;
}

void printRoute() {
  for (int i = 0; i < n + 4; i++) {
    for (int j = 0; j < n + 4; j++) {
      cout << route[i][j] << ' ' ;
    }
    cout << '\n';
  }
  cout << '\n';
}

void solve() {
  int startX = n/2 + 2, startY = n/2 + 2;
  route[startX][startY] = 1;

  int dir = -1;

  for (int len = 1; len < n; len++) {
    // row move
    for (int row = 0; row < len; row++) {
      move(startX, startY, startX, startY + dir);
      startY += dir;
    }
    // col move
    for (int col = 0; col < len; col++) {
      move(startX, startY, startX - dir, startY);
      startX -= dir;
    }

    // change dir
    dir *= -1;
  }

  for (int row = 0; row < n-1; row++) {
    move(startX, startY, startX, startY - 1);
    startY--;
  }

}

int run() {
  cin >> n;
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i+2][j+2];
    }
  }

  solve();

  for (int i = 0; i < n + 4; i++) {
    for (int j = 0; j < n + 4; j++) {
      if (i >= 2 && i < n + 2 && j >= 2 && j < n + 2) continue;
      ans += board[i][j];
    }
  }

  cout << ans << '\n';

  return 0;
}