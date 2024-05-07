#include <iostream>

using namespace std;

int n, board[25][25];

int area[25][25], population[7];

int ans = 0x7fffffff;

void printArea() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << area[i][j] << ' ' ;
    }
    cout << '\n';
  }
  cout << '\n';
}

bool makeBoundary(int x, int y, int d1, int d2) {
  int ax = x + d1, ay = y - d1;
  int bx = x + d2, by = y + d2;
  int cx = x + d1 + d2, cy = y - d1 + d2;
  
  if (ax < 1 || ax > n || bx < 1 || bx > n || cx < 1 || cx > n) return false;

  // Initialize
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      area[i][j] = 0;
    }
  }
  for (int i = 1; i <= 5; i++) population[i] = 0;

  for (int i = 0; i <= d1; i++) {
    area[x + i][y - i] = 5;
    area[x + d2 + i][y + d2 - i] = 5;
  }
  for (int i = 0; i <= d2; i++) {
    area[x + i][y + i] = 5;
    area[x + d1 + i][y - d1 + i] = 5;
  }

  // 1
  for (int i = 1; i < x + d1; i++) {
    for (int j = 1; j <= y; j++) {
      if (area[i][j] == 5) break;
      area[i][j] = 1;
    }
  }

  // 2
  for (int i = 1; i <= x + d2; i++) {
    for (int j = n; j > y; j--) {
      if (area[i][j] == 5) break;
      area[i][j] = 2;
    }
  }
  
  // 3
  for (int i = x + d1; i <= n; i++) {
    for (int j = 1; j < y - d1 + d2; j++) {
      if (area[i][j] == 5) break;
      area[i][j] = 3;
    }
  }

  // 4
  for (int i = x + d2 + 1; i <= n; i++) {
    for (int j = n; j >= y - d1 + d2; j--) {
      if (area[i][j] == 5) break;
      area[i][j] = 4;
    }
  }

  // 5
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (area[i][j] == 0) area[i][j] = 5;
    }
  }

  // calculate poulation
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      population[area[i][j]] += board[i][j];
    }
  }

  // get max and min
  int max = -1, min = 0x7fffffff;
  for (int i = 1; i < 6; i++) {
    if (max < population[i]) max = population[i];
    if (min > population[i]) min = population[i];
  }

  int sub = max - min;
  if (ans > sub) {
    ans = sub;
  }

  return true;
}

int run() {
  // input
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      cin >> board[i][j];
  }

  // makeBoundary(2, 4, 2, 2);
  // return 0;
  
  for (int x = 1; x <= n; x++) {
    for (int y = 1; y <= n; y++) {
      for (int d1 = 1; d1 <= n; d1++) {
        for (int d2 = 1; d2 <= n; d2++) {
          bool done = makeBoundary(x, y, d1, d2);
        }
      }
    }
  }

  cout << ans << '\n';

  return 0;
}