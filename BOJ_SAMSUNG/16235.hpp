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
    for (int j = 1; j <= n; j++)
      for (int k = tree[i][j].size() - 1; k >= 0; k--) {
        int curAge = tree[i][j][k];

        if (map[i][j] >= curAge) {
          map[i][j] -= curAge;
        } else {
          dead[i][j] += curAge / 2;
          tree[i][j].erase(tree[i][j].begin() + k);
        }
      }
}

void Summer() {
  
}

void Investment() {
  for (int year = 0; year < end_year; year++) {
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
}