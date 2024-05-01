#include <iostream>

using namespace std;

typedef struct _SHARK {
  int x;
  int y;
  int vel;
  int dir;
  int size;
} SHARK;

int row, column, numOfSharks, sea[110][110];
int copySea[110][110] = {0, };

int isSharkAlive[10010];

SHARK sharks[10010];

int fisherCol = -1;

int dirX[4] = {-1, 1, 0, 0};
int dirY[4] = {0, 0, 1, -1};

int ans;

int getOppositeDir(int dir) {
  if (dir == 1) return 2;
  if (dir == 2) return 1;
  if (dir == 3) return 4;
  if (dir == 4) return 3;

  return -1;
}

int run() {
  cin >> row >> column >> numOfSharks;

  for (int i = 1; i <= numOfSharks; i++) {
    cin >> sharks[i].x >> sharks[i].y >> sharks[i].vel >> sharks[i].dir >> sharks[i].size;
    sharks[i].x--;
    sharks[i].y--;
    sea[sharks[i].x][sharks[i].y] = i;
  }
  isSharkAlive[0] = 1;

  while (fisherCol < column) {
    // Act 1
    fisherCol++;

    // Act 2
    for (int j = 0; j < row; j++) {
      int id = sea[j][fisherCol];

      if (id == 0) continue;

      if (!isSharkAlive[id]) {
        isSharkAlive[id] = 1;
        ans += sharks[id].size;
        sea[j][fisherCol] = 0;
        break;
      }
    }

    // Act 3
    for (int i = 1; i <= numOfSharks; i++) {
      if (!isSharkAlive[i]) {
        int nx = sharks[i].x + dirX[sharks[i].dir - 1] * sharks[i].vel;
        int ny = sharks[i].y + dirY[sharks[i].dir - 1] * sharks[i].vel;

        int rowCut = row * 2 - 2;
        int colCut = column * 2 - 2;

        if (rowCut == 0) rowCut = 1;
        if (colCut == 0) colCut = 1;

        // nx, ny가 음수일 때
        if (nx < 0) {
          int tmpx = nx * -1;
          int tmp = tmpx/rowCut;
          nx += (tmp + 2) * rowCut;
        }
        if (ny < 0) {
          int tmpy = ny * -1;
          int tmp = tmpy/colCut;
          ny += (tmp + 2) * colCut;
        }

        nx = nx % rowCut;
        ny = ny % colCut;

        if (nx >= row) {
          int over = nx % row;
          nx = row - 2 - over; 
          sharks[i].dir = getOppositeDir(sharks[i].dir);
        }
        if (ny >= column) {
          int over = ny % column;
          ny = column - 2 - over; 
          sharks[i].dir = getOppositeDir(sharks[i].dir);
        }

        sea[sharks[i].x][sharks[i].y] = 0;

        if (copySea[nx][ny] != 0) {
          int id = copySea[nx][ny];

          if (sharks[id].size < sharks[i].size) {
            isSharkAlive[id] = 1;
            copySea[nx][ny] = i;
            sharks[i].x = nx;
            sharks[i].y = ny;
          }
        } else {
          copySea[nx][ny] = i;
          sharks[i].x = nx;
          sharks[i].y = ny;
        }
      }
    }

    // Act 4.5 (sea <- copySea)
    for (int i = 0; i < row; i++)
      for (int j = 0; j < column; j++){
        sea[i][j] = copySea[i][j];
        copySea[i][j] = 0;  
      }
  }

  cout << ans << '\n';

  return 0;
}