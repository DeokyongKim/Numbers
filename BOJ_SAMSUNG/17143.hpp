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
}

void printSea() {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      cout << sea[i][j] << ' ' ;
    }
    cout << '\n';
  }
  cout << '\n';
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

    printSea();

  while (fisherCol < column) {
    // Act 1
    fisherCol++;

    // Act 2
    for (int i = 0; i < column; i++) {
      bool got = false;
      for (int j = 0; j < row; j++) {
        int id = sea[j][i];

        if (id == 0) continue;

        if (!isSharkAlive[id]) {
          got = true;
          isSharkAlive[id] = 1;
          ans += sharks[id].size;
          sea[j][i] = 0;
          break;
        }
      }
      if (got) break;
    }

    // Act 3
    for (int i = 1; i <= numOfSharks; i++) {
      if (!isSharkAlive[i]) {
        int nx = sharks[i].x + dirX[sharks[i].dir - 1] * sharks[i].vel;
        int ny = sharks[i].y + dirY[sharks[i].dir - 1] * sharks[i].vel;

        int rowCut = row * 2 - 2;
        int colCut = column * 2 - 2;

        // TODO: nx, ny가 음수일 때 해결하기
        if (nx < 0) nx += rowCut;
        if (ny < 0) ny += colCut;

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
        if (sea[nx][ny] != 0) {
          int id = sea[nx][ny];
          if (sharks[id].size < sharks[i].size) {
            isSharkAlive[id] = 1;
            sea[nx][ny] = i;
          }
        } else {
          sea[nx][ny] = i;
        }
      }
    }

    printSea();
  }

  cout << ans << '\n';

  return 0;
}