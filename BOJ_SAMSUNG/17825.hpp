#include <iostream>
#define TURN 10
#define PIECENUMBER 4

using namespace std;

typedef struct _PIECE {
  int idx;
  int route;
} PIECE;

int dice[TURN];

int route[4][55];

int board[4][55] = {
  {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, -1},
  {0, 2, 4, 6, 8, 10, 13, 16, 19, 25, 30, 35, 40, -1},
  {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 25, 30, 35, 40, -1},
  {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 28, 27, 26, 25, 30, 35, 40, -1}
};

int ans = 0;

void solve(int idx, PIECE piece[4], int score) {
  if (idx == TURN) {
    if (ans < score) {
      ans = score;
    }
    return;
  }

  PIECE curPieceArray[PIECENUMBER];

  for (int i = 0; i < PIECENUMBER; i++) curPieceArray[i] = {piece[i].idx, piece[i].route};

  for (int pieceIdx = 0; pieceIdx < PIECENUMBER; pieceIdx++) {
    PIECE curPiece = curPieceArray[pieceIdx];

    int curDice = dice[idx];

    int nextPieceIdx = curPiece.idx + curDice;

    curPieceArray[pieceIdx].idx = nextPieceIdx;
    if (curPiece.route == 0) {
      if (nextPieceIdx == 5) {
        curPieceArray[pieceIdx].route = 1;
        if (!route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] || route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] == -1) {
          route[curPiece.route][curPiece.idx] = 0;
          route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] = 1;
          int plusScore = board[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] < 0 ? 0 : board[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx];
          solve(idx+1, curPieceArray, score + plusScore);
          route[curPiece.route][curPiece.idx] = 1;
          route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] = 0;
          }
        curPieceArray[pieceIdx].route = 0;
      } else if (nextPieceIdx == 10) {
        curPieceArray[pieceIdx].route = 2;
        if (!route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] || route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] == -1) {
          route[curPiece.route][curPiece.idx] = 0;
          route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] = 1;
          int plusScore = board[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] < 0 ? 0 : board[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx];
          solve(idx+1, curPieceArray, score + plusScore);
          route[curPiece.route][curPiece.idx] = 1;
          route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] = 0;
          }
        curPieceArray[pieceIdx].route = 0;
      } else if (nextPieceIdx == 15) {
        curPieceArray[pieceIdx].route = 3;
        if (!route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] || route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] == -1) {
          route[curPiece.route][curPiece.idx] = 0;
          route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] = 1;
          int plusScore = board[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] < 0 ? 0 : board[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx];
          solve(idx+1, curPieceArray, score + plusScore);
          route[curPiece.route][curPiece.idx] = 1;
          route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] = 0;
          }
        curPieceArray[pieceIdx].route = 0;
      } else {
        if (!route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] || route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] == -1) {
          route[curPiece.route][curPiece.idx] = 0;
          route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] = 1;
          int plusScore = board[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] < 0 ? 0 : board[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx];
          solve(idx+1, curPieceArray, score + plusScore);
          route[curPiece.route][curPiece.idx] = 1;
          route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] = 0;
          }
      } 
    } else {
      if (!route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] || route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] == -1) {
        route[curPiece.route][curPiece.idx] = 0;
        route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] = 1;
        int plusScore = board[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] < 0 ? 0 : board[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx];
        solve(idx+1, curPieceArray, score + plusScore);
        route[curPiece.route][curPiece.idx] = 1;
        route[curPieceArray[pieceIdx].route][curPieceArray[pieceIdx].idx] = 0;
      }
    }
    curPieceArray[pieceIdx].idx = curPiece.idx;
  }
}

int run() {
  for (int i = 0; i < TURN; i++) cin >> dice[i];

  PIECE tmpArray[4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};

  solve(0, tmpArray, 0);

  cout << ans << '\n';

  return 0;
}