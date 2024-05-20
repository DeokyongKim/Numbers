#include <iostream>
#define WHITE 0
#define RED 1
#define BLUE 2
#define ENDTURN 3
#define ENDPIECE 4

using namespace std;

typedef struct _PIECE {
  int row;
  int col;
  int dir;
} PIECE;

typedef struct _DIRECTION {
  int x;
  int y;
} DIRECTION;

DIRECTION direction[5] = {{0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0}};

int n, k;

int boardColor[15][15];
int board[15][15][13];
int boardNum[15][15];

PIECE piece[15];

int turn = 1;

void printBoardNum() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << boardNum[i][j] << ' '; 
    }
    cout << '\n';
  }
  cout << "^NUMBER==\n";
}

void printPieces() {
  for (int i = 1; i <= k; i++) {
    cout << i << ": " << piece[i].row << ' ' << piece[i].col << ' ' << piece[i].dir << '\n';
  }
  cout << "P-------------\n";
}

void printBoard() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      bool did = false;
      for (int k = 0; k < boardNum[i][j]; k++) {
        cout << board[i][j][k];
        did = true;
      }
      if (!did) cout << 0;
      cout << " ";
    }
    cout << '\n';
  }
  cout << "========\n";

  printBoardNum();

  printPieces();
}

int findPieceIndexInBoard(int pieceIndex) {
  int x = piece[pieceIndex].row;
  int y = piece[pieceIndex].col;

  for (int i = 0; i < boardNum[x][y]; i++)
    if (board[x][y][i] == pieceIndex) return i;
}

void white(int idx) {
  int x = piece[idx].row;
  int y = piece[idx].col;
  int nx = x + direction[piece[idx].dir].x;
  int ny = y + direction[piece[idx].dir].y;
 
  int startIdx = findPieceIndexInBoard(idx);
  int endIdx = boardNum[x][y];

  for (int i = startIdx; i < endIdx; i++) {
    piece[i].row = nx;
    piece[i].col = ny;

    board[nx][ny][boardNum[nx][ny]++] = board[x][y][i];
    board[x][y][i] = 0;
    boardNum[x][y]--;
  }
}

void red(int idx) {
  int x = piece[idx].row;
  int y = piece[idx].col;
  int nx = x + direction[piece[idx].dir].x;
  int ny = y + direction[piece[idx].dir].y;
 
  int startIdx = findPieceIndexInBoard(idx);
  int endIdx = boardNum[x][y];

  for (int i = endIdx-1; i >= startIdx; i--) {
    piece[i].row = nx;
    piece[i].col = ny;

    board[nx][ny][boardNum[nx][ny]++] = board[x][y][i];
    board[x][y][i] = 0;
    boardNum[x][y]--;
  }
}

int getOppositeDirectionIndex(int dir) {
  if (dir == 1) return 2;
  if (dir == 2) return 1;
  if (dir == 3) return 4;
  if (dir == 4) return 3;

  return 0;
}

void blue(int idx) {
  int x = piece[idx].row;
  int y = piece[idx].col;
  int nDir = getOppositeDirectionIndex(piece[idx].dir);
  piece[idx].dir = nDir;
  int nx = x + direction[nDir].x;
  int ny = y + direction[nDir].y;

  if (boardColor[nx][ny] == BLUE) return;
  else if (boardColor[nx][ny] == WHITE) white(idx);
  else if (boardColor[nx][ny] == RED) red(idx);
}

void move() {
  for (int i = 1; i <= k; i++) {
    int nx = piece[i].row + direction[piece[i].dir].x;
    int ny = piece[i].col + direction[piece[i].dir].y;

    // cout << piece[i].row << ' ' << piece[i].col << ' ' << piece[i].dir << '\n';

    if (boardColor[nx][ny] == WHITE) {
      cout << "WHITE!!\n";

      white(i);
    } else if (boardColor[nx][ny] == RED) {
      cout << "RED!!\n";

      red(i);
    } else if (boardColor[nx][ny] == BLUE) {
      cout << "BLUE!!\n";
      blue(i);
    }

    printBoard();
  }
}

bool isEnd() {
  for (int i = 1; i <= k; i++) {
    int x = piece[i].row;
    int y = piece[i].col;

    if (boardNum[x][y] >= 4) return true;
  }
  return false;
}

int run() {
  cin >> n >> k;

  for (int i = 0; i <= n+1; i++)
    for (int j = 0; j <= n+1; j++) {
      if (i == 0 || i == n+1 || j == 0 || j == n+1) {
        boardColor[i][j] = BLUE;
      } else {
        cin >> boardColor[i][j];
      }
    }

  for (int i = 1; i <= k; i++) {
    cin >> piece[i].row >> piece[i].col >> piece[i].dir;
    board[piece[i].row][piece[i].col][0] = i;
    boardNum[piece[i].row][piece[i].col] = 1;
  }

  for (int i = 0; i <= n+1; i++) {
    for (int j = 0; j <= n+1; j++) {
      cout << boardColor[i][j] << ' ';
    }
    cout << '\n';
  }

  printBoard();
  cout << "--------------------\n\n";

  for (; turn <= ENDTURN; turn++) {
    move();

    cout << "--------------------\n\n";

    if(isEnd()) {
      cout << turn << '\n';
      return 0;
    }
  }

  if (turn > ENDTURN) cout << -1 << '\n';

  return 0;
}