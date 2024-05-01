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

int isSharkAlive[10010] = {0, };

SHARK sharks[10010];

int fisherCol = -1;

int run() {
  cin >> row >> column >> numOfSharks;

  for (int i = 0; i < numOfSharks; i++) {
    cin >> sharks[i].x >> sharks[i].y >> sharks[i].vel >> sharks[i].dir >> sharks[i].size;
  }


  while (fisherCol < column) {
    // Act 1
    fisherCol++;


  }

  return 0;
}