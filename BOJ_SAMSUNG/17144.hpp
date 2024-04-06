#include <iostream>
#include <vector>

using namespace std;

typedef struct _AIRCONDITIONER {
  int x;
  int y;
} AIRCONDITIONER;

int r, c, t;

int board[60][60];

AIRCONDITIONER airCon[2];

void ventilation() {
  int addition[60][60] = {0, };
  
  // dust diffusion
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      if (board[i][j] > 0) {
        int quantity = 0;
        int quality = board[i][j] / 5;

        int dx[4] = {1, 0, -1 ,0};
        int dy[4] = {0, 1, 0, -1};
        for (int dir = 0; dir < 4; dir++) {
          int nx = i + dx[dir];
          int ny = j + dy[dir];

          if (nx >= 0 && nx < r && ny >= 0 && ny < c && board[nx][ny] != -1) {
            quantity++;
            addition[nx][ny] += quality;
          }
        }

        board[i][j] -= quality * quantity;
      }
  
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      board[i][j] += addition[i][j];

  // ventilation
  // counterclockwise
  // left
  for (int i = airCon[0].x - 1; i > 0; i--) board[i][0] = board[i-1][0];
  // up
  for (int i = 0; i < c-1; i++) board[0][i] = board[0][i + 1];
  // right
  for (int i = 0; i <= airCon[0].x; i++) board[i][c-1] = board[i+1][c-1];
  // down
  for (int i = c-1; i > 0; i--) board[airCon[0].x][i] = board[airCon[0].x][i-1];
  board[airCon[0].x][1] = 0;

  // clockwise
  // left
  for (int i = airCon[1].x + 1; i < r-1; i++) board[i][0] = board[i+1][0];
  // down
  for (int i = 0; i < c-1; i++) board[r-1][i] = board[r-1][i+1];
  // right
  for (int i = r-1; i > airCon[1].x; i--) board[i][c-1] = board[i-1][c-1];
  // up
  for (int i = c-1; i > 0; i--) board[airCon[1].x][i] = board[airCon[1].x][i-1];
  board[airCon[1].x][1] = 0;
}

int run() {
  cin >> r >> c >> t;
  airCon[0] = {0, 0};
  airCon[1] = {0, 0};

  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++) {
      cin >> board[i][j];

      if (board[i][j] == -1) {
        if (airCon[0].x == 0) {
          airCon[0].x = i;
          airCon[0].y = j;
        } else {
          airCon[1].x = i;
          airCon[1].y = j;
        }
      }
    }

  for (int workingTime = 0; workingTime < t; workingTime++) {
    ventilation();
  }

  int ans = 0;
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      if (board[i][j] > 0)
        ans += board[i][j];

  cout << ans << '\n';

  return 0;
}