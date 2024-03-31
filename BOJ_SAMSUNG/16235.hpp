// Gold

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef struct _TREE {
  int x;
  int y;
  int age;
} TREE;

int n, m, end_year, add[15][15], dead[15][15];

int map[15][15];
vector<int> tree[15][15];

bool comp(int a, int b) { return a > b; }

void Spring() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++){
      int k = tree[i][j].size() - 1;
      for (; k >= 0; k--) {
        int curAge = tree[i][j][k];

        if (map[i][j] >= curAge) {
          map[i][j] -= curAge;
          tree[i][j][k]++;
        } else {
          break;
        }
      }

      for (; k >= 0; k--) {
        int curAge = tree[i][j][k];

        dead[i][j] += curAge / 2;
        tree[i][j].erase(tree[i][j].begin() + k);
      }
    }
}

void Summer() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      map[i][j] += dead[i][j];
      dead[i][j] = 0;
    }
}

void Fall() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      for (int k = 0; k < tree[i][j].size(); k++)
        if (tree[i][j][k] % 5 == 0) {
          int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
          int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

          for (int dir = 0; dir < 8; dir++) {
            int x = i + dx[dir];
            int y = j + dy[dir];

            if (x >= 1 && x <= n && y >= 1 && y <= n)
              tree[x][y].push_back(1);
          }
        }
}

void Winter() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      map[i][j] += add[i][j];
}

void Investment() {
  for (int year = 0; year < end_year; year++) {
    Spring();
    Summer();
    Fall();
    Winter();
  }
}

int run() {
  cin >> n >> m >> end_year;

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> add[i][j];

  vector<int> tmp[15][15];
  for (int i = 0; i < m; i++) {
    int tmpX, tmpY, tmpAge;
    cin >> tmpX >> tmpY >> tmpAge;

    tmp[tmpX][tmpY].push_back(tmpAge);
  }

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      sort(tmp[i][j].begin(), tmp[i][j].end(), comp);

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      for (int k = 0; k < tmp[i][j].size(); k++)
        tree[i][j].push_back(tmp[i][j][k]);

  // initialize
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      map[i][j] = 5;

  Investment();

  int ans = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      ans += tree[i][j].size();

  cout << ans << '\n';

  return 0;
}