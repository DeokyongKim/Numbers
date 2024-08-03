#include <iostream>
#define MAX 0x7fffffff

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int n, population[25][25], difference = MAX;

bool isOverBoundery(int x, int y, int l, int m) {
  if (x - l - m < 0) return true;
  if (y - m < 0) return true;
  if (y + l >= n) return true;

  return false;
}

void solve() {
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      for (int l = 1; l < n; l++) {
        for (int m = 1; m < n; m++) {
          if (isOverBoundery(x, y, l, m)) continue;

          int board[25][25] = {0, }, eachPopulation[10] = {0, };

          for (int a = 0; a < n; a++) {
            for (int b = 0; b < n; b++) {
              if (a < x-m && b <= y+l-m && a+b < x+y-2*m) {
                board[a][b] = 1;
              } else if (a <= x-l && b > y+l-m && b-a > y-x+2*l) {
                board[a][b] = 2;
              } else if (a >= x-m && b < y && a-b > x-y) {
                board[a][b] = 3;
              } else if (a > x-l && b >= y && a+b > x+y) {
                board[a][b] = 4;
              }
            }
          }

          for (int a = 0; a < n; a++) {
            for (int b = 0; b < n; b++) {
              eachPopulation[board[a][b]] += population[a][b];
            }
          }

          int min = MAX, max = 0;
          for (int each = 0; each < 5; each++) {
            if (eachPopulation[each] < min) min = eachPopulation[each];
            if (eachPopulation[each] > max) max = eachPopulation[each];
          }

          if (max - min < difference) {
          
            // for (int row = 0; row < n; row++) {
            //   for (int col = 0; col < n; col++) {
            //     cout << board[row][col] << ' ';
            //   }
            //   cout << '\n';
            // }
            // cout << '\n';

            difference = max - min;  
          }
        }
      }
    }
  }
}

int run() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> population[i][j];
    }
  }

  solve();

  cout << difference << '\n';

  return 0;
}