// Gold

#include <iostream>
#include <string.h>

using namespace std;

int n, board[60][60], visited[60][60], l, r, day, unionNum;

int unionPopulation[3000], unionCountries[3000];

bool did;

int abs(int number) { return number >= 0 ? number : -1 * number; }

void initialize() {
  memset(unionPopulation, 0, n * n * sizeof(int));
  memset(unionCountries, 0, n * n * sizeof(int));

  for (int i = 0; i < n; i++)
    memset(visited[i], 0, n * sizeof(int));

  unionNum = 1;
  did = false;
}

void markEachUnion(int x, int y) {
  visited[x][y] = unionNum;

  int dx[4] = {1, 0, -1, 0};
  int dy[4] = {0, 1, 0, -1};

  for (int dir = 0; dir < 4; dir++) {
    int curX = x + dx[dir];
    int curY = y + dy[dir];

    if (curX >= 0 && curX < n && curY >= 0 && curY < n) {
      if (visited[curX][curY])
        continue;

      int sub = abs(board[x][y] - board[curX][curY]);
      if (sub >= l && sub <= r) {
        markEachUnion(curX, curY);
      }
    }
  }
}

void markUnion() {
  int dx[4] = {1, 0, -1, 0};
  int dy[4] = {0, 1, 0, -1};

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (!visited[i][j]) {
        bool found = false;

        for (int dir = 0; dir < 4; dir++) {
          int curX = i + dx[dir];
          int curY = j + dy[dir];

          if (curX >= 0 && curX < n && curY >= 0 && curY < n) {
            int sub = abs(board[i][j] - board[curX][curY]);
            if (sub >= l && sub <= r) {
              markEachUnion(i, j);
              found = true;
              break;
            }
          }
        }

        if (found) {
          did = true;
          unionNum++;
          continue;
        }
      }
}

void averaging() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (visited[i][j]) {
        unionPopulation[visited[i][j]] += board[i][j];
        unionCountries[visited[i][j]]++;
      }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (visited[i][j])
        board[i][j] =
            unionPopulation[visited[i][j]] / unionCountries[visited[i][j]];
}

int main() {
  freopen("input.txt", "r", stdin);

  cin >> n >> l >> r;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> board[i][j];

  while (true) {
    initialize();

    markUnion();

    averaging();

    if (!did)
      break;

    day++;
  }

  cout << day << '\n';
}