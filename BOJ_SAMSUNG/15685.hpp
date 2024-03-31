// Gold

#include <iostream>
#include <vector>

using namespace std;

int n, board[110][110];

int getSquareNumbers() {
  int num = 0;

  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 100; j++)
      if (board[i][j] && board[i + 1][j] && board[i][j + 1] &&
          board[i + 1][j + 1])
        num++;

  return num;
}

void drawDragonCurve(int x, int y, int dir, int gen, int id) {
  int dx[4] = {1, 0, -1, 0};
  int dy[4] = {0, -1, 0, 1};

  vector<int> v;

  v.push_back(dir);
  for (int i = 0; i < gen; i++) {
    int len = v.size();
    for (int j = len - 1; j >= 0; j--) {
      v.push_back((v[j] + 1) % 4);
    }
  }

  int curX = x, curY = y;
  board[curX][curY] = id;
  for (int i = 0; i < v.size(); i++) {
    curX += dx[v[i]];
    curY += dy[v[i]];
    board[curX][curY] = id;
  }
}

int main() {
  freopen("input.txt", "r", stdin);

  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y, dir, gen;
    cin >> x >> y >> dir >> gen;
    drawDragonCurve(x, y, dir, gen, i + 1);
  }

  cout << getSquareNumbers() << '\n';
}