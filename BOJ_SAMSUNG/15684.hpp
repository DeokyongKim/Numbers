// Gold

#include <iostream>

using namespace std;

int n, m, h;
bool did = false;

int board[40][20];

bool checkEachLine(int lineIdx) {
  int curLine = lineIdx;

  for (int i = 1; i <= h; i++) {
    if (board[i][curLine])
      curLine = board[i][curLine];
  }

  return curLine == lineIdx;
}

bool checkAllLine() {
  for (int i = 1; i <= n; i++) {
    if (!checkEachLine(i))
      return false;
  }

  return true;
}

void solve(int maxDepth, int add) {
  if (add == maxDepth) {
    if (checkAllLine()) {
      cout << add << '\n';
      exit(0);
    }
    return;
  }

  for (int i = 1; i <= n - 1; i++)
    for (int j = 1; j <= h; j++) {
      if (!board[j][i] && !board[j][i + 1]) {
        board[j][i] = i + 1;
        board[j][i + 1] = i;
        solve(maxDepth, add + 1);
        board[j][i] = 0;
        board[j][i + 1] = 0;
      }

      while (!board[j][i] && !board[j][i + 1])
        j++;
    }
}

int main() {
  freopen("input.txt", "r", stdin);

  cin >> n >> m >> h;

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    board[a][b] = b + 1;
    board[a][b + 1] = b;
  }

  for (int i = 0; i <= 3; i++)
    solve(i, 0);

  cout << -1 << '\n';

  return 0;
}