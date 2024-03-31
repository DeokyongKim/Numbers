// Gold

#include <iostream>

using namespace std;

typedef struct _coordinate {
  int x;
  int y;
} coordinate;

int abs(int num) { return num >= 0 ? num : -1 * num; }

int n, m, board[60][60], hNum, cNum, ans = 0x7fffffff;

coordinate house[110], chicken[20];

int chickToHouse[20][110];

void minimizeChickenDistance(int idx, int added, int visited) {
  if (idx == cNum && added < m)
    return;

  if ((cNum - idx) + added < m)
    return;

  if (added == m) {
    int selected[20] = {
        0,
    };
    int index = 0;
    while (visited) {
      selected[index++] = visited % 2;
      visited = visited >> 1;
    }

    int preAns = 0;
    for (int i = 0; i < hNum; i++) {
      int minDis = 0x7fffffff;
      for (int j = 0; j < cNum; j++)
        if (chickToHouse[j][i] < minDis && selected[j])
          minDis = chickToHouse[j][i];
      preAns += minDis;
    }

    if (ans > preAns)
      ans = preAns;

    return;
  }

  minimizeChickenDistance(idx + 1, added, visited);
  minimizeChickenDistance(idx + 1, added + 1, visited | (1 << idx));
}

int main() {
  freopen("input.txt", "r", stdin);

  cin >> n >> m;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];

      if (board[i][j] == 1)
        house[hNum++] = {i, j};
      if (board[i][j] == 2)
        chicken[cNum++] = {i, j};
    }

  for (int i = 0; i < cNum; i++)
    for (int j = 0; j < hNum; j++) {
      chickToHouse[i][j] =
          abs(chicken[i].x - house[j].x) + abs(chicken[i].y - house[j].y);
    }

  minimizeChickenDistance(0, 0, 0);

  cout << ans << '\n';
}