#include <iostream>

using namespace std;

typedef struct _DUST {
  int x;
  int y;
  int quantity;
} DUST;

int r, c, t;

int board[60][60];

int airUp, airDown;
DUST dust[3000];

int run() {
  cin >> r >> c >> t;

  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++) {
      cin >> board[i][j];

      if (map[i][j] != 0) {
        
      }
    }
}