#include <iostream>
#define TURN 10
#define PIECENUMBER 4

using namespace std;

typedef struct _PIECE {
  int idx = 0;
  int route = 0;
} PIECE;

int dice[TURN];

int route[5][55];

int board[5][55] = {
  {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40},
  {10, 13, 16, 19},
  {20, 22, 24},
  {30, 28, 27, 26},
  {25, 30, 35, 40},
};

int boardLen[5] = {21, 4, 3, 4, 4};

int ans = 0;

bool forty = false;

bool isCrossWay(int boardNumberInput) {
  int a = boardNumberInput;
  if (a == 10 || a == 20 || a == 30) return true;
  return false;
}

int getHash(int boardNumberInput) {
  int a = boardNumberInput;
  if (a == 10) return 1;
  if (a == 20) return 2;
  if (a == 30) return 3;
}

void solve(int idx, PIECE piece[4], int score) {
  // cout << "Idx: " << idx << " Piece: " << piece[0].route << ' ' << piece[0].idx << " Score: " << score << '\n';

  if (idx == TURN) {
    if (ans < score) {
      // cout << "SCORE: " << score << '\n';
      ans = score;
    }
    return;
  }

  PIECE tmpPieceArray[PIECENUMBER];

  for (int i = 0; i < PIECENUMBER; i++) tmpPieceArray[i] = {piece[i].idx, piece[i].route};

  for (int pieceIdx = 0; pieceIdx < PIECENUMBER; pieceIdx++) {
    PIECE curPiece = tmpPieceArray[pieceIdx];

    // ended ones
    if (curPiece.idx == -1) {
      continue;
    }

    int diceNumber = dice[idx];

    int nextBoardIdx = curPiece.idx + diceNumber;

    int curBoard = board[curPiece.route][curPiece.idx];

    int arrayLen = boardLen[curPiece.route];

    if (nextBoardIdx >= boardLen[curPiece.route]) {
      // over limit
      if (curPiece.route == 4 || curPiece.route == 0) {
        // over board
        route[curPiece.route][curPiece.idx] = 0;
        tmpPieceArray[pieceIdx].idx = - 1;
        solve(idx+1, tmpPieceArray, score);
        tmpPieceArray[pieceIdx].idx = curPiece.idx;
        route[curPiece.route][curPiece.idx] = 1;
      } else {
        int nextPieceRoute = 4;
        int nextPieceIdx = nextBoardIdx - arrayLen;

        int lastWayLen = boardLen[4];

        if (nextPieceIdx >= lastWayLen) {
          route[curPiece.route][curPiece.idx] = 0;
          tmpPieceArray[pieceIdx].idx = - 1;
          solve(idx+1, tmpPieceArray, score);
          tmpPieceArray[pieceIdx].idx = curPiece.idx;
          route[curPiece.route][curPiece.idx] = 1;
        } else if (!route[nextPieceRoute][nextPieceIdx]) {
          int plusScore = board[nextPieceRoute][nextPieceIdx];

          if (!(plusScore == 40 && forty == true)) {
            route[curPiece.route][curPiece.idx] = 0;
            tmpPieceArray[pieceIdx].idx = nextPieceIdx;
            tmpPieceArray[pieceIdx].route = nextPieceRoute;
            route[nextPieceRoute][nextPieceIdx] = 1;
            if (plusScore == 40) forty = true;
            solve(idx+1, tmpPieceArray, score + plusScore);
            if (plusScore == 40) forty = false;
            route[nextPieceRoute][nextPieceIdx] = 0;
            tmpPieceArray[pieceIdx].idx = curPiece.idx;
            tmpPieceArray[pieceIdx].route = curPiece.route;
            route[curPiece.route][curPiece.idx] = 1;
          }
        }
      }
    } else if (curPiece.route == 0) {
      // ROUTE 0
      int nextPieceIdx = curPiece.idx + dice[idx];
      int nextBoard = board[0][nextPieceIdx];

      if (isCrossWay(nextBoard)) {
        int nextPieceRoute = getHash(nextBoard);
        if (!route[nextPieceRoute][0]) {
          route[curPiece.route][curPiece.idx] = 0;
          route[nextPieceRoute][0] = 1;
          tmpPieceArray[pieceIdx].idx = 0;
          tmpPieceArray[pieceIdx].route = nextPieceRoute;
          int plusScore = board[nextPieceRoute][0];
          solve(idx+1, tmpPieceArray, score + plusScore);
          route[curPiece.route][curPiece.idx] = 1;
          route[nextPieceRoute][0] = 0;
          tmpPieceArray[pieceIdx].idx = curPiece.idx;
          tmpPieceArray[pieceIdx].route = curPiece.route;
        }
      } else {
        int plusScore = board[0][nextPieceIdx];

        if (!(plusScore == 40 && forty == true)) {
          if (!route[0][nextPieceIdx]) {
            route[curPiece.route][curPiece.idx] = 0;
            route[0][nextPieceIdx] = 1;
            tmpPieceArray[pieceIdx].idx = nextBoardIdx;
            if (plusScore == 40) forty = true;
            solve(idx+1, tmpPieceArray, score + plusScore);
            if (plusScore == 40) forty = false;
            route[curPiece.route][curPiece.idx] = 1;
            route[0][nextPieceIdx] = 0;
            tmpPieceArray[pieceIdx].idx = curPiece.idx;
          }
        }
      }
    } else {
      // Other routes
      int nextPieceIdx = curPiece.idx + dice[idx];
      int plusScore = board[curPiece.route][nextPieceIdx];

      if (!(plusScore == 40 && forty == true)) {
        if (!route[curPiece.route][nextPieceIdx]) {
          route[curPiece.route][curPiece.idx] = 0;
          route[curPiece.route][nextPieceIdx] = 1;
          tmpPieceArray[pieceIdx].idx = nextBoardIdx;
          if (plusScore == 40) forty = true;
          solve(idx+1, tmpPieceArray, score + plusScore);
          if (plusScore == 40) forty = false;
          route[curPiece.route][curPiece.idx] = 1;
          route[curPiece.route][nextPieceIdx] = 0;
          tmpPieceArray[pieceIdx].idx = curPiece.idx;
        }
      }
    }
  }
}

int run() {
  for (int i = 0; i < TURN; i++) cin >> dice[i];

  PIECE tmpArray[4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};

  solve(0, tmpArray, 0);

  cout << ans << '\n';

  return 0;
}