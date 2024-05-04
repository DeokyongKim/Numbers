#include <iostream>

using namespace std;

typedef struct _SHARK {
  int x;
  int y;
  int vel;
  int dir;
  int size;
  bool alive;
} SHARK;

typedef struct _DIRECTION {
  int x;
  int y;
} DIRECTION;

DIRECTION direction[4] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

int getOppositeDirection(int dir) {
  if (dir == 1) return 2;
  if (dir == 2) return 1;
  if (dir == 3) return 4;
  if (dir == 4) return 3;
}

int row, col, sharkNum, sea[110][110];

SHARK sharks[10010];

int fisher = -1, ans;

int run() {
  cin >> row >> col >> sharkNum;

  for (int i = 1; i <= sharkNum; i++) {
    cin >> sharks[i].x >> sharks[i].y >> sharks[i].vel >> sharks[i].dir >> sharks[i].size;
    sharks[i].x--;
    sharks[i].y--;
    sharks[i].alive = true;
    sea[sharks[i].x][sharks[i].y] = i;
  }

  while (fisher < col) {
    // 1. fisher move
    fisher++;

    // 2. fishing
    for (int i = 0; i < row; i++) {
      int id = sea[i][fisher];
      if (id && sharks[id].alive) {
        ans += sharks[id].size;
        sharks[id].alive = false;
        sea[sharks[id].x][sharks[id].y] = 0;
        break;
      }
    }

    // 3. sharks move
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        sea[i][j] = 0;

    for (int i = 1; i <= sharkNum; i++) {
      if (sharks[i].alive) {
        int newRow = row * 2 - 2;
        int newCol = col * 2 - 2;

        int velX = sharks[i].vel % newRow;
        int velY = sharks[i].vel % newCol;

        int nx = sharks[i].x + velX * direction[sharks[i].dir - 1].x;
        int ny = sharks[i].y + velY * direction[sharks[i].dir - 1].y;

        nx = (nx < 0 ? nx + newRow : nx);
        ny = (ny < 0 ? ny + newCol : ny);

        nx %= newRow;
        ny %= newCol;

        if (nx >= row) {
          nx = row - 1 - (nx - (row - 1));
          sharks[i].dir = getOppositeDirection(sharks[i].dir);
        }
        if (ny >= col) {
          ny = col - 1 - (ny - (col - 1));
          sharks[i].dir = getOppositeDirection(sharks[i].dir);
        }

        sharks[i].x = nx;
        sharks[i].y = ny;
        if (sea[nx][ny]) {
          if (sharks[sea[nx][ny]].size < sharks[i].size) {
            sharks[sea[nx][ny]].alive = false;
            sea[nx][ny] = i;
          } else {
            sharks[i].alive = false;
          }
        } else {
          sea[nx][ny] = i;
        }
      }
    }
  }

  cout << ans << '\n';

  return 0;
}


// #include <iostream>

// using namespace std;

// typedef struct _SHARK {
//   int x;
//   int y;
//   int vel;
//   int dir;
//   int size;
// } SHARK;

// int row, column, numOfSharks, sea[110][110];

// int isSharkAlive[10010];

// SHARK sharks[10010];

// int fisherCol = -1;

// int dirX[4] = {-1, 1, 0, 0};
// int dirY[4] = {0, 0, 1, -1};

// int ans;

// int getOppositeDir(int dir) {
//   if (dir == 1) return 2;
//   if (dir == 2) return 1;
//   if (dir == 3) return 4;
//   if (dir == 4) return 3;

//   return -1;
// }

// int run() {
//   cin >> row >> column >> numOfSharks;

//   for (int i = 1; i <= numOfSharks; i++) {
//     cin >> sharks[i].x >> sharks[i].y >> sharks[i].vel >> sharks[i].dir >> sharks[i].size;
//     sharks[i].x--;
//     sharks[i].y--;
//     sea[sharks[i].x][sharks[i].y] = i;
//   }
//   isSharkAlive[0] = 1;

//   while (fisherCol < column) {
//     // Act 1
//     fisherCol++;

//     // Act 2
//     for (int j = 0; j < row; j++) {
//       int id = sea[j][fisherCol];

//       if (id == 0) continue;

//       if (!isSharkAlive[id]) {
//         isSharkAlive[id] = 1;
//         ans += sharks[id].size;
//         sea[j][fisherCol] = 0;
//         break;
//       }
//     }

//     // Act 3
//     for (int i = 0; i < row; i++)
//       for (int j = 0; j < column; j++)
//         sea[sharks[i].x][sharks[i].y] = 0;

//     for (int i = 1; i <= numOfSharks; i++) {
//       if (!isSharkAlive[i]) {
//         int rowCut = row * 2 - 2;
//         int colCut = column * 2 - 2;

//         if (rowCut == 0) rowCut = 1;
//         if (colCut == 0) colCut = 1;

//         int speedX = sharks[i].vel % rowCut; 
//         int speedY = sharks[i].vel % colCut; 

//         int nx = sharks[i].x + dirX[sharks[i].dir - 1] * (speedX % rowCut);
//         int ny = sharks[i].y + dirY[sharks[i].dir - 1] * (speedY % colCut);

//         // nx, ny가 음수일 때
//         if (nx < 0) {
//           nx += rowCut;
//         }
//         if (ny < 0) {
//           ny += colCut;
//         }

//         nx = nx % rowCut;
//         ny = ny % colCut;

//         if (nx >= row) {
//           int over = nx % row;
//           nx = row - 2 - over; 
//           sharks[i].dir = getOppositeDir(sharks[i].dir);
//         }
//         if (ny >= column) {
//           int over = ny % column;
//           ny = column - 2 - over; 
//           sharks[i].dir = getOppositeDir(sharks[i].dir);
//         }

//         if (sea[nx][ny] != 0) {
//           int id = sea[nx][ny];

//           if (sharks[id].size < sharks[i].size) {
//             isSharkAlive[id] = 1;
//             sea[nx][ny] = i;
//             sharks[i].x = nx;
//             sharks[i].y = ny;
//           }
//         } else {
//           sea[nx][ny] = i;
//           sharks[i].x = nx;
//           sharks[i].y = ny;
//         }
//       }
//     }
//   }

//   cout << ans << '\n';

//   return 0;
// }