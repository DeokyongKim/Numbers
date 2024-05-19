#include <iostream>
#define WHITE 0
#define RED 1
#define BLUE 2
#define ENDTURN 1000
#define ENDPIECE 4

using namespace std;

typedef struct _PIECE {
  int row;
  int col;
  int dir;
  int prev;
  int next;
} PIECE;

typedef struct _DIRECTION {
  int x;
  int y;
} DIRECTION;

DIRECTION direction[5] = {{0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0}};

int n, k;

int board[15][15];
int lastPieceBoard[15][15];

PIECE piece[15];

int turn = 1;

void white(int idx) {
  int x = piece[idx].row;
  int y = piece[idx].col;
  int nx = x + piece[idx].dir.x;
  int ny = y + piece[idx].dir.y;
 
  for (int curIdx = idx; piece[curIdx].next != 0; curIdx = piece[curIdx].next) {
    piece[curIdx].row = nx;
    piece[curIdx].col = ny;
  }

  int moveIdx = lastPieceBoard[nx][ny];
  int prevIdx = piece[idx].prev;

  if (moveIdx != 0) {
    lastPieceBoard[nx][ny] = lastPieceBoard[x][y];
    piece[moveIdx].next = idx;
    piece[idx].prev = moveIdx;
  } else {
    lastPieceBoard[nx][ny] = lastPieceBoard[x][y];
    piece[idx].prev = 0;
  }

  if (prevIdx != 0) {
    lastPieceBoard[x][y] = prevIdx;
    piece[prevIdx].next = 0;
  } else {
    lastPieceBoard[x][y] = 0;
  }
}

void red(int idx) {
  
}

void move() {
  for (int i = 1; i <= k; i++) {
    int nx = piece[i].row + piece[i].dir.x;
    int ny = piece[i].col + piece[i].dir.y;

    if (board[nx][ny] == WHITE) {
      white(i);
    } else if (board[nx][ny] == RED) {
      red(i);
    } else if (board[nx][ny] == BLUE) {
      blue(i);
    }
  }
}

bool isEnd() {
  for (int i = 1; i <= k; i++) {
    int num = 0;
    for (int idx = i; piece[idx].next != 0; idx = piece[idx].next) num++;
    if (num >= 4) return true;
  }
  return false;
}

int run() {
  cin >> n >> k;

  for (int i = 0; i <= n+1; i++)
    for (int j = 0; j <= n+1; j++) {
      if (i == 0 || i == n+1 || j == 0 || j == n+1) {
        board[i][j] = BLUE;
      } else {
        cin >> board[i][j];
      }
    }

  for (int i = 1; i <= k; i++) {
    cin >> piece[i].row >> piece[i].col >> piece[i].dir;
    lastPieceBoard[piece[i].row][piece[i].col] = i;
    piece[i].prev = 0;
    piece[i].next = 0;
  }

  for (; turn <= ENDTURN; turn++) {
    move();
    if(isEnd()) break;
  }

  if (turn > ENDTURN) cout << -1 << '\n';

  return 0;
}